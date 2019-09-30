#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Box.H>

int main() 
{
    fl_register_images(); // initialize image lib
    Fl_Window win(500,400); // make a window
    Fl_Box box(10,10,500-20,400-20); // widget that will contain image
    Fl_PNG_Image png("jolly.png"); // load png image into ram
    box.image(png); // attach png image to box
    win.show();
    return(Fl::run());
}
