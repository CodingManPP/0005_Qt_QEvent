#include "widget.h"
#include "ui_widget.h"

#include <QKeyEvent>
#include <QWheelEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->textEdit->installEventFilter(this);        //为编辑器textEdit部件在本窗口安装事件过滤器
    ui->spinBox->installEventFilter(this);         //为spinBox在本窗口安装事件过滤器

    /**
     * 发送事件的另外一种方法
     * @brief myEvent
     * @return
     */
    QKeyEvent myEvent(QEvent::KeyPress,Qt::Key_Up,Qt::NoModifier);          //次操作：模仿了按下Key_Up键
    for (int i=0 ; i<10; i++){
        qApp->sendEvent(ui->spinBox,&myEvent);   //发送键盘事件到spinBox
    }
}

Widget::~Widget()
{
    delete ui;
}

/**
 * 事件过滤器：可以很容易的处理多个部件的多个事件
 */
bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->textEdit){
        if (event->type() == QEvent::Wheel){                                //判断部件
            //将event事件强制转换为发生的事件的类型
            QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
            if (wheelEvent->delta() > 0){
                ui->textEdit->zoomIn();                                     //滚轮滚动，则textEdit字体放大
                return true;
            }else {
                ui->textEdit->zoomOut();
                return false;
            }
        }
    }else if (watched == ui->spinBox) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*> (event);
            if (keyEvent->key() == Qt::Key_Space){
                ui->spinBox->setValue(0);                               //按下空格键，则spinBox的值设置为0
                return true;
            }else {
                return false;
            }
        }else {
            return false;
        }
    }else {
        return QWidget::eventFilter(watched,event);
    }
}
