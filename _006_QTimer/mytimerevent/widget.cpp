#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    id1 = startTimer(1000);         //开启一个1s定时器，返回id值
    id2 = startTimer(1500);
    id3 = startTimer(2200);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == id1){          //event->timerId()获取定时器id
        qDebug()<<"timer1";
    }else if(event->timerId() == id2){
        qDebug() <<"timer2";
    }else{
        qDebug()<<"timer3";
    }
}
