#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //记事本标题名
    ui->textEdit->setDocumentTitle("Untitled - Notepad");
    //用户保存而更改记事本标题名
    setWindowTitle(ui->textEdit->documentTitle());

    //功能连接
    //文件（F）——菜单栏
    connect(ui->newFileAction,&QAction::triggered,this,&MainWindow::newFile);
    //connect(ui->openFileAction,&QAction::triggered,this,&MainWindow::openFile);
    //connect(ui->saveFileAction,&QAction::triggered,this,&MainWindow::save);
    //connect(ui->saveAsFileAction,&QAction::triggered,this,&MainWindow::save_as);

    //connect(ui->exitNotepadAction,&QAction::triggered,this,&MainWindow::exit);

    //编辑(E)——菜单栏
    //connect(ui->undoAction,&QAction::triggered,ui->textEdit,&QTextEdit::undo);
    //connect(ui->redoAction,&QAction::triggered,ui->textEdit,&QTextEdit::redo);

    //connect(ui->cutAction,&QAction::triggered,ui->textEdit,&QTextEdit::cut);
    //connect(ui->copyAction,&QAction::triggered,ui->textEdit,&QTextEdit::copy);
    //connect(ui->pasteAction,&QAction::triggered,ui->textEdit,&QTextEdit::paste);
    //connect(ui->deleteAction,&QAction::triggered,this,&MainWindow::del);

    //connect(ui->selectAllAction,&QAction::triggered,ui->textEdit,&QTextEdit::selectAll);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//新建文件
void MainWindow::newFile()
{
    if (ui->textEdit->document()->isModified()) //判断编辑文件是否改变
    {
        qDebug() << "document is modified";
        switch (requestSave())  //判断是否需要保存文件
        {
            case QMessageBox::Yes : //确认保存
                saveDocument();
                if (!currentFileName.isEmpty()) //判断文件名是否为空
                {
                    currentFileName.clear();
                }
                setDocument("Untitled - Notepad");
                ui->textEdit->document()->clear();
                break;
            case QMessageBox::No :  //不保存
                setDocument("Untitled - Notepad");
                ui->textEdit->document()->clear();
                break;
            case QMessageBox::Cancel :  //取消
                qDebug() << "取消";
                break;
            default:
                break;
        }
    }
    else
    {
        qDebug() << "document is not modified";
    }

}
