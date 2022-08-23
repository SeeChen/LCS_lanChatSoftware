#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QLabel>
#include <QPixmap>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("LCS");
    QFont v ("Simsun",10);
    this->setFont(v);

    //UI界面设置
    ui->lineEditSearch->setPlaceholderText("搜索");

    //设置圆形用户图片
//    QPixmap target = QPixmap(size());
//    target.fill(Qt::transparent);

//    QPixmap p;
//    p.load(":/image/defaultuser.jpg");
//    p.scaled(10,10,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

//    QPainter painter(&target);
//    painter.setRenderHint(QPainter::Antialiasing,true);
//    painter.setRenderHint(QPainter::HighQualityAntialiasing,true);
//    painter.setRenderHint(QPainter::SmoothPixmapTransform,true);

//    int x = ui->labelPic->x();
//    int y = ui->labelPic->y();
//    int w = ui->labelPic->width();
//    int h = ui->labelPic->height();
//    qDebug() << x << " " << y << w;
//    int radius = 30 ;
//    int increment = 360;

//    QPainterPath path = QPainterPath();
//    path.addRoundedRect(0,y+increment,radius*2,radius*2,radius,radius);
//    painter.setClipPath(path);
//    painter.drawPixmap(0,y+increment,radius*2,radius*2,p);
//    ui->labelPic->setPixmap(target);
//    this->update();


    //移入代码by:誉航
    ui->pushButtonDelete->setEnabled(false);
    QIcon *icon = new QIcon(QPixmap(":/image/sun-svgrepo-com.svg"));
    ui->pushButtonUiMode->setIcon(*icon);

    createTable();
    showTable();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createTable()
{
    userDataBase dataBaseAtMainWindow;

    //这里的db需要从db类获取（未实现）
    int opened = dataBaseAtMainWindow.connectDataBase();

    if(false == opened)
    {
        QMessageBox::warning(this,"打开数据库错误","打不开数据库");
        return;
    }

    QSqlQuery query;

    //这里需要依据user(id)来制造表格（可能可以在register时就弄出来）（未实现）
    query.exec("create table user(id int primary key, name varchar(25));");

    //（未实现）
    query.exec("insert into user(id, name) values (1,'朋友1');");

    //批量
    query.prepare("insert into user(id,name) values(?,?)");

    //example
    QVariantList nameList;
    nameList << "朋友2"<<"朋友3"<<"朋友4"<<"朋友5";
    QVariantList idList;
    idList << 2 << 3 << 4 << 5;

    query.addBindValue(idList);
    query.addBindValue(nameList);
    //将上述都处理
    query.execBatch();
}

void MainWindow::showTable()
{
    model = new QSqlTableModel(this);
    //(未实现)
    model->setTable("user");

    ui->tableView->setModel(model);
    ui->tableView->setGridStyle(Qt::SolidLine);
    ui->tableView->setColumnWidth(0,170);
    ui->tableView->setColumnWidth(1,206);


    model->select();
}

bool MainWindow::loadThemeFile(QString str)
{
    QFile *lobConfigFile = new QFile(str);
    if(!lobConfigFile->open(QFile::ReadOnly)){

        return false;
    }

    QFile style(str);

    if(style.exists() && style.open(QFile::ReadOnly)) {
        QString styleContents = QLatin1String(style.readAll());
        style.close();
        this->setStyleSheet(styleContents);
    }

    lobConfigFile->close();

    return true;
}


void MainWindow::on_pushButtonDelete_clicked()
{
    int value = QMessageBox::question(this,"警告","确定删除好友吗？",QMessageBox::Yes,QMessageBox::No);
    switch(value){
    case QMessageBox::Yes:
        if(selectedIdFromTable == NULL){
            //1.获得信息
            QItemSelectionModel *selected = ui->tableView->selectionModel();
            QModelIndexList selectedInd =selected->selectedIndexes();
            qDebug()<<"-----";
            qDebug()<<selectedInd.first().row();
            qDebug()<<"-----";
            qDebug()<<selectedInd.first().data().toInt();
            qDebug()<<selectedInd.at(1).data().toString();

            //获取其信息。现在要通过这两个信息来删除他的朋友
            selectedId = selectedInd.first().data().toInt();
            selectedName = selectedInd.at(1).data().toString();

            QSqlQuery query;
            QString queryString(QString("delete from user where id = %1;").arg(selectedId));
            qDebug()<<queryString;
            query.prepare(queryString);
            query.exec();

        }else{
            //2.删除
            //需要连接数据库通过sql语句实行删除数据。
            QSqlQuery query;
            QString queryString(QString("delete from user where id = %1;").arg(selectedIdFromTable));
            qDebug()<<queryString;
            query.prepare(queryString);
            query.exec();

            selectedIdFromTable=NULL;
        }

        //3.更新
        model->submitAll();
        model->select();

        //4.刷新会原本界面
        ui->tableView->setModel(model);


        break;
    case QMessageBox::No:
        return;
        break;
    }


    ui->pushButtonDelete->setEnabled(false);

}

void MainWindow::on_pushButtonSort_clicked()
{
    model->setSort(0,Qt::AscendingOrder);

    model->submitAll();
    model->select();

    ui->tableView->setModel(model);
}

void MainWindow::on_lineEditSearch_textChanged(const QString &arg1)
{
    qDebug()<<arg1;

    if(arg1 == ""){
        ui->tableView->setModel(model);
    }else{
        //临时查找
        QSqlQuery query;
        QSqlQueryModel *modal = new QSqlQueryModel();

        //！！！！此地方的名字查找未完成！！！！
        QString queryString(QString("select * from user where name LIKE '%1%' or id = %1;").arg(arg1));

        qDebug()<<queryString;

        query.prepare(queryString);
        query.exec();

        while(true == query.next()){
            qDebug()<<query.value(0).toString()
                   <<query.value(1).toString();
        }

        //在表上显示
        modal->setQuery(query);
        ui->tableView->setModel(modal);
    }
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    ui->pushButtonDelete->setEnabled(true);
    //想要获取其id并且删除他，可点击任意值在该行
    selectedIdFromTable = index.sibling(index.row(),0).data().toInt();
}



//点击按钮切换UI（暗/亮）
void MainWindow::on_pushButtonUiMode_clicked()
{
    //需要传给chat page(这个比较重要)
    QString gsThemePath;

    if(isMode == "light"){
        gsThemePath = QString(":/QSS/Dark.qss");

        ui->pushButtonUiMode->setIcon(*dark);
        //这边！
        cw.loadThemeFile(gsThemePath);

        loadThemeFile(gsThemePath);
        isMode = "dark";
    }else{
        gsThemePath = QString(":/QSS/Light.qss");
        ui->pushButtonUiMode->setIcon(*light);
        //这边！
        cw.loadThemeFile(gsThemePath);

        loadThemeFile(gsThemePath);
        isMode = "light";
    }

    qDebug()<<isMode;


}

//进入聊天页面
void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    doubleClickedIdFromTable = index.sibling(index.row(),0).data().toInt();
    cw.show();

}

void MainWindow::on_lineEditAddId_returnPressed()
{
    int value = QMessageBox::question(this,"警告","添加好友？",QMessageBox::Yes,QMessageBox::No);
    int id = ui->lineEditAddId->text().toInt();
    QSqlRecord record;
    int row;

    switch(value){
    case QMessageBox::Yes:

        record = model->record();
        record.setValue(0,id);
        record.setValue(1,"请给该朋友添加名字");

        row = model->rowCount();
        model->insertRecord(row,record);

        ui->lineEditAddId->clear();
        break;
    case QMessageBox::No:
        ui->lineEditAddId->clear();
        break;
    }
}
