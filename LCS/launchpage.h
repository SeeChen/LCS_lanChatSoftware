#ifndef LAUNCHPAGE_H
#define LAUNCHPAGE_H

#include "login.h"
#include "register.h"
#include "mainwindow.h"
#include "chatwindow.h"

#include <QWidget>

#include <QTcpSocket>

namespace Ui {
class LaunchPage;
}

class LaunchPage : public QWidget
{
    Q_OBJECT

public:
    explicit LaunchPage(QWidget *parent = nullptr);
    ~LaunchPage();

    QTcpSocket *clientSocket;

    logIn      loginPage;
    //Register   registerPage;
    MainWindow mainPage;
    chatWindow chatPage;

    void responseError(QString);

public slots:
    void requestLogin(QString, QString);    // 请求登录

private slots:
    void on_btn_Connect_clicked();

private:
    Ui::LaunchPage *ui;

signals:
    void responseLogin();
};

#endif // LAUNCHPAGE_H
