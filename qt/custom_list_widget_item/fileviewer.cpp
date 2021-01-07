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
//    for(unsigned int i=0;i<2;i++)
    {
        QFileInfo tmpFileInfo=list.at(i);
        if((tmpFileInfo.isDir()))
        {
            QString fileName = tmpFileInfo.fileName();
            QListWidgetItem *tmp = new QListWidgetItem(ui->ListWidgetFile);
            MyListWidgetItem *widget = new MyListWidgetItem(ui->ListWidgetFile);
            tmp->setSizeHint(QSize(360,120));
            widget->setImage(":/images/dir.png");
            widget->setText(fileName);
            ui->ListWidgetFile->setItemWidget(tmp, widget);

        }
        else if(tmpFileInfo.isFile())
        {
            QString fileName = tmpFileInfo.fileName();
            QListWidgetItem *tmp = new QListWidgetItem(ui->ListWidgetFile);
            MyListWidgetItem *widget = new MyListWidgetItem(ui->ListWidgetFile);
            tmp->setSizeHint(QSize(360,120));
            widget->setImage(":/images/file.png");
            widget->setText(fileName);
            ui->ListWidgetFile->setItemWidget(tmp, widget);
        }
    }
}
