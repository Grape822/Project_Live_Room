#include "liveroom.h"
#include "ui_liveroom.h"
#include <QMessageBox>
#include <QTcpSocket>

LiveRoom::LiveRoom(QTcpSocket* ptcpsocket, const QString& ownername, const QString& username, const QString& roomid, bool isowner, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LiveRoom),
    m_ptcpsocket(ptcpsocket),
    m_ownername(ownername),
    m_username(username),
    m_roomid(roomid),
    m_isowner(isowner)
{
    ui->setupUi(this);
    init_window();

    // 点击开启直播
    connect(ui->pushButton_startliving, &QPushButton::clicked, this, &LiveRoom::startliving_clicked);

    // 点击关闭直播
    connect(ui->pushButton_closeliving, &QPushButton::clicked, this, &LiveRoom::closeliving_clicked);
}

LiveRoom::~LiveRoom()
{
    delete ui;
}

// 点击开启直播
void LiveRoom::startliving_clicked()
{
    if(!m_isowner)
    {
        QMessageBox::warning(this, "警告", "不是房主无法开启直播");
        return;
    }
}

// 点击关闭直播
void LiveRoom::closeliving_clicked()
{
    if(!m_isowner)
    {
        QMessageBox::warning(this, "警告", "不是房主无法关闭直播");
        return;
    }
}

// 列表中添加新的用户名
void LiveRoom::add_newuser(const QString& newusername)
{
    ui->listWidget_allusername->addItem(new QListWidgetItem(newusername));
}

// 列表中删除退出直播间的用户名
void LiveRoom::delete_user(const QString &newusername)
{

    // 查找匹配项（就一项，因为用户名唯一）
    QList<QListWidgetItem*> items = ui->listWidget_allusername->findItems(newusername, Qt::MatchExactly);

//    if(!items.isEmpty())
//    {
//        // 删除该项
        ui->listWidget_allusername->takeItem(ui->listWidget_allusername->row(items[0]));
        delete items[0];
//    }

    return;
}

// 初始化直播界面
void LiveRoom::init_window()
{
    setWindowTitle(m_username);
    ui->label_roomid->setText(m_roomid);

    // 是房主
    if(m_isowner)
    {
        ui->listWidget_allusername->addItem(new QListWidgetItem(m_username));
        return;
    }

    // 不是房主
    ui->listWidget_allusername->addItem(new QListWidgetItem(m_ownername));
    ui->listWidget_allusername->addItem(new QListWidgetItem(m_username));

    return;
}

// 直播间窗口关闭
void LiveRoom::closeEvent(QCloseEvent *e)
{
    // 关闭套接字
    m_ptcpsocket->close();

}
