/*
  "$Id: arcball.cxx,v 1.1 2000/02/03 07:37:08 jamespalmer Exp $"
  
  This program tests fArcball and Fl_Gl_Arcball_Window.

  Copyright 1999-2000 by James Dean Palmer and others.
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Library General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.
  
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Library General Public License for more details.
  
  You should have received a copy of the GNU Library General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
  USA.
  
  Please report all bugs and problems to "flek-devel@sourceforge.net".

*/

#include <config.h>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Toggle_Button.H>
#include <FL/math.h>

#include <Flek/Fl_Gl_Arcball_Window.H>

class arcball_window : public Fl_Gl_Arcball_Window 
{
public:
  arcball_window (int x,int y,int w,int h,const char *l=0);  
  void draw ();
};

arcball_window::arcball_window(int x,int y,int w,int h,const char *l) :
  Fl_Gl_Arcball_Window(x,y,w,h,l) 
{
  origin (fVector3 (0,0,0));
  radius (1);
}

float v0[3] = {0.0, 0.0, 0.0};
float v1[3] = {1.0, 0.0, 0.0};
float v2[3] = {1.0, 1.0, 0.0};
float v3[3] = {0.0, 1.0, 0.0};
float v4[3] = {0.0, 0.0, 1.0};
float v5[3] = {1.0, 0.0, 1.0};
float v6[3] = {1.0, 1.0, 1.0};
float v7[3] = {0.0, 1.0, 1.0};

#define v3f(x) glVertex3fv(x)

void drawcube (int wire) 
{
  /* Draw a colored cube */
  glBegin(wire ? GL_LINE_LOOP : GL_POLYGON);
    glColor3ub(0,0,255);
    v3f(v0); v3f(v1); v3f(v2); v3f(v3);
    glEnd();
  glBegin(wire ? GL_LINE_LOOP : GL_POLYGON);
    glColor3ub(0,255,255); v3f(v4); v3f(v5); v3f(v6); v3f(v7);
    glEnd();
  glBegin(wire ? GL_LINE_LOOP : GL_POLYGON);
    glColor3ub(255,0,255); v3f(v0); v3f(v1); v3f(v5); v3f(v4);
    glEnd();
  glBegin(wire ? GL_LINE_LOOP : GL_POLYGON);
    glColor3ub(255,255,0); v3f(v2); v3f(v3); v3f(v7); v3f(v6);
    glEnd();
  glBegin(wire ? GL_LINE_LOOP : GL_POLYGON);
    glColor3ub(0,255,0); v3f(v0); v3f(v4); v3f(v7); v3f(v3);
    glEnd();
  glBegin(wire ? GL_LINE_LOOP : GL_POLYGON);
    glColor3ub(255,0,0); v3f(v1); v3f(v2); v3f(v6); v3f(v5);
    glEnd();
}

void arcball_window::draw() 
{
  // the valid() property may be used to avoid reinitializing your
  // GL transformation for each redraw:
  if (!valid ()) {
    valid (1);
    glLoadIdentity ();
    glViewport (0, 0, w (), h ());
    glEnable (GL_DEPTH_TEST);
    glFrustum (-1, 1, -1, 1, 2, 10000);
    glTranslatef (0, 0, -10);
  }

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Draw the arcball controls.
  arcball_draw ();

  glMatrixMode (GL_MODELVIEW); 
  glLoadIdentity ();

  glPushMatrix ();
    {
      // Multiply by the arcball transformation.
      arcball_transform ();
	{ 
	  // Make the cube a little smaller :
	  glScalef (0.5, 0.5, 0.5);
	  // Center the cube :
	  glTranslatef (-.5, -.5, -.5);
	  // Draw the cube :
	  drawcube (0);
	}
    }
  glPopMatrix ();
}

int main (int argc, char **argv) 
{
  Fl_Window window (300, 370);
  
  arcball_window arcball_window (10, 10, window.w()-20, window.h()-90);
  window.resizable (&arcball_window);

  window.end ();
  window.show (argc,argv);
  arcball_window.show ();
  
  return Fl::run ();
}
