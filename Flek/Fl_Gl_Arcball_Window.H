/* -*-C++-*- 

   "$Id: Fl_Gl_Arcball_Window.H,v 1.5 2000/02/10 17:03:42 jamespalmer Exp $"
   
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

#include <FL/Fl_Gl_Window.H>
#include <Flek/fArcball.h>
#include <Flek/gl.h>

/** @package libflek_ui (The Flek User Interface Library)
 * Fl_Gl_Arcball_Window is a subclass of Fl_Gl_Window that provides an arcball 3d rotation controller. What is arcball? From the
 * comp.graphics.algorithms FAQ: 
 * <blockquote>
 *  Arcball is a general purpose 3-D rotation controller described by Ken Shoemake in the Graphics Interface '92 Proceedings. It features good
 *  behavior, easy implementation, cheap execution, and optional axis constraints. A Macintosh demo and electronic version of the original
 *  paper (Microsoft Word format) may be obtained from ftp::/ftp.cis.upenn.edu/pub/graphics. 
 * </blockquote>
 * See the arcball demo in the test directory. 
 * <p><img src="Fl_Gl_Arcball_Window.png">
 */
class Fl_Gl_Arcball_Window : public Fl_Gl_Window
{
public:

  /**
   * Creates an Fl_Gl_Arcball_Window with the arcball centered at
   * <0, 0, 0> and a radius of 1.0.
   */
  Fl_Gl_Arcball_Window(int x, int y, int w, int h, const char *l=0) :
     Fl_Gl_Window (x, y, w, h, l),
     rim_color_ (1., 1., 1.),
     far_color_ (195./255., 127./255., 31./255.),
     near_color_ (1., 1., 63./255.),
     drag_color_ (127./255., 1., 1.)
    {
      arcball.place (origin_, radius_);
    }

  /**
   * Draw the arcball controls.
   */
  void arcball_draw ();

  void drawDragArc (void);
  void drawConstraints (void) const;

		 
  /**
   * Multiply the current Gl matrix by the arcball transformation
   * matrix.
   */
  void arcball_transform ();
  int handle (int event);
  int handle_rotation (int event);

  /**
   * Sets the arcball origin. <0, 0, 0> is default.
   */
  void origin (fVector3 o) { origin_ = o; arcball.place (origin_, radius_); }

  /**
   * Gets the arcball origin.
   */
  fVector3 origin () { return origin_; }

  /** 
   * Sets the arcball radius.
   */
  void radius (double o) { radius_ = o; arcball.place (origin_, radius_); }

  /**
   * Gets the arcball radius.
   */
  double radius () { return radius_; }

  fVector3 rim_color () { return rim_color_; }
  fVector3 far_color () { return far_color_; }
  fVector3 near_color () { return near_color_; }
  fVector3 drag_color () { return drag_color_; }

  void rim_color (const fVector3 &v) { rim_color_ = v; }
  void far_color (const fVector3 &v) { far_color_ = v; }
  void near_color (const fVector3 &v) { near_color_ = v; }
  void drag_color (const fVector3 &v) { drag_color_ = v; }

protected:

  fArcball arcball;
  fVector3 origin_;
  double radius_;

  fVector3 rim_color_;
  fVector3 far_color_;
  fVector3 near_color_;
  fVector3 drag_color_;

private:

  fVector3 drag;
};

