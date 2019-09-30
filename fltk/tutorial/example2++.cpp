#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>

class MyWindow : public Fl_Window {
public:
    MyWindow(int width, int height, const char* title=0) :
        Fl_Window(width,height,title)
    {
        // Set color of window to white
        color(FL_WHITE);
        // Begin adding children to this window
        begin();
        //Create a button - x , y , width, height, label
        Fl_Button *button1 = new Fl_Button(25,15,140,40,"OK");
        // Set color of button to red
        button1->color(FL_RED);
        // Stop adding children to this window
        end();
        // Display the window
        show();
    }
};

int main()
{
    // Create a window with our new class - width, height, label (=title)
    MyWindow win(340,180,"FLTK Tutorial - Example 2++");
    // Run and return
    return Fl::run();
}
