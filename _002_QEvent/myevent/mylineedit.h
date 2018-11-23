#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QEvent>
#include <QLineEdit>
#include <QObject>

class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit MyLineEdit(QWidget *parent = 0);

    bool event(QEvent *event);
protected:
    void keyPressEvent(QKeyEvent *event);  //键盘按下事件
};

#endif // MYLINEEDIT_H
