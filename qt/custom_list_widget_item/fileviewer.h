#ifndef FILEVIEWER_H
#define FILEVIEWER_H

#include <QDialog>

namespace Ui {
class FileViewer;
}

class FileViewer : public QDialog
{
    Q_OBJECT

public:
    explicit FileViewer(QWidget *parent = 0);
    ~FileViewer();

private:
    Ui::FileViewer *ui;
};

#endif // FILEVIEWER_H
