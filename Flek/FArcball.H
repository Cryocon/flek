/* -*-C++-*- 

   "$Id: FArcball.H,v 1.1 2000/04/13 14:10:02 jamespalmer Exp $"
   
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

#ifndef _FARCBALL_H_
#define _FARCBALL_H_

#include <Flek/FVector3.H>
#include <Flek/FQuaternion.H>
#include <Flek/FMatrix4x4.H>

enum AxisSet { CameraAxes=0, BodyAxes=1, NoAxes=2 };

/** @package libflek_core
 * The FArcball class provides a convenient 3d rotation controller.
 * This class is used by <a href="Fl_Gl_Arcball_Window.html">Fl_Gl_Arcball_Window</a>
 * to provide a user friendly rotation manipulator.
 */
class FArcball
{
public:

  typedef FVector3 * Axes;
    
  FArcball ();
  FArcball (const FArcball& ab);
  FArcball (const FVector3& cen, double rad);
  ~FArcball ();
  
  FArcball& operator = (const FArcball& ab);
  
  /**
   * Place the center of the ball and set it's radius.
   */
  void place (const FVector3& cen, double rad) {
    vCenter = cen; dRadius = rad;
  }
  
  void center (const FVector3& cen) {
    vCenter = cen;
  }
  
  void center (double x, double y, double z) {
    vCenter.set (x, y, z);
  }
    
  FVector3 center(void) const {                      // Get the center
    return vCenter;
  }
  
  /**
   * Register an x-y mouse event.
   */
  void mouse (const FVector3& pos)
    {
      vNow = pos;
    }

  void reset (void) {
    qDown.reset(); qNow.reset(); mNow.reset();
  }
  
  /**
   * Register an x-y mouse event.
   */
  void mouse (double x, double y) {
    vNow.set (x, y, 0);
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
  FMatrix4x4 value(void) const
    {
      return mNow;
    }

  /**
   * Return the rotation quaternion.
   */  
  FQuaternion quat_value(void) const
    {
      return qNow;
    }
  
  /**
   * Start dragging the mouse.
   */  
  void begin_drag (void)
    {
      bDragging = true; vDown = vNow;
    }

  /**
   * End dragging the mouse.
   */    
  void end_drag (void)
    {
      bDragging = false; qDown = qNow;
      sets[BodyAxes][0] = mNow[0];
      sets[BodyAxes][1] = mNow[1];
      sets[BodyAxes][2] = mNow[2];
    }

  void draw(void) const;

  /**
   * Returns if we are currently dragging the mouse.
   */
  bool dragging () const { return bDragging; }
  
  AxisSet axisSet () const { return asAxisSet; }

  int axisIndex () const { return iAxisIndex; }

  Axes sets[2];

  FVector3 & from () { return vFrom; }
  FVector3 & to () { return vTo; }

  /**
   * Get the arcball radius.
   */
  double radius () const { return dRadius; }

  /** 
   * Set the arcball radius.
   */
  void radius (const double r) { dRadius = r; }
  
 protected:
  FVector3 vCenter;
  double dRadius;

  FQuaternion qNow, qDown, qDrag;
  FVector3 vNow, vDown, vFrom, vTo;
  FMatrix4x4 mNow;
  bool bDragging;
  AxisSet asAxisSet;
  int iAxisIndex;
  
private:
  
  static FVector3 mouseOnSphere (const FVector3& mouse, const FVector3& ballCenter, double ballRadius);
  static FVector3 constrainToAxis (const FVector3& loose, const FVector3& axis);
  static int nearestConstraintAxis (const FVector3& loose, FVector3 * axes, int nAxes);
  static FQuaternion quatFromBallPoints (const FVector3& from, const FVector3& to);
  static void quatToBallPoints (const FQuaternion& q, FVector3& arcFrom, FVector3& arcTo);
    
};

#endif // #ifndef FArcBALL_H_
