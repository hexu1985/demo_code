#include "mylistwidgetitem.h"
#include "ui_mylistwidgetitem.h"

MyListWidgetItem::MyListWidgetItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyListWidgetItem)
{
    ui->setupUi(this);
}

MyListWidgetItem::~MyListWidgetItem()
{
    delete ui;
}
