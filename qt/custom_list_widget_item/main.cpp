#include "fileviewer.h"
#include "mylistwidgetitem.h"
#include <QApplication>
#include <QTranslator>


int main( int argc, char **argv )
{
    QFont font("ZYSong18030",12);
    QApplication::setFont(font);
    	
    QApplication a( argc, argv );
    QTranslator translator(0);
    translator.load("fileviewer_zh",".");
    a.installTranslator(&translator);    
    
    FileViewer *fileviewer = new FileViewer();
    fileviewer->show();

#if 0
    MyListWidgetItem *widget = new MyListWidgetItem();
    widget->setText("aabbcc");
    widget->setImage(":/images/dir.png");
    widget->show();
#endif

    return a.exec();
}
