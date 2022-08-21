#ifndef REGISTER_H
#define REGISTER_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QButtonGroup>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QValidator>

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();
    QLabel *labelUsername;  //用户名
    QLineEdit *lineEditUsername;    //用户名编辑框
    QLabel  *labelPassword; //密码
    QLineEdit *lineEditPassword;    //密码编辑框
    QLabel  *labelPassword2; //再次输入密码
    QLineEdit *lineEditPassword2;    //再次输入密码编辑框
    QLabel *labelVerify;    //验证码
    QLineEdit *lineEditVerify;  //验证码编辑框
    QPushButton *pushButtonRegister;   //注册并登录
    QPushButton *pushButtonReturnLogin;   //返回登录页面

public slots:
    void gotoLogining();
    void RegistertoLogin();


private:
    Ui::Register *ui;
};

#endif // REGISTER_H
