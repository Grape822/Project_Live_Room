#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>
#include <QTcpSocket>

/*
2.
背景：使用QT实现Tcp协议的服务器和客户端
1. 客户端可以输入用户名和密码打包发送给服务器进行注册，注册的方式是服务器将用户的信息存入数据库，要求用户名不能重复。
2. 在第一题的基础上实现用户登陆的功能。
3. 在第二题的基础上实现相同用户名的用户无法同时登陆。
*/

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , m_ptcpserver(new QTcpServer(this))
    , m_createroom_id(0)
{
    ui->setupUi(this);
    init_db();
    init_network();
}

Widget::~Widget()
{
    delete ui;
}

// 新的客户端连接成功
void Widget::new_connection()
{
    // 取出一个新的和客户端通信的套接字
    QTcpSocket* ptcpsocket = m_ptcpserver->nextPendingConnection();

    // 使用 QTcpSocket 构建出来 MyTcpSocket（也就是让 QTcpSocket 作为 MyTcpSocket 的一个成员）
    MyTcpSocket* pmytcpsocket = new MyTcpSocket(ptcpsocket);

    // 存储和客户端通信的所有子套接字
    m_mytcpsocket_vector.push_back(pmytcpsocket);

    // 服务器子套接字收到客户端发来的信息发射信号
    connect(ptcpsocket, &QTcpSocket::readyRead, this, &Widget::ready_read);

    // 服务器子套接字收到客户端发来的退出信息发射信号
    connect(ptcpsocket, &QTcpSocket::disconnected, this, &Widget::disconnected_socket);

    return;
}

// 处理客户端发来的信息
void Widget::ready_read()
{
    QTcpSocket* ptcpsocket = (QTcpSocket*)sender();

    // 根据 QTcpSocket 找到 MyTcpSocket
    MyTcpSocket* pmytcpsocket = find_mytcpsocket(ptcpsocket);

    // 用pack包接收客户端发来的应用层协议包，然后开始解析
    while (true) // 可能有多个应用层协议包发来
    {
        Pack pack;
        int size = 0;

        // 先解析包的长度（四个字节）
        int rst = pmytcpsocket->read((char*)&size, 4);
        if(0 == rst)
        {
            break;
        }

        // 再解析包的长度后面的的字节（包总长度 - 4)
        pmytcpsocket->read(pack.data() + 4, size - 4);

        // 根据包的类型开始处理业务逻辑
        switch ((Type)pack.get_type())
        {
        case TYPE_REGISTER:
            user_register(pmytcpsocket, pack);
            break;

        case TYPE_LOGIN:
            user_login(pmytcpsocket, pack);
            break;

        case TYPE_CREATE_ROOM:
            user_createroom(pmytcpsocket, pack);
            break;

        case TYPE_FLUSH_ROOM:
            user_flushroom(pmytcpsocket, pack);
            break;

        case TYPE_JOIN_ROOM:
            user_join_room(pmytcpsocket, pack);
            break;
        }
    }
}

// 客户端退出，删除掉和客户端通信的子套接字
void Widget::disconnected_socket()
{
    QString strusername;
    QString strjoinroomid;
    QString strcreateroomid;

    qDebug() << "删除之前" << m_mytcpsocket_vector.size();
    QTcpSocket* ptcpsocket = (QTcpSocket*)sender();

    MyTcpSocket* pmytcpsocket = find_mytcpsocket(ptcpsocket);
    strusername = pmytcpsocket->get_username();
    strjoinroomid = pmytcpsocket->get_joinroom_id();
    strcreateroomid = pmytcpsocket->get_createroom_id();

    m_mytcpsocket_vector.removeOne(pmytcpsocket);
    pmytcpsocket->close();
    delete pmytcpsocket;

    qDebug() << "删除一个套接字，还剩下套接字的个数" << m_mytcpsocket_vector.size();

    // 说明该客户不在直播间里面
    if((strjoinroomid.isEmpty()) && (strcreateroomid.isEmpty()))
    {
        return;
    }

    // 通知其它同房间的客户端把该用户名去掉
    Pack pack;
    pack.set_type(TYPE_DELETE_USER);
    pack.append(strusername);
    for(auto other_ptcpsocket: m_mytcpsocket_vector)
    {
        if(other_ptcpsocket->get_joinroom_id() == strjoinroomid || other_ptcpsocket->get_createroom_id() == strjoinroomid)
        {
           other_ptcpsocket->write(pack.data(), pack.size());
        }
    }

    return;
}

// 根据 QTcpSocket 查找 m_mytcpsocket_vector 里面的 MyTcpSocket
MyTcpSocket *Widget::find_mytcpsocket(QTcpSocket *ptcpsocket)
{
    for(auto pmytcpsocket: m_mytcpsocket_vector)
    {
        if(pmytcpsocket->get_tcpsocket() == ptcpsocket)
        {
            return pmytcpsocket;
        }
    }

    return NULL;
}


// 初始化数据库
void Widget::init_db()
{
    if(!DbHelper::get_instance().init_db())
    {
        QMessageBox::warning(this, "初始化数据库", "连接数据库失败");
        exit(0);
    }

    return;
}

// 初始化套接字（进行监听）
void Widget::init_network()
{
    if(!m_ptcpserver->listen(QHostAddress("127.0.0.1"), 11810))
    {
        QMessageBox::warning(this, "初始化套接字", "套接字监听失败");
    }

    // 新的客户端连接成功
    connect(m_ptcpserver, &QTcpServer::newConnection, this, &Widget::new_connection);

    return;
}

// 处理用户登录结果的反馈
void Widget::user_login(MyTcpSocket* pmytcpsocket, Pack& pack)
{
    // 取出包的内容（用户名和密码）
    QStringList strlist = pack.get_data();

    // 清空数据包，后面会重新构建数据包
    pack.clear();
    // 发给客户端的包设置登录类型
    pack.set_type(TYPE_LOGIN);

    QString strname = strlist[0];
    QString strpwd = strlist[1];

    // 先查看和客户端通信的子套接字是否是登录状态
    if(pmytcpsocket->get_login_state())
    {
        pack.set_lgoin_state(ERR_RELOGIN_LOGIN);
    }

    // 如果客户端不是重复登录
    if(ERR_RELOGIN_LOGIN != pack.get_login_state())
    {
        // 获取登录的结果
        Login_State login_rst = DbHelper::get_instance().user_login(strname, strpwd);
        pack.set_lgoin_state(login_rst);

        // 如果用户登录成功，设置和客户端通信的子套接字的状态为ture
        if(SUCCESS_LOGIN == login_rst)
        {
            // 和客户端通信的子套接字记录客户端套接字的登录状态为true
            pmytcpsocket->set_login_state(true);

            // 把客户端的用户名和子套接字关联起来
            pmytcpsocket->set_username(strname);
        }
    }

    // 把登录的结果返回给客户端
    pmytcpsocket->write(pack.data(), pack.size());

    return;
}

// 处理用户注册结果的反馈
void Widget::user_register(MyTcpSocket*  pmytcpsocket, Pack& pack)
{
    // 取出包的内容（用户名和密码）
    QStringList strlist = pack.get_data();
    QString strname = strlist[0];
    QString strpwd = strlist[1];

    // 获取注册的结果
    Register_State register_rst = DbHelper::get_instance().user_register(strname, strpwd);

    // 清空数据包，重新构建数据包
    pack.clear();
    pack.set_type(TYPE_REGISTER);
    pack.set_register_state(register_rst);

    // 把注册的结果返回给客户端
    pmytcpsocket->write(pack.data(), pack.size());

    return;
}

// 收到用户创建房间的请求
void Widget::user_createroom(MyTcpSocket *ptcpsocket, Pack &pack)
{
    // 和客户端通信的子套接字记录上服务器分配的房间号
    ptcpsocket->set_createroom_id(QString::number(++m_createroom_id));

    pack.clear();
    pack.set_type(TYPE_CREATE_ROOM);
    pack.append(QString::number(m_createroom_id));

    // 把服务器分配的房间号返回给请求创建房间的客户端
    ptcpsocket->write(pack.data(), pack.size());


    // 把服务器分配的房间号返回给所有登录的客户端
    pack.clear();
    pack.set_type(TYPE_GET_NEW_ROOM);
    pack.append(QString::number(m_createroom_id));
    for(auto pother_ptcpsocket: m_mytcpsocket_vector)
    {
        if((pother_ptcpsocket->get_login_state()) && (ptcpsocket != pother_ptcpsocket))
        {
            pother_ptcpsocket->write(pack.data(), pack.size());
        }
    }

    return;
}

// 把所有的客户端创建的房间号返回给刚刚登录成功的客户端
void Widget::user_flushroom(MyTcpSocket *ptcpsocket, Pack &pack)
{
    pack.clear();
    pack.set_type(TYPE_FLUSH_ROOM);

    // 循环把所有创建房间的客户端房间号加入pack
    for(auto pother_ptcpsocket: m_mytcpsocket_vector)
    {
        if(0 != pother_ptcpsocket->get_createroom_id())
        {
            pack.append(pother_ptcpsocket->get_createroom_id());
        }
    }

    ptcpsocket->write(pack.data(), pack.size());

    return;
}

// 收到用户加入房间的请求
void Widget::user_join_room(MyTcpSocket *ptcpsocket, Pack &pack)
{
    QStringList strlist = pack.get_data();

    // 取出客户端要加入的房间号
    QString strjoinroom_id = strlist[0];

    // 存储房主的名字
    QString strownername;

    // 根据客户端要加入的房间号,通知该房间号的房主以及加入该房间的其他客户端
    for(auto other_ptcpsocket: m_mytcpsocket_vector)
    {
        if(other_ptcpsocket->get_createroom_id() == strjoinroom_id || other_ptcpsocket->get_joinroom_id() == strjoinroom_id)
        {
            // 根据客户端要加入的房间号找到该房间号所属房主的用户名
            if(other_ptcpsocket->get_createroom_id() == strjoinroom_id)
            {
                strownername = other_ptcpsocket->get_username();
            }
            // 给房主返回加入者的用户名
            pack.clear();
            pack.set_type(TYPE_GET_NEW_USER);
            pack.append(ptcpsocket->get_username());
            other_ptcpsocket->write(pack.data(), pack.size());
        }
    }

    // 给加入者返回房主的用户名
    pack.clear();
    pack.set_type(TYPE_JOIN_ROOM);
    pack.append(strownername);
    ptcpsocket->write(pack.data(), pack.size());


    // 把同直播间的其它客户端的用户名（不含房主）发给该客户端
    pack.clear();
    pack.set_type(TYPE_FLUSH_OTHER_USERS);
    for(auto other_ptcpsocket: m_mytcpsocket_vector)
    {
        if(other_ptcpsocket->get_joinroom_id() == strjoinroom_id)
        {

            pack.append(other_ptcpsocket->get_username());
        }
    }

    ptcpsocket->write(pack.data(), pack.size());

    // 和客户端通信的子套接字保存下来加入的房间号
    ptcpsocket->set_joinroom_id(strjoinroom_id);

    return;
}

