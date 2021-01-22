#ifndef NOTIFY_H
#define NOTIFY_H

class App;

/**A class with listens/grabs/records all Events
  of the X-Server and notifies the Application App.

  The only method to implement is run() which will
  be called endlessly.
  It is allowed to block there.

  RAII should be used for all resources used by Notify.
  */
class Notify
{
protected:
	App &app;
public:
	Notify (App &a);
	virtual ~Notify() = 0;

	/**Run notify process endless.
	  */
	virtual void run() = 0;
};

#endif
