#include "server.h"

#include <QApplication>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server serverWindow;

    // 设置服务器界面固定大小
    serverWindow.setMinimumSize(800, 600);
    serverWindow.setMaximumSize(800, 600);

    serverWindow.setObjectName("serverFrame");
    serverWindow.setStyleSheet("QWidget#serverFrame{border-image:url(:/background/logo.png);}");

    serverWindow.show();

    return a.exec();
}
