#include "mylineedit.h"
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>

MyLineEdit::MyLineEdit(QWidget *parent):
    QLineEdit(parent)
{

}

void MyLineEdit::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<tr("MyLineEdit 键盘按下事件");
    QLineEdit::keyPressEvent(event);
    event->ignore();
}

/*事件过滤机制*/
bool MyLineEdit:: event(QEvent *event)
{
    if (event->type() == QEvent::KeyPress){
        qDebug()<<tr("MyLineEdit的event()函数");
    }
    return QLineEdit::event(event);         //执行QLineEdit了的event函数的默认操作
}
