#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator *translator = new QTranslator;
    QString path;
    path = QApplication::applicationDirPath() + "/TestHello.qm";
    translator->load(path);
    a.installTranslator(translator);

    MainWindow w;
    w.show();
    
    return a.exec();
}
