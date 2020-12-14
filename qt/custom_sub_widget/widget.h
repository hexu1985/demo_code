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

private slots:
    void slider1_valuechanged(int value);
    void slider2_valuechanged(int value);
    void slider3_valuechanged(int value);

};

#endif // WIDGET_H
