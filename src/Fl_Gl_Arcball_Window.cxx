#include <FL/Fl.H>
#include <Flek/Fl_Gl_Arcball_Window.H>
#include <GL/gl.h>

int Fl_Gl_Arcball_Window::handle (int event)
{
  switch (event)
    {
     case FL_PUSH:
      drag.set ((2.0*Fl::event_x ()) / w() - 1.0, (-2.0 * Fl::event_y ()) / h() + 1.0, 0);
      arcball.mouse (drag);
      arcball.beginDrag ();
      arcball.update ();
      break;
     case FL_RELEASE:
      drag.set ((2.0*Fl::event_x ()) / w() - 1.0, (-2.0 * Fl::event_y ()) / h() + 1.0, 0);
      arcball.mouse (drag);
      arcball.endDrag ();
      arcball.update ();
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

/*
void fglMultMatrix (const fMatrix4x4 &M)
{
  double N[16];
  
  for (int i=0; i<4; i++)
    for (int j=0; j<4; j++)
      N[i][j] = M [i][j]; 
  glMultMatrixd ((double *)N);
}
*/
  
void Fl_Gl_Arcball_Window::arcball_transform ()
{
  double rot[16];
  //glMultMatrixd ((arcball.value ()).value ());
  arcball.value().fillArrayRowMajor(rot);
  glMultMatrixd (rot);
}

