#ifndef LIVEROOM_H
#define LIVEROOM_H

#include <QWidget>

namespace Ui {
class LiveRoom;
}

class QTcpSocket;
class LiveRoom : public QWidget
{
    Q_OBJECT

public:
    explicit LiveRoom(QTcpSocket* ptcpsocket, const QString& ownername, const QString& username, const QString& roomid, bool isowner, QWidget *parent = nullptr);
    ~LiveRoom();

public slots:
    void startliving_clicked();
    void closeliving_clicked();
    void add_newuser(const QString& newusername);
    void delete_user(const QString& newusername);

public:
    void init_window();

protected:
    virtual void closeEvent(QCloseEvent* e) override;

private:
    Ui::LiveRoom *ui;
    QTcpSocket* m_ptcpsocket;
    QString m_ownername;
    QString m_username;
    QString m_roomid;
    bool m_isowner;
};

#endif // LIVEROOM_H
