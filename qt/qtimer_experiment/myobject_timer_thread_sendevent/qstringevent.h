#ifndef QSTRING_EVENT_INC
#define QSTRING_EVENT_INC

#include <QEvent>
#include <QString>

class QStringEvent : public QEvent
{
private:
    QString mstr;

public:
    const static Type TYPE = static_cast<Type>(QEvent::User+0x10);
    explicit QStringEvent(QString s);
    QString str();
};

#endif
