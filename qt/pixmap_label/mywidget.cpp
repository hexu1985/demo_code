#include "mywidget.h"
#include "ui_mywidget.h"
#include <iostream>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    {
        QPixmap img;
        img.load("vim_png", "png");
        auto size = img.size();
        std::cout << "img: size: (" << size.width() << "," << size.height() << ")" << std::endl;
        ui->label_default->clear();
        ui->label_default->setPixmap(img);
    }

    {
        QPixmap img;
        img.load("vim_png", "png");
        ui->label_autosize->clear();
        //ui->label_autosize->setScaledContents(true);
        ui->label_autosize->resize(img.size());
        ui->label_autosize->setPixmap(img);
    }

    {
        QSize size(60,60);
        QPixmap img;
        img.load("vim_png", "png");
        ui->label_fixsize->clear();
        ui->label_fixsize->resize(size);
        ui->label_fixsize->setScaledContents(true);
        ui->label_fixsize->setPixmap(img);
    }
}

MyWidget::~MyWidget()
{
    delete ui;
}
