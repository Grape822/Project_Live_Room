#include "mytcpsocket.h"
#include <QTcpSocket>

MyTcpSocket::MyTcpSocket(QTcpSocket* tcpsocket, QObject *parent) : QObject(parent), m_islogin(false), m_createroom_id()
{
    m_ptcpsocket = tcpsocket;
}

// 获取 QTcpSocket 成员
QTcpSocket *MyTcpSocket::get_tcpsocket()
{
    return m_ptcpsocket;
}

// 读取消息
qint64 MyTcpSocket::read(char* data, qint64 maxlen)
{
    return m_ptcpsocket->read(data, maxlen);
}


// 发送消息
qint64 MyTcpSocket::write(const char *data, qint64 len)
{
    return m_ptcpsocket->write(data, len);
}

// 关闭套接字
void MyTcpSocket::close()
{
    m_ptcpsocket->close();
}

// 获取客户端套接字的登录状态
bool MyTcpSocket::get_login_state()
{
    return m_islogin;
}

// 获取客户端创建的房间号
const QString& MyTcpSocket::get_createroom_id()
{
    return m_createroom_id;
}

const QString& MyTcpSocket::get_joinroom_id()
{
    return m_joinroom_id;
}

const QString &MyTcpSocket::get_username()
{
    return m_username;
}

// 设置客户端套接字的登录状态
void MyTcpSocket::set_login_state(bool islogin)
{
    m_islogin = islogin;
}

void MyTcpSocket::set_username(const QString& username)
{
    m_username = username;
}

void MyTcpSocket::set_createroom_id(const QString& createroomid)
{
    m_createroom_id = createroomid;
}

void MyTcpSocket::set_joinroom_id(const QString& joinroomid)
{
    m_joinroom_id = joinroomid;
}


