/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_logIn
{
public:
    QLabel *labelPic;
    QLineEdit *lineEditUsername;
    QLineEdit *lineEditPassword;
    QLabel *labelRegister;
    QPushButton *pushButtonLogin;

    void setupUi(QWidget *logIn)
    {
        if (logIn->objectName().isEmpty())
            logIn->setObjectName(QString::fromUtf8("logIn"));
        logIn->resize(600, 600);
        labelPic = new QLabel(logIn);
        labelPic->setObjectName(QString::fromUtf8("labelPic"));
        labelPic->setGeometry(QRect(100, 0, 350, 350));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelPic->sizePolicy().hasHeightForWidth());
        labelPic->setSizePolicy(sizePolicy);
        labelPic->setScaledContents(true);
        lineEditUsername = new QLineEdit(logIn);
        lineEditUsername->setObjectName(QString::fromUtf8("lineEditUsername"));
        lineEditUsername->setGeometry(QRect(150, 360, 300, 40));
        lineEditUsername->setInputMethodHints(Qt::ImhNone);
        lineEditPassword = new QLineEdit(logIn);
        lineEditPassword->setObjectName(QString::fromUtf8("lineEditPassword"));
        lineEditPassword->setGeometry(QRect(150, 410, 300, 40));
        labelRegister = new QLabel(logIn);
        labelRegister->setObjectName(QString::fromUtf8("labelRegister"));
        labelRegister->setGeometry(QRect(390, 460, 61, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("SimSun-ExtB"));
        font.setPointSize(7);
        labelRegister->setFont(font);
        pushButtonLogin = new QPushButton(logIn);
        pushButtonLogin->setObjectName(QString::fromUtf8("pushButtonLogin"));
        pushButtonLogin->setGeometry(QRect(150, 500, 300, 30));

        retranslateUi(logIn);

        QMetaObject::connectSlotsByName(logIn);
    } // setupUi

    void retranslateUi(QWidget *logIn)
    {
        logIn->setWindowTitle(QApplication::translate("logIn", "Form", nullptr));
        labelPic->setText(QApplication::translate("logIn", "Pic", nullptr));
        labelRegister->setText(QApplication::translate("logIn", "\347\253\213\345\215\263\346\263\250\345\206\214", nullptr));
        pushButtonLogin->setText(QApplication::translate("logIn", "\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class logIn: public Ui_logIn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
