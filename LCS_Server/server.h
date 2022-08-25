#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>

// About Network
#include <QTcpSocket>
#include <QTcpServer>

// About Database
#include <QSqlDatabase>
#include <QSqlQuery>

// tableview 相关
#include <QStandardItemModel>

// Other
#include <QHash>

QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();

private:
    Ui::Server *ui;

// 自定义
public:
    // 网络相关
    QTcpServer server;

    QHash <int, QTcpSocket*> socketHash;    // 用于保存 UID 与 Socket 之间的关系
    QHash <int, QString>     userHash  ;    // 用于保存用户 ID 与 用户名之间的关系
    QHash <int, QString>     onlineHash;    // 用户保存在线用户列表
    QHash <int, QString>    offlineHash;    // 用户保存离线用户列表

    // 数据库相关
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "First");

    QSqlDatabase senderDB = QSqlDatabase::addDatabase("QSQLITE", "Second");
    QSqlDatabase targetDB = QSqlDatabase::addDatabase("QSQLITE", "Third" );

    // tableview 相关
    QStandardItemModel *standModel;

    // 函数相关
    int  requestLogin(QString);             // 客户端请求登录
    int  requestRegister(QString);          // 客户端请求注册
    void requestSendMessage(QString, int);  // 客户端请求发送消息
    void requestAllUser(int);               // 客户端请求所有用户列表

    void addNewTable(QString, QString);    // 用于添加用户连接状态

// 槽函数
public slots:
    void serverNewConnection();             // 当有用户连接时
};
#endif // SERVER_H
