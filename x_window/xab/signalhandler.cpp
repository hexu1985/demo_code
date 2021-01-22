#include "signalhandler.h"

EventHandler  *SignalHandler::handlers[NSIG];

EventHandler * SignalHandler::registerHandler (int signum, EventHandler *handler)
{
	if (signum < 0 || signum > NSIG) throw SignalHandlerException();
	EventHandler *oldHandler = SignalHandler::handlers[signum];
	SignalHandler::handlers[signum] = handler;

	//Register dispatcher to handle signum
	struct sigaction sa;
	sa.sa_handler = dispatcher;
	sigemptyset (&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction (signum, &sa, 0);

	return oldHandler;
}

void SignalHandler::removeHandler (int signum)
{
	//Unregister dispatcher to handle signum
	struct sigaction sa;
	sa.sa_handler = SIG_DFL;
	sigemptyset (&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction (signum, &sa, 0);
}

void SignalHandler::dispatcher (int signum)
{
	if (SignalHandler::handlers[signum] != 0)
	{
		SignalHandler::handlers[signum]->handle (signum);
	}
}

