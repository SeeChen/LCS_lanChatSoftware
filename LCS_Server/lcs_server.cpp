#include "lcs_server.h"
#include "Function/ipv4.h"
#include "Function/returnloginerror.h"
#include "ui_lcs_server.h"

#include "enum_Var.h"

#include <QTcpServer>
#include <QTcpSocket>

#include <QHostAddress>

#include <QHash>

#include <QFile>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

LCS_Server::LCS_Server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LCS_Server)
{
    ui->setupUi(this);

    IPv4 *ipv4 = new IPv4();

    this->setWindowTitle(ipv4->DeviceIP);

    bool dbExists = QFile::exists("../userList.db");
    db.setDatabaseName("../userList.db");
    if (!db.open()){
        qDebug() << db.lastError().text();
    }
    if(dbExists == false) {
        dbQuery.exec("CREATE TABLE UserList (UID INT UNIQUE, Password varchar(255), nickName varchar(255));");
        dbQuery.exec("INSERT INTO UserList VALUES (1, 'dsdfsdfs', 'fdsafsf');");
    }

    dbQuery.exec("SELECT * FROM UserList");
    while (dbQuery.next()) {
        qDebug() << dbQuery.value(0).toInt() << dbQuery.value(1).toString() << dbQuery.value(2).toString();
    }

    ui->label_IP->setText(": " + ipv4->DeviceIP);
    ui->label_Port->setText(": 6666");

    lcsServer.listen(QHostAddress::AnyIPv4, 6666);

    connect(&lcsServer, &QTcpServer::newConnection, this, &LCS_Server::on_LCSServer_newConnection);
}

LCS_Server::~LCS_Server()
{
    delete ui;
}

bool LCS_Server::userLogin(QString data)
{
    /* 格式
     * 0 : UID
     * 1 : 已加密的密码
    */
    QStringList dataList = data.split("%%");

    QString       UID = dataList.at(0).toUtf8();
    QString UPassword = dataList.at(0).toUtf8();

}

int LCS_Server::userRegister(QString data)
{
    /* 格式
     * 0 昵称
     * 1 UID
     * 2 已加密的密码
    */

    QStringList dataList = data.split("%%");

    QString    nickName = dataList.at(0).toUtf8();
    int             UID = dataList.at(1).toInt();
    QString md5Password = dataList.at(2).toUtf8();

    dbQuery.exec(QString("SELECT * FROM UserList WHERE nickName='%1';").arg(nickName));

    if(dbQuery.next()) {
        qDebug() << dbQuery.value(0).toString();
        return 0;
    }

    dbQuery.exec(QString("INSERT INTO UserList VALUES(%1, '%2', '%3')").arg(UID).arg(md5Password).arg(nickName));

    return UID;
}

void LCS_Server::sendMessage(QString data)
{
    /* 格式
     * 0 : Target ID
     * 1 : Message
     * 2 : Message Type
    */
    QStringList dataList = data.split("%%");

    int    targetID = dataList.at(0).toInt();
    QString message = dataList.at(1).toUtf8();
    int        type = dataList.at(2).toUInt();

    socketHash.find(targetID).value()->write(message.toUtf8());
}

void LCS_Server::on_LCSServer_newConnection()
{
    if (lcsServer.hasPendingConnections()) {
        QTcpSocket *newSocket = lcsServer.nextPendingConnection();
        //socketList.append(newSocket);

        QLabel *label = new QLabel();
        label->setText(newSocket->peerAddress().toString());
        ui->ConnectdDeviceList->addWidget(label);

        connect(newSocket, &QTcpSocket::readyRead,
                [=]()
        {
            QByteArray array = newSocket->readAll();
            QString tempStr = QString(array);

            /* 列表格式
             * 0 : 验证是否为 LCS 客户端发来的消息
             * 1 : 用户 ID , 0 表示没有用户 id
             * 2 : 执行的行为
             * 3 : 信息
             */
            QStringList dataList = tempStr.split("|");

            bool   vertifyLCS = (dataList.at(0) == "LCS");
            int           UID = dataList.at(1).toInt();
            int  ClientAction = dataList.at(2).toInt();
            QString ClientMsg = dataList.at(3);

            // 防止其它应用连接 验证是否为 LCS 发来的信息
            if(!vertifyLCS) {
                return;
            }

            // 0 表示登录操作或注册操作
            if(UID == 0) {
                int newUid = 0;
                switch(ClientAction) {
                    case todoAction::LOGIN:
                        break;
                    case todoAction::REGISTER:

                        newUid = userRegister(ClientMsg);
                        break;
                }

                if(newUid == 0) {
                    returnLoginError *err = new returnLoginError();
                    QString errMsg = err->errorMessage(ClientAction);

                    newSocket->write(errMsg.toUtf8());
                    return;
                }

                UID = newUid;
            }

            // 判断 UID 是否第一次连接
            if(!socketHash.contains(UID)) {
                socketHash.insert(UID, newSocket);
            }

            // 判断用户操作
            switch(ClientAction) {
                case todoAction::EDITPROFILE:
                    break;
                case todoAction::SENDMESSAGE:
                    sendMessage(ClientMsg);
                    break;
            }
        });
    }
}
