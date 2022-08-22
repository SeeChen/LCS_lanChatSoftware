#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLineEdit>
#include <QPainter>
#include <QDebug>
#include <QEvent>

namespace Ui {
class logIn;
}

class logIn : public QWidget
{
    Q_OBJECT

public:
    explicit logIn(QWidget *parent = nullptr);
    ~logIn();

private:
    Ui::logIn *ui;
    QLineEdit *lineEdit_Password;

protected:
    //密码显示功能
    bool eventFilter(QObject *watched, QEvent *event);

public slots:
    void responseLogin();

private slots:
    void on_pushButtonLogin_clicked();

    void on_pushButtonRegister_clicked();

signals:
    void requestLogin(QString, QString);

    void registerOpen();
};

#endif // LOGIN_H
