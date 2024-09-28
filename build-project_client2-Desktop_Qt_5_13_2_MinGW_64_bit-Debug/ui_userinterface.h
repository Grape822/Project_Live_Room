/********************************************************************************
** Form generated from reading UI file 'userinterface.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERINTERFACE_H
#define UI_USERINTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserInterface
{
public:
    QLabel *label_username;
    QListWidget *listWidget_allroom_id;
    QPushButton *pushButton_createroom;
    QPushButton *pushButton_joinroom;

    void setupUi(QWidget *UserInterface)
    {
        if (UserInterface->objectName().isEmpty())
            UserInterface->setObjectName(QString::fromUtf8("UserInterface"));
        UserInterface->resize(212, 645);
        label_username = new QLabel(UserInterface);
        label_username->setObjectName(QString::fromUtf8("label_username"));
        label_username->setGeometry(QRect(60, 20, 111, 41));
        QFont font;
        font.setPointSize(21);
        label_username->setFont(font);
        listWidget_allroom_id = new QListWidget(UserInterface);
        listWidget_allroom_id->setObjectName(QString::fromUtf8("listWidget_allroom_id"));
        listWidget_allroom_id->setGeometry(QRect(20, 80, 171, 421));
        listWidget_allroom_id->setFont(font);
        pushButton_createroom = new QPushButton(UserInterface);
        pushButton_createroom->setObjectName(QString::fromUtf8("pushButton_createroom"));
        pushButton_createroom->setGeometry(QRect(20, 520, 171, 51));
        pushButton_createroom->setFont(font);
        pushButton_joinroom = new QPushButton(UserInterface);
        pushButton_joinroom->setObjectName(QString::fromUtf8("pushButton_joinroom"));
        pushButton_joinroom->setGeometry(QRect(20, 580, 171, 51));
        pushButton_joinroom->setFont(font);

        retranslateUi(UserInterface);

        QMetaObject::connectSlotsByName(UserInterface);
    } // setupUi

    void retranslateUi(QWidget *UserInterface)
    {
        UserInterface->setWindowTitle(QCoreApplication::translate("UserInterface", "Form", nullptr));
        label_username->setText(QString());
        pushButton_createroom->setText(QCoreApplication::translate("UserInterface", "\345\210\233\345\273\272\346\210\277\351\227\264", nullptr));
        pushButton_joinroom->setText(QCoreApplication::translate("UserInterface", "\345\212\240\345\205\245\346\210\277\351\227\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserInterface: public Ui_UserInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERINTERFACE_H
