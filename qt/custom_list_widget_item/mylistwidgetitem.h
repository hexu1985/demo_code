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

    void setImage(QString image_path);
    void setText(QString str);

private:
    Ui::MyListWidgetItem *ui;
};

#endif // MYLISTWIDGETITEM_H
