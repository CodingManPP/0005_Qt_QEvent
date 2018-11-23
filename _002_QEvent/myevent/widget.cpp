#include "widget.h"
#include "ui_widget.h"

#include "mylineedit.h"
#include <QKeyEvent>
#include <QDebug>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    lineEdit = new MyLineEdit(this);
    lineEdit->move(100,100);
    lineEdit->installEventFilter(this);     //在widget上为LineEdit安装事件过滤器
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<tr("Widget键盘按下事件");
}

/* 事件过滤机制*/
bool Widget::eventFilter(QObject *watched, QEvent *event)  //事件过滤
{
    if (watched == lineEdit){
        if (event->type() == QEvent::KeyPress){
            qDebug()<< tr("Widget的事件过滤器");
        }
    }

    return QWidget::eventFilter(watched,event);
}

Widget::~Widget()
{
    delete ui;
}
