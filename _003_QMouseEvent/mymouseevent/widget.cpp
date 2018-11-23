#include "widget.h"
#include "ui_widget.h"

#include <QMouseEvent>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

#if 1

    setMouseTracking(true);         //  测试无效,为什么？？？
                                    //设置ui属性的mouseTracking属性勾选上
#endif


#if 1
    QCursor cursor;                         //创建光标对象
    cursor.setShape(Qt::OpenHandCursor);    //设置光标形状
    setCursor(cursor);                      //使用光标
#endif



}

Widget::~Widget()
{
    delete ui;
}

/* 鼠标单击--按下事件*/
void Widget::mousePressEvent(QMouseEvent *event)
{
     if (event->button() == Qt::LeftButton){
         QCursor cursor;
         cursor.setShape(Qt::ClosedHandCursor);             //鼠标暂时改变形状
         QApplication::setOverrideCursor(cursor);
         offset = event->globalPos() - pos();               //获取指针的位置和窗口位置的差值
     }else if(event->button() == Qt::RightButton){          //鼠标右键按下
         QCursor cursor(QPixmap("../mymouseevent/logo.png"));  //使用图片会报错：QCursor: Cannot create bitmap cursor; invalid bitmap(s)
         QApplication::setOverrideCursor(cursor);           //使用鼠标自定义的图片作为鼠标指针

     }
}

/* 鼠标移动事件*/
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton){             //此处必须使用buttons，鼠标移动时会检测所有按下的键
        QPoint temp;
        temp = event->globalPos() - offset;             //使用鼠标指针当前的位置减去差值得到窗口应该移动的位置
        move(temp);
    }
}

/* 鼠标单击--松开事件*/
void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    QApplication::restoreOverrideCursor();              //恢复指标的形状
}

/* 鼠标双击事件*/
void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){                 //鼠标左键按下
        if (windowState() != Qt::WindowFullScreen){         //全屏显示
            setWindowState(Qt::WindowFullScreen);
        }else {
            setWindowState(Qt::WindowNoState);
        }
    }
}


/* 鼠标滚轮事件*/
void Widget::wheelEvent(QWheelEvent *event)
{
    if (event->delta() > 0){
        ui->textEdit->zoomIn();                     //字体放大
        qDebug()<<tr("鼠标滚轮值：")<<event->delta();   //120
    }else {
        ui->textEdit->zoomOut();                    //字体缩小
    }
}
















