#include <QDir>
#include <QString>
#include <QListWidgetItem>
#include "fileviewer.h"
#include "ui_fileviewer.h"
#include "mylistwidgetitem.h"

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
