#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

public slots:
    void responseError();

private slots:
    void on_btn_Back_clicked();

    void on_btn_Register_clicked();

    bool loadThemeFile(QString);

private:
    Ui::Register *ui;

signals:
    void requestRegister(QString, QString);

    void registerClose();
};

#endif // REGISTER_H
