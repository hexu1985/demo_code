#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>

Fl_Input input1(90, 10, 180, 20, "Input : ");
Fl_Output output1(90, 40, 180, 20, "Output : ");

static void cb_input1(Fl_Input*, void* userdata) 
{
    input1.label((const char*)userdata);
    output1.value(input1.value());
    input1.value(""); //clear again
}

int main(int argc, char **argv) 
{
    Fl_Window win(300, 90, "Example for Input and Output boxes");
    win.begin();
    win.add(input1);
    input1.callback((Fl_Callback*)cb_input1,(void *)"Enter next:");
    input1.when(FL_WHEN_RELEASE | FL_WHEN_ENTER_KEY);
    win.add(output1);
    win.end();
    win.show();
    return Fl::run();
}
