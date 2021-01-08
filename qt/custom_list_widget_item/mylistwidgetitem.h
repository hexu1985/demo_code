#ifndef MYLISTWIDGETITEM_H
#define MYLISTWIDGETITEM_H

#include <QWidget>
#include <QString>

namespace Ui {
class MyListWidgetItem;
}

class MyListWidgetItem : public QWidget
{
    Q_OBJECT

public:
    explicit MyListWidgetItem(QWidget *parent = 0);
    ~MyListWidgetItem();

    void setImageLabel(QString image_path);
    void setTextLabel(QString str);

    void setIndex(int index);
    int getIndex() const;

private:
    Ui::MyListWidgetItem *ui;
    int index_;
};

#endif // MYLISTWIDGETITEM_H
