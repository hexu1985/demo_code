#include "grab.h"
#include "exc.h"

/**Grabs the keyboard.
  */
Grab::Grab(Display *display, Window& window) : display(display), window(window)
{

	if (XGrabKeyboard(display,window,False,GrabModeAsync,GrabModeAsync,
		CurrentTime)!=GrabSuccess) throw grab_exception("could not grab keyboard");
}

/**Ungrabs the keyboard.
 */
Grab::~Grab()
{

	XUngrabKeyboard(display, CurrentTime);
}
