#include <Fl/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <Fl/Fl_Box.H>
#include <Fl/fl_draw.H>

#define window_size 400
static Fl_Double_Window *main_window = 0; // the main app window
static Fl_Offscreen offscreen_buffer = 0; // the offscreen surface

/*****************************************************************************/
/* This class provides a view to copy the offscreen surface to */
class canvas : public Fl_Box {
    void draw();
    int handle(int event);
    public:
    canvas(int x, int y, int w, int h);
};

/*****************************************************************************/
/* Constructor */
canvas::canvas(int x, int y, int w, int h) : Fl_Box(x,y,w,h)
{
} // Constructor

/*****************************************************************************/
void canvas::draw() 
{
    if(offscreen_buffer) { // offscreen exists
        // blit the required view from the offscreen onto the box
        fl_copy_offscreen(x(), y(), w(), h(), offscreen_buffer, 0,0);
    }
    else { // create the offscreen
        main_window->make_current(); //ensures suitable graphic context
        offscreen_buffer = fl_create_offscreen( w(), h() );
        if(!offscreen_buffer){fprintf(stderr,"Failed buffer creation"); exit(1);}
        fl_begin_offscreen(offscreen_buffer); /* Open the offscreen context */
        fl_color(FL_WHITE);
        fl_rectf(0, 0, w(), h() );
        fl_end_offscreen(); /* close the offscreen context */
        /* init screen with offscreen buffer */
        fl_copy_offscreen(x(), y(), w(), h(), offscreen_buffer, 0,0);
    }
} // draw method

/*****************************************************************************/
int canvas::handle(int event) 
{
    static char labeltext[100];
    int button,x,y;
    int retvalue = 0;
    static int x_old,y_old;
    static int push1st=0;
    if (!offscreen_buffer) return 1;
    retvalue = Fl_Box::handle(event);
    switch (event) {
        case FL_PUSH:
        case FL_DRAG:
            button = Fl::event_button();
            x = Fl::event_x();
            y = Fl::event_y();
    };
    switch ( button ) {
        case 1: // Left button
            sprintf(labeltext,"Last mouse button= Left | Mouse at %d,%d now",x,y);
            window()->label(labeltext);
            retvalue = 1;
            break;
        case 3: // Right button
            sprintf(labeltext,"Last mouse button= Right | Mouse at %d,%d now",x,y);
            window()->label(labeltext);
            retvalue = 1;
            break;
    }
    switch(event) {
        case FL_PUSH:
            if (push1st == 0) {
                x_old = x;
                y_old = y;
                push1st = 1;
                break;
            } else {
                push1st = 0;
                /* Open the offscreen context for drawing */
                fl_begin_offscreen(offscreen_buffer);
                if (button==1){ //left mouse button
                    fl_color(FL_RED);
                    fl_line(x_old,y_old,x,y);
                } else { //right mouse button
                    fl_draw_box(FL_BORDER_FRAME,x_old,y_old,(x-x_old),
                            (y-y_old),FL_BLUE);
                }
                fl_end_offscreen(); /* close the offscreen context */
                redraw();
            }
        case FL_DRAG:
            {push1st=0; //clear if dragging
                /* Open the offscreen context for drawing */
                fl_begin_offscreen(offscreen_buffer);
                fl_color(FL_BLACK);
                fl_point(x,y);
                fl_end_offscreen(); // close the offscreen context
                redraw();}
            break;
        default:
            redraw();
            break;
    }
    return retvalue;
} // handle

/*****************************************************************************/
int main (int argc, char **argv) 
{
    main_window = new Fl_Double_Window(window_size, window_size,
            "Drawing with mouse example");
    main_window->begin();
    // a view of the offscreen, inside the main window
    static canvas *os_box = new canvas(5,5,(window_size-10),(window_size-10));
    main_window->end();
    main_window->resizable(os_box);
    main_window->show(argc, argv);
    return Fl::run();
} // main
