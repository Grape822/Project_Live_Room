/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *label_name;
    QLabel *label_pwd;
    QLineEdit *lineEdit_name;
    QLineEdit *lineEdit_pwd;
    QPushButton *pushButton_login;
    QPushButton *pushButton_register;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(351, 281);
        label_name = new QLabel(Widget);
        label_name->setObjectName(QString::fromUtf8("label_name"));
        label_name->setGeometry(QRect(10, 20, 101, 51));
        QFont font;
        font.setPointSize(21);
        label_name->setFont(font);
        label_pwd = new QLabel(Widget);
        label_pwd->setObjectName(QString::fromUtf8("label_pwd"));
        label_pwd->setGeometry(QRect(10, 110, 101, 51));
        label_pwd->setFont(font);
        lineEdit_name = new QLineEdit(Widget);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(120, 30, 211, 51));
        lineEdit_name->setFont(font);
        lineEdit_pwd = new QLineEdit(Widget);
        lineEdit_pwd->setObjectName(QString::fromUtf8("lineEdit_pwd"));
        lineEdit_pwd->setGeometry(QRect(120, 120, 211, 51));
        lineEdit_pwd->setFont(font);
        pushButton_login = new QPushButton(Widget);
        pushButton_login->setObjectName(QString::fromUtf8("pushButton_login"));
        pushButton_login->setGeometry(QRect(10, 210, 111, 51));
        pushButton_login->setFont(font);
        pushButton_register = new QPushButton(Widget);
        pushButton_register->setObjectName(QString::fromUtf8("pushButton_register"));
        pushButton_register->setGeometry(QRect(210, 210, 111, 51));
        pushButton_register->setFont(font);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        label_name->setText(QCoreApplication::translate("Widget", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        label_pwd->setText(QCoreApplication::translate("Widget", "\345\257\206  \347\240\201\357\274\232", nullptr));
        pushButton_login->setText(QCoreApplication::translate("Widget", "\347\231\273\345\275\225", nullptr));
        pushButton_register->setText(QCoreApplication::translate("Widget", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
