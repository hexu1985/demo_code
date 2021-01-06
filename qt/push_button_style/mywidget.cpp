#include "mywidget.h"
#include "ui_mywidget.h"
#include "button_proxy_style.h"

static std::string no_selected = R"(
QPushButton { 
  color: black;
  background-color: rgb(255,255,255);
border:1px solid gray;
}

QPushButton:pressed
{
  background-color:rgb(255,255,255);
  padding-left:0px;
  padding-top:0px;
}
)";

static std::string selected = R"(
QPushButton { 
  color: blue;
  background-color: rgb(255,255,255);
border:1px solid blue;
}

QPushButton:pressed
{
  background-color:rgb(255,255,255);
  padding-left:0px;
  padding-top:0px;
}
)";

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    ui->pushButton->setStyle(new ButtonProxyStyle());
    ui->pushButton_2->setStyle(new ButtonProxyStyle());

    ui->pushButton->setStyleSheet(QString::fromStdString(selected));
    ui->pushButton_2->setStyleSheet(QString::fromStdString(no_selected));
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushButton_clicked()
{
  ui->pushButton->setStyleSheet(QString::fromStdString(selected));
  ui->pushButton_2->setStyleSheet(QString::fromStdString(no_selected));
}

void MyWidget::on_pushButton_2_clicked()
{
  ui->pushButton->setStyleSheet(QString::fromStdString(no_selected));
  ui->pushButton_2->setStyleSheet(QString::fromStdString(selected));
}
