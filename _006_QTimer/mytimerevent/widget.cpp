#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

#include <QTime>
#include <QTimer>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    id1 = startTimer(1000);                                    //开启一个1s定时器，返回id值
    id2 = startTimer(1500);
    id3 = startTimer(2200);

    QTimer *timer = new QTimer(this);                           //创建新的定时器
    connect(timer,&QTimer::timeout,this,&Widget::timerUpdate);  //关联定时器的溢出信号到槽上
    timer->start(1000);                                         //设置溢出时间为1s，启动定时器

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));           //使用qrand()时需要先设置随机数qsrand，否则每次运行都会产生相同的值
    //secsTo两个时间点之间包含的秒数，此处表示从0点到当前时间所经过的秒数
    //    QTimer::singleShot(10000,this,&Widget::close);               //只运行一次的定时器，此处运行10s后关闭窗口

}

Widget::~Widget()
{
    delete ui;
}

void Widget::timerEvent(QTimerEvent *event)
{
#if 0
    if (event->timerId() == id1){          //event->timerId()获取定时器id
        qDebug()<<"timer1";
    }else if(event->timerId() == id2){
        qDebug() <<"timer2";
    }else{
        qDebug()<<"timer3";
    }
#endif
}

/*定时器溢出信号槽函数*/
void Widget::timerUpdate()
{
    QTime time = QTime::currentTime();          //获取当前时间
    QString text = time.toString("hh:mm:ss");      //转为字符串
    qDebug()<<text;
    qDebug()<<text.size();
    int size = text.size();
    for (int i=0; i<size; i++){
        qDebug()<<text[i];
    }
    if ((time.second() % 2 == 0)){                       //每隔一秒显示让hh与mm中的“:”闪烁一下
        text[5] =' ';                                   //此处的单引号中需要增加空格，否则报错：error: empty character constant text[2] ='';
        ui->lcdNumber->display(text);

#if 0
        int rand = qrand() % 300;                   //产生300以内的正整数
        ui->lcdNumber->move(rand,rand);
#endif
    }
}
