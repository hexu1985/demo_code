#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Button.H>
#include <FL/names.h>

Fl_Window *win;
Fl_Browser *b;

class MyButton : public Fl_Button {
    static int count;
public:
    char linetext[100];
    MyButton(int x,int y,int w,int h,const char*l=0)
        :Fl_Button(x,y,w,h,l) {}
    int handle(int e) 
    {
        int ret = Fl_Button::handle(e);
        sprintf(linetext,"Button %s got event: %s, returns: %d ", \
                label(),fl_eventnames[e],ret);
        b->add(linetext);
        b->bottomline(32000); //always display the last line
        return(ret);
    }
};

int MyButton::count=0;

void but_a_cb(Fl_Widget* w, void* v)
{
    win->label("Button A callback!");
}

void but_b_cb(Fl_Widget* w, void* v)
{
    win->label("Button B callback!");
}

int main()
{
    win= new Fl_Window(530,350,"FLTK events example");
    win->begin();
    b = new Fl_Browser(140,20,win->w()-160, win->h()-50);
    b->type(FL_MULTI_BROWSER);
    MyButton but_a(10,20,100,25,"A");
    but_a.color(FL_BLUE);
    but_a.shortcut('a');
    but_a.callback(but_a_cb);
    MyButton but_b(10,60,100,25,"B");
    but_b.color(FL_GREEN);
    but_b.shortcut('b');
    but_b.callback(but_b_cb);
    win->end();
    win->show();
    return(Fl::run());
}
