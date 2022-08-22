#include "returnloginerror.h"
#include "enum_Var.h"

#include <QMainWindow>

returnLoginError::returnLoginError()
{

}

QString returnLoginError::errorMessage(int clientAction)
{
    QString str;

    str = QString("LCS|%1|%2").arg(serverAction::ERROR).arg(clientAction);

    return str;
}
