#include "app.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <cstdlib> // for mbstowcs
#include <X11/extensions/record.h> // for XRecordQueryVersion

using namespace std;

App::App() :
	ready_to_send(false),
	ready_to_quit(false)
{
	display = XOpenDisplay(0);

	if (display==0) throw "cannot open display";
}

App::~App()
{
	XCloseDisplay(display);
}

wstring App::XRecordVersion()
{
	int cmajor_return;
	int cminor_return;
	if (XRecordQueryVersion (display, &cmajor_return, &cminor_return))
	{
		wstring str;
		wstringstream ss;
		ss << cmajor_return << "." << cminor_return;
		return ss.str();
	} else return L"";
}

/**Store built-in Abbbreviations.

  @pre Make sure that Mappings are added first,
  otherwise it will be recoded to nothing.
  */
void App::addAbb()
{
	abbreviations[L"xab"] = recode(version());
}

/**Read all Abbbreviations in from a file.

  @pre Make sure that Mappings are added first,
  otherwise it will be recoded to nothing.
  */
void App::readAbb(std::wstring const& file)
{
	string sfile (file.begin(), file.end());
	wifstream ifs (sfile.c_str());

	wstring word;
	wstring rest;

	while (ifs >> word)
	{
		getline (ifs, rest);
		// trim(rest);
		abbreviations[word] = recode(rest);
	}
}

/**Add build in mappings for small latin letters and
  numbers.

  Everything added here can be overwritten by using
  readMap().
  */
void App::addMap()
{
	mappings[L" "].push_back(L"space");

	for (int i='a'; i<='z'; i++)
	{
		wstring toadd;
		toadd.push_back(i);

		mappings[toadd].push_back(toadd);
	}

	for (int i='0'; i<='9'; i++)
	{
		wstring toadd;
		toadd.push_back(i);

		mappings[toadd].push_back(toadd);
	}
}

/**Read in mappings from a file.
  */
void App::readMap(std::wstring const& file)
{
	string sfile(file.begin(), file.end());
	wifstream ifs (sfile.c_str());

	wstring letter;
	wstring word;
	wstring rest;

	while (ifs >> letter)
	{
		getline (ifs, rest);
		wstringstream ss(rest);

		while (ss >> word)
		{
			mappings[letter].push_back(word);
		}
	}
}

wstring event_type (int type)
{
	if (type == KeyPress)           return L"KeyPress";
	else if (type == KeyRelease)    return L"KeyRelea";
	else if (type == ButtonPress)   return L"BtnPress";
	else if (type == ButtonRelease) return L"BtnRelea";
	else if (type == MotionNotify)  return L"MotnNtfy";
	else return L"UnknownType";
}

/**Will be called whenever a new XEvent occurs.

  You are allowed to generate any XEvents
  within.

  Here you are allowed to send XEvents or XFakeKeys.
  See send_key(), forward_key_release() and forward_key_press()
  to do so.

  The event itself will be forwarded by Notify.
  */
void App::processEvent(XEvent &ev)
{
	int len;
	char cbuf[10];
	wchar_t wbuf[1];
	size_t wret;

	KeySym ks;

	if (ev.type != KeyPress && ev.type != KeyRelease) return;

	len= XLookupString(&ev.xkey,cbuf,9,&ks,0);

#ifdef DEBUG
	wcout << "got " << ev.xkey.keycode
		<< "\tstate: " << ev.xkey.state
		<< "\tcbuf: " << cbuf
		<< endl;
#endif

	switch (ks)
	{
	case XK_Escape: case XK_Clear:
#ifdef DEBUG
			wcout << "clear input because of esc" << endl;
#endif
		input.clear();
		break;
	case XK_Delete: case XK_BackSpace:
		if (ev.type == KeyRelease) break;

		if (input.length()>0) input.resize(input.length()-1);
		break;
	case XK_Linefeed: case XK_Return: case XK_space: case XK_Tab:
		if (ev.type == KeyRelease)
		{
			if (!output.empty()) ready_to_send = true;
			break;
		}

		{
			abbreviations_t::iterator it;
			it = abbreviations.find(input);
			if (it != abbreviations.end())
			{
				output = abbreviations[input];
				output_length = input.length()+1;
			}
		}

		input.clear();
		break;
	default:
		if (ev.type == KeyRelease) break;

		wret = mbstowcs (wbuf, cbuf, 1);
		if (wret == (size_t) -1) break;
		if (wbuf[0] == L'\0')
		{
#ifdef DEBUG
			wcout << "clear input because of wbuf" << endl;
#endif
			input.clear();
			break;
		}

		input += wbuf[0];
#ifdef DEBUG
		wcout << "input: " << input << endl;
#endif
		break;
	}

	if (ready_to_send)
	{
#ifdef DEBUG
		wcout << "Will send text" << endl;
#endif
		for (int i=0; i<output_length; i++)
		{
			send_key(XKeysymToKeycode(display, XK_BackSpace));
		}
		send_text(output);

		output.clear();
		ready_to_send = false;

		send_key(ev.xkey.keycode);
	}
}

/**Forward a key press event.
  */
void App::forward_key_press(int keycode)
{
#ifdef DEBUG
	wcout << "fake press: " << keycode << endl;
#endif
	XTestFakeKeyEvent(display, keycode, True, CurrentTime);
	XFlush(display);
}

/**Forward a key release event.
  */
void App::forward_key_release(int keycode)
{
#ifdef DEBUG
	wcout << "fake release: " << keycode << endl;
#endif
	XTestFakeKeyEvent(display, keycode, False, CurrentTime);
	XFlush(display);
}

/**Send a single key.
  */
void App::send_key(int keycode)
{
	XTestFakeKeyEvent(display, keycode, True, CurrentTime);
	XFlush(display);
	XTestFakeKeyEvent(display, keycode, False, CurrentTime);
	XFlush(display);
}

/*
void App::send_key(int keycode)
{
	ev.xkey.keycode = keycode;
	XSendEvent(display, PointerWindow, true, KeyPressMask, &ev );
}
*/

void App::send_text(vector<int> const& keycodes)
{
	for (size_t i=0; i<keycodes.size(); i++)
	{
		send_key(keycodes[i]);
	}
}

/**Recode a wstring to a vector of keycodes.
 
 @param str a wstring with characters defined in the mappings
 which should be recoded.
 @return keycodes which can be send so that the user will
 see str afterwards.
 */
App::keycodes_t App::recode(std::wstring const& str)
{
	keycodes_t ret;
	for (size_t i = 1; i<str.length(); i++)
	{
		wstring letter;
		letter += str[i];

		vector<wstring> names = mappings[letter];

		for (size_t i = 0; i<names.size(); i++)
		{
			string str (names[i].begin(), names[i].end());
			int keys = XStringToKeysym(str.c_str());
			ret.push_back(XKeysymToKeycode(display, keys));
		}
	}

	return ret;
}
