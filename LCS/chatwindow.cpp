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

    const QIcon boldIcon(":/image/boldIcon.png");
    ui->pushButtonBold->setText("");
    ui->pushButtonBold->setIcon(boldIcon);

    const QIcon underlineIcon(":/image/underlineIcon.png");
    ui->pushButtonUnderline->setText("");
    ui->pushButtonUnderline->setIcon(underlineIcon);

    const QIcon italicIcon(":/image/italicIcon.png");
    ui->pushButtonItalic->setText("");
    ui->pushButtonItalic->setIcon(italicIcon);

}

chatWindow::~chatWindow()
{
    delete ui;
}

void chatWindow::on_pushButtonFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,"Open file","D:/",tr("ZIP files(*.zip *.rar);; TEXT FILES(*.txt)"));
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
    QString filePath = QFileDialog::getOpenFileName(this,"Open file","D:/",tr("JPEG(*.jpg *.jpeg);; PNG(*.png);; GIF(*.gif)"));
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

    ui->labelChatting->clear();

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

void chatWindow::historyChat(QString sender, QString msg)
{
    QString befMsg = ui->labelChatting->text();
    ui->labelChatting->setText(QString("%1%2 : %3\n").arg(befMsg).arg(sender=="opposite"?(ui->label_User->text()):"ME").arg(msg));
}

void chatWindow::on_pushButtonBold_clicked()
{
    textCursor = ui->textEdit->textCursor();

    if(textCursor.hasSelection()){
        font = textCursor.charFormat().font();
        if(!textCursor.charFormat().font().bold()){
            font.setBold(true);
            format.setFont(font);
            textCursor.setCharFormat(format);
        }
        else{
            font.setBold(false);
            format.setFont(font);
            textCursor.setCharFormat(format);
       }
       ui->textEdit->setTextCursor(textCursor);
    }
    ui->textEdit->setFocus();
}

void chatWindow::on_pushButtonItalic_clicked()
{
    textCursor = ui->textEdit->textCursor();

    if(textCursor.hasSelection()){
        font = textCursor.charFormat().font();
        if(!textCursor.charFormat().font().italic()){
            font.setItalic(true);
            format.setFont(font);
            textCursor.setCharFormat(format);
         }
         else{
             font.setItalic(false);
             format.setFont(font);
             textCursor.setCharFormat(format);
         }
     ui->textEdit->setTextCursor(textCursor);
    }
    ui->textEdit->setFocus();
}

void chatWindow::on_pushButtonUnderline_clicked()
{
      textCursor = ui->textEdit->textCursor();

      if(textCursor.hasSelection()){
            font = textCursor.charFormat().font();
          if(!textCursor.charFormat().font().underline()){
                font.setUnderline(true);
                format.setFont(font);
                textCursor.setCharFormat(format);
           }
           else{
                font.setUnderline(false);
                format.setFont(font);
                textCursor.setCharFormat(format);
           }
       ui->textEdit->setTextCursor(textCursor);
       }
      ui->textEdit->setFocus();
}

void chatWindow::on_pushButtonColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Choose color");
    if(color.isValid()){
        ui->textEdit->setTextColor(color);
        ui->textEdit->setFocus();
    }
}
