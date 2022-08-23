#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include "enum_Var.h"

#include <QWidget>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QString>
#include <QMessageBox>

#include <QTimer>
#include <QTcpSocket>
#include <QTcpServer>

#include <QStackedWidget>
#include <QImage>

namespace Ui {
class chatWindow;
}

class chatWindow : public QWidget
{
    Q_OBJECT

public:
    explicit chatWindow(QWidget *parent = nullptr);
    ~chatWindow();

    bool loadThemeFile(QString);

    int currentID = 0;
    int msgType   = messageType::TEXT;

private slots:
    void on_pushButtonFile_clicked();

    void on_pushButtonPic_clicked();

    //void on_pushButtonEmoji_clicked();

    void on_pushButtonSend_clicked();

    void on_pushButtonConnect_clicked();

private:
    Ui::chatWindow *ui;
    QFile file; //文件对象
    QString fileName; //文件名字
    qint64 fileSize; //文件大小
    qint64 recvSize; //已经接收文件的大小
    qint64 sendSize; //已经发送文件的大小
    QString fPath;// file path for videos and pictures
    QString textLog="";
    QString chatStr;



    bool isStart;

    QTimer timer;

public slots:
    void responseChat(int, QString);

signals:
    void requsetSendText(int, QString, int);

};

#endif // CHATWINDOW_H
