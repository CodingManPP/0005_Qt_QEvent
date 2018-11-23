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
    ~Widget();

private:
    Ui::Widget *ui;

protected:
    void keyPressEvent(QKeyEvent *event);
    MyLineEdit *lineEdit;
};

#endif // WIDGET_H
