#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Choice.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Menu_Bar.H>
#include <stdint.h>

#define FONT_SERIF 1
#define FONT_SANS_SERIF 2
#define FONT_MONOSPACE 3

static const char *save_xpm[] = {
    "16 16 9 1",
    " c None",
    ". c #000000",
    "+ c #0000FF",
    "@ c #000080",
    "# c #A0A0A0",
    "$ c #0000C0",
    "% c #FFFFFF",
    "& c #C0C0FF",
    "* c #DCDCDC",
    "................",
    ".+@##########@+.",
    ".$@%%%%%%%%%%@$.",
    ".+@%%%%%%%%%%@+.",
    ".+@%########%@+.",
    ".+@%%%%%%%%%%@+.",
    ".+@%########%@+.",
    ".+@&%%%%%%%%&@+.",
    ".++@@@@@@@@@@++.",
    ".++++++++++++++.",
    ".++$......@@$++.",
    ".++.******.+@++.",
    ".++.*@+***.+@++.",
    ".++.*@+***.+@++.",
    ".@+.******.+@++.",
    " ..............."};

class Toolbar : public Fl_Group {
public:
    Fl_Button *save1;
    Fl_Button *save2;
    Fl_Pixmap *p_save;
    Fl_Choice *font_group;
    Fl_Menu_Item *font_group_items;
    static void cb_save(Fl_Widget*, void*);
    static void cb_fonts(Fl_Widget*, void*);
    Toolbar(int Xpos, int Ypos, int Width, int Height);
};

void Toolbar::cb_save(Fl_Widget *w, void *data)
{
    fl_alert("Save Button %d pressed!", (int) reinterpret_cast<uint64_t>(data));
}

void Toolbar::cb_fonts(Fl_Widget *w, void *data)
{
    fl_alert("Font number %d selected!", (int) reinterpret_cast<uint64_t>(data));
}

Toolbar::Toolbar(int Xpos, int Ypos, int Width, int Height) :
    Fl_Group(Xpos, Ypos, Width, Height)
{
    box(FL_UP_BOX);
    Ypos += 2; Height -= 4; Xpos += 3; Width = Height;
    int i;
    save1 = new Fl_Button(Xpos, Ypos, Width, Height); Xpos += Width + 5;
    save2 = new Fl_Button(Xpos, Ypos, Width, Height); Xpos += Width + 5;
    font_group = new Fl_Choice(Xpos, Ypos, 110, Height); Xpos += 111;
    p_save = new Fl_Pixmap(save_xpm);
    save1->image(p_save);
    save2->image(p_save);
    save1->tooltip("Save file1");
    save1->callback(cb_save,(void*)1);
    save2->tooltip("Save file2");
    save2->callback(cb_save,(void*)2);
    font_group_items = new Fl_Menu_Item[4];
    for (i = 0; i < 4; i++) font_group_items[i].text = NULL;
    font_group_items->add("Serif", 0, cb_fonts, (void*) FONT_SERIF, 0);
    font_group_items->add("Sans-Serif", 0, cb_fonts,(void*) FONT_SANS_SERIF, 0);
    font_group_items->add("Monospace", 0, cb_fonts, (void*) FONT_MONOSPACE, 0);
    font_group->menu(font_group_items);
}

int main()
{
    Fl_Window win(500, 300,"FLTK Toolbar Example");
    win.color(FL_WHITE);
    win.begin();
    Fl_Menu_Bar menubar(0, 0, win.w(), 25);
    menubar.add("&File", 0, 0);
    menubar.add("&Edit", 0, 0);
    Toolbar tool(0,26,win.w(),30);
    tool.clear_visible_focus(); //just use mouse, no TABs
    win.end();
    win.show();
    return Fl::run();
}
