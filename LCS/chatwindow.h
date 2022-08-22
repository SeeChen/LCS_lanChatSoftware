#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QString>
#include <QStackedWidget>
#include <QImage>

#include <QTimer>
#include <QTcpSocket>
#include <QTcpServer>

namespace Ui {
class chatWindow;
}

class chatWindow : public QWidget
{
    Q_OBJECT

public:
    explicit chatWindow(QWidget *parent = nullptr);
    ~chatWindow();

private slots:
    void on_pushButtonFile_clicked();

    void on_pushButtonPic_clicked();

    void on_pushButtonEmoji_clicked();

    void on_pushButtonSend_clicked();

private:
    Ui::chatWindow *ui;
    QFile file; //文件对象
    QString fileName; //文件名字
    qint64 fileSize; //文件大小
    qint64 sendSize; //已经发送文件的大小
    QString fPath;// file path for videos and pictures
    QString textLog="";
    QString chatStr;

    QTcpSocket *tcpSocket;

    QTimer timer;
};

#endif // CHATWINDOW_H
