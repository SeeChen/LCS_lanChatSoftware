/********************************************************************************
** Form generated from reading UI file 'chatwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWINDOW_H
#define UI_CHATWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chatWindow
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *labelUser;
    QPushButton *pushButtonChangeBg;
    QSpacerItem *horizontalSpacer_2;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *labelChatting;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButtonFile;
    QPushButton *pushButtonPic;
    QPushButton *pushButtonEmoji;
    QPushButton *pushButtonSend;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QTextEdit *textEditChat;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QWidget *chatWindow)
    {
        if (chatWindow->objectName().isEmpty())
            chatWindow->setObjectName(QString::fromUtf8("chatWindow"));
        chatWindow->resize(800, 800);
        layoutWidget = new QWidget(chatWindow);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 801, 51));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        labelUser = new QLabel(layoutWidget);
        labelUser->setObjectName(QString::fromUtf8("labelUser"));

        horizontalLayout->addWidget(labelUser);

        pushButtonChangeBg = new QPushButton(layoutWidget);
        pushButtonChangeBg->setObjectName(QString::fromUtf8("pushButtonChangeBg"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonChangeBg->sizePolicy().hasHeightForWidth());
        pushButtonChangeBg->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButtonChangeBg);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        layoutWidget_2 = new QWidget(chatWindow);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(0, 60, 801, 521));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        labelChatting = new QLabel(layoutWidget_2);
        labelChatting->setObjectName(QString::fromUtf8("labelChatting"));
        labelChatting->setScaledContents(true);

        horizontalLayout_2->addWidget(labelChatting);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        pushButtonFile = new QPushButton(chatWindow);
        pushButtonFile->setObjectName(QString::fromUtf8("pushButtonFile"));
        pushButtonFile->setGeometry(QRect(30, 590, 100, 30));
        pushButtonPic = new QPushButton(chatWindow);
        pushButtonPic->setObjectName(QString::fromUtf8("pushButtonPic"));
        pushButtonPic->setGeometry(QRect(140, 590, 100, 30));
        pushButtonEmoji = new QPushButton(chatWindow);
        pushButtonEmoji->setObjectName(QString::fromUtf8("pushButtonEmoji"));
        pushButtonEmoji->setGeometry(QRect(250, 590, 100, 30));
        pushButtonSend = new QPushButton(chatWindow);
        pushButtonSend->setObjectName(QString::fromUtf8("pushButtonSend"));
        pushButtonSend->setGeometry(QRect(700, 590, 80, 30));
        layoutWidget_3 = new QWidget(chatWindow);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(0, 630, 801, 171));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        textEditChat = new QTextEdit(layoutWidget_3);
        textEditChat->setObjectName(QString::fromUtf8("textEditChat"));

        horizontalLayout_3->addWidget(textEditChat);

        horizontalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        retranslateUi(chatWindow);

        QMetaObject::connectSlotsByName(chatWindow);
    } // setupUi

    void retranslateUi(QWidget *chatWindow)
    {
        chatWindow->setWindowTitle(QApplication::translate("chatWindow", "Form", nullptr));
        labelUser->setText(QApplication::translate("chatWindow", "User", nullptr));
        pushButtonChangeBg->setText(QApplication::translate("chatWindow", "Change Background", nullptr));
        labelChatting->setText(QString());
        pushButtonFile->setText(QApplication::translate("chatWindow", "\346\226\207\344\273\266", nullptr));
        pushButtonPic->setText(QApplication::translate("chatWindow", "\345\233\276\347\211\207/\350\247\206\351\242\221", nullptr));
        pushButtonEmoji->setText(QApplication::translate("chatWindow", "\350\241\250\346\203\205", nullptr));
        pushButtonSend->setText(QApplication::translate("chatWindow", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class chatWindow: public Ui_chatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWINDOW_H
