#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Text_Editor.H>

int main() 
{
    Fl_Window *win = new Fl_Window(400, 200);
    Fl_Text_Buffer *buff = new Fl_Text_Buffer();
    Fl_Text_Editor *disp = new Fl_Text_Editor(20, 20, 360, 160, "Editor Window");
    disp->buffer(buff);
    win->resizable(*disp);
    win->show();
    buff->text("FLTK Tutorial"); //add initial text here if required
    return(Fl::run());
}
