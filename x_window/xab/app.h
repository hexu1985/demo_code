#ifndef APP_H
#define APP_H

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/Xos.h>
#include <X11/extensions/XTest.h>

#include "eventhandler.h"

#include <map>
#include <vector>
#include <string>

class App : public EventHandler
{
private:
	typedef std::vector<int> keycodes_t;
	typedef std::map<std::wstring, keycodes_t> abbreviations_t;
	typedef std::map<std::wstring, std::vector<std::wstring> > mappings_t;

private:
	Display *display;

	abbreviations_t abbreviations;
	mappings_t mappings;

	std::wstring input;

	keycodes_t output;
	int output_length;
	bool ready_to_send;
	sig_atomic_t ready_to_quit;

public:
	App();
	~App();

	std::wstring version()
	{
		return L" v0.6";
	}

	std::wstring XRecordVersion();

	void processEvent(XEvent &ev);

	Display* getDisplay()
	{
		return display;
	}

	bool quit()
	{
		return ready_to_quit;
	}

	void handle(int)
	{
		ready_to_quit = true;
	}

	void addAbb();
	void readAbb(std::wstring const& file);

	void addMap();
	void readMap(std::wstring const& file);

public:
	void forward_key_press(int keycode);
	void forward_key_release(int keycode);
	void send_key(int keycode);
	void send_text(keycodes_t const& text);

private: // helpers
	keycodes_t recode(std::wstring const& str);
};

#endif
