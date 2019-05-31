/***************************************************************
  按钮事件例子
 ***************************************************************/
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/fl_ask.H>
void Btn01_cb(Fl_Widget *w, void *data)
{
    ((Fl_Button *)w)->label((char *)data);
    fl_alert("Hello");
}
int main(int argc, char **argv)
{
    char *buff ="Hello";
    Fl_Window* w = new Fl_Window(272, 144);
    Fl_Button* Btn01 = new Fl_Button(85, 50, 105, 25, "&Test callback");
    Btn01->shortcut(FL_ALT+'t'); //定义按钮的快捷键
    Btn01->callback((Fl_Callback*)Btn01_cb,buff); //调用处理函数 buff作为参数
    w->end();
    w->show(argc, argv);
    return Fl::run();
}
