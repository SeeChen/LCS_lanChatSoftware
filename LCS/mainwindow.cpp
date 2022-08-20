#include "mainwindow.h"
#include "ui_mainwindow.h"

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

