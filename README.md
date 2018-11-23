# 0005_Qt_QEvent
Qt事件系统实例
## 【1】事件传递机制

### 001_QEvent
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

### 002_QEvent
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

## 【2】【鼠标事件】
###  003_QMouseEvent
鼠标事件：
【1】点击左键，鼠标箭头变为小拳头。
【2】双击：窗口放大
【3】右击:鼠标箭头变为图片，但是没有成功
【4】滚轮：Text中的字体大小改变
【5】设置鼠标追踪，没有生效，待查问题
```
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
```
## 【3】键盘事件
### 004_QKeyboardEvent
键盘事件：
组合键：ctrl+m，放大窗口
```
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
```
### 005_QKeyboardEvent
```

```

## 【4】定时器
### 006_QTimer
功能：开启3个定时器，会在输出后台打印哪个定时器被触发
```
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    id1 = startTimer(1000);         //开启一个1s定时器，返回id值
    id2 = startTimer(1500);
    id3 = startTimer(2200);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == id1){          //event->timerId()获取定时器id
        qDebug()<<"timer1";
    }else if(event->timerId() == id2){
        qDebug() <<"timer2";
    }else{
        qDebug()<<"timer3";
    }
}
```
### 006_QTimer
功能：
【1】增加了lcdNumber显示数字，使用了定时器。
【2】使用了定时器
```
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

```
![avatar](https://github.com/CodingManPP/0005_Qt_QEvent/blob/master/_006_QTimer/mytimerevent/%E6%97%B6%E9%92%9F%E6%98%BE%E7%A4%BA%E6%95%88%E6%9E%9C%E5%9B%BE.png)






