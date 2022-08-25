#ifndef LAUNCHER_H
#define LAUNCHER_H

#include "login.h"
#include "register.h"
#include "chatlist.h"
#include "chat.h"

#include <QMainWindow>

// 网络相关
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Launcher; }
QT_END_NAMESPACE

class Launcher : public QMainWindow
{
    Q_OBJECT

public:
    Launcher(QWidget *parent = nullptr);
    ~Launcher();

private:
    Ui::Launcher *ui;

// 自定义
public:
    // 网络相关
    QTcpSocket *client;

    // 账号相关
    int       UID = 0;
    QString UName = "";

    // 页面相关
    logIn    loginPage   ;
    Register registerPage;
    ChatList chatListPage;
    Chat     chatPage    ;

// 自定义
public:
    void responseSuccessful();

// 槽函数
public slots:
    // 登录页与注册页相关
    void requestLogin(QString, QString);
    void registerOpen();
    void requestRegister(QString, QString);
    void registerClose();

    // 聊天列表相关
    void requestChat(int, QString, QString);

    void requestSendMessage(int, QString);

    //void requestHis(int);

// 信号
signals:
    // 登录页相关
    void responseErrorLog();
    void responseErrorReg();

    // 聊天列表相关
    void responseUserInfo(int, QString);
    void responseUserList(QString);

    void responseChat(int, QString, QString);
    void responseMessage(QString, int);

    void responseHis(QString, int);


private slots:
    void on_btn_Connect_clicked();      // Connect 按钮点击事件


};
#endif // LAUNCHER_H
