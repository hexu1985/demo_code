#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>

Fl_Window* win;
void Menu_CB_Open(Fl_Widget* w,void*) {win->label("Open selected");}
void Menu_CB_Save(Fl_Widget* w,void*) {win->label("Save selected");}
void Menu_CB_Quit(Fl_Widget* w,void*) {win->label("Quit selected");}
void Menu_CB_Help(Fl_Widget* w,void*) {win->label("Help selected");}

int main() 
{
    // Open the application window and menu bar with callbacks
    win = new Fl_Window(420, 280);
    win->color(FL_WHITE);
    Fl_Menu_Bar menubar(0, 0, win->w(), 25);
    menubar.add("&File/&Open", 0, Menu_CB_Open);
    menubar.add("&File/&Save", 0, Menu_CB_Save);
    menubar.add("&File/&Quit", 0, Menu_CB_Quit);
    menubar.add("&Help", 0, Menu_CB_Help);
    win->end();
    win->show();
    return(Fl::run());
}
