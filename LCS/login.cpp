#include "login.h"
#include "ui_login.h"

#include <QPainter>
#include <QPainterPath>

logIn::logIn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::logIn)
{
    ui->setupUi(this);
    this->setWindowTitle("登录页面");
    QFont v ("Simsun",10);
    this->setFont(v);

    /*UI界面设置*/
    //用户名和密码提示
    ui->lineEditUsername->setPlaceholderText("用户名");
    ui->lineEditPassword->setPlaceholderText("密码");

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
    path.addRoundedRect(150,150,350,350,200,200);
    painter.setClipPath(path);
    painter.drawPixmap(150,150,p);
    ui->labelPic->setPixmap(target);
    this->update();
}

logIn::~logIn()
{
    delete ui;
}
