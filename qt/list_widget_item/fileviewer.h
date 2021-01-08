#ifndef FILEVIEWER_H
#define FILEVIEWER_H

#include <QDialog>
#include <QFileInfoList>
#include <QListWidgetItem>

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

public slots:
    void OnCurrentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void OnCurrentRowChanged(int currentRow);
    void OnItemClicked(QListWidgetItem *item);

private:
    Ui::FileViewer *ui;
};

#endif // FILEVIEWER_H
