#include "launchpage.h"

//delete


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /* DON'T add any code here !  Thank You!*/
    /* If you want to see effect, please REMOVE the code you added before upload */
    /* Thank you for your understanding */

    LaunchPage launchPage;

    launchPage.setMaximumSize(400, 100);
    launchPage.setMinimumSize(400, 100);

    launchPage.setWindowTitle("Input Server IP Address");

    launchPage.show();

    //delete code below after adding


    return a.exec();


}
