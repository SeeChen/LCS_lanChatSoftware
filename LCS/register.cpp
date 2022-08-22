#include "register.h"
#include "ui_register.h"

#include <QMessageBox>
#include <QRegExpValidator>

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);

    ui->lineEdit_UserName->setPlaceholderText("请输入用户名");
    ui->lineEdit_Password->setPlaceholderText("请输入密码");
    ui->lineEdit_Configm->setPlaceholderText("再一次输入密码");

    ui->lineEdit_UserName->setValidator(new QRegExpValidator(QRegExp("[0-9a-zA-Z]*"), ui->lineEdit_UserName));
}

Register::~Register()
{
    delete ui;
}

void Register::on_btn_Register_clicked()
{
    QString usrName = ui->lineEdit_UserName->text();

    QString password1 = ui->lineEdit_Password->text();
    QString password2 = ui->lineEdit_Configm->text();

    // 判断是否有空数值
    if(usrName == "") {
        ui->lineEdit_UserName->setPlaceholderText("用户名不能为空");
        ui->lineEdit_UserName->setStyleSheet("border: 2px solid red;");
    }

    if(password1 == "") {
        ui->lineEdit_Password->setPlaceholderText("密码不能为空");
        ui->lineEdit_Password->setStyleSheet("border: 2px solid red;");
    }

    if(password2 == "") {
        ui->lineEdit_Configm->setPlaceholderText("密码不能为空");
        ui->lineEdit_Configm->setStyleSheet("border: 2px solid red;");
    }

    if(password1.length() < 8) {
        QMessageBox::warning(this, "注意", "密码必须大于八位", QMessageBox::Retry);
    }

    if((password1 != password2) && (password1 != "") && (password2 != "") ) {
        QMessageBox::warning(this, "注意", "两次密码必须相同", QMessageBox::Retry);
    }
}

void Register::on_btn_Back_clicked()
{

}
