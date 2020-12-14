#include <QApplication>
#include "dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog d;
    d.show();
#if 0
    Widget w;
    w.show();
#endif

    return a.exec();
}
