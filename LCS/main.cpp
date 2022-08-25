#include "launcher.h"

//delete


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Launcher launcherWin;

        launcherWin.setMaximumSize(500, 400);
        launcherWin.setMinimumSize(500, 400);

        launcherWin.setObjectName("serverFrame");
        launcherWin.setStyleSheet("QWidget#serverFrame{border-image:url(:/image/logo.png);}");

        launcherWin.setWindowTitle("LCS Client");

        launcherWin.show();


    return a.exec();


}
