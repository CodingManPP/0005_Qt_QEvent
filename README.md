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
