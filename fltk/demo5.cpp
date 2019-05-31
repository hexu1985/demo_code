#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/fl_ask.H>
class EnterButton : public Fl_Button
{
    int handle(int e)
    {
        switch (e)
        {
            case FL_ENTER:
                color(FL_GREEN);
                labelsize(18);
                redraw();
                return 1;
            case FL_LEAVE:
                color(FL_GRAY);
                labelsize(18);
                redraw();
                return 1;
            default: return Fl_Button::handle(e);
        }
    }
    public:
    EnterButton(int x, int y, int w, int h, const char *l ) : Fl_Button(x,y,w,h,l) {}
};

static void cb(Fl_Widget* s, void *data)
{
    fl_alert( "Hello World!" );
}

int main(int argc, char **argv)
{
    Fl_Window* w = new Fl_Window(130, 50);
    EnterButton *eBtn = new EnterButton(25,50,120,25,"HelloWorld");
    eBtn->callback((Fl_Callback*)cb);
    w->end();
    w->show(argc, argv);
    return Fl::run();
}
