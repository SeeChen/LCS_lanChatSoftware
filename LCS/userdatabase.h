#ifndef USERDATABASE_H
#define USERDATABASE_H

#include <QSqlDatabase>

class userDataBase
{
public:
    userDataBase();
    QSqlDatabase db;
    int connectDataBase();
    void createDataBase();

private:

};

#endif // USERDATABASE_H
