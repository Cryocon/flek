#include <FL/Fl.H>
#include <Flek/Fl_App_Window.H>
#include <Flek/Fl_Dockable_Group.H>

// sample application

void
main ()
{
  Fl_App_Window *myapp = new Fl_App_Window (50, 50, 200, 200, "My First Application!");
  myapp->show ();
  Fl_Dockable_Group *mygroup = new Fl_Dockable_Group (0, 0, 200, 30, "menu");
  mygroup->show ();

  myapp->add_dockable (mygroup);

  Fl_Button *button = new Fl_Button (5, 5, 100, 100, "Hello World");
  myapp->add (button);
  
  Fl::run();  
}

