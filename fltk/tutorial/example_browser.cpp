#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Browser.H>

void browser_cb(Fl_Widget *w) 
{
    Fl_Browser *b = (Fl_Browser*)w; //cast to get access to Browser methods
    // retrieve selected item from browser
    int index = b->value();
    // add text to browser using the retrieved index number
    if ( index == 1 ) {
        b->add("You selected Line1");
    } else if ( index == 2 ) {
        b->add("You selected Line2");
    } else if ( index == 3 ) {
        b->add("You selected Line3");
    }
}

int main() 
{
    Fl_Window *win = new Fl_Window(300,200,"Browser Example");
    Fl_Browser *b = new Fl_Browser(10,40,win->w()-20, win->h()-50);
    b->type(FL_MULTI_BROWSER);
    b->add("Line1");
    b->add("Line2");
    b->add("Line3");
    b->callback(browser_cb);
    win->show();
    return(Fl::run());
}
