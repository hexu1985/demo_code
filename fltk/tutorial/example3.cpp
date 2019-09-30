#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>

void button1_cb(Fl_Widget* buttonptr)
{
    if (buttonptr->color() == FL_BLUE) {
        buttonptr->color(FL_RED); //toggle
    }else {
        buttonptr->color(FL_BLUE);//toggle
    }
}

int main(int argc, char **argv)
{
    // Create a window - width, height, label (=title)
    Fl_Window *win = new Fl_Window(340,180,"FLTK Tutorial - Example 3");
    win->color(FL_WHITE);
    // Begin adding children to this window
    win->begin();
    //Create a button - x , y , width, height, label
    Fl_Button *button1 = new Fl_Button(25,15,140,40,"Click me!");
    button1->color(FL_RED);
    //register callback function with this button
    button1->callback(button1_cb);
    // Stop adding children to this window
    win->end();
    // Display the window
    win->show();
    // Run and return
    return Fl::run();
}
