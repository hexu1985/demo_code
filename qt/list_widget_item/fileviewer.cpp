#include <QDir>
#include <QString>
#include <QListWidgetItem>
#include "fileviewer.h"
#include "ui_fileviewer.h"
#include <iostream>

FileViewer::FileViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileViewer)
{
    ui->setupUi(this);

    QString root = "/";
    QDir rootDir(root);	
    QStringList string;
    string << "*" ; 	
    QFileInfoList list=rootDir.entryInfoList (string);
    showFileInfoList(list);

    connect(ui->ListWidgetFile,SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),this,SLOT(OnCurrentItemChanged(QListWidgetItem *, QListWidgetItem *)));
    connect(ui->ListWidgetFile,SIGNAL(currentRowChanged(int)),this,SLOT(OnCurrentRowChanged(int)));
    connect(ui->ListWidgetFile,SIGNAL(itemClicked(QListWidgetItem * )),this,SLOT(OnItemClicked(QListWidgetItem *)));
}

FileViewer::~FileViewer()
{
    delete ui;
}

void FileViewer::showFileInfoList(QFileInfoList list)
{
    ui->ListWidgetFile->clear();
    for(unsigned int i=0;i<list.count();i++)
    {
        QFileInfo tmpFileInfo=list.at(i);
        if((tmpFileInfo.isDir()))
        {
            QIcon icon(":/images/dir.png");
            QString fileName=tmpFileInfo.fileName();
            QListWidgetItem *tmp=new QListWidgetItem (icon,fileName);
            ui->ListWidgetFile->addItem(tmp);

        }
        else if(tmpFileInfo.isFile())
        {
            QIcon icon(":/images/file.png");
            QString fileName=tmpFileInfo.fileName();
            QListWidgetItem *tmp=new QListWidgetItem (icon,fileName);
            ui->ListWidgetFile->addItem(tmp);
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
