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
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *lineEditSearch;
    QLabel *PicLabel;
    QLabel *labelCreateGroup;
    QLabel *labelAddFriend;
    QListView *listView;
    QMenuBar *menubar;

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
        PicLabel = new QLabel(centralwidget);
        PicLabel->setObjectName(QString::fromUtf8("PicLabel"));
        PicLabel->setGeometry(QRect(340, 10, 50, 50));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(PicLabel->sizePolicy().hasHeightForWidth());
        PicLabel->setSizePolicy(sizePolicy1);
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
        listView->setGeometry(QRect(0, 130, 400, 651));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 400, 21));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        PicLabel->setText(QApplication::translate("MainWindow", "UserPic", nullptr));
        labelCreateGroup->setText(QApplication::translate("MainWindow", "Create Group Button", nullptr));
        labelAddFriend->setText(QApplication::translate("MainWindow", "Add Friend Button", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
