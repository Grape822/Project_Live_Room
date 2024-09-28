/********************************************************************************
** Form generated from reading UI file 'liveroom.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIVEROOM_H
#define UI_LIVEROOM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LiveRoom
{
public:
    QLabel *label_roomid;
    QLabel *label_allusername;
    QListWidget *listWidget_allusername;
    QLabel *label_camera;
    QTextEdit *textEdit_talkinformation;
    QPushButton *pushButton_sendtalk_information;
    QPushButton *pushButton_startliving;
    QPushButton *pushButton_closeliving;

    void setupUi(QWidget *LiveRoom)
    {
        if (LiveRoom->objectName().isEmpty())
            LiveRoom->setObjectName(QString::fromUtf8("LiveRoom"));
        LiveRoom->resize(842, 676);
        label_roomid = new QLabel(LiveRoom);
        label_roomid->setObjectName(QString::fromUtf8("label_roomid"));
        label_roomid->setGeometry(QRect(30, 20, 121, 41));
        QFont font;
        font.setPointSize(21);
        label_roomid->setFont(font);
        label_allusername = new QLabel(LiveRoom);
        label_allusername->setObjectName(QString::fromUtf8("label_allusername"));
        label_allusername->setGeometry(QRect(660, 20, 121, 41));
        label_allusername->setFont(font);
        listWidget_allusername = new QListWidget(LiveRoom);
        listWidget_allusername->setObjectName(QString::fromUtf8("listWidget_allusername"));
        listWidget_allusername->setGeometry(QRect(630, 90, 171, 391));
        listWidget_allusername->setFont(font);
        label_camera = new QLabel(LiveRoom);
        label_camera->setObjectName(QString::fromUtf8("label_camera"));
        label_camera->setGeometry(QRect(40, 90, 521, 381));
        label_camera->setFont(font);
        textEdit_talkinformation = new QTextEdit(LiveRoom);
        textEdit_talkinformation->setObjectName(QString::fromUtf8("textEdit_talkinformation"));
        textEdit_talkinformation->setGeometry(QRect(40, 570, 361, 81));
        textEdit_talkinformation->setFont(font);
        pushButton_sendtalk_information = new QPushButton(LiveRoom);
        pushButton_sendtalk_information->setObjectName(QString::fromUtf8("pushButton_sendtalk_information"));
        pushButton_sendtalk_information->setGeometry(QRect(410, 570, 161, 81));
        pushButton_sendtalk_information->setFont(font);
        pushButton_startliving = new QPushButton(LiveRoom);
        pushButton_startliving->setObjectName(QString::fromUtf8("pushButton_startliving"));
        pushButton_startliving->setGeometry(QRect(630, 510, 171, 71));
        pushButton_startliving->setFont(font);
        pushButton_closeliving = new QPushButton(LiveRoom);
        pushButton_closeliving->setObjectName(QString::fromUtf8("pushButton_closeliving"));
        pushButton_closeliving->setGeometry(QRect(630, 590, 171, 71));
        pushButton_closeliving->setFont(font);

        retranslateUi(LiveRoom);

        QMetaObject::connectSlotsByName(LiveRoom);
    } // setupUi

    void retranslateUi(QWidget *LiveRoom)
    {
        LiveRoom->setWindowTitle(QCoreApplication::translate("LiveRoom", "Form", nullptr));
        label_roomid->setText(QString());
        label_allusername->setText(QCoreApplication::translate("LiveRoom", "\346\211\200\346\234\211\347\224\250\346\210\267", nullptr));
        label_camera->setText(QString());
        pushButton_sendtalk_information->setText(QCoreApplication::translate("LiveRoom", "\345\217\221\351\200\201", nullptr));
        pushButton_startliving->setText(QCoreApplication::translate("LiveRoom", "\345\274\200\345\220\257\347\233\264\346\222\255", nullptr));
        pushButton_closeliving->setText(QCoreApplication::translate("LiveRoom", "\345\205\263\351\227\255\347\233\264\346\222\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LiveRoom: public Ui_LiveRoom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIVEROOM_H
