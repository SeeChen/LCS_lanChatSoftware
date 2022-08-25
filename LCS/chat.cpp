#include "chat.h"
#include "ui_chat.h"

#include <QStandardItemModel>
#include <QAbstractItemView>

#include <QDebug>

Chat::Chat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);

    standModel = new QStandardItemModel;
    standModel->setColumnCount(1);

    ui->tableView->setModel(standModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setDefaultSectionSize(75);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->horizontalHeader()->setVisible(false);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setFocusPolicy(Qt::NoFocus);
    ui->tableView->setShowGrid(false);
}

Chat::~Chat()
{
    delete ui;
}

void Chat::on_btn_Send_clicked()
{

    QString chatContent = ui->textEdit->toPlainText();
    int        targetID = ui->oppoID->text().toUInt();

    ui->textEdit->setText("");

    emit requestSendMessage(targetID, chatContent);

}

void Chat::responseChat(int id, QString name, QString status)
{
    ui->oppoID->setText(QString("  %1").arg(id));
    ui->oppoName->setText(name);
    ui->oppoStatus->setText(status + "  ");

    standModel->clear();
    ui->tableView->update();
}

void Chat::responseMessage(QString data, int myID)
{
    QStringList temp = data.split("%%");

    int     fromID  = temp.at(0).toInt();
    QString Msg     = temp.at(1);
    QString    time = temp.at(2);

    int     currentID   = ui->oppoID->text().toInt();
    QString currentName = ui->oppoName->text();

    QString text;

    if (myID == fromID) {
        text = "<br/><span style='color:#1aa260;'>&nbsp;&nbsp;&nbsp;ME&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" + time + "</span><br/>&nbsp;&nbsp;&nbsp;" + Msg + "<br/>";
    }
    else text = "<br/><span style='color:#f00;'>&nbsp;&nbsp;&nbsp;" + currentName + "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" + time + "</span><br/>&nbsp;&nbsp;&nbsp;" + Msg + "<br/>";

    qDebug() <<text;

    int row = ui->tableView->model()->rowCount();

    standModel->setItem(row, 0, new QStandardItem(""));

    QLabel *label = new QLabel();

    label->setText(text);
    ui->tableView->setIndexWidget(standModel->index(row, 0), label);
}

void Chat::responseHis(QString, int)
{

}
