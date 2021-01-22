#ifndef SIGNALHANDLER_H
#define SIGNALHANDLER_H

#include <csignal>
#include <memory>

#include "eventhandler.h"

/**Handles signals.
 *
 * Signal handling is done by using patterns:
 * Singleton [GOF] and Adapter [GOF]
 *
 * @pattern Singleton
 * @pattern Adapter
 *
 * @link http://www.cs.wustl.edu/~schmidt/signal-patterns.html @endlink
 * */
class SignalHandler
{
public:
	EventHandler * registerHandler (int signum, EventHandler *eh);
	void removeHandler (int signum);

private:
	/**Adapter*/
	static void dispatcher (int signum);
	static EventHandler * handlers[NSIG];
};

#endif
