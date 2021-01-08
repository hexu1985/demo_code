#ifndef FILEVIEWER_H
#define FILEVIEWER_H

#include <QDialog>
#include <QFileInfoList>
#include <QListWidgetItem> 
#include <vector>
#include "mylistwidgetitem.h"

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

    void OnCustomItemClicked(int index);

private:
    Ui::FileViewer *ui;
    std::vector<MyListWidgetItem *> widget_vector_;
    std::vector<QListWidgetItem *> item_vector_;
};

#endif // FILEVIEWER_H
