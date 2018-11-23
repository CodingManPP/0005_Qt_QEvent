#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

//前置声明
class MyLineEdit;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    bool eventFilter(QObject *watched, QEvent *event);  //事件过滤
    ~Widget();

private:
    Ui::Widget *ui;
    MyLineEdit *lineEdit;

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // WIDGET_H
