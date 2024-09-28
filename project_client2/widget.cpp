#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include "pack.h"
#include "userinterface.h"
#include "liveroom.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , m_ptcpsocket(new QTcpSocket(this))
{
    ui->setupUi(this);
    init_network();

    // 点击登录按钮
    connect(ui->pushButton_login, &QPushButton::clicked, this, &Widget::login_clicked);

    // 点击注册按钮
    connect(ui->pushButton_register, &QPushButton::clicked, this, &Widget::register_clicked);

    // 客户端套子套接字收到服务器发来的信息发射信号
    connect(m_ptcpsocket, &QTcpSocket::readyRead, this, &Widget::ready_read);
}

Widget::~Widget()
{
    // 客户端退出，告诉服务器端通信的子套接字
    m_ptcpsocket->close();
    delete ui;
}

// 点击注册按钮
void Widget::register_clicked()
{
    // 取出用户名和密码
    QString strname = ui->lineEdit_name->text();
    QString strpwd = ui->lineEdit_pwd->text();

    // 先做用户名和密码的规则性检测
    // 1.名字不符合约束
    if(strname.length() < 3 || strname.length() > 12)
    {
        QMessageBox::warning(this, "警告", "用户名不符合约束（3-12）");
        return;
    }

    // 2.密码不符合约束
    if(strpwd.length() < 3 || strpwd.length() > 12)
    {
        QMessageBox::warning(this, "警告", "密码不符合约束（3-12）");
        return;
    }

    // 网络上只能传输字符串或者字节类型的数据
    Pack pack;
    pack.set_type(TYPE_REGISTER);
    pack.append(strname);
    pack.append(strpwd);

    // 发送应用层协议包
    m_ptcpsocket->write(pack.data(), pack.size());

}

// 点击登录按钮
void Widget::login_clicked()
{
    // 取出用户名和密码
    QString strname = ui->lineEdit_name->text();
    QString strpwd = ui->lineEdit_pwd->text();

    // 先做用户名和密码的规则性检测
    // 1.名字不符合约束
    if(strname.length() < 3 || strname.length() > 12)
    {
        QMessageBox::warning(this, "警告", "用户名不符合约束（3-12）");
        return;
    }

    // 2.密码不符合约束
    if(strpwd.length() < 3 || strpwd.length() > 12)
    {
        QMessageBox::warning(this, "警告", "密码不符合约束（3-12）");
        return;
    }

    // 网络上只能传输字符串或者字节类型的数据
    Pack pack;
    pack.set_type(TYPE_LOGIN);
    pack.append(strname);
    pack.append(strpwd);

    // 存储用户名
    m_username = strname;
    // 发送应用层协议包
    m_ptcpsocket->write(pack.data(), pack.size());

    return;
}

void Widget::ready_read()
{
    // 用pack包接收客户端发来的应用层协议包，然后开始解析
    while (true)  // 可能有多个应用层协议包发来
    {
        Pack pack;
        int size = 0;

        // 先解析包的长度（四个字节）
        int rst = m_ptcpsocket->read((char*)&size, 4);
        if(0 == rst)
        {
            break;
        }

        // 再解析包的长度后面的的字节（包总长度 - 4)
        m_ptcpsocket->read(pack.data() + 4, size - 4);

        // 根据包的类型开始处理业务逻辑
        switch ((Type)pack.get_type())
        {
        case TYPE_REGISTER:
            user_register_back(pack);
            break;

        case TYPE_LOGIN:
            user_login_back(pack);
            break;

        case TYPE_CREATE_ROOM:
            user_createroom_back(pack);
            break;

        case TYPE_GET_NEW_ROOM:
            user_get_newroom_back(pack);
            break;

        case TYPE_FLUSH_ROOM:
            user_flushroom_back(pack);
            break;

        case TYPE_JOIN_ROOM:
            user_joinroom_back(pack);
            break;

        case TYPE_GET_NEW_USER:
            user_get_newuser_back(pack);
            break;

        case TYPE_FLUSH_OTHER_USERS:
            user_flush_otherusers_back(pack);
            break;

        case TYPE_DELETE_USER:
            user_deleteuser_back(pack);
            break;
        }
    }
}

// 获取服务器端返回的注册结果
void Widget::user_register_back(Pack& pack)
{
    // 获取服务器端返回的注册结果
    Register_State register_rst = (Register_State)pack.get_register_state();

    switch (register_rst)
    {
    case SUCCESS_REGISTER:
        QMessageBox::information(this, "注册", "注册成功");
        break;

    case ERR_NAME_RULE_REGISTER:
        QMessageBox::warning(this, "注册", "名字不符合规范（3-12）");
        break;

    case ERR_PWD_RULE_REGISTER:
        QMessageBox::warning(this, "注册", "密码不符合规范（3-12）");
        break;

    case ERR_PWD_PWD_REGISTER:
        QMessageBox::warning(this, "注册", "两次密码不一致");
        break;

    case ERR_REREGISTER_REGISTER:
        QMessageBox::warning(this, "注册", "重复注册");
        break;

    case ERR_DB_REGISTER:
        QMessageBox::warning(this, "注册", "数据库错误");
        break;
    }
}

// 获取服务器端返回的注册结果
void Widget::user_login_back(Pack& pack)
{
    // 获取服务器端返回的登录结果
    Login_State login_rst = (Login_State)pack.get_login_state();

    switch (login_rst)
    {
    case SUCCESS_LOGIN:
        QMessageBox::information(this, "登录", "登录成功");
        // 登录成功，隐藏登录窗口
        hide();

        // 把用户界面窗口创建出来并传入套接字和用户名
        m_puserinterface = new UserInterface(m_ptcpsocket, m_username);
        m_puserinterface->show();

        break;

    case ERR_NAME_RULE_LOGIN:
        QMessageBox::warning(this, "登录", "名字不符合规范（3-12）");
        break;

    case ERR_PWD_RULE_LOGIN:
        QMessageBox::warning(this, "登录", "密码不符合规范（3-12）");
        break;

    case ERR_NAME_LOGIN:
        QMessageBox::warning(this, "登录", "用户名错误");
        break;

    case ERR_PWD_LOGIN:
        QMessageBox::warning(this, "登录", "密码错误");
        break;

    case ERR_RELOGIN_LOGIN:
        QMessageBox::warning(this, "登录", "重复登录");
        break;

    case ERR_DB_LOGIN:
        QMessageBox::warning(this, "登录", "数据库错误");
        break;
    }
}

// 获取服务器端返回的创建房间号结果
void Widget::user_createroom_back(Pack &pack)
{
    QStringList strlist = pack.get_data();
    pack.clear();

    // 取出服务器返回的房间号
    QString strroom_id = strlist[0];

    // 加入房间号到用户列表中
    m_puserinterface->add_room_id(strroom_id);
    m_puserinterface->hide();

    // 进入直播间
    m_puserlivingroom = new LiveRoom(m_ptcpsocket, m_username, m_username, strroom_id, true);
    m_puserlivingroom->show();

    return;
}

// 其它客户端创建房间被动获取服务器返回的其它创建房间的客户端的房间号
void Widget::user_get_newroom_back(Pack &pack)
{
    QStringList strlist = pack.get_data();
    QString room_id = strlist[0];

    m_puserinterface->add_room_id(room_id);

    return;
}

// 刚登陆成功后主动获取服务器返回的其它创建房间的客户端的房间号
void Widget::user_flushroom_back(Pack &pack)
{
    QStringList strlist = pack.get_data();

    for(auto room_id: strlist)
    {
        m_puserinterface->add_room_id(room_id);
    }

    return;
}

// 收到服务器返回的加入房间的请求
void Widget::user_joinroom_back(Pack& pack)
{
    QStringList strlist = pack.get_data();
    QString strroomowner_name = strlist[0];

    m_puserinterface->hide();

    // 进入房主的直播间
    m_puserlivingroom = new LiveRoom(m_ptcpsocket, strroomowner_name, m_username, m_puserinterface->get_joinroom_id_(), false);
    m_puserlivingroom->show();

    return;
}

// 房主直播间界面里面加入新加入该房间用户的用户名
void Widget::user_get_newuser_back(Pack &pack)
{
    QStringList strlist = pack.get_data();
    QString strnewuser_name = strlist[0];

    m_puserlivingroom->add_newuser(strnewuser_name);

    return;
}

// 收到服务器返回的加入同房间的所有其它客户端（没有房主）的名字的信息
void Widget::user_flush_otherusers_back(Pack &pack)
{
    QStringList strlist = pack.get_data();

    for(auto sameroomusername: strlist)
    {
        m_puserlivingroom->add_newuser(sameroomusername);
    }

    return;
}

// 收到服务器返回的退出直播间的用户的名字的信息
void Widget::user_deleteuser_back(Pack &pack)
{
     QStringList strlist = pack.get_data();
     QString strname = strlist[0];

     m_puserlivingroom->delete_user(strname);

     return;
}

// 客户端启动，先连接服务器
void Widget::init_network()
{
    // 对服务器发起连接（三次握手）
    m_ptcpsocket->connectToHost("127.0.0.1", 11810);

    // 客户端启动连接服务器成功发射 connected 信号
    connect(m_ptcpsocket, &QTcpSocket::connected, this, &Widget::connect_ok);

    // 客户端启动连接服务器失败发射 xxx 信号
    connect(m_ptcpsocket, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error),
            this, &Widget::connect_fail);

    return;
}

// 连接服务器成功
void Widget::connect_ok()
{
    QMessageBox::information(this, "连接", "连接服务器成功");

    return;
}

// 连接服务器失败
void Widget::connect_fail()
{
    QMessageBox::information(this, "连接", "连接服务器失败");

    return;
}

