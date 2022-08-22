#ifndef LCS_SERVER_H
#define LCS_SERVER_H

#include <QMainWindow>

#include <QTcpServer>
#include <QTcpSocket>

#include <QHash>

#include <QSqlDatabase>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui { class LCS_Server; }
QT_END_NAMESPACE

class LCS_Server : public QMainWindow
{
    Q_OBJECT

public:
    LCS_Server(QWidget *parent = nullptr);
    ~LCS_Server();

    QTcpServer lcsServer;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery dbQuery;

    QHash <int, QTcpSocket*> socketHash;    // 保存 UID 与 socket 对象的关系
    QHash <int, QString> onlineHash;

    int     userLogin(QString);
    int     userRegister(QString);
    void    sendMessage(QString, int);
    void    onlineList(int);

public slots:
    void on_LCSServer_newConnection();

private:
    Ui::LCS_Server *ui;
};
#endif // LCS_SERVER_H
