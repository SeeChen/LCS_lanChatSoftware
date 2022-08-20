#include "mainwindow.h"
#include "login.h"
#include "chatwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //logIn w2;
    //w2.show();

    //chatWindow w3;
    //w3.show();

    return a.exec();
}
