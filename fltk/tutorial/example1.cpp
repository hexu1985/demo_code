#include <FL/Fl.H>
#include <FL/Fl_Window.H>

int main()
{
    // Create a window - width, height, label (=title)
    Fl_Window win(400, 400,"FLTK Tutorial - Example 1");
    // Display the window
    win.show();
    // Run and return
    return Fl::run();
}
