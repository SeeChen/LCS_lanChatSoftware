#include "Function/ipv4.h"
#include "Function/ENUM_VAR.h"

#include "server.h"
#include "ui_server.h"

// 网络相关
#include <QTcpServer>
#include <QTcpSocket>

#include <QHostAddress>

// 数据库相关
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

// tableview 相关
#include <QStandardItemModel>

// 时间相关
#include <QDateTime>

// Other
#include <QHash>
#include <QFile>
#include <QDebug>

Server::Server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);

    // 获取本机 IP 地址
    IPv4    *ipv4    = new IPv4();
    QString DeviceIP = ipv4->DeviceIP;

    this->setWindowTitle(DeviceIP);

    bool dbExists = QFile::exists("../userList.db");
    db.setDatabaseName("../userList.db");
    db.open();
    QSqlQuery dbQuery(db);
    if(!dbExists) {
        dbQuery.exec("CREATE TABLE UserList (UID INT UNIQUE, Password varchar(255), Username varchar(255), ProfilePicture INT);");
    }

    dbQuery.exec("SELECT * FROM UserList");
    while (dbQuery.next()) {

        userHash.insert(dbQuery.value(0).toInt(), dbQuery.value(2).toString());
        offlineHash.insert(dbQuery.value(0).toInt(), dbQuery.value(2).toString());

        qDebug() << dbQuery.value(0).toInt() << dbQuery.value(1).toString() << dbQuery.value(2).toString() << dbQuery.value(3).toInt();
    }

    // 显示 IP 和端口
    ui -> label_IP   -> setText(DeviceIP);
    ui -> label_PORT -> setText("6666");

    ui -> label_IP   -> setStyleSheet("border: 5px solid rgba(0, 0, 0, 0.5);");
    ui -> label_PORT -> setStyleSheet("border: 5px solid rgba(0, 0, 0, 0.5);");

    // 显示 tableview
    standModel = new QStandardItemModel;
    standModel->setColumnCount(2);

    ui->tableView->setModel(standModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    standModel->setHeaderData(0, Qt::Horizontal, QString("IP Address"));
    standModel->setHeaderData(1, Qt::Horizontal, QString("Status"  ));

    // 监听连接状态
    server.listen(QHostAddress::AnyIPv4, 6666);
    connect(&server, &QTcpServer::newConnection, this, &Server::serverNewConnection);

    addNewTable(DeviceIP, "Connected");
}

Server::~Server()
{
    delete ui;
}

int Server::requestLogin(QString data)
{
        /* 格式
         * 0 : Username
         * 1 : Password
         */
        QStringList dataList = data.split("%%");

        QString username = dataList.at(0).toUtf8();
        QString password = dataList.at(1).toUtf8();

        QSqlQuery dbQuery(db);

        dbQuery.exec(QString("SELECT * FROM UserList WHERE Username='%1';").arg(username));

        if(dbQuery.next()) {
            QString Password = dbQuery.value(1).toString();

            if(password != Password) {

                return -2;
            }

            return dbQuery.value(0).toUInt();
        } else {

            return -2;
        }
}

int Server::requestRegister(QString data)
{
    /*  格式
     *  0 : UserName
     *  1 : Password
     */

    QStringList dataList = data.split("%%");

    QString username = dataList.at(0);
    QString password = dataList.at(1);

    QSqlQuery dbQuery(db);

    dbQuery.exec(QString("SELECT * FROM UserList WHERE Username='%1';").arg(username));
    if (dbQuery.next()) return -1;

    dbQuery.exec("SELECT count(*) FROM UserList");
    dbQuery.next();
    int count = dbQuery.value(0).toUInt();
    int UID = count + 1;

    dbQuery.exec(QString("INSERT INTO UserList VALUES(%1, '%2', '%3', 0)").arg(UID).arg(password).arg(username));

       userHash.insert(UID, username);
    offlineHash.insert(UID, username);

    return UID;
}

void Server::requestSendMessage(QString data, int senderID)
{
    /*  格式
     *  0 : Target ID
     *  1 : Message
     *  2 : Message Type
     */

    QStringList dataList = data.split("%%");

    int     targetID = dataList.at(0).toInt() ;
    QString  Message = dataList.at(1).toUtf8();
    int      msgType = dataList.at(2).toUInt();

    QString currentTime = (QDateTime::currentDateTime()).toString("yyyy.MM.dd hh:mm");

    QString senderName = QString("ME (%1)").arg(userHash.find(senderID).value());
    QString targetName = QString(    "%1" ).arg(userHash.find(targetID).value());

    QSqlQuery senderQuery(senderDB);
    QSqlQuery targetQuery(targetDB);

    if (senderID != targetID) {
        senderDB.setDatabaseName(QString("../%1.db").arg(senderID));
        targetDB.setDatabaseName(QString("../%1.db").arg(targetID));

        senderDB.open();
        targetDB.open();

        senderQuery.exec(QString("CREATE TABLE User%1 (MsgFrom varchar(255), Message varchar(255), Time varchar(255), Type varchar(255))").arg(targetID));
        targetQuery.exec(QString("CREATE TABLE User%1 (MsgFrom varchar(255), Message varchar(255), Time varchar(255), Type varchar(255))").arg(senderID));

        senderQuery.exec(QString("INSERT INTO User%1 VALUES ('%2', '%3', '%4', '%5')").arg(targetID).arg(senderName).arg(Message).arg(currentTime).arg(msgType));
        targetQuery.exec(QString("INSERT INTO User%1 VALUES ('%2', '%3', '%4', '%5')").arg(senderID).arg(targetName).arg(Message).arg(currentTime).arg(msgType));

    } else {
        senderDB.setDatabaseName(QString("../%1.db").arg(senderID));

        senderDB.open();

        senderQuery.exec(QString("CREATE TABLE User%1 (MsgFrom varchar(255), Message varchar(255), Time varchar(255), Type varchar(255))").arg(targetID));

        senderQuery.exec(QString("INSERT INTO User%1 VALUES ('%2', '%3', '%4', '%5')").arg(targetID).arg(senderName).arg(Message).arg(currentTime).arg(msgType));
    }

    QString msg = QString("LSeCrvSer|%1|%2").arg(ServerAction::MESSAGE).arg("%1%%%2%%%3").arg(senderID).arg(Message).arg(currentTime);

    if (targetID != senderID) {
        socketHash.find(senderID).value()->write(msg.toUtf8());
    }

    if (!onlineHash.contains(targetID)) {
        return;
    }
    socketHash.find(targetID).value()->write(msg.toUtf8());
}

void Server::requestAllUser(int id)
{
    QString returnValue = "";

    QHashIterator<int, QString> iter(onlineHash);
    while(iter.hasNext()) {
        iter.next();
        returnValue = returnValue + QString("%1:%2:%3%%").arg(iter.key()).arg(iter.value()).arg("Online");
    }

    QHashIterator<int, QString> _iter(offlineHash);
    while(_iter.hasNext()) {
        _iter.next();
        returnValue = returnValue + QString("%1:%2:%3%%").arg(_iter.key()).arg(_iter.value()).arg("Offline");
    }

    socketHash.find(id).value()->write(QString("LSeCrvSer|%1|%2").arg(ServerAction::ALL).arg(returnValue).toUtf8());
}

void Server::addNewTable(QString ipAddr, QString status)
{
    static int currentIndex = 0;

    standModel->setItem(currentIndex, 0, new QStandardItem(ipAddr));
    standModel->setItem(currentIndex, 1, new QStandardItem(status));

    standModel->item(currentIndex, 0)->setTextAlignment(Qt::AlignCenter);
    standModel->item(currentIndex, 1)->setTextAlignment(Qt::AlignCenter);

    currentIndex++;
}

void Server::serverNewConnection()
{
    if(server.hasPendingConnections()) {
        QTcpSocket *newSocket = server.nextPendingConnection();

        addNewTable(newSocket->peerAddress().toString(), "Connected");

        // ReadyRead
        connect(newSocket, &QTcpSocket::readyRead,
                [=]()
        {
            QString tempStr = QString(newSocket->readAll());
            qDebug() << tempStr;

            /*  列表格式
             *  0 : 用于验证是否为 LCS 客户端发来的消息
             *  1 : 用户 ID , 0 表示非用户请求操作
             *  2 : 客户端请求执行的行为
             *  3 : 信息
            */
            QStringList dataList = tempStr.split("|");

            bool      vertifyLCS = (dataList.at(0) == "LClCieSnt");
            int              UID = dataList.at(1).toInt();
            int     ClientAction = dataList.at(2).toInt();
            QString    ClientMsg = dataList.at(3);

            if(!vertifyLCS) {
                // 验证失败 不执行任何操作
                return;
            }

            if(UID == 0) {
                // 定义一个 UID 用于判断操作是否成功
                int tempUID = 0;

                switch (ClientAction) {
                    case ClientAction::REGISTER:

                        addNewTable(newSocket->peerAddress().toString(), "Request Register");

                        tempUID = requestRegister(ClientMsg);
                        break;
                    case ClientAction::LOGIN:

                        addNewTable(newSocket->peerAddress().toString(), "Request Login");

                        tempUID = requestLogin(ClientMsg);
                        break;
                }

                if (tempUID < 0) {
                    switch (tempUID) {
                        case -1:

                            addNewTable(newSocket->peerAddress().toString(), "Register Failed");
                            break;
                        case -2:

                            addNewTable(newSocket->peerAddress().toString(), "Login Failed");
                            break;
                    }

                    newSocket->write(QString("LSeCrvSer|%1|%2").arg(ServerAction::ERROR).arg(ClientAction).toUtf8());

                    return;
                }

                addNewTable(newSocket->peerAddress().toString(), QString("%1 Successful").arg(ClientAction==ClientAction::LOGIN?"Login":"Register"));
                UID = tempUID;

                QString username_ = ClientMsg.split("%%").at(0);
                newSocket->write(QString("LSeCrvSer|%1|%2").arg(ServerAction::SUCCESSFUL).arg(QString("%1%%%2").arg(UID).arg(username_)).toUtf8());
            }

            // 判断是否第一次连接
            if (!socketHash.contains(UID)) {
                socketHash.insert(UID, newSocket);                                          // 插入

                QSqlQuery dbQuery(db);

                dbQuery.exec(QString("SELECT * FROM UserList WHERE UID=%1").arg(UID));      // 通过 UID 获取用户名
                dbQuery.next();

                onlineHash.insert(UID, dbQuery.value(2).toString());                        // 插入在线列表

                offlineHash.remove(UID);
            }

            // 判断用户操作
            switch (ClientAction) {
                case ClientAction::SENDMESSAGE:

                    addNewTable(newSocket->peerAddress().toString(), "Send Message");
                    requestSendMessage(ClientMsg, UID);
                    break;
                case ClientAction::ALLUSER:

                    addNewTable(newSocket->peerAddress().toString(), "Request User List");
                    requestAllUser(UID);
                    break;
            }
        });

        // Disconnected
        connect(newSocket, &QTcpSocket::disconnected,
                [=]()
        {
            QHashIterator<int, QTcpSocket*> iter(socketHash);
            while(iter.hasNext()) {
                iter.next();
                if(newSocket == iter.value()) {
                    socketHash.remove(iter.key());
                    onlineHash.remove(iter.key());

                    offlineHash.insert(iter.key(), userHash.find(iter.key()).value());
                }
            }
            addNewTable(newSocket->peerAddress().toString(), "Disconnected");
        });
    }
}

