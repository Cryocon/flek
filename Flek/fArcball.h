/* -*-C++-*- 

   "$Id: fArcball.h,v 1.6 2000/02/13 01:02:32 jamespalmer Exp $"
   
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

// The original vector, matrix, and quaternion code was written by
// Vinod Srinivasan and then adapted for Flek.

#ifndef FARCBALL_H_
#define FARCBALL_H_

#include <Flek/fVector3.h>
#include <Flek/fQuaternion.h>
#include <Flek/fMatrix4x4.h>

enum AxisSet { CameraAxes=0, BodyAxes=1, NoAxes=2 };

/** @package libflek_core
 * The fArcball class provides a convenient 3d rotation controller.
 * This class is used by <a href="Fl_Gl_Arcball_Window.html">Fl_Gl_Arcball_Window</a>
 * to provide a user friendly rotation manipulator.
 */
class fArcball
{
public:

  typedef fVector3 * Axes;
    
  fArcball ();
  fArcball (const fArcball& ab);
  ~fArcball ();
  
  fArcball& operator = (const fArcball& ab);
  
  /**
   * Place the center of the ball and set it's radius.
   */
  void place (const fVector3& cen, double rad)
    {
      vCenter = cen; dRadius = rad;
    }

  /**
   * Register an x-y mouse event.
   */
  void mouse (const fVector3& pos)
    {
      vNow = pos;
    }

  /**
   * Set the axis to use.
   */
  void useSet (AxisSet set)
    {
      if ( !bDragging ) asAxisSet = set;
    }

  /**
   * Update the arcball transformation matrix.
   */
  void update (void);

  /**
   * Return the arcball transformation matrix.
   */  
  fMatrix4x4 value(void) const
    {
      return mNow;
    }

  /**
   * Start dragging the mouse.
   */  
  void beginDrag (void)
    {
      bDragging = true; vDown = vNow;
    }

  /**
   * End dragging the mouse.
   */    
  void endDrag (void)
    {
      bDragging = false; qDown = qNow;
      sets[BodyAxes][0] = mNow[0];
      sets[BodyAxes][1] = mNow[1];
      sets[BodyAxes][2] = mNow[2];
    }
  
  /**
   * Draw the arcball. Give vector from eye point to center of interest
   */
  void draw (const fVector3& dir = fVector3 (0.0, 0.0, 1.0)) const;

  /**
   * Returns if we are currently dragging the mouse.
   */
  bool dragging () const { return bDragging; }
  
  AxisSet axisSet () const { return asAxisSet; }

  int axisIndex () const { return iAxisIndex; }

  Axes sets[2];

  fVector3 & from () { return vFrom; }
  fVector3 & to () { return vTo; }

  /**
   * Get the arcball radius.
   */
  double radius () { return dRadius; }

  /** 
   * Set the arcball radius.
   */
  void radius (const double r) { dRadius = r; }
  
 protected:
  fVector3 vCenter;
  double dRadius;

  fQuaternion qNow, qDown, qDrag;
  fVector3 vNow, vDown, vFrom, vTo;
  fMatrix4x4 mNow;
  bool bDragging;
  AxisSet asAxisSet;
  int iAxisIndex;
  
private :
  
  static fVector3 mouseOnSphere (const fVector3& mouse, const fVector3& ballCenter, double ballRadius);
  static fVector3 constrainToAxis (const fVector3& loose, const fVector3& axis);
  static int nearestConstraintAxis (const fVector3& loose, fVector3 * axes, int nAxes);
  static fQuaternion quatFromBallPoints (const fVector3& from, const fVector3& to);
  static void quatToBallPoints (const fQuaternion& q, fVector3& arcFrom, fVector3& arcTo);

};

#endif // #ifndef FARCBALL_H_
