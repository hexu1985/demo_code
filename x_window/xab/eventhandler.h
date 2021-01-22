#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <csignal>
#include <cassert>

class EventException
{};

class SignalHandlerException
{};

/**Eventhandler for Hook Method [Pree].
 *
 * Is a interface with a pure virtual function to handle a
 * request (here it will be triggered by signals.
 *
 * @pattern HookMethod decouples from registration logic
 *
 * [Pree]  Wolfgang Pree, Design Patterns for Object-Oriented
 * 	Software Development, Addison-Wesley, Reading, MA, 1994.
 * */
class EventHandler
{
public:
	virtual void handle (int) = 0;
};

#endif
