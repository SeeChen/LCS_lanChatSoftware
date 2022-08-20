#include "chatwindow.h"
#include "ui_chatwindow.h"

chatWindow::chatWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chatWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("聊天室");
    QFont v ("Simsun",10);
    this->setFont(v);

    //UI界面设置
    ui->labelChatting->setAttribute(Qt::WA_TranslucentBackground,true);
}

chatWindow::~chatWindow()
{
    delete ui;
}
