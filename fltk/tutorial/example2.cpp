#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>

int main(int argc, char **argv)
{
    // Create a window - width, height, label (=title)
    Fl_Window *win = new Fl_Window(340,180,"FLTK Tutorial - Example 2");
    // Set color of window to white
    win->color(FL_WHITE);
    // Begin adding children to this window
    win->begin();
    //Create a button - x , y , width, height, label
    Fl_Button *button1 = new Fl_Button(25,15,140,40,"OK");
    // Set color of button to red
    button1->color(FL_RED);
    // Stop adding children to this window
    win->end();
    // Display the window
    win->show();
    // Run and return
    return Fl::run();
}
