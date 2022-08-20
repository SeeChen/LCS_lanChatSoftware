/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *lineEditSearch;
    QLabel *labelPic;
    QLabel *labelCreateGroup;
    QLabel *labelAddFriend;
    QListView *listView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(400, 800);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lineEditSearch = new QLineEdit(centralwidget);
        lineEditSearch->setObjectName(QString::fromUtf8("lineEditSearch"));
        lineEditSearch->setGeometry(QRect(10, 20, 300, 40));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEditSearch->sizePolicy().hasHeightForWidth());
        lineEditSearch->setSizePolicy(sizePolicy);
        labelPic = new QLabel(centralwidget);
        labelPic->setObjectName(QString::fromUtf8("labelPic"));
        labelPic->setGeometry(QRect(320, 10, 60, 60));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelPic->sizePolicy().hasHeightForWidth());
        labelPic->setSizePolicy(sizePolicy1);
        labelCreateGroup = new QLabel(centralwidget);
        labelCreateGroup->setObjectName(QString::fromUtf8("labelCreateGroup"));
        labelCreateGroup->setGeometry(QRect(200, 70, 200, 60));
        sizePolicy1.setHeightForWidth(labelCreateGroup->sizePolicy().hasHeightForWidth());
        labelCreateGroup->setSizePolicy(sizePolicy1);
        labelCreateGroup->setScaledContents(true);
        labelAddFriend = new QLabel(centralwidget);
        labelAddFriend->setObjectName(QString::fromUtf8("labelAddFriend"));
        labelAddFriend->setGeometry(QRect(0, 70, 200, 60));
        sizePolicy1.setHeightForWidth(labelAddFriend->sizePolicy().hasHeightForWidth());
        labelAddFriend->setSizePolicy(sizePolicy1);
        labelAddFriend->setScaledContents(true);
        listView = new QListView(centralwidget);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(10, 470, 400, 651));
        MainWindow->setCentralWidget(centralwidget);
        lineEditSearch->raise();
        labelCreateGroup->raise();
        labelAddFriend->raise();
        listView->raise();
        labelPic->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        labelPic->setText(QApplication::translate("MainWindow", "UserPic", nullptr));
        labelCreateGroup->setText(QApplication::translate("MainWindow", "Create Group Button", nullptr));
        labelAddFriend->setText(QApplication::translate("MainWindow", "Add Friend Button", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
