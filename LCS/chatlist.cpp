#include "chatlist.h"
#include "ui_chatlist.h"

#include <QDebug>

#include <QStandardItemModel>

ChatList::ChatList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatList)
{
    ui->setupUi(this);

    // 请求用户名和用户 ID
}

ChatList::~ChatList()
{
    delete ui;
}

void ChatList::responseUserInfo(int UserId, QString UserName)
{
    ui->label_ID->setText(QString("UID : %1").arg(UserId));
    ui->label_Name->setText(QString("Username : %1").arg(UserName));
}

void ChatList::responseUserList(QString data)
{
    QStandardItemModel *standModel;

    standModel = new QStandardItemModel;
    standModel->setColumnCount(3);

    ui->tableView->setModel(standModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    standModel->setHeaderData(0, Qt::Horizontal, QString("ID"      ));
    standModel->setHeaderData(1, Qt::Horizontal, QString("Username"));
    standModel->setHeaderData(2, Qt::Horizontal, QString("Status"  ));

    QStringList tempData = data.split("%%");

    for(int i = 0; i < tempData.length() - 1; i++) {
        QStringList temp = tempData.at(i).split(":");

        standModel->setItem(i, 0, new QStandardItem(temp.at(0)));
        standModel->setItem(i, 1, new QStandardItem(temp.at(1)));
        standModel->setItem(i, 2, new QStandardItem(temp.at(2)));

        if ("Username : " + temp.at(1) == ui->label_Name->text())
            standModel->setItem(i, 1, new QStandardItem(temp.at(1) + " ( ME )"));

        standModel->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        standModel->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        standModel->item(i, 2)->setTextAlignment(Qt::AlignCenter);
    }
}

void ChatList::on_tableView_clicked(const QModelIndex &index)
{
    int     toChatId     = index.sibling(index.row(), 0).data().toInt();
    QString toChatUsr    = index.sibling(index.row(), 1).data().toString();
    QString toChatStatus = index.sibling(index.row(), 2).data().toString();

    emit requestChat(toChatId, toChatUsr, toChatStatus);
    emit requestHis(toChatId);
}
