#include "mywidget.h"
#include "ui_mywidget.h"
#include "button_proxy_style.h"

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    ui->pushButton->setStyle(new ButtonProxyStyle());
    ui->pushButton_2->setStyle(new ButtonProxyStyle());
}

MyWidget::~MyWidget()
{
    delete ui;
}
