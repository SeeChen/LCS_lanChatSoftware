#include "mainwindow.h"
#include "login.h"
#include "chatwindow.h"
#include "userdatabase.h"
#include "register.h"
#include "server.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    logIn w2;
    w2.show();

    chatWindow w3;
    w3.show();

    //Register w4;
    //w4.show();

    Server w5;
    w5.show();

    return a.exec();
}
