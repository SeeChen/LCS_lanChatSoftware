#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include  <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //文件（F）——菜单栏
    void newFile();
    void openFile();
    void save();
    void save_as();
    void exit();

    //编辑（E）——菜单栏
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void del();
    void selectAll();

    //判断是否需要保存文件
    int requestSave();
    //保存编辑内容信息
    QString saveDocument();
    void getDocumentText();

    void setDocument(QString title);

    void doForSelectChanged();

private:
    Ui::MainWindow *ui;
    QString currentFileName;
};
#endif // MAINWINDOW_H
