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

    ui->labelChatting->setAlignment(Qt::AlignTop);
    ui->labelChatting->setWordWrap(true);

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
    switch(msgType) {
        case messageType::TEXT:
            QString msg = ui->textEdit->toPlainText();

            if(!ui->label_User->text().startsWith("ME"))
                ui->labelChatting->setText(ui->labelChatting->text() + "\nME : " + msg);
            ui->textEdit->clear();
            emit requsetSendText(currentID, msg, msgType);
            break;
    }
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

void chatWindow::responseChat(int oppoID, QString oppoUsr)
{
    currentID = oppoID;

    ui->label_ID->setText(QString("%1").arg(oppoID));
    ui->label_User->setText(QString(oppoUsr));
}

void chatWindow::incomingMsg(int oppoID, QString msg)
{
    if(currentID == oppoID) {
        QString hisChat = ui->labelChatting->text();
        QString showMsg = QString("%1\n%2 : %3").arg(hisChat).arg(ui->label_User->text()).arg(msg);
        ui->labelChatting->setText(showMsg);
    }
}
