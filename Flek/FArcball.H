/* -*-C++-*- 

   "$Id: FArcball.H,v 1.3 2000/04/14 16:39:20 jamespalmer Exp $"
   
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
  
  /**
   * Default constructor.
   */
  FArcball ();

  /**
   * Copy constructor.  This constructor copies the values from another
   * FArcball.
   *
   * @param ab The FArcball that this FArcball should copy it's values from.
   */
  FArcball (const FArcball& ab);

  /**
   * Two argument constructor.  This constructor sets the initial center
   * and radius of the arcball.
   *
   * @param cen The center for all subsequent rotation, zoom, pan, and 
   *   dolly operations.
   * @param radius The radius of the sphere used for determining where
   *   the user sweeps a rotation arc.  The radius is relative to the
   *   window, where the value 1.0 would be the size of the window.
   */
  FArcball (const FVector3& cen, double rad);

  /**
   * The destructor.
   */
  ~FArcball ();

  /**
   * The assignment operator.  This method assigns the values contained
   * in this arcball to that of another.
   *
   * @param ab The FArcball that this FArcball should copy it's values from.
   */
  FArcball& operator = (const FArcball& ab);
  
  /**
   * Sets the center of the arcball and it's radius.
   *
   * @param cen The center for all subsequent rotation, zoom, pan, and 
   *   dolly operations.
   * @param radius The radius of the sphere used for determining where
   *   the user sweeps a rotation arc.  The radius is relative to the
   *   window, where the value 1.0 would be the size of the window.
   */
  void place (const FVector3& cen, double rad) {
    vCenter = cen; dRadius = rad;
  }

  /**
   * Sets the center of the arcball.
   *
   * @param cen The center for all subsequent rotation, zoom, pan, and 
   *   dolly operations.
   */  
  void center (const FVector3& cen) {
    vCenter = cen;
  }

  /**
   * Sets the center of the arcball.
   *
   * @param x The x coordinate center for all subsequent rotation, zoom,
   *   pan, and dolly operations.
   * @param y The y coordinate center for all subsequent rotation, zoom,
   *   pan, and dolly operations.
   * @param z The z coordinate center for all subsequent rotation, zoom,
   *   pan, and dolly operations.
   */    
  void center (double x, double y, double z) {
    vCenter.set (x, y, z);
  }

  /**
   * Gets the center of the arcball.
   *
   * @return The center of the arcball.
   */    
  FVector3 center () const {
    return vCenter;
  }
  
  /**
   * Register an x-y mouse event.
   *
   * @param x The new x coordinate of the mouse.
   * @param y The new y coordinate of the mouse.
   */
  void mouse (double x, double y) {
    vNow.set (x, y, 0);
  }

  void reset (void) {
    qDown.reset(); qNow.reset(); mNow.reset();
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
  void update ();

  /**
   * Gets the arcball transformation matrix.
   *
   * @return The current arcball transforamtion matrix.
   */  
  FMatrix4x4 value(void) const
    {
      return mNow;
    }

  /**
   * Gets the rotation quaternion.
   *
   * @return The current arcball quaternion.
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

  /**
   * Gets wether or not we are currently dragging the mouse.
   *
   * @return True if we are dragging the mouse, else false.
   */
  bool dragging () const { return bDragging; }

  /**
   * Gets the axis.  
   * 
   * @return The current axis.  Possible values include CameraAxes, BodyAxes and NoAxes.
   */
  AxisSet axisSet () const { return asAxisSet; }

  /**
   * Gets the axis index.
   *
   * @return The axis index.
   */
  int axisIndex () const { return iAxisIndex; }

  Axes sets[2];

  /**
   * Gets the "from" point.
   *
   * @return The point on the arcball we are rotating from (initial click).
   */
  FVector3 & from () { return vFrom; }

  /**
   * Gets the "to" point.
   *
   * @return The point on the arcball we are rotating to.
   */
  FVector3 & to () { return vTo; }

  /**
   * Gets the arcball radius.
   *
   * @return The arcball radius relative to the size of the viewport.  
   *   Where 1.0 equals a diameter equal to the size of the viewport.
   */
  double radius () const { return dRadius; }

  /** 
   * Sets the arcball radius.
   *
   * @param The arcball radius.  Good values are usually less than 1.0.
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
