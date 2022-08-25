#ifndef CHAT_H
#define CHAT_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class Chat;
}

class Chat : public QWidget
{
    Q_OBJECT

public:
    explicit Chat(QWidget *parent = nullptr);
    ~Chat();

private slots:
    void on_btn_Send_clicked();

private:
    Ui::Chat *ui;

public:
    QStandardItemModel *standModel;

public slots:
    void responseChat(int, QString, QString);

    void responseMessage(QString, int);

    void responseHis(QString, int);

signals:
    void requestSendMessage(int, QString);
};

#endif // CHAT_H
