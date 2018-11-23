#include "mylineedit.h"

#include <QKeyEvent>
#include <QDebug>

MyLineEdit::MyLineEdit(QWidget *parent):
    QLineEdit(parent)
{

}

/**
 * @function:Myline键盘按下事件
 * @brief MyLineEdit::keyPressEvent
 * @param event
 */
//MylineEdit键盘按下事件
void MyLineEdit::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<tr("MyLineEdit键盘按下事件");
    QLineEdit::keyPressEvent(event);        //执行QLineEdit类的默认事件处理，可以输入字符
    event->ignore();
}
