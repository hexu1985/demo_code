#include <QApplication>
#include <QLabel>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    translator.load("hello.qm", ".");
    app.installTranslator(&translator);

    QLabel *label = new QLabel(QObject::tr("Hello Qt!"));
    label->show();
    return app.exec();
}
