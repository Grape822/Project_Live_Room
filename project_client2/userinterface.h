#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QWidget>

namespace Ui {
class UserInterface;
}

class QTcpSocket;
class QListWidgetItem;
class UserInterface : public QWidget
{
    Q_OBJECT

public:
    explicit UserInterface(QTcpSocket* ptcpsocket, const QString& username, QWidget *parent = nullptr);
    ~UserInterface();

public:
    void init_window();
    void add_room_id(const QString& roomid);
    const QString& get_joinroom_id_();

public slots:
    void createroom_clicked();
    void joinroom_clicked();
    void roomid_clicked(QListWidgetItem *item);

private:
    Ui::UserInterface *ui;
    QTcpSocket* m_ptcpsocket;
    QString m_username;
    QString m_joinroom_id;
};

#endif // USERINTERFACE_H
