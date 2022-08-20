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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chatWindow
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *labelUser;
    QPushButton *pushButtonChangeBg;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QLabel *labelChatting;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButtonFile;
    QPushButton *pushButtonPic;
    QPushButton *pushButtonEmoji;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButtonSend;
    QLineEdit *lineEdit;

    void setupUi(QWidget *chatWindow)
    {
        if (chatWindow->objectName().isEmpty())
            chatWindow->setObjectName(QString::fromUtf8("chatWindow"));
        chatWindow->resize(800, 800);
        verticalLayout_3 = new QVBoxLayout(chatWindow);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        labelUser = new QLabel(chatWindow);
        labelUser->setObjectName(QString::fromUtf8("labelUser"));

        horizontalLayout->addWidget(labelUser);

        pushButtonChangeBg = new QPushButton(chatWindow);
        pushButtonChangeBg->setObjectName(QString::fromUtf8("pushButtonChangeBg"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonChangeBg->sizePolicy().hasHeightForWidth());
        pushButtonChangeBg->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButtonChangeBg);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        scrollArea = new QScrollArea(chatWindow);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1222, 1222));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelChatting = new QLabel(scrollAreaWidgetContents);
        labelChatting->setObjectName(QString::fromUtf8("labelChatting"));
        labelChatting->setMinimumSize(QSize(0, 1200));
        labelChatting->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout->addWidget(labelChatting);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_2->addWidget(scrollArea);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButtonFile = new QPushButton(chatWindow);
        pushButtonFile->setObjectName(QString::fromUtf8("pushButtonFile"));

        horizontalLayout_3->addWidget(pushButtonFile);

        pushButtonPic = new QPushButton(chatWindow);
        pushButtonPic->setObjectName(QString::fromUtf8("pushButtonPic"));

        horizontalLayout_3->addWidget(pushButtonPic);

        pushButtonEmoji = new QPushButton(chatWindow);
        pushButtonEmoji->setObjectName(QString::fromUtf8("pushButtonEmoji"));

        horizontalLayout_3->addWidget(pushButtonEmoji);

        horizontalSpacer_5 = new QSpacerItem(318, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        pushButtonSend = new QPushButton(chatWindow);
        pushButtonSend->setObjectName(QString::fromUtf8("pushButtonSend"));

        horizontalLayout_3->addWidget(pushButtonSend);


        verticalLayout_2->addLayout(horizontalLayout_3);

        lineEdit = new QLineEdit(chatWindow);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout_2->addWidget(lineEdit);


        verticalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(chatWindow);

        QMetaObject::connectSlotsByName(chatWindow);
    } // setupUi

    void retranslateUi(QWidget *chatWindow)
    {
        chatWindow->setWindowTitle(QApplication::translate("chatWindow", "Form", nullptr));
        labelUser->setText(QApplication::translate("chatWindow", "User", nullptr));
        pushButtonChangeBg->setText(QApplication::translate("chatWindow", "Change Background", nullptr));
        labelChatting->setText(QApplication::translate("chatWindow", "TextLabel", nullptr));
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
