#ifndef RECORDASYNCNOTIFY_H
#define RECORDASYNCNOTIFY_H

#include "notify.h"

class RecordAsyncNotify : public Notify
{
public:
	RecordAsyncNotify(App &app);
	~RecordAsyncNotify();

	void run();
};

#endif
