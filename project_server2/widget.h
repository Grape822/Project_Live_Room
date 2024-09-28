#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include "dbhelper.h"
#include <QVector>
#include "mytcpsocket.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void new_connection();
    void ready_read();
    void disconnected_socket();

public:
    MyTcpSocket* find_mytcpsocket(QTcpSocket* ptcpsocket);

public:
    void init_db();
    void init_network();
    void user_login(MyTcpSocket* ptcpsocket, Pack& pack);
    void user_register(MyTcpSocket* ptcpsocket, Pack& pack);
    void user_createroom(MyTcpSocket* ptcpsocket, Pack& pack);
    void user_flushroom(MyTcpSocket* ptcpsocket, Pack& pack);
    void user_join_room(MyTcpSocket* ptcpsocket, Pack& pack);

private:
    Ui::Widget *ui;
    QTcpServer* m_ptcpserver;
    QVector<MyTcpSocket*> m_mytcpsocket_vector;
    unsigned int m_createroom_id;
};
#endif // WIDGET_H
