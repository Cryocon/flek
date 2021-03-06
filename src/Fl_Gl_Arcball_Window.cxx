/* -*-C++-*- 

   "$Id: Fl_Gl_Arcball_Window.cxx,v 1.11 2000/05/12 14:18:12 jamespalmer Exp $"
   
   Copyright 1999-2000 by the Flek development team.
   
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

#include <FL/Fl.H>
#include <Flek/Fl_Gl_Arcball_Window.H>
#include <Flek/gl.H>

#define LG_NSEGS 4
#define NSEGS (1<<LG_NSEGS)
#define CIRCSEGS 32
#define HALFCIRCSEGS 16

static void unitCircle (void)
{
  // Draw a unit circle in the XY plane, centered at the origin
  float dtheta = 2.0*M_PI/32.0;
  
  glBegin (GL_LINE_LOOP);
  for (int i=0; i < 32; ++i)
    glVertex (cos (i*dtheta), sin (i*dtheta), 0.0);
  glEnd ();
}

/*
 * Draw a circle with the given normal, center and radius 
 */
static void drawCircle (const FVector3& center, const FVector3& normal, double radius)
{
  // First find the coordinate axis centered at the circle center.
  // The normal will be the Z axis.
  FVector3 xaxis, yaxis, zaxis;
  
  zaxis = normalized (normal);
  xaxis = FVector3 (0,1,0) % zaxis;
  if ( normsqr(xaxis) < 1.0e-5 ) 
    xaxis.set (1,0,0);
  yaxis = zaxis % xaxis;
  
  // Circle will be on the XY plane, defined by the axis system 
  // just computed 
  FVector3 pts[CIRCSEGS+1];
  double theta = 0.0, dtheta = M_PI/HALFCIRCSEGS;
  double costheta, sintheta;
  for (int i=0; i < (HALFCIRCSEGS >> 2); ++i )
    {
      costheta = radius*cos (theta); sintheta = radius*sin (theta);
      pts[0] = center + costheta*xaxis + sintheta*yaxis;
      pts[HALFCIRCSEGS-i] = center - costheta*xaxis + sintheta*yaxis;
      pts[HALFCIRCSEGS+i] = center - costheta*xaxis - sintheta*yaxis;
      pts[CIRCSEGS-i] = center + costheta*xaxis - sintheta*yaxis;
      theta += dtheta;
    }
  
  glBegin (GL_LINE_LOOP);
  {
    for (int i=0; i < CIRCSEGS; ++i)
      glVertex (pts[i]);
  }
  glEnd ();
}

/*
 * Halve arc between unit vectors v1 and v2.
 * Assumes that v1 and v3 are unit vectors
 */
static FVector3 bisect (const FVector3& v1, const FVector3& v2)
{
  FVector3 v = v1 + v2;
  float Nv = normsqr (v);
  
  if (Nv < 1.0e-5) 
    v.set (0.0, 0.0, 1.0);
  else
    v /= sqrt(Nv);
  return v;
}

/*
 *  Draw an arc defined by its ends.
 */
static void drawAnyArc (const FVector3& vFrom, const FVector3& vTo)
{
  int i;
  FVector3 pts[NSEGS+1];
  double dot;
  
  pts[0] = vFrom;
  pts[1] = pts[NSEGS] = vTo;
  for (i=0; i < LG_NSEGS; ++i) pts[1] = bisect (pts[0], pts[1]);
  
  dot = 2.0*(pts[0]*pts[1]);
  for (i=2; i < NSEGS; ++i)
    pts[i] = pts[i-1]*dot - pts[i-2];
  
  glBegin (GL_LINE_STRIP);
  for (i=0; i <= NSEGS; ++i)
    glVertex (pts[i]);
  glEnd ();
}

/*
 * Draw the arc of a semi-circle defined by its axis.
 */
static void drawHalfArc(const FVector3& n)
{
  FVector3 p, m;
  
  if ( fabs(n[2]-1.0) > 1.0e-5 )
    {
      p[0] = n[1]; p[1] = -n[0];
      normalize(p);
    }
  else
    {
      p[0] = 0; p[1] = 1;
    }
  m = p % n;
  drawAnyArc (p, m);
  drawAnyArc (m, -p);
}

/**
 * Draw all constraint arcs.
 */
void Fl_Gl_Arcball_Window::drawConstraints (void) const
{
  if ( arcball.axis () == NoAxes ) return;
  
  FVector3 axis;
  int i;
  
  for (i=0; i < 3; ++i)
    {
      if ( arcball.axis_index () != i)
	{
	  if (arcball.dragging ()) continue;
	  glColor (far_color_);
	}
      else 
	glColor (near_color_);
      
      axis = arcball.sets[arcball.axis ()][i];
      if ( fabs(axis[2]-1.0) < 1.0e-5 )
	unitCircle();
      else
	drawHalfArc(axis);
    }
}

/**
 *  Draw "rubber band" arc during dragging.
 */
void Fl_Gl_Arcball_Window::drawDragArc (void)
{
  if ( arcball.dragging () )
    {
      glColor (drag_color_);
      drawAnyArc ((arcball.from ()), (arcball.to ()));
    }
}

/**
 * Draw the controller with all its arcs. Parameter is the vector from 
 * the eye point to the center of interest. Default is -ve Z axis
 */
void Fl_Gl_Arcball_Window::arcball_draw ()
{
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
  
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  {
    glColor (rim_color_);
    glScale (arcball.radius (), arcball.radius (), arcball.radius ());
    unitCircle();
    
    drawConstraints();
    drawDragArc();
  }
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}
