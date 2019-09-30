#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>

int main(int argc, char *argv[]) 
{
    Fl_Window *win = new Fl_Window(400,200,"Tabs Example");
    {
        Fl_Tabs *tabs = new Fl_Tabs(10,10,400-20,200-20);
        {
            // A tab
            Fl_Group *aaa = new Fl_Group(10,35,400-20,200-45,"A-Buttons");
            {
                Fl_Button *b1 = new Fl_Button(50, 60,90,25,"Button A1");
                b1->color(88+1);
                Fl_Button *b2 = new Fl_Button(50, 90,90,25,"Button A2");
                b2->color(88+2);
                Fl_Button *b3 = new Fl_Button(50,120,90,25,"Button A3");
                b3->color(88+3);
            }
            aaa->end();
            // B tab
            Fl_Group *bbb = new Fl_Group(10,35,400-10,200-35,"B-Buttons");
            {
                Fl_Button *b1 = new Fl_Button( 50,60,90,25,"Button B1");
                b1->color(88+1);
                Fl_Button *b2 = new Fl_Button(150,60,90,25,"Button B2");
                b2->color(88+3);
                Fl_Button *b3 = new Fl_Button(250,60,90,25,"Button B3");
                b3->color(88+5);
            }
            bbb->end();
        }
        tabs->end();
    }
    win->end();
    win->show();
    return(Fl::run());
}
