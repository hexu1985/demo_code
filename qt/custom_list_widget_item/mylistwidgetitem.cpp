#include "mylistwidgetitem.h"
#include "ui_mylistwidgetitem.h"
#include <QPixmap>
#include <iostream>

MyListWidgetItem::MyListWidgetItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyListWidgetItem)
{
    ui->setupUi(this);
}

MyListWidgetItem::~MyListWidgetItem()
{
#if 0
    std::cout << "MyListWidgetItem::~MyListWidgetItem()" << std::endl;
#endif
    delete ui;
}

void MyListWidgetItem::setImageLabel(QString image_path)
{
    QPixmap img(image_path);
    ui->label_image->setScaledContents(true);
    ui->label_image->setPixmap(img);
}

void MyListWidgetItem::setTextLabel(QString str)
{
    ui->label_path->setText(str);
}

void MyListWidgetItem::setIndex(int index)
{
    index_ = index;
}

int MyListWidgetItem::getIndex() const
{
    return index_;
}

