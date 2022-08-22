#include "emoticonwidget.h"
#include "emojipack.h"

#include <QFile>
#include <QGridLayout>
#include <QLayout>
#include <QMouseEvent>
#include <QPushButton>
#include <QRadioButton>
#include <QtDebug>

#include<QSpacerItem>

#include <math.h>

QString getStyleSheet(const QString& filename){
    QFile file(filename);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        qWarning() << "Stylesheet " <<filename << "notfound";
        return QString();

    }
    return  file.readAll();
}

emoticonWidget::emoticonWidget(QWidget *parent)
    : QWidget(parent)
{
    setLayout(&layout);
    layout.addWidget(&sWidget);

    QWidget* pageButtonsContainer = new QWidget;
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    pageButtonsContainer->setLayout(buttonLayout);

    layout.addWidget(pageButtonsContainer);

    const int maxCols = 0;
    const int maxRows = 0;
    const int items = maxCols * maxRows;

    const QList<QStringList>& emoticons = emojiPack::getInstance().getEmoticons();

    int itemCount = emoticons.size();
    int pageCount = ceil(float(itemCount) / float(items));
    int currPage = 0;
    int currItem = 0;
    int row = 0;
    int col = 0;

    const int px = 40;
    const QSize size(px,px);

    //创建页面
    buttonLayout->addStretch();
    for(int i = 0; i < pageCount; i ++){
        QGridLayout *pageLayout = new QGridLayout(this);
        pageLayout->addItem(new QSpacerItem(0,0,
                                            QSizePolicy::Minimum,
                                            QSizePolicy::Expanding),
                                            maxRows,0);
        pageLayout->addItem(new QSpacerItem(0,0,
                                           QSizePolicy::Expanding,
                                           QSizePolicy::Minimum),
                                           maxRows,0);
        QWidget *page = new QWidget(this);
        page->setLayout(pageLayout);
        sWidget.addWidget(page);

         //只有当页面超过1个是才需要按钮
         if(pageCount > 1){
             QRadioButton* pageButton = new QRadioButton(this);
             pageButton->setProperty("PageIndex",i);
             pageButton->setCursor(Qt::PointingHandCursor);
             pageButton->setChecked(i == 0);
             buttonLayout->addWidget(pageButton);

             connect(pageButton,&QRadioButton::clicked,this, &emoticonWidget::on_PageButton_Clicked );
        }
    }
    buttonLayout->addStretch();

    emojiPack &emojiPack = emojiPack::getInstance();
    for(const QStringList& set : emoticons){
        QPushButton * button = new QPushButton;
        std::shared_ptr<QIcon> icon = emojiPack.getAsIcon(set[0]);
        emoticonsIcon.append(icon);
        button->setIcon(icon->pixmap(size));
        button->setToolTip(set.join(" "));
        button->setProperty("sequence",set[0]);
        button->setCursor(Qt::PointingHandCursor);
        button->setFlat(true);
        button->setIconSize(size);
        button->setFixedSize(size);

        connect(button,&QPushButton::clicked,this,&emoticonWidget::on_buttonEmoji_Clicked);
        qobject_cast<QGridLayout*>(sWidget.widget(currPage)->layout())->addWidget(button,row,col++);

        ++currItem;

        //next row
        if(col>=maxCols){
            col = 0;
            row++;
        }

        //nextpage
        if(currItem >= items){
            row = 0;
            col = 0;
            currPage++;
        }
    }
    // calculate sizeHint
    layout.activate();

}

void emoticonWidget::on_buttonEmoji_Clicked(){
    QWidget* sender = qobject_cast<QWidget*>(QObject::sender());
    if(sender){
        QString sq = sender->property("sequence").toString().replace("&lt;","<").replace("&gt;",">");
        emit insertEmoticon(sq);
    }
}

void emoticonWidget::on_PageButton_Clicked(){
    QWidget* sender = qobject_cast<QRadioButton*>(QObject::sender());
    if(sender){
        int page = sender->property("pageIndex").toInt();
        sWidget.setCurrentIndex(page);
    }
}

QSize emoticonWidget::sizeHint() const
{
    return layout.sizeHint();
}

void emoticonWidget::mouseReleaseEvent(QMouseEvent *ev)
{
    if(!rect().contains(ev->pos()))
        hide();
}

void emoticonWidget::mousePressEvent(QMouseEvent *){}

void emoticonWidget::wheelEvent(QWheelEvent *event)
{
    if(event->orientation() == Qt::Vertical){
        if(event->delta() < 0)
            sWidget.setCurrentIndex(sWidget.currentIndex() + 1);
        else
            sWidget.setCurrentIndex(sWidget.currentIndex() - 1);

        emit pageButtonUpdate();
    }
}
void emoticonWidget::pageButtonUpdate()
{
    QList<QRadioButton*> pageButtons = this->findChildren<QRadioButton*>(QString());
    for(QRadioButton *t_pageButtons : pageButtons){
        if(t_pageButtons->property("pageIndex").toInt()==sWidget.currentIndex())
            t_pageButtons->setChecked(true);
        else
            t_pageButtons->setChecked(false);
    }
}
void emoticonWidget::keyPressEvent(QKeyEvent *ev)
{
    Q_UNUSED(ev);
    hide();
}


