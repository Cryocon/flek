#include <FL/Fl.H>
#include <stdio.h>

#include <Flek/Fl_App_Window.H>

Fl_App_Window::Fl_App_Window (int x, int y, int w, int h, const char *l = 0) : 
  Fl_Window (x, y, w, h, l)
{
  pack = new Fl_Pack_Fu (0, 0, w, h);
  pack->type (Fl_Pack_Fu::VERTICAL);
  contents = new Fl_Window (0, 0, w, h);
  contents->box(FL_BORDER_BOX);
  pack->add (contents);
  begin ();
}

Fl_App_Window::Fl_App_Window (int w, int h, const char *l = 0) : 
  Fl_Window (w, h, l)
{
  pack = new Fl_Pack_Fu (0, 0, w, h);
  pack->type (Fl_Pack_Fu::VERTICAL);
  contents = new Fl_Window (0, 0, w, h);
  contents->box(FL_BORDER_BOX);
  pack->add (contents);
  begin ();
}

int 
Fl_App_Window::handle (int event)
{  
  if (event == FL_UNDOCK)
    {
      //pack->draw ();
      //redraw();
      //if ((w() != pack->w()) || (h() != pack->h()))
      //size (pack->w(), pack->h());
      //damage (FL_DAMAGE_ALL);
      redraw ();
      return 1;
    }
  
  if (event == FL_DOCK)
    {
      int dx = Fl::event_x_root ();
      int dy = Fl::event_y_root ();
      int ex = x_root ();
      int ey = y_root ();

      // printf ("Handling FL_DOCK event!!\n");
      
      // Check to see if we can dock along any of 
      // the pack boundaries.
      
      // This code should probably go into Pack_2's handle:
      Fl_Widget*const* a = pack->array();
      for (int i=0; i <= pack->children(); i++)
	{
	  int cY;
	  
	  if (i==pack->children())
	    cY = h();
	  else
	    {
	      Fl_Widget* o = *a++;
	      cY = o->y ();
	    }
	  
	  if (   (dx < (ex + FL_DOCK_DELTA + w()))      // xmax
		 && (dx > (ex - FL_DOCK_DELTA))         // xmin 
		 && (dy < (ey + FL_DOCK_DELTA + cY))    // ymax
		 && (dy > (ey - FL_DOCK_DELTA + cY)) )  // ymin
	    {
	      printf ("DOCK!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	      add_dockable (Fl_Dockable_Group::current, i);
	      return 1;
	    }
	}
      return 0;
    }
  return Fl_Window::handle (event);
}

// Anything added to Fl_App should actually get 
// added to the contents group.

void Fl_App_Window::add (Fl_Widget *w)
{
  contents->add (w);
}

void Fl_App_Window::add_dockable (Fl_Dockable_Group *W, int pos = 0)
{
  Fl_Dockable_Group::current = W;
  Fl_Dockable_Group::current->hide ();
  pack->insert (*W, pos);
  W->set_docked (1);
  
  if (pack->horizontal ())
    Fl_Dockable_Group::current->size(Fl_Dockable_Group::current->w(), h());
  else
    Fl_Dockable_Group::current->size(w(), Fl_Dockable_Group::current->h());
  
  Fl_Dockable_Group::current->show ();
  
  // FLTK BUG???  calling redraw() should call draw(), right??  
  // Not always so we need to pack things here..
  {
    pack->draw ();
    if ((w() != pack->w()) || (h() != pack->h()))
      size (pack->w(), pack->h());
    redraw ();
  }
}

void Fl_App_Window::show ()
{
  Fl_Window::show ();
  pack->show ();
  contents->show ();
}

void 
Fl_App_Window::draw ()
{
  printf ("####################################\n");
  // if pack->w() and pack->h() change...
  pack->draw ();
  resize (x(), y(), pack->w(), pack->h());
  return Fl_Window::draw ();
}
