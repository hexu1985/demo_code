#include "qstringevent.h"

QStringEvent::QStringEvent(QString s) :
    QEvent(TYPE)
{
    mstr = s;
}

QString QStringEvent::str()
{
    return mstr;
}
