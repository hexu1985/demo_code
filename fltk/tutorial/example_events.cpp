#include <FL/Fl_Window.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>

Fl_Window* win;

class EventWindow: public Fl_Box
{
private:
    int handle_key(int e,int key);
public:
    EventWindow(int t, int l, int width, int height);
    int handle(int e);
};

EventWindow::EventWindow(int t, int l, int width, int height)
    :Fl_Box(FL_UP_BOX, t, l, width, height, "")
{ 
    labelfont(FL_ITALIC);
    labelsize(24);
    labeltype(FL_SHADOW_LABEL);
    label("OnMouseOver");
    Fl::focus(this);
}

int EventWindow::handle(int e)
{
    switch(e) {
        case FL_ENTER:
            color (FL_RED);
            labelcolor(FL_BLACK);
            damage(1);
            return 1;
        case FL_LEAVE:
            color(FL_GRAY);
            labelcolor(FL_BLACK);
            damage(1);
            return 1;
        case FL_KEYDOWN:
            return handle_key(e,Fl::event_key());
        default:
            return Fl_Box::handle(e);
    };
}

int EventWindow::handle_key(int e,int key)
{
    char labeltext[20];
    sprintf(labeltext,"Key entered: %c ",key);
    win->label(labeltext);
    return 1;
}

int main()
{
    win = new Fl_Window(300, 200);
    win->color(FL_BLUE);
    EventWindow ewin(20, 20, 260, 160);
    ewin.show();
    win->end();
    win->show();
    return Fl::run();
}
