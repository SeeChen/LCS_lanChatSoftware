#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QAction>
#include <QIcon>
#include <QMessageBox>
#include <QDebug>
#include <QSqlRecord>
#include <QItemSelectionModel>
#include <QModelIndexList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include "userdatabase.h"
#include "chatwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:

    void on_pushButtonDelete_clicked();

    void on_pushButtonSort_clicked();

    void on_lineEditSearch_textChanged(const QString &arg1);

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButtonUiMode_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_lineEditAddId_returnPressed();

    bool loadThemeFile(QString);

private:
    Ui::MainWindow *ui;

    int selectedId;
    QString selectedName;

    int selectedIdFromTable = NULL;



    QString isMode = "light";
    QIcon *light = new QIcon(QPixmap(":/image/sun-svgrepo-com.svg"));
    QIcon *dark = new QIcon(QPixmap(":/image/moon-svgrepo-com.svg"));

    chatWindow cw;
    QSqlTableModel *model;

public slots:
    void responseOnlineList(QString, int);

signals:
    void requestChat(int, QString);
    void sendUiLink(QString);
};
#endif // MAINWINDOW_H
