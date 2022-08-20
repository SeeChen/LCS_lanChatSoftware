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
    ui->labelChatting->setMargin(10);


}

chatWindow::~chatWindow()
{
    delete ui;
}

void chatWindow::on_pushButtonFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,"Open file","D:/");
    fPath = filePath;
    if(false == filePath.isEmpty()) //如果选择文件路径有效
    {
        fileName.clear();
        fileSize = 0;

        //获取文件信息
        QFileInfo info(filePath);
        fileName = info.fileName(); //获取文件名字
        fileSize = info.size(); //获取文件大小

        sendSize = 0; //发送文件的大小

        //只读方式打开文件
        //指定文件的名字
        file.setFileName(filePath);

        //打开文件
        bool isOk = file.open(QIODevice::ReadOnly);
        if(false == isOk)
        {
            qDebug() << "Faied to Open file (Read only) 106";
        }

        //提示打开文件的路径
        ui->textEdit->append(filePath);
    }
    else
    {
        qDebug() << "选择文件路径出错 118";
    }
}

void chatWindow::on_pushButtonPic_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,"Open file","D:/");
    fPath = filePath;
    if(false == filePath.isEmpty()) //如果选择文件路径有效
    {
        fileName.clear();
        fileSize = 0;

        //获取文件信息
        QFileInfo info(filePath);
        fileName = info.fileName(); //获取文件名字
        fileSize = info.size(); //获取文件大小

        sendSize = 0; //发送文件的大小

        //只读方式打开文件
        //指定文件的名字
        file.setFileName(filePath);

        //打开文件
        bool isOk = file.open(QIODevice::ReadOnly);
        if(false == isOk)
        {
            qDebug() << "Faied to Open file (Read only) 106";
        }

        //提示打开文件的路径
        ui->textEdit->append(filePath);
    }
    else
    {
        qDebug() << "选择文件路径出错 118";
    }
}

void chatWindow::on_pushButtonEmoji_clicked()
{

}

void chatWindow::on_pushButtonSend_clicked()
{
    //先发送文件头信息  文件名##文件大小
//    QString head = QString("%1##%2").arg(fileName).arg(fileSize);
    //发送头部信息
//    qint64 len = tcpSocket->write( head.toUtf8() );
//    if(len > 0)//头部信息发送成功
//    {
//        //发送真正的文件信息
//        //防止TCP黏包
//        //需要通过定时器延时 20 ms
//        timer.start(20);

//    }
//    else
//    {
//        qDebug() << "头部信息发送失败 142";
//        file.close();
//    }

    QImage p;
    p.load(":/image/defaultuser.jpg");
    p.scaled(10,10,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);


    chatStr = ui->textEdit->toPlainText();

    if(chatStr == NULL){
       return;
    }

    textLog += "\n" + chatStr;
    //ui->labelChatting->setTextFormat(Qt::AutoText);
    //ui->labelUser->setText(str);
    //ui->labelChatting->setWordWrap(true);
    ui->labelChatting->setText(textLog);

    ui->textEdit->clear();// 清空TextEdit
}
