#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

#include <QKeyEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
     /*初始化*/
     keyup = false;         //向上方向键按下的标志
     keyLeft = false;       //向左方向键按下的标志
     move = false;          //是否完成一次移动标志

    ui->setupUi(this);
    setFocus();             //使主界面获取焦点

}

Widget::~Widget()
{
    delete ui;
}

//键盘按键按下
void Widget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up){
        qDebug()<<"press:"<<event->isAutoRepeat();
        if (event->isAutoRepeat()){
            return;
        }
        keyup = true;
    }else if(event->key() == Qt::Key_Left){
        if (event->isAutoRepeat()){
            return;
        }
        keyLeft = true;
    }
}

//键盘按键释放
void Widget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up){
        qDebug()<<"release:"<<event->isAutoRepeat();
        qDebug()<<"up";
        if (event->isAutoRepeat()){
            return;
        }
        keyup = true;
        if (move){
            move = false;
            return;
        }

        if (keyLeft){
            ui->pushButton->move(30,80);        //斜移
            move = true;
        }else {
            ui->pushButton->move(120,80);      //直接上移
        }
    }else if(event->key() == Qt::Key_Left) {
        if (event->isAutoRepeat()){
            return;
        }
        keyLeft = false;
        if (move){
            move = false;
            return;
        }
        if (keyup){
            ui->pushButton->move(30,80);        //斜移
            move = true;
        }else {
            ui->pushButton->move(30,120);       //
        }
    }else if (event->key() == Qt::Key_Down){
        ui->pushButton->move(120,120);                  //使用下方向键来还原按钮的位置
    }
}










