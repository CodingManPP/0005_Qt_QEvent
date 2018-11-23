#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    bool keyup;         //向上方向键按下的标志
    bool keyLeft;       //向左方向键按下的标志
    bool move;          //是否完成一次移动标志

protected:
    void keyPressEvent(QKeyEvent *event);               //键盘按键按下
    void keyReleaseEvent(QKeyEvent *event);           //键盘按键释放
};

#endif // WIDGET_H
