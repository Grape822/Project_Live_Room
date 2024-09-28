#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Pack;
class UserInterface;
class LiveRoom;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void register_clicked();
    void login_clicked();

public slots:
    void ready_read();
    void user_register_back(Pack& pack);
    void user_login_back(Pack& pack);
    void user_createroom_back(Pack& pack);
    void user_get_newroom_back(Pack& pack);
    void user_flushroom_back(Pack& pack);
    void user_joinroom_back(Pack& pack);
    void user_get_newuser_back(Pack& pack);
    void user_flush_otherusers_back(Pack& pack);
    void user_deleteuser_back(Pack& pack);

public:
    void init_network();
    void connect_ok();
    void connect_fail();

private:
    Ui::Widget *ui;
    QTcpSocket* m_ptcpsocket;
    UserInterface* m_puserinterface;
    LiveRoom* m_puserlivingroom;
    QString m_username;
};
#endif // WIDGET_H
