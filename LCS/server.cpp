#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
    this->setWindowTitle("服务器");
    //UI界面设置
    //ui->comboBoxIP->setPlaceholderText("请选择IP地址");

    //port端口号码
    ui->lineEditServerPort->setPlaceholderText("端口号码");

}

Server::~Server()
{
    delete ui;
}
