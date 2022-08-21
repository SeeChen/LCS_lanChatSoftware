#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("LCS");
    QFont v ("Simsun",10);
    this->setFont(v);

    //UI界面设置
    ui->lineEditSearch->setPlaceholderText("搜索");

    //设置圆形用户图片
    QPixmap target = QPixmap(size());
    target.fill(Qt::transparent);

    QPixmap p;
    p.load(":/image/defaultuser.jpg");
    p.scaled(10,10,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    QPainter painter(&target);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setRenderHint(QPainter::HighQualityAntialiasing,true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform,true);

    int x = ui->labelPic->x();
    int y = ui->labelPic->y();
    int w = ui->labelPic->width();
    int h = ui->labelPic->height();
    qDebug() << x << " " << y << w;
    int radius = 30 ;
    int increment = 360;

    QPainterPath path = QPainterPath();
    path.addRoundedRect(0,y+increment,radius*2,radius*2,radius,radius);
    painter.setClipPath(path);
    painter.drawPixmap(0,y+increment,radius*2,radius*2,p);
    ui->labelPic->setPixmap(target);
    this->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

