#include <FL/Fl.H>
#include <FL/fl_draw.H>

#include <Flek/Fl_Dockable_Group.H>
#include <Flek/grip_tile.xpm>

long Fl_Dockable_Group::gripper_width = 10;
Fl_Dockable_Group * Fl_Dockable_Group::current = 0;

void Fl_Gripper::draw ()
{
  // Draw the Gnome style gripper:
  Fl_Color col = value() ? selection_color() : color();
  draw_box (box(), col);
  draw_label ();

  fl_push_clip (x()+1, y()+1, w()-3, h()-3);
  
  for (int i=0; i<w(); i+=6)
    for (int j=0; j<h(); j+=6)
      fl_draw_pixmap(grip_tile_xpm, i+2, j+2);
  
  fl_pop_clip ();
}

int Fl_Gripper::handle (int event)
{
  int rval = Fl_Button::handle (event);
  int x_drag, y_drag;
  
  switch (event) {
   case FL_PUSH:
    // Set the Fl_Dockable_Group that may eventually get docked.
    Fl_Dockable_Group::current = (Fl_Dockable_Group *)parent ();
    x_down = Fl::event_x_root ();
    y_down = Fl::event_y_root ();
    x_first = Fl_Dockable_Group::current->x_root();
    y_first = Fl_Dockable_Group::current->y_root();
    return 1;
    break;
   case FL_DRAG:
   case FL_RELEASE:
      {
	Fl_Dockable_Group *group = (Fl_Dockable_Group *)parent ();

	x_drag = Fl::event_x_root ();
	y_drag = Fl::event_y_root ();

	int delta = ((x_drag + y_drag) - (x_down + y_down));
	
	if (delta < 0) delta *= -1;
	
	if (group->parent ())
	  {
	    if (delta > (FL_DOCK_DELTA * 2))
	      {
		x_first = Fl_Dockable_Group::current->x_root ();
		y_first = Fl_Dockable_Group::current->y_root ();

		group->undock ((x_first + (x_drag - x_down)), (y_first + (y_drag - y_down)));
		
		// Once undocked, give the window focus and continue dragging.
		take_focus ();
		Fl::pushed (this);
	      }
	  }
	else
	  {
	    // See if anyone want to dock with me..
	    for (Fl_Window *o = Fl::first_window(); o; o = Fl::next_window (o))
	      {
		if (o != window ()) // Don't dock with self!
		  {
		    int ex = o->x_root ();
		    int ey = o->y_root ();
		    int ew = o->w();
		    int eh = o->h();
		    
		    int cx = Fl::event_x_root ();
		    int cy = Fl::event_y_root ();
		    
		    if ( o->visible () 
			&& (cx > ex)
			&& (cy > ey)
			&& (cx < (ew + ex))
			&& (cy < (eh + ey)) )
		      {
			// Send the host window a message that we are docking with it.
			if (Fl::handle (FL_DOCK, o))
			  {
			    redraw ();
			    if (event != FL_RELEASE) 
			      {
				// I want to send JUST the drag event.  Not push!
				// Right now it just stops dragging after a successful dock.
				// take_focus ();
				// Fl::pushed (this);
			      }
			    break;
			  }
		      }
		  }
	      }	    
	  }
	
	if (group->get_docked ())
	  {
	    // Don't move the Dock_Group around if it is docked.
	  }
	else
	  {
	    // Move the Dock_Group around the screen.
	    group->position ((x_first + (x_drag - x_down)), (y_first + (y_drag - y_down)));
	  }
	return 1;
      }
    break;
  }
  return rval;
}

Fl_Dockable_Group::Fl_Dockable_Group (int x, int y, int w, int h, const char *l = 0) 
  : Fl_Window (x,y,(w+gripper_width),h,l)
{
  usize (w, h);
  gripper = new Fl_Gripper (0, 0, gripper_width, h);
  docked = 0;
  contents = new Fl_Window (gripper_width, 0, w, h);
  contents->box (FL_UP_BOX);
  contents->color (52);
  resizable (contents);
  begin ();
}

Fl_Dockable_Group::Fl_Dockable_Group (int w, int h, const char *l = 0) 
  : Fl_Window ((w+gripper_width),h,l)
{
  usize (w, h);
  gripper = new Fl_Gripper (0, 0, gripper_width, h);
  docked = 0;
  contents = new Fl_Window (gripper_width, 0, w, h);
  contents->box (FL_UP_BOX);
  contents->color (52);
  resizable (contents);
  begin ();
}

Fl_Dockable_Group::~Fl_Dockable_Group ()
{
  delete gripper;
}

void Fl_Dockable_Group::draw ()
{
  clear_border ();
  Fl_Window::draw ();
}

void Fl_Dockable_Group::show ()
{
  Fl_Window::show ();
  gripper->show ();
}

int Fl_Dockable_Group::handle (int event)
{
  switch (event)
    {
    case FL_SHOW:
      contents->show ();
      break;
    case FL_HIDE:
      contents->hide ();
      break;
    }
  return Fl_Window::handle (event);
}

void Fl_Dockable_Group::undock (int x=-1, int y=-1)
{
  docked = 0;
  if (parent())
    {
      Fl_Group *group = (Fl_Group *) parent ();
      hide ();
      
      group->remove ((Fl_Widget *)this);
      
      // Give the dock an opportunity to handle the event.
      Fl::handle (FL_UNDOCK, group->window ());
      
      group->redraw ();
      
      if (x > -1)
	position (x, y);
      
      size (uw (), uh ());
      show ();
    }
}
