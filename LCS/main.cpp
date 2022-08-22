#include "launchpage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LaunchPage launchPage;

    launchPage.setMaximumSize(400, 100);
    launchPage.setMinimumSize(400, 100);

    launchPage.setWindowTitle("Input Server IP Address");

    launchPage.show();

    return a.exec();
}
