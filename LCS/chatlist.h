#ifndef CHATLIST_H
#define CHATLIST_H

#include <QWidget>

namespace Ui {
class ChatList;
}

class ChatList : public QWidget
{
    Q_OBJECT

public:
    explicit ChatList(QWidget *parent = nullptr);
    ~ChatList();

private:
    Ui::ChatList *ui;

public slots:
    void responseUserInfo(int, QString);
    void responseUserList(QString);

    void on_tableView_clicked(const QModelIndex &index);

signals:
    void requestChat(int ,QString, QString);

    void requestHis(int);
};

#endif // CHATLIST_H
