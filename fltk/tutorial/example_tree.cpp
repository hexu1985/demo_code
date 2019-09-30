#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Tree.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Browser.H>
#include <FL/fl_message.H>

Fl_Double_Window* win = new Fl_Double_Window(645, 414,"Tree widget example");
Fl_Tree* tree = new Fl_Tree(25, 25, 275, 260);
Fl_Browser *b;

/**
  Assign user icons to the items
  */
void AssignUserIcons() {
    static const char *L_folder_xpm[] = {
        "11 11 3 1",
        ". c None",
        "x c #d8d833",
        "@ c #808011",
        "...........",
        ".....@@@@..",
        "....@xxxx@.",
        "@@@@@xxxx@@",
        "@xxxxxxxxx@",
        "@xxxxxxxxx@",
        "@xxxxxxxxx@",
        "@xxxxxxxxx@",
        "@xxxxxxxxx@",
        "@xxxxxxxxx@",
        "@@@@@@@@@@@"};
    static Fl_Pixmap L_folderpixmap(L_folder_xpm);
    static const char *L_document_xpm[] = {
        "11 11 3 1",
        ". c None",
        "x c #d8d8f8",
        "@ c #202060",
        ".@@@@@@@@@.",
        ".@xxxxxxx@.",
        ".@xxxxxxx@.",
        ".@xxxxxxx@.",
        ".@xxxxxxx@.",
        ".@xxxxxxx@.",
        ".@xxxxxxx@.",
        ".@xxxxxxx@.",
        ".@xxxxxxx@.",
        ".@xxxxxxx@.",
        ".@@@@@@@@@."};
    static Fl_Pixmap L_documentpixmap(L_document_xpm);
    // Assign user icons to tree items
    for ( Fl_Tree_Item *item = tree->first(); item; item=item->next())
        // Assign custom icons
        item->usericon(item->has_children() ? &L_folderpixmap : &L_documentpixmap);
    //item->usericon(0); // Don't assign custom icons
    tree->redraw();
}

void tree_cb(Fl_Tree* w, void*)
{
    Fl_Tree *tree = (Fl_Tree*)w;
    // Find item that was clicked
    Fl_Tree_Item *item = (Fl_Tree_Item*)tree->item_clicked();
    if ( item->is_selected() ) { //item is already selected
    } else { //click on additional item
        tree->select(item); // select this one too
    }
    AssignUserIcons(); //includes tree->redraw();
}

//Now the button callbacks for four buttons
void button_pathname_cb(Fl_Widget*)
{
    char pathname[256];
    Fl_Tree_Item *item = tree->first_selected_item();
    if ( !item ) { fl_message("No item was selected"); } else {
        tree->item_pathname(pathname, sizeof(pathname), item);
        fl_message("Pathname for '%s' is: \"%s\"", (item->label() ? item->label() : \
                    "???"), pathname);
    }
}

void button_copy_cb(Fl_Widget*)
{
    char linetext[100];
    for ( Fl_Tree_Item *item = tree->first(); item; item = tree->next(item))
    {
        if ( item->is_selected()) {
            sprintf(linetext,"Item selected: '%s'\n", item->label());
            b->add(linetext);
            b->bottomline(32000); //always display the last line
        }
    }
}

void button_select_group_cb(Fl_Widget*)
{
    Fl_Tree_Item *item = (Fl_Tree_Item*)tree->first_selected_item();
    if (item->has_children()) {
        tree->select_all(item);
        tree->deselect(item,0); //do not select the folder itself
        //2nd parameter=0 - no callback triggered
        AssignUserIcons(); //includes tree->redraw();
    } else {
        fl_message("Please select just a folder first!");
        return;
    }
}

void button_deselect_cb(Fl_Widget*)
{
    tree->deselect_all(0,0); //2nd parameter=0 - no callback triggered
    AssignUserIcons(); //includes tree->redraw();
}

int main(int argc, char **argv)
{
    // Create tree and add items
    tree->add("Cars/Chevrolet");
    tree->add("Cars/Mercedes Benz");
    tree->add("Cars/Volvo");
    tree->add("Cars/Toyota");
    tree->add("Motorcycles/Harley Davidson");
    tree->add("Motorcycles/Honda");
    tree->add("Motorcycles/Suzuki");
    tree->close("/Motorcycles");
    tree->selectmode(FL_TREE_SELECT_MULTI); // Multiple Items
    tree->callback((Fl_Callback*)tree_cb);
    tree->end();
    //Create buttons and define callbacks
    Fl_Button *button_pathname = new Fl_Button(25,300,120,30,"Show pathname");
    button_pathname->color(FL_GREEN);
    button_pathname->callback(button_pathname_cb);
    Fl_Button *button_select_group = new Fl_Button(180,300,120,30,"Select group");
    button_select_group->color(FL_GREEN);
    button_select_group->callback(button_select_group_cb);
    Fl_Button *button_copy = new Fl_Button(25,350,120,30,"Copy selected");
    button_copy->color(FL_GREEN);
    button_copy->callback(button_copy_cb);
    Fl_Button *button_deselect = new Fl_Button(180,350,120,30,"Deselect all");
    button_deselect->color(FL_GREEN);
    button_deselect->callback(button_deselect_cb);
    //Create browser window
    b = new Fl_Browser(340,25,260,355);
    b->type(FL_MULTI_BROWSER);
    win->end();
    // Display the window
    win->show();
    AssignUserIcons(); //includes tree->redraw();
    // Run and return
    return Fl::run();
}
