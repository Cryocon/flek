#include <stdio.h>

#include <FL/Fl.H>
#include <Flek/Fl_App_Window.H>
#include <Flek/Fl_Dockable_Group.H>

void print_children(Fl_Group* o) {
  printf(">> label=\"%s\" xywh=%d,%d,%d,%d\n", o->label(), o->x(), o->y(), o->w(), o->h());
  Fl_Widget* const* a = o->array();
  for(int i = o->children(); i--;) {
    Fl_Widget* o = *a++;
    printf ("   label=\"%s\" xywh=%d,%d,%d,%d\n", o->label(), o->x(), o->y(), o->w(), o->h());
  }
}

void main() {
  // Create an application window.
  Fl_App_Window* application_window = new Fl_App_Window(200, 200, "dockable_group");

  // Make it resizable.
  application_window->resizable(application_window);

  // Add a button to the application window.
  // This actually adds the button to the "contents" child window.
  new Fl_Button(10, 10, 100, 30, "Hello World");

  // We are done adding widgets to the application window.
  application_window->end();

  // Create a dockable window.
  Fl_Dockable_Group* dockable_window = new Fl_Dockable_Group(0, 0, 200, 30, "group");

  // Add a couple of buttons to the dockable window.
  new Fl_Button(0, 0, 75, 30, "View");
  new Fl_Button(75, 0, 75, 30, "About");

  // Dock it to the application window.
  application_window->add_dockable(dockable_window);

  // Print some diagnostics.
  print_children(application_window);
  print_children(dockable_window);
  print_children(application_window->tpack());

  // Show the application window.
  // This automatically shows any docked windows.
  application_window->show();

  Fl::run();  
}
