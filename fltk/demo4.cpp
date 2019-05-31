#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_ask.H>
void Btn01_cb(Fl_Widget *w, void *data)
{
	fl_alert("Hello");
}
int main(int argc, char **argv)
{
	char *buff = "Hello";
	Fl_Window* w = new Fl_Window(272, 144);
	Fl_Button* Btn01 = new Fl_Button(85, 50, 105, 25, "&Test callback");
	Btn01->shortcut(FL_ALT + 't');
	Btn01->callback((Fl_Callback*) Btn01_cb, buff);
	Btn01->when(FL_WHEN_RELEASE_ALWAYS);
	w->end();
	w->show(argc, argv);
	return Fl::run();
}
