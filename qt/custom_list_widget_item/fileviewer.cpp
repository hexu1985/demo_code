#include <QDir>
#include <QString>
#include <QListWidgetItem>
#include <QTimer>
#include "fileviewer.h"
#include "ui_fileviewer.h"
#include "mylistwidgetitem.h"

#include <iostream>

static QString list_widget_style = R"(
QListWidget {
  border:0px;
  background-color:rgba(0,0,0,0);
}

QListWidget::Item {
  padding-left:0px;
  padding-right:0px;
}

QListWidget::Item:hover {
  background:rgba(0,0,0,0); 
}

QListWidget::item:selected {
  background:rgba(0,0,0,0); 
  color:rgba(0,0,0,0); 
}

QListWidget::item:selected:!active {
  border-width:0px; 
  background:rgba(0,0,0,0); 
  color:rgba(0,0,0,0); 
}

QScrollBar:vertical
{
    width:5px;
}
    )";

FileViewer::FileViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileViewer)
{
    std::cout << "FileViewer::FileViewer()" << std::endl;
    ui->setupUi(this);
    ui->ListWidgetFile->setStyleSheet(list_widget_style);

    QString root = "/";
    QDir rootDir(root);	
    QStringList string;
    string << "*" ; 	
    QFileInfoList list=rootDir.entryInfoList (string);
    showFileInfoList(list);
}

FileViewer::~FileViewer()
{
    std::cout << "FileViewer::~FileViewer()" << std::endl;
    delete ui;
}

void FileViewer::showFileInfoList(QFileInfoList list)
{
    widget_vector_.clear();
    item_vector_.clear();
    ui->ListWidgetFile->clear();
//    for(unsigned int i=0;i<list.count();i++)
    for(unsigned int i=0;i<2;i++)
    {
        QFileInfo tmpFileInfo=list.at(i);
        if((tmpFileInfo.isDir()))
        {
            QString fileName = tmpFileInfo.fileName();
            QListWidgetItem *tmp = new QListWidgetItem(ui->ListWidgetFile);
            MyListWidgetItem *widget = new MyListWidgetItem(ui->ListWidgetFile);
            tmp->setSizeHint(widget->size());
            // tmp->setSizeHint(QSize(360,120));
            widget->setImageLabel(":/images/dir.png");
            widget->setTextLabel(fileName);
            widget->setIndex(i);
            ui->ListWidgetFile->setItemWidget(tmp, widget);
            widget_vector_.push_back(widget);
            item_vector_.push_back(tmp);
            connect(widget, SIGNAL(clicked(int)), this, SLOT(OnCustomItemClicked(int)));
        }
        else if(tmpFileInfo.isFile())
        {
            QString fileName = tmpFileInfo.fileName();
            QListWidgetItem *tmp = new QListWidgetItem(ui->ListWidgetFile);
            MyListWidgetItem *widget = new MyListWidgetItem(ui->ListWidgetFile);
            //tmp->setSizeHint(QSize(360,120));
            tmp->setSizeHint(widget->size());
            widget->setImageLabel(":/images/file.png");
            widget->setTextLabel(fileName);
            widget->setIndex(i);
            ui->ListWidgetFile->setItemWidget(tmp, widget);
            widget_vector_.push_back(widget);
            item_vector_.push_back(tmp);
            connect(widget, SIGNAL(clicked(int)), this, SLOT(OnCustomItemClicked(int)));
        }
    }
}

void FileViewer::OnCurrentItemChanged(QListWidgetItem *current, QListWidgetItem *previous) 
{
    std::cout << "FileViewer::OnCurrentItemChanged()" << std::endl;
    std::cout << "current: " << current->text().toStdString() << std::endl;
    if (previous) {
      std::cout << "previous: " << previous->text().toStdString() << std::endl;
    } else {
      std::cout << "previous: nullptr" << std::endl;
    }
}

void FileViewer::OnCurrentRowChanged(int currentRow)
{
    std::cout << "FileViewer::OnCurrentRowChanged()" << std::endl;
    std::cout << "currentRow: " << currentRow << std::endl;
}

void FileViewer::OnItemClicked(QListWidgetItem *item)
{
    std::cout << "FileViewer::OnItemClicked()" << std::endl;
    std::cout << "item: " << item->text().toStdString() << std::endl;
}

void FileViewer::OnCustomItemClicked(int index)
{
    std::cout << "FileViewer::OnCustomItemClicked()" << std::endl;
    std::cout << "index: " << index << std::endl;
    MyListWidgetItem *widget = widget_vector_[index];
    QTimer::singleShot(1000, [widget] {
        std::cout << "xxx" << std::endl;
        widget->setTestLabel(":/images/vim.png");});
}
