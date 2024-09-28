#include "userinterface.h"
#include "ui_userinterface.h"
#include "pack.h"
#include <QTcpSocket>
#include <QMessageBox>

UserInterface::UserInterface(QTcpSocket* ptcpsocket, const QString& username, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserInterface),
    m_ptcpsocket(ptcpsocket),
    m_username(username)
{
    ui->setupUi(this);
    init_window();

    // 做一次对服务器的请求，请求服务器把已经创建的房间号返回给我
    Pack pack;
    pack.set_type(TYPE_FLUSH_ROOM);
    ptcpsocket->write(pack.data(), pack.size());

    // 点击创建房间
    connect(ui->pushButton_createroom, &QPushButton::clicked, this, &UserInterface::createroom_clicked);

    // 点击加入房间
    connect(ui->pushButton_joinroom,  &QPushButton::clicked, this, &UserInterface::joinroom_clicked);

    // 点击 listwidget 的某项触发信号
    connect(ui->listWidget_allroom_id, &QListWidget::itemClicked, this, &UserInterface::roomid_clicked);
}

UserInterface::~UserInterface()
{
    delete ui;
}


void UserInterface::init_window()
{
    ui->label_username->setText(m_username);

    return;
}

// 用户列表里面加入房间号
void UserInterface::add_room_id(const QString &roomid)
{
    ui->listWidget_allroom_id->addItem(new QListWidgetItem(roomid));
}

// 返回客户端加入的房间号
const QString &UserInterface::get_joinroom_id_()
{
    return m_joinroom_id;
}

// 点击创建房间
void UserInterface::createroom_clicked()
{
    Pack pack;
    pack.set_type(TYPE_CREATE_ROOM);

    m_ptcpsocket->write(pack.data(), pack.size());

    return;
}

// 点击加入房间
void UserInterface::joinroom_clicked()
{
    if(m_joinroom_id.isEmpty())
    {
       QMessageBox::warning(this, "警告", "请先选中房间号");
       return;
    }

    Pack pack;
    pack.set_type(TYPE_JOIN_ROOM);
    pack.append(m_joinroom_id);

    m_ptcpsocket->write(pack.data(), pack.size());

    return;
}

// 点击了房间号
void UserInterface::roomid_clicked(QListWidgetItem *item)
{
    // 记录该房间号
    m_joinroom_id = item->text();
}
