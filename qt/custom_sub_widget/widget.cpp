#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->slider1, SIGNAL(valueChanged(int)), this,
            SLOT(slider1_valuechanged(int)));

    connect(ui->slider2, SIGNAL(valueChanged(int)), this,
            SLOT(slider2_valuechanged(int)));

    connect(ui->slider3, SIGNAL(valueChanged(int)), this,
            SLOT(slider3_valuechanged(int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slider1_valuechanged(int value)
{
    ui->spinBox1->setValue(value);
}

void Widget::slider2_valuechanged(int value)
{
    ui->spinBox2->setValue(value);
}

void Widget::slider3_valuechanged(int value)
{
    ui->spinBox3->setValue(value);
}





