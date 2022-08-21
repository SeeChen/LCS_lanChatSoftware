#include "register.h"
#include "ui_register.h"
#include "login.h"
#include "mainwindow.h"

#include <QCryptographicHash>
#include <QDebug>
#include <QIntValidator>

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    QValidator *input=new QIntValidator(100,1000000,this);
    this->setWindowTitle("新用户注册");
    this->setFixedSize(850,650);

    //用户名
    this->labelUsername=new QLabel("用户账号：",this);
    this->labelUsername->setGeometry(100,100,100,50);
    this->lineEditUsername=new QLineEdit(this);
    this->lineEditUsername->setGeometry(270,100,400,50);
    this->lineEditUsername->setPlaceholderText("请输入账号         (3~10位以内数字)");
    this->lineEditUsername->setValidator(input);

    //密码
    this->labelPassword=new QLabel("输入密码",this);
    this->labelPassword->setGeometry(100,180,100,50);
    this->labelPassword2=new QLabel("确认密码",this);
    this->labelPassword2->setGeometry(100,260,200,50);
    this->lineEditPassword->setGeometry(270,180,400,50);
    this->lineEditPassword->setEchoMode(QLineEdit::Password);
    this->lineEditPassword->setPlaceholderText("请输入密码         (内容为3~6位数字)");
    this->lineEditPassword->setValidator(input);
    this->lineEditPassword2=new QLineEdit(this);
    this->lineEditPassword2->setGeometry(270,260,400,50);
    this->lineEditPassword2->setPlaceholderText("请再次输入密码");
    this->lineEditPassword2->setEchoMode(QLineEdit::Password);
    this->lineEditPassword2->setValidator(input);
    //验证码
    this->labelVerify=new QLabel("验证码：",this);
    this->labelVerify->setGeometry(100,340,100,50);
    this->lineEditVerify =new QLineEdit(this);
    this->lineEditVerify->setGeometry(270,340,250,50);
    this->lineEditVerify->setPlaceholderText("请输入验证码");
    this->lineEditVerify->setValidator(input);

    //验证码
    //this->verifyCode=new Verification(this);
    //this->verifyCode->setGeometry(555,340,100,50);

    this->pushButtonRegister=new QPushButton("注册并登陆",this);
    this->pushButtonRegister->setGeometry(180,450,200,80);

    this->pushButtonReturnLogin=new QPushButton("返回登陆页面",this);
    this->pushButtonReturnLogin->setGeometry(400,450,200,80);
    connect(this->pushButtonReturnLogin,SIGNAL(clicked(bool)),this,SLOT(RegistertoLogin()));
    connect(this->pushButtonReturnLogin,SIGNAL(clicked(bool)),this,SLOT(gotoLogining()));
}

Register::~Register()
{
    delete ui;
}

void Register::gotoLogining()
{
    logIn * login= new logIn;
    login->show();
    this->hide();
}

void Register::RegistertoLogin()
{
    QString USER=this->lineEditUsername->text();
    QString PASS=this->lineEditPassword->text();
    QString PASS2=this->lineEditPassword2->text();
    if(USER.length()<3 || PASS.length()<3)
    {
        QMessageBox::information(this,"注册失败","输入的账号或密码不符合要求");
    }
    else if(PASS==PASS2)
    {
        char * user=const_cast<char *>(USER.toStdString().c_str());

        QString PassMD5;
        QString passWd=PASS;
        QByteArray str;
        str = QCryptographicHash::hash(passWd.toLatin1(),QCryptographicHash::Md5);
        PassMD5.append(str.toHex());
        char * pass=const_cast<char *>(PassMD5.toStdString().c_str());
        qDebug()<<"在注册页面中"<<pass;
        /*if(::RegisterDB(user,pass))
        {
            //注册成功并登陆
            QMessageBox::information(this,"注册成功","正在为您登录...");

            //跳转到主聊天窗
        }
        else
        {
            QMessageBox::information(this,"注册失败","已存在此账号");
        }
    }
    else
    {
        QMessageBox::information(this,"注册失败","两次密码输入不一致");
    }*/
    }
}
