#ifndef FILEVIEWER_H
#define FILEVIEWER_H

#include <QDialog>
#include <QFileInfoList>

namespace Ui {
class FileViewer;
}

class FileViewer : public QDialog
{
    Q_OBJECT

public:
    explicit FileViewer(QWidget *parent = 0);
    ~FileViewer();

protected:
    void showFileInfoList(QFileInfoList list);

private:
    Ui::FileViewer *ui;
};

#endif // FILEVIEWER_H
