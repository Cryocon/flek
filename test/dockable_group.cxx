#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Group.H>
#include <Flek/Fl_App_Window.H>
#include <Flek/Fl_Dockable_Group.H>

#include <stdio.h>

void print_children (Fl_Group *o)
{
  printf (">> label=\"%s\" xywh=%d,%d,%d,%d\n", o->label(), o->x(), o->y(), o->w(), o->h());
  Fl_Widget*const* a = o->array();
  for (int i = o->children(); i--;) {
    Fl_Widget* o = *a++;
    printf ("   label=\"%s\" xywh=%d,%d,%d,%d\n", o->label(), o->x(), o->y(), o->w(), o->h());
  }
}

void
main ()
{
  Fl_App_Window *myapp = new Fl_App_Window (50, 50, 200, 200, 
					    "dockable_group test");
  myapp->resizable(myapp);
  myapp->show ();

  Fl_Dockable_Group *mygroup = new Fl_Dockable_Group (0, 0, 100, 30, "mygroup");

  mygroup->show ();

  myapp->add_dockable (mygroup);

  myapp->begin ();
  (void) new Fl_Button (5, 5, 100, 100, "Hello World");
  myapp->end ();

  //myapp->layout();
  
  print_children (myapp);
  print_children (mygroup);

  print_children (myapp->tpack());

  printf ("Entering Run Loop\n");
  Fl::run();  
}

