#include "launcher.h"
#include "ui_launcher.h"

#include "Function/ENUM_VAR.h"

// 正则表达式
#include <QRegExpValidator>

// 网络相关
#include <QTcpSocket>
#include <QHostAddress>

Launcher::Launcher(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Launcher)
{
    ui->setupUi(this);

    // 设置一些样式
    ui->lineEdit_IP->setStyleSheet("background: rgba(255, 255, 255, 0.5); border-radius: 20px;");
    ui->btn_Connect->setStyleSheet("background: rgba(255, 255, 255, 0.8); border-radius: 20px;");

    ui->lineEdit_IP->setValidator(new QRegExpValidator(QRegExp("[0-9.]*"), ui->lineEdit_IP));   // 设置输入规则
    ui->lineEdit_IP->setPlaceholderText("Please Input Server IP address");                      // 设置提示

    client = new QTcpSocket(this);

    // 成功连接函数
    connect(client, &QTcpSocket::connected,
             [=]()
    {
        this->hide();

        loginPage.setMaximumSize(600, 600);
        loginPage.setMinimumSize(600, 600);

        loginPage.setWindowTitle("LOGIN");
        loginPage.show();                    // 连接完成 打开登录页面
    });

    connect(client, &QTcpSocket::readyRead,
            [=]()
    {
        QString tempStr = QString(client->readAll());

        QStringList dataList = tempStr.split("|");

        qDebug() << dataList;

        bool        vertifyLCS = (dataList.at(0) == "LSeCrvSer");
        int     ServerResponse = dataList.at(1).toInt();
        QString      ServerMsg = dataList.at(2);

        if (!vertifyLCS) {
            return;
        }

        switch (ServerResponse) {
            case ServerAction::ERROR:
                if (ServerMsg.toInt() == ClientAction::LOGIN)
                    emit responseErrorLog();
                else
                    emit responseErrorReg();
                break;
            case ServerAction::SUCCESSFUL:
                UID   = ServerMsg.split("%%").at(0).toInt();
                UName = ServerMsg.split("%%").at(1);
                responseSuccessful();
                break;
            case ServerAction::ALL:
                emit responseUserList(ServerMsg);
                break;
            case ServerAction::MESSAGE:
                emit responseMessage(ServerMsg, UID);
                break;
        }
    });

    // 连接登录页
    connect(&loginPage, &logIn::requestLogin       , this      , &Launcher::requestLogin);
    connect(this      , &Launcher::responseErrorLog, &loginPage, &logIn::responseError  );
    connect(&loginPage, &logIn::registerOpen       , this      , &Launcher::registerOpen);

    // 连接注册页
    connect(&registerPage, &Register::registerClose   , this         , &Launcher::registerClose  );
    connect(&registerPage, &Register::requestRegister , this         , &Launcher::requestRegister);
    connect(this         , &Launcher::responseErrorReg, &registerPage, &Register::responseError  );

    // 连接廖倩列表
    connect(this         , &Launcher::responseUserInfo, &chatListPage, &ChatList::responseUserInfo);
    connect(this         , &Launcher::responseUserList, &chatListPage, &ChatList::responseUserList);
    connect(&chatListPage, &ChatList::requestChat      , this        , &Launcher::requestChat);

    connect(this     , &Launcher::responseChat   , &chatPage, &Chat::responseChat          );
    connect(&chatPage, &Chat::requestSendMessage , this     , &Launcher::requestSendMessage);
    connect(this     , &Launcher::responseMessage, &chatPage, &Chat::responseMessage       );
}

Launcher::~Launcher()
{
    delete ui;
}

void Launcher::responseSuccessful()
{
    loginPage.close();
    registerPage.close();

    chatListPage.setMinimumSize(280, 650);
    chatListPage.setMaximumSize(280, 650);

    emit responseUserInfo(UID, UName);
    client->write(QString("LClCieSnt|%1|%2|").arg(UID).arg(ClientAction::ALLUSER).toUtf8());

    chatListPage.show();
}

void Launcher::requestLogin(QString username, QString password)
{
    QString msg = QString("LClCieSnt|0|%1|%2%%%3").arg(ClientAction::LOGIN).arg(username).arg(password);

    client->write(msg.toUtf8());
}

void Launcher::registerOpen()
{
    loginPage.close();
    registerPage.show();
}

void Launcher::requestRegister(QString username, QString password)
{
    QString msg = QString("LClCieSnt|0|%1|%2%%%3").arg(ClientAction::REGISTER).arg(username).arg(password);

    client->write(msg.toUtf8());
}

void Launcher::registerClose()
{
    registerPage.close();
    loginPage.show();
}

void Launcher::requestChat(int UID, QString UName, QString Status)
{
    chatPage.show();

    emit responseChat(UID, UName, Status);
}

void Launcher::requestSendMessage(int targetID, QString msg)
{
    client->write(QString("LClCieSnt|%1|%2|%3").arg(UID).arg(ClientAction::SENDMESSAGE).arg(QString("%1%%%2%%%3").arg(targetID).arg(msg).arg(0)).toUtf8());
}


void Launcher::on_btn_Connect_clicked()
{
    // Connect 按钮点击事件
    QString serverIP = ui->lineEdit_IP->text();              // 获取用户输入的 IP 地址

    client->connectToHost(QHostAddress(serverIP), 6666);    // 尝试进行通信
}
