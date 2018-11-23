# 0005_Qt_QEvent
Qt事件系统实例

## 001_QEvent
事件传递：
自定义了一个LineEdit，在窗口Widget中加入了自定义的LineEdit。
在LineEdit中键盘的事件会传递到Widget中
* widget.cpp
```
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
```
* mylineedit.cpp
```
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

```
运行结果如下：部件的键盘事件会传递到父控件窗口中widget
![avatar](https://github.com/CodingManPP/0005_Qt_QEvent/blob/master/_001_QEvent/myevent/%E4%BA%8B%E4%BB%B6%E4%BC%A0%E9%80%92%E5%AE%9E%E4%BE%8B1.png)

## 002_QEvent
事件过滤机制：
* widget.cpp
```
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
```
* myLineEdit.cpp
```
/*事件过滤机制*/
bool MyLineEdit:: event(QEvent *event)
{
    if (event->type() == QEvent::KeyPress){
        qDebug()<<tr("MyLineEdit的event()函数");
    }
    return QLineEdit::event(event);         //执行QLineEdit了的event函数的默认操作
}
```
运行结果如下：
![avatar](https://github.com/CodingManPP/0005_Qt_QEvent/blob/master/_002_QEvent/myevent/%E4%BA%8B%E4%BB%B6%E4%BC%A0%E9%80%92%E5%AE%9E%E4%BE%8B2.png)
* 事件过滤机制如下：
事件的传递顺序如下：
先是事件过滤器，然后是焦点部件的event()函数，最后是焦点部件的事件处理函数；如果焦点部件忽略了该事件，那么会执行父部件的事件处理函数。
![avatra](https://github.com/CodingManPP/0005_Qt_QEvent/blob/master/_002_QEvent/myevent/%E4%BA%8B%E4%BB%B6%E4%BC%A0%E9%80%92%E6%9C%BA%E5%88%B6%E7%A4%BA%E6%84%8F%E5%9B%BE.png)
