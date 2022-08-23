#include "login.h"
#include "ui_login.h"

#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QCryptographicHash>
#include <QRegExpValidator>
#include <QFile>

#include <QMessageBox>

logIn::logIn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::logIn)
{

    ui->setupUi(this);
    this->setWindowTitle("登录页面");
    QFont v ("Simsun",10);
    this->setFont(v);
    this->loadThemeFile(":/QSS/Dark.qss");

    /*UI界面设置*/
    // 设置圆形用户图片
    QPixmap targetPixmap = QPixmap(size());
    targetPixmap.fill(Qt::transparent);

    QPixmap pixmap;
    pixmap.load(":/image/defaultuser.jpg");
    pixmap.scaled(200,200,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);

    QPainter painter(&targetPixmap);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setRenderHint(QPainter::HighQualityAntialiasing,true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform,true);

    QPainterPath path = QPainterPath();
    path.addRoundedRect(120, 150, 350, 350, 200, 200);
    painter.setClipPath(path);
    painter.drawPixmap(120, 150, pixmap);
    ui->labelPic->setPixmap(targetPixmap);
    this->update();

    // 用户名和密码的icon
    const QIcon usernameIcon(":/image/Username.png");
    const QIcon passwordIcon(":/image/Password.ico");

    ui->lineEditUsername->setValidator(new QRegExpValidator(QRegExp("[0-9a-zA-Z]*"), ui->lineEditUsername));

    ui->lineEditUsername->addAction(usernameIcon, QLineEdit::LeadingPosition);
    ui->lineEditPassword->addAction(passwordIcon, QLineEdit::LeadingPosition);

    //用户名提示
    ui->lineEditUsername->setPlaceholderText("用户名");
    ui->lineEditPassword->setPlaceholderText("密码");

    ui->lineEditPassword->setEchoMode(QLineEdit::Password);

    ui->labelEye->installEventFilter(this);

    ui->pushButtonRegister->setFlat(true);
}

logIn::~logIn()
{
    delete ui->pushButtonLogin;
    delete ui->pushButtonRegister;
    delete ui->lineEditUsername;
    delete ui->lineEditPassword;
    delete ui->labelPic;
}


//登录按钮功能
void logIn::on_pushButtonLogin_clicked()
{
    QString UserName     = ui -> lineEditUsername -> text();
    QString UserPassword = ui -> lineEditPassword -> text();

    // 判断是否有空数值
    if(UserName == "") {
        ui->lineEditUsername->setPlaceholderText("用户名不能为空");
        ui->lineEditUsername->setStyleSheet("border: 2px solid red;");
    }

    if(UserPassword == "") {
        ui->lineEditPassword->setPlaceholderText("密码不能为空");
        ui->lineEditPassword->setStyleSheet("border: 2px solid red;");
    }

    // 加密密码
    QString    md5Password;
    QByteArray str;

    str = QCryptographicHash::hash(UserPassword.toLatin1(), QCryptographicHash::Md5);
    md5Password.append(str.toHex());

    emit requestLogin(UserName, md5Password);
}

bool logIn::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type()) {
        case QEvent::Enter:
            ui->lineEditPassword->setEchoMode(QLineEdit::Normal);
            break;
        case QEvent::Leave:
            ui->lineEditPassword->setEchoMode(QLineEdit::Password);
            break;
        default:
            break;
    }
    return QWidget::eventFilter(watched, event);
}

void logIn::responseLogin()
{
    QMessageBox::critical(this, "登陆失败", "用户名或密码错误", QMessageBox::Retry);

    ui->lineEditUsername->clear();
    ui->lineEditPassword->clear();
}

void logIn::on_pushButtonRegister_clicked()
{
    emit registerOpen();
}

bool logIn::loadThemeFile(QString str)
{
    QFile *lobConfigFile = new QFile(str);
    if(!lobConfigFile->open(QFile::ReadOnly)){

        return false;
    }

    QFile style(str);

    if(style.exists() && style.open(QFile::ReadOnly)) {
        QString styleContents = QLatin1String(style.readAll());
        style.close();
        this->setStyleSheet(styleContents);
    }

    lobConfigFile->close();

    return true;
}
