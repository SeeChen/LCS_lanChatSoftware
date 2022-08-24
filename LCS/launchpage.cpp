#include "launchpage.h"
#include "ui_launchpage.h"

#include "enum_Var.h"

#include <QRegExpValidator>

#include <QSqlError>

LaunchPage::LaunchPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LaunchPage)
{
    ui->setupUi(this);

    ui->ipAddress->setPlaceholderText("Please Input Server IP Address");                    // 设置提示
    ui->ipAddress->setValidator(new QRegExpValidator(QRegExp("[0-9.]*"), ui->ipAddress));   // 设置输入限制

    clientSocket = new QTcpSocket(this);

    connect(clientSocket, &QTcpSocket::connected,
            [=]()
    {
        this->hide();
        loginPage.show();
    });

    connect(clientSocket, &QTcpSocket::readyRead,
            [=]()
    {
        QByteArray array = clientSocket->readAll();
        QString tempStr = QString(array);

        QStringList dataList = tempStr.split("|");

        qDebug() << tempStr;

        bool    vertifyLCS     = (dataList.at(0) == "LCS");
        int     serverResponse = dataList.at(1).toInt();
        QString serverMsg      = dataList.at(2);

        if(!vertifyLCS) {
            return;
        }

        switch(serverResponse) {
            case serverAction::ERROR:
                responseError(serverMsg);
                break;
            case serverAction::MESSAGE:
                responseMessage(serverMsg);
                break;
            case serverAction::VERIFIED:
                responseVertify(serverMsg);
                break;
            case serverAction::ONLINEUSER:
                emit responseOnlineList(serverMsg, UID);
                break;
        }
    });

    // 与 Login 界面进行通信
    connect(&loginPage, &logIn::requestLogin      , this      , &LaunchPage::requestLogin);
    connect(this      , &LaunchPage::responseLogin, &loginPage, &logIn::responseLogin);

    // 打开注册页面
    connect(&loginPage, &logIn::registerOpen, this, &LaunchPage::registerOpen);

    // 与注册页面进行通信
    connect(&registerPage, &Register::requestRegister   , this         , &LaunchPage::requestRegister);
    connect(&registerPage, &Register::registerClose     , this         , &LaunchPage::registerClose);
    connect(this         , &LaunchPage::responseReigster, &registerPage, &Register::responseRegister);

    // 与在线列表进行通信
    connect(this     , &LaunchPage::responseOnlineList, &mainPage, &MainWindow::responseOnlineList);
    connect(&mainPage, &MainWindow::requestChat       , this     , &LaunchPage::requestChat);
    connect(&mainPage, &MainWindow::sendUiLink        , this     , &LaunchPage::sendUiLink);

    // 与对话窗口进行通信
    connect(this     , &LaunchPage::responseChat   , &chatPage, &chatWindow::responseChat   );
    connect(&chatPage, &chatWindow::requsetSendText, this     , &LaunchPage::requestSendText);
    connect(this     , &LaunchPage::incomingMsg    , &chatPage, &chatWindow::incomingMsg    );
    connect(this     , &LaunchPage::historyChat    , &chatPage, &chatWindow::historyChat    );
}

LaunchPage::~LaunchPage()
{
    delete ui;
}

void LaunchPage::responseError(QString data)
{
    int code = data.toUInt();

    switch (code) {
        case todoAction::LOGIN:
            emit responseLogin();
            break;
        case todoAction::REGISTER:
            emit responseReigster();
            break;
    }
}

void LaunchPage::responseVertify(QString data)
{
    QStringList strList = data.split("%%");

    UID   = strList.at(0).toInt();
    UNAME = strList.at(1);

    db.setDatabaseName(QString("../%1.db").arg(UID));
    if (!db.open()){
        qDebug() << db.lastError().text();
    }

    loginPage.close();
    registerPage.close();

    mainPage.show();
    mainPage.setWindowTitle(UNAME);

    QString onlineList = QString("LCS|%1|%2|").arg(UID).arg(todoAction::ONLINELIST);
    clientSocket->write(onlineList.toUtf8());
}

void LaunchPage::responseMessage(QString data)
{
    QStringList dataList = data.split("%%");

    int     msgFrom = dataList.at(0).toUInt();
    QString msg     = dataList.at(1);
    int     msgType = dataList.at(2).toUInt();

    dbQuery.exec(QString("CREATE TABLE %1 (sender varchar(255), message varchar(255) );").arg(QString("User%1").arg(msgFrom)));
    dbQuery.exec(QString("INSERT INTO %1 VALUES('opposite', '%2');").arg(QString("User%1").arg(msgFrom)).arg(msg));

    dbQuery.exec(QString("SELECT * FROM User%1;").arg(msgFrom));

    while(dbQuery.next()) {
        qDebug() << dbQuery.value(0).toString() << " : " << dbQuery.value(1).toString();
    }

    switch(msgType) {
        case messageType::TEXT:
            emit incomingMsg(msgFrom, msg);
            break;
    }
}

void LaunchPage::requestLogin(QString UsrName, QString UsrPwrd)
{
    QString loginMsg = QString("LCS|%1|%2|%3%%%4").arg(0).arg(todoAction::LOGIN).arg(UsrName).arg(UsrPwrd);

    clientSocket->write(loginMsg.toUtf8());
}

void LaunchPage::requestRegister(QString username, QString password)
{
    QString registerMsg = QString("LCS|%1|%2|%3%%%4").arg(0).arg(todoAction::REGISTER).arg(username).arg(password);
    clientSocket->write(registerMsg.toUtf8());
}

void LaunchPage::registerOpen()
{
    loginPage.close();
    registerPage.show();
}

void LaunchPage::registerClose()
{
    registerPage.close();
    loginPage.show();
}

void LaunchPage::requestChat(int toID, QString toUsr)
{
    chatPage.show();
    chatPage.setWindowTitle(toUsr);

    emit responseChat(toID, toUsr);

    // 发送历史消息
    dbQuery.exec(QString("SELECT * FROM User%1").arg(toID));
    while(dbQuery.next()) {
        emit historyChat(dbQuery.value(0).toString(), dbQuery.value(1).toString());
    }
}

void LaunchPage::sendUiLink(QString str)
{
    chatPage.loadThemeFile(str);
}

void LaunchPage::requestSendText(int targetID, QString msg, int type)
{
    if(targetID != UID){
        dbQuery.exec(QString("CREATE TABLE %1 (sender varchar(255), message varchar(255) );").arg(QString("User%1").arg(targetID)));
        dbQuery.exec(QString("INSERT INTO %1 VALUES('ME', '%2');").arg(QString("User%1").arg(targetID)).arg(msg));

        dbQuery.exec(QString("SELECT * FROM User%1;").arg(targetID));
    }

    while(dbQuery.next()) {
        qDebug() << dbQuery.value(0).toString() << " : " << dbQuery.value(1).toString();
    }

    QString str = QString("LCS|%1|%2|%3").arg(UID).arg(todoAction::SENDMESSAGE).arg( QString("%1%%%2%%%3").arg(targetID).arg(msg).arg(type) );

    clientSocket->write(str.toUtf8());
}

// Connect 点击事件
void LaunchPage::on_btn_Connect_clicked()
{
    QString serverIP = ui->ipAddress->text();
    clientSocket->connectToHost(QHostAddress(serverIP), 6666);
}
