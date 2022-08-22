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
    void on_pushButtonAdd_clicked();

    void on_pushButtonDelete_clicked();

    void on_pushButtonSort_clicked();

    void on_lineEditSearch_textChanged(const QString &arg1);

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButtonUiMode_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

    int selectedId;
    QString selectedName;

    int selectedIdFromTable = NULL;
    int doubleClickedIdFromTable =NULL;

    QSqlTableModel *model;

    void createTable();
    void showTable();

    bool loadThemeFile(QString);

    chatWindow cw;
};
#endif // MAINWINDOW_H
