#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QObject>
#include <QTcpSocket>

class MyTcpSocket : QObject
{
    Q_OBJECT
public:
    explicit MyTcpSocket(QTcpSocket* tcpsocket, QObject *parent = nullptr);

public:
    QTcpSocket* get_tcpsocket();
    qint64 read(char* data, qint64 maxlen);
    qint64 write(const char *data, qint64 len);
    void close();

    void set_login_state(bool islogin);
    void set_username(const QString& username);
    void set_createroom_id(const QString& createroomid);
    void set_joinroom_id(const QString& createroomid);

    bool get_login_state();
    const QString& get_createroom_id();
    const QString& get_joinroom_id();
    const QString& get_username();

signals:

public slots:

private:
    QTcpSocket* m_ptcpsocket;
    QString m_username;
    bool m_islogin;
    QString m_createroom_id;
    QString m_joinroom_id;
};

#endif // MYTCPSOCKET_H
