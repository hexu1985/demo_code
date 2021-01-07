#include "fileviewer.h"
#include "ui_fileviewer.h"

FileViewer::FileViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileViewer)
{
    ui->setupUi(this);
}

FileViewer::~FileViewer()
{
    delete ui;
}
