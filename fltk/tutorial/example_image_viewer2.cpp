#include <stdio.h>
#include <stdlib.h>
#include <FL/Fl.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Box.H>

#define JPGFILE "jolly.jpg"

int main() 
{
    fl_register_images();
    Fl_Double_Window win(520,400,"Example image viewer with scrollbars");
    Fl_Scroll scr(0,0,520,400);
    Fl_JPEG_Image jpg(JPGFILE);
    if ( jpg.h() == 0 ) { perror(JPGFILE); exit(1); } // error check
    Fl_Box box(0,0,jpg.w(),jpg.h());
    box.image(jpg);
    win.resizable(win);
    win.show();
    return(Fl::run());
}
