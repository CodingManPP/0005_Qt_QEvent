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
    lineEdit = new MyLineEdit(this);            //窗口中添加MyLineEdit控件
    lineEdit->move(100,100);
}

void Widget::keyPressEvent(QKeyEvent *event)    //widget键盘按下事件
{
    qDebug()<<tr("Widget 键盘按下事件");
}


Widget::~Widget()
{
    delete ui;
}
