#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHostInfo>
#include <QString>
#include <QDebug>
#include <QNetworkInterface>
#include <QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 获取本机 IP 地址
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost){

            this->setWindowTitle(address.toString());
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
