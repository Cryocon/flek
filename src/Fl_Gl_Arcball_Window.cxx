#include <FL/Fl.H>
#include <Flek/Fl_Gl_Arcball_Window.H>

int Fl_Gl_Arcball_Window::handle (int event)
{
  switch (event)
    {
     case FL_PUSH:
      arcball.begin_drag ();
      break;
     case FL_RELEASE:
      arcball.end_drag ();
      break;
     case FL_DRAG:
	{
	  drag.set ((2.0*Fl::event_x ()) / w() - 1.0, (-2.0 * Fl::event_y ()) / h() + 1.0, 0);
	  arcball.mouse (drag);
	  arcball.update ();
	  redraw ();
	}
      break;
     default:
      return Fl_Gl_Window::handle (event);
    }
  return 1;
}

void Fl_Gl_Arcball_Window::arcball_draw ()
{
  arcball.draw ();  
}

void Fl_Gl_Arcball_Window::arcball_transform ()
{
  glMultMatrixd ((arcball.value ()).value ());
}

