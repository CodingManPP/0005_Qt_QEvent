#include "widget.h"
#include "ui_widget.h"

#include <QKeyEvent>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

/*键盘按下事件*/
void Widget::keyPressEvent(QKeyEvent *event)
{
      if (event->modifiers() == Qt::ControlModifier){               //是否按下ctrl
          if (event->key() == Qt::Key_M){                           //是否按下M键
               qDebug()<<tr("键盘按键按下：")<<event->key();
              setWindowState(Qt::WindowMaximized);                  //窗口最大化
          }
      }else {
          QWidget::keyPressEvent(event);
      }
}

/* 键盘释放事件*/
void Widget::keyReleaseEvent(QKeyEvent *event)                      //按键释放
{
    //其他操作
    qDebug()<<tr("键盘按键释放：")<<event->key();
}


