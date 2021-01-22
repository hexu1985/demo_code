#include "app.h"
#include "notify.h"

#include "grabnotify.h"
#include "recordnotify.h"
#include "recordasyncnotify.h"

#include "signalhandler.h"

#include <iostream>
#include <locale>
#include <memory>

using namespace std;


int main(int argc, char**argv) try
{
	locale::global(locale(""));

	string argument;
	if (argc == 2)
	{
		argument = argv[1];
	} else argument = "--xrecord-async";

	if (argument == "--help")
	{
		cout << "Generic options:" << endl;
		cout << "  --help            you are viewing it" << endl;
		cout << "  --version         display version number" << endl;
		cout << endl;
		cout << "Method options:" << endl;
		cout << "  --xrecord         uses the XRecord extension in an" << endl;
		cout << "                    synchron  way to  receive  input" << endl;
		cout << "                    Default  if xrecord is available" << endl;
		cout << "  --xrecord-async   uses the XRecord extension in an" << endl;
		cout << "                    asynchronic way to receive input" << endl;
		cout << "  --grab            uses a  window  which  grabs all" << endl;
		cout << "                    keyboard events." << endl;
		cout << "                    Default if x-ext isn't available" << endl;
		cout << endl;

		return 0;
	}

	App app;

	SignalHandler sig;
	sig.registerHandler (SIGHUP, &app);
	sig.registerHandler (SIGINT, &app);
	sig.registerHandler (SIGQUIT, &app);
	sig.registerHandler (SIGTERM, &app);

	if (argument == "--version")
	{
		wcout << app.version() << endl;
		wcout << "X-Record Version: " << app.XRecordVersion() << endl;

		return 0;
	}

	app.addMap();
	app.readMap(L".xmap");

	app.addAbb();
	app.readAbb(L".xab");

	auto_ptr<Notify> notify;

	if (app.XRecordVersion() == L"" || argument == "--grab")
	{
		wcout << "Using Grab Notify" << endl;
		notify.reset(new GrabNotify(app));
	} else if (argument == "--record-async") {
		wcout << "Using Record Async Notify" << endl;
		notify.reset(new RecordAsyncNotify(app));
	} else {
		wcout << "Using Record Notify" << endl;
		notify.reset(new RecordNotify(app));
	}

	notify->run();

	return 0;
}
catch (const char * msg)
{
	cerr << msg << endl;
	return 1;
}
