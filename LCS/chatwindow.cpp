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

    ui->labelFileStatus->setText("");

    isStart= true;

//    connect(tcpSocket,&QTcpSocket::connected,[=](){
//       // show connection status bottom right
//        ui->labelConnectionStatus->setText("Connected");
//    });
//    connect(tcpSocket,&QTcpSocket::readyRead,[=](){
//       QByteArray buf = tcpSocket->readAll();

//       if(isStart){
//           isStart = false;

//           fileName = QString(buf).section("##",0,0);
//           fileSize = QString(buf).section("##", 1, 1).toInt();
//           recvSize = 0;
//           //打开文件
//           //关联文件名字
//           file.setFileName(fileName);

//           //只写方式打开文件
//           bool isOk = file.open(QIODevice::WriteOnly);
//           if(false == isOk)
//           {
//               qDebug() << "WriteOnly error 49";

//               tcpSocket->disconnectFromHost(); //断开连接
//               tcpSocket->close(); //关闭套接字

//               return; //如果打开文件失败，中断函数
//           }
//           QString str = QString("接收的文件: [%1: %2kb]").arg(fileName).arg(fileSize/1024);
//           QMessageBox::information(this, "文件信息", str);
//           ui->labelFileStatus->setText(str);
//           ui->labelFileStatus->setText("正在接收文件……");

//       }
//       else{
//           qint64 len = file.write(buf);
//           if(len >0) //接收数据大于0
//           {
//               recvSize += len; //累计接收大小
//               qDebug() << len;
//           }

//           if(recvSize == fileSize) //文件接收完毕
//           {
//               //先给服务发送(接收文件完成的信息)
//               tcpSocket->write("Done.");

//               ui->textEdit->append("文件接收完成");
//               QMessageBox::information(this, "完成", "文件接收完成");
//               file.close(); //关闭文件
//               //断开连接
//               tcpSocket->disconnectFromHost();
//               tcpSocket->close();
//            }
//       }
//    });
}

chatWindow::~chatWindow()
{
    delete ui;
}

void chatWindow::on_pushButtonFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,"Open file","D:/",tr("All files(*.*)"));
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
    else{
        qDebug() << "选择文件路径出错 118";
    }
}

void chatWindow::on_pushButtonPic_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,"Open file","D:/",tr("JPEG(*.jpg *.jpeg);; PNG(*.png);; MP3(*.mp3);; MP4(.mp4)"));
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

void chatWindow::on_pushButtonSend_clicked()
{
    //先发送文件头信息  文件名##文件大小
    QString head = QString("%1##%2").arg(fileName).arg(fileSize);
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

    //QImage p;
    //p.load(":/image/defaultuser.jpg");
    //p.scaled(10,10,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);


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

bool chatWindow::loadThemeFile(QString str){
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

void chatWindow::on_pushButtonConnect_clicked()
{
//    //获取服务器的ip和端口
//    QString ip = ui->lineEditIp->text();
//    quint16 port = ui->lineEditPort->text().toInt();

//    //主动和服务器连接
//    tcpSocket->connectToHost(QHostAddress(ip), port);

//    isStart = true;

}
