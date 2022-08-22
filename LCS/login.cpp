#include "login.h"
#include "ui_login.h"
#include "register.h"

#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QCryptographicHash>
#include <QRegExpValidator>

logIn::logIn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::logIn)
{
    ui->setupUi(this);
    this->setWindowTitle("登录页面");
    QFont v ("Simsun",10);
    this->setFont(v);

    /*UI界面设置*/
    //设置圆形用户图片
    QPixmap target = QPixmap(size());
    target.fill(Qt::transparent);

    QPixmap p;
    p.load(":/image/defaultuser.jpg");
    p.scaled(200,200,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);

    QPainter painter(&target);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setRenderHint(QPainter::HighQualityAntialiasing,true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform,true);

    QPainterPath path = QPainterPath();
    path.addRoundedRect(120,150,350,350,200,200);
    painter.setClipPath(path);
    painter.drawPixmap(120,150,p);
    ui->labelPic->setPixmap(target);
    this->update();

    //用户名和密码的icon
    const QIcon usernameIcon(":/image/Username.png");
    const QIcon passwordIcon(":/image/Password.ico");
    ui->lineEditUsername->setClearButtonEnabled(true);
    ui->lineEditUsername->addAction(usernameIcon,QLineEdit::LeadingPosition);
    ui->lineEditPassword->setClearButtonEnabled(true);
    ui->lineEditPassword->addAction(passwordIcon,QLineEdit::LeadingPosition);

    //用户名提示
    ui->lineEditUsername->setPlaceholderText("用户名");
    //密码提示
    lineEdit_Password=new QLineEdit;
    ui->lineEditPassword->setPlaceholderText("密码");
    ui->lineEditPassword->setEchoMode(QLineEdit::Password);
    QRegExp regx("[0-9]+$");    //仅限输入数字
    QValidator *validator=new QRegExpValidator(regx,lineEdit_Password);
    lineEdit_Password->setValidator(validator);
    lineEdit_Password->setMaxLength(6);
    //密码眼睛
    ui->labelEye->installEventFilter(this);

    //找回按钮
    ui->pushButtonFindPassword->setFlat(true);  //无外框按钮
    //注册按钮
    ui->pushButtonRegister->setFlat(true);  //无外框按钮
}

logIn::~logIn()
{
    delete ui->pushButtonFindPassword;
    delete ui->pushButtonLogin;
    delete ui->pushButtonRegister;
    delete ui->lineEditUsername;
    delete ui->lineEditPassword;
    delete ui->labelPic;
}


//登录按钮功能
void logIn::on_pushButtonLogin_pressed()
{
    QString Username=ui->lineEditUsername->text(); //获取用户名内容
    QString Password=ui->lineEditPassword->text(); //获取密码内容
    char *u_name=const_cast<char *>(Username.toStdString().c_str());
    QString MD5;
    QByteArray str;
    str=QCryptographicHash::hash(Password.toLatin1(),QCryptographicHash::Md5);
    MD5.append(str.toHex());
    char *p_word=const_cast<char *>(MD5.toStdString().c_str());

}


void logIn::on_pushButtonRegister_pressed()
{
    Register *rgtwindow=new Register;
    rgtwindow->show();
    this->hide();
}

bool logIn::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type()) {
        case QEvent::Enter:
            lineEdit_Password->setEchoMode(QLineEdit::Normal);
            break;
        case QEvent::Leave:
            lineEdit_Password->setEchoMode(QLineEdit::Password);
            break;
        default:
            break;
    }
    return QWidget::eventFilter(watched, event);
}
