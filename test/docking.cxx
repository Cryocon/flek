#include <stdio.h>

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <Flek/Fl_App_Window.H>
#include <Flek/Fl_Dockable_Window.H>

void print_children(Fl_Group* o) {
  printf(">> label=\"%s\" xywh=%d,%d,%d,%d\n", o->label(), o->x(), o->y(), o->w(), o->h());
  Fl_Widget* const* a = o->array();
  for(int i = o->children(); i--;) {
    Fl_Widget* o = *a++;
    printf ("   label=\"%s\" xywh=%d,%d,%d,%d\n", o->label(), o->x(), o->y(), o->w(), o->h());
  }
}

Fl_App_Window* application_window;

Fl_Dockable_Window* new_dockable(const char* label, unsigned char grippertype) {
  Fl_Dockable_Window* dw = new Fl_Dockable_Window(0, 0, 200, 30, "Dockable Window");
  dw->grippertype(grippertype);
  new Fl_Button(0, 0, 100, 30, label);
  dw->end();
  return dw;
}

void new_dockable(Fl_Widget* w, void* d) {
  Fl_Dockable_Window* dw = new_dockable("New Dragable", FL_DRAGABLE);
  application_window->add_dockable(dw);
}

void main() {
  // Create an application window.
  application_window = new Fl_App_Window(200, 200, "Application Window");

  // Make it resizable.
  application_window->resizable(application_window);

  // Add a button to the application window.
  // This actually adds the button to the "contents" child window.
  Fl_Button* b = new Fl_Button(10, 10, 100, 30, "New Dockable");
  b->callback(new_dockable);

  // We are done adding widgets to the application window.
  application_window->end();

  Fl_Dockable_Window* dw;
  dw = new_dockable("Dragable", FL_DRAGABLE);
  application_window->add_dockable(dw);
  dw = new_dockable("Shovable", FL_SHOVABLE);
  application_window->add_dockable(dw);
  dw = new_dockable("Drag/Shov", FL_DRAGABLE | FL_SHOVABLE);
  application_window->add_dockable(dw);
  dw = new_dockable("Fixed", 0);
  application_window->add_dockable(dw);

  // Show the application window.
  // This automatically shows any docked windows.
  application_window->show();


#if 0
  // Enable this section of code to demonstrate 
  // how docking authorization can be denied for
  // a particular dockable window.

  // Create another dockable window, but don't dock this one.
  Fl_Dockable_Window* dockable_window2 = new Fl_Dockable_Window(0, 0, 200, 30, "Dockable");

  // Add a widgets to it.
  new Fl_Box(10, 10, 100, 20, "Not Dockable");

  dockable_window2->clear_border();

  // Done adding widgets to the second dockable window.
  dockable_window2->end();

  // Explicitly show this dockable window since it isn't docked to any
  // application window.
  dockable_window2->show();
#endif


#if 0
  // Enable this section of code to demonstrate 
  // how docking authorization can be denied for
  // a particular application window.

  // Create another application window.
  Fl_App_Window* non_dockable = new Fl_App_Window(200, 200, "Not Dockable");
  non_dockable->show();
#endif

  // Print some diagnostics.
  print_children(application_window);
  print_children(application_window->tpack());

  Fl::run();  
}
