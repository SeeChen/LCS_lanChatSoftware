#ifndef EMOTICONWIDGET_H
#define EMOTICONWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QVector>
#include <memory>
#include <QString>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>

class QIcon;

QT_BEGIN_NAMESPACE
namespace Ui { class emoticonWidget; }
QT_END_NAMESPACE

class emoticonWidget : public QWidget
{
    Q_OBJECT

public:
    emoticonWidget(QWidget *parent = nullptr);
    //~emoticonWidget();
    QSize sizeHint() const override;

signals :
    void insertEmoticon(QString str);

protected:
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent* ev) override;

private slots:
    void on_buttonEmoji_Clicked();
    void on_PageButton_Clicked();
    void pageButtonUpdate();

private:
    Ui::emoticonWidget *ui;
    QStackedWidget sWidget;
    QVBoxLayout layout;
    QList<std::shared_ptr<QIcon>> emoticonsIcon;

};
#endif // EMOTICONWIDGET_H
