#include <QDir>
#include <QString>
#include <QListWidgetItem>
#include "fileviewer.h"
#include "ui_fileviewer.h"
#include "mylistwidgetitem.h"

#include <iostream>

FileViewer::FileViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileViewer)
{
    std::cout << "FileViewer::FileViewer()" << std::endl;
    ui->setupUi(this);

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
    ui->ListWidgetFile->clear();
    for(unsigned int i=0;i<list.count();i++)
//    for(unsigned int i=0;i<2;i++)
    {
        QFileInfo tmpFileInfo=list.at(i);
        if((tmpFileInfo.isDir()))
        {
            QString fileName = tmpFileInfo.fileName();
            QListWidgetItem *tmp = new QListWidgetItem(ui->ListWidgetFile);
            MyListWidgetItem *widget = new MyListWidgetItem(ui->ListWidgetFile);
            tmp->setSizeHint(QSize(360,120));
            widget->setImageLabel(":/images/dir.png");
            widget->setTextLabel(fileName);
            widget->setIndex(i);
            ui->ListWidgetFile->setItemWidget(tmp, widget);

        }
        else if(tmpFileInfo.isFile())
        {
            QString fileName = tmpFileInfo.fileName();
            QListWidgetItem *tmp = new QListWidgetItem(ui->ListWidgetFile);
            MyListWidgetItem *widget = new MyListWidgetItem(ui->ListWidgetFile);
            tmp->setSizeHint(QSize(360,120));
            widget->setImageLabel(":/images/file.png");
            widget->setTextLabel(fileName);
            widget->setIndex(i);
            ui->ListWidgetFile->setItemWidget(tmp, widget);
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
