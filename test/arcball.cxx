#include <Flek/FVector3.H>
#include <Flek/Fl_Gl_Arcball_Window.H>
//#include "Grid.hh"
#include <fstream.h>

class Arcball : public Fl_Gl_Arcball_Window 
{
  protected :

     GLUquadric * quadric;
  //Grid grid;
     
  public :

     Arcball(int x, int y, int w, int h, const char *l=0)
       : Fl_Gl_Arcball_Window(x,y,w,h,l) //, grid(ZX,20.0,20)
       {
         quadric = gluNewQuadric();
       }

     ~Arcball()
       {
         gluDeleteQuadric(quadric);
       }

  // CTRL+left = zoom; CTRL+mid = dolly; ALT+LEFT = rotate; ALT+MID = pan
  
     int handle(int event)
       {
	 /* Maya like controls:
         if ( (event == FL_PUSH) && (Fl::event_button() == FL_RIGHT_MOUSE) )
            exit(0);
         if ( (event == FL_PUSH) || (event == FL_RELEASE) || (event == FL_DRAG) )
            {
              if ( Fl::event_state(FL_ALT) ) {
                   if ( Fl::event_state(FL_CTRL) ) {
                           // ALT and CTRL buttons were down. Do zooming on middle mouse
                        if ( Fl::event_button() == FL_MIDDLE_MOUSE ) handle_zoom (event);
                        else if ( Fl::event_button() == FL_LEFT_MOUSE ) handle_dolly (event);
                      }
                   else
                      {
                           // ALT button was down. Handle rotates and translates                   
                        if ( Fl::event_button() == FL_LEFT_MOUSE ) handle_rotate (event);
                        else if ( Fl::event_button() == FL_MIDDLE_MOUSE ) handle_pan (event);
                      }
                   if ( event != FL_PUSH ) redraw();
                   return 1;
                 }
	      return Fl_Gl_Arcball_Window::handle(event);
              //return 0;
            }
	  */
         return Fl_Gl_Arcball_Window::handle(event);
       }

     void reshape(void)
       {
         cenx = ceny = 0.0; cenz = 0.0;
         eyex = eyey = 0.0; eyez = 20.0;
         upx = upz = 0.0; upy = 1.0;

         aspect = double(w())/double(h());
         near = 1.0; far = 100.0;
#if 1
            // Perspective projection
         fovy = 45.0;
         projtype = Perspective;
#else
            // Orthographic projection
         vmin = -10.0; vmax = 10.0;
         umin = vmin*aspect; umax = vmax*aspect;
         projtype = Orthographic;
#endif 
         Fl_Gl_Arcball_Window :: reshape();
       }
     
     void draw(void)
       {
         if ( !valid() )
            {
              valid(1);
              reshape();
              //grid.generate();
            }

         glClearColor(0,0,0,1);
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

         glEnable(GL_DEPTH_TEST);

            // Draw the arcball controls.
         arcball_draw();

         glMatrixMode(GL_MODELVIEW);

         glPushMatrix();

             // Multiply by the arcball transformation.
         arcball_transform();

            // Draw a grid in the ZX plane
         glLineWidth(0.5);
         glColor3f(0.3,0.3,0.3);
         //grid.render();

            // Draw the axes
         {
           glLineWidth(2.0);
           glBegin(GL_LINES);

           glColor3f(0.0,1.0,1.0);                     // X Axis
           glVertex3f(0,0,0); glVertex3f(5,0,0);

           glColor3f(1.0,0.0,1.0);                     // Y Axis
           glVertex3f(0,0,0); glVertex3f(0,5,0);

           glColor3f(1.0,1.0,0.0);                     // Z Axis
           glVertex3f(0,0,0); glVertex3f(0,0,5);

           glEnd();
           glLineWidth(1.0);
         }

         glPushMatrix();
         glRotatef(-90,1,0,0);

         glEnable(GL_CULL_FACE);
            // Draw sphere
         glColor3f(1.0,0.75,0.5);
         glPolygonMode(GL_FRONT,GL_FILL);
         gluSphere(quadric,4,8,8);

            // Draw sphere grid
         glColor3f(0,0,0);
         glEnable(GL_POLYGON_OFFSET_LINE);
         glPolygonOffset(1,-4.01);
         glPolygonMode(GL_FRONT,GL_LINE);
         gluSphere(quadric,4,8,8);
         glDisable(GL_POLYGON_OFFSET_LINE);
         glPopMatrix();

         glPopMatrix();

         glFlush();
       }
};

int main (int argc, char **argv) 
{
  Fl_Window window(500, 500);
  
  Arcball win(10, 10, window.w()-20, window.h()-20, "ArcballWindow Test Program");

  win.mode(FL_RGB|FL_DOUBLE|FL_DEPTH);
  window.add(win);
  window.resizable(&win);

  window.end();
  window.show(argc,argv);
  win.show();
  
  return Fl::run();
}
