#include "userdatabase.h"

userDataBase::userDataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./user.db");
}

int userDataBase::connectDataBase()
{
    db.open();
}

void userDataBase::createDataBase()
{

}
