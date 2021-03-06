/* -*-C++-*- 

   "$Id: FArcball_Control.cxx,v 1.2 2000/04/21 13:50:37 jamespalmer Exp $"
   
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

#include <Flek/FArcball_Control.H>

FArcball_Control::FArcball_Control ()
{
  dRadius = 1.0;
  vCenter.set (0, 0, 0);
  bDragging = false;
  asAxisSet = NoAxes;
  
  sets[CameraAxes] = new FVector3[3];
  sets[BodyAxes] = new FVector3[3];
  
  // All matrices are initially identity matrices
  // Camera axes are simply the X,Y and Z axes. They don't change
  sets[CameraAxes][0].set (1.0, 0.0, 0.0); // X axis for camera
  sets[CameraAxes][1].set (0.0, 1.0, 0.0); // Y axis for camera
  sets[CameraAxes][2].set (0.0, 0.0, 1.0); // Z axis for camera
  
  // Body axes are same as camera axes initially. Body axes are the rows of the
  // Rotation matrix. Uses functions to convert Vector4d to FVector3
  // Need to use the vector library
  sets[BodyAxes][0] = mNow[0];
  sets[BodyAxes][1] = mNow[1];
  sets[BodyAxes][2] = mNow[2];
}

FArcball_Control::FArcball_Control (const FArcball_Control& ab)
{
  // Copy only the center and radius. initialize to same as new arcball
  vCenter = ab.vCenter;
  dRadius = ab.dRadius;
  
  bDragging = false;
  asAxisSet = NoAxes;
  
  sets[CameraAxes] = new FVector3[3];
  sets[BodyAxes] = new FVector3[3];
  
  // Camera axes are simply the X,Y and Z axes. They don't change
  sets[CameraAxes][0].set (1.0, 0.0, 0.0); // X axis for camera
  sets[CameraAxes][1].set (0.0, 1.0, 0.0); // Y axis for camera
  sets[CameraAxes][2].set (0.0, 0.0, 1.0); // Z axis for camera
  
  // Body axes are same as camera axes initially
  sets[BodyAxes][0] = mNow[0];
  sets[BodyAxes][1] = mNow[1];
  sets[BodyAxes][2] = mNow[2];
}

FArcball_Control::FArcball_Control (const FVector3& cen, double rad)
{
  vCenter = cen;
  dRadius = rad;
  bDragging = false;
  asAxisSet = NoAxes;
  
  sets[CameraAxes] = new FVector3[3];
  sets[BodyAxes] = new FVector3[3];
  
  sets[CameraAxes][0].set(1.0,0.0,0.0); // X axis for camera
  sets[CameraAxes][1].set(0.0,1.0,0.0); // Y axis for camera
  sets[CameraAxes][2].set(0.0,0.0,1.0); // Z axis for camera
  
  sets[BodyAxes][0] = mNow[0];
  sets[BodyAxes][1] = mNow[1];
  sets[BodyAxes][2] = mNow[2];
}

FArcball_Control::~FArcball_Control ()
{
  delete [] sets[CameraAxes];
  delete [] sets[BodyAxes];
}

FArcball_Control& FArcball_Control::operator = (const FArcball_Control& ab)
{
  // Copy only the center and radius. Reset rest to same as new arcball
  vCenter = ab.vCenter;
  dRadius = ab.dRadius;
  
  bDragging = false;
  asAxisSet = NoAxes;
  
  sets[CameraAxes] = new FVector3[3];
  sets[BodyAxes] = new FVector3[3];
  
  // Camera axes are simply the X,Y and Z axes. They don't change
  sets[CameraAxes][0].set (1.0, 0.0, 0.0); // X axis for camera
  sets[CameraAxes][1].set (0.0, 1.0, 0.0); // Y axis for camera
  sets[CameraAxes][2].set (0.0, 0.0, 1.0); // Z axis for camera
  
  // Body axes are same as camera axes initially
  sets[BodyAxes][0] = mNow[0];
  sets[BodyAxes][1] = mNow[1];
  sets[BodyAxes][2] = mNow[2];
  
  return (*this);
}

/**
 * Using vDown, vNow, dragging, and asAxisSet, compute rotation etc.
 */
void FArcball_Control::update (void)
{
  vFrom = mouseOnSphere (vDown, vCenter, dRadius);
  vTo = mouseOnSphere (vNow, vCenter, dRadius);
  if (bDragging)
    {
      if ( asAxisSet != NoAxes)
	{
	  vFrom = constrainToAxis (vFrom, sets[asAxisSet][iAxisIndex]);
	  vTo = constrainToAxis (vTo, sets[asAxisSet][iAxisIndex]);
	}
      
      //vnFrom[0] = -vFrom[0];
      //vnFrom[1] = -vFrom[1];
      //vnFrom[2] = vFrom[2];
      //vnTo[0] = -vTo[0];
      //vnTo[1] = -vTo[1];
      //vnTo[2] = vTo[2];
      
      qDrag = quatFromBallPoints (vFrom, vTo);
      qNow = qDrag * qDown;
    }
  else
    {
      if ( asAxisSet != NoAxes)
	iAxisIndex = nearestConstraintAxis (vTo, sets[asAxisSet], 3);
    }
  mNow = to_matrix4 (conjugate (qNow));
}

FVector3 FArcball_Control::mouseOnSphere (const FVector3& mouse, const FVector3& center, double radius)
{
  FVector3 ballMouse;
  register double magsqr;

  ballMouse[0] = (mouse[0] - center[0]) / radius;
  ballMouse[1] = (mouse[1] - center[1]) / radius;
  magsqr = sqr(ballMouse[0]) + sqr(ballMouse[1]);
  if (magsqr > 1.0)
    {
      register double scale = 1.0/sqrt(magsqr);
      ballMouse[0] *= scale; 
      ballMouse[1] *= scale;
      ballMouse[2] = 0.0;
    }
  else
    {
      ballMouse[2] = sqrt (1.0 - magsqr);
    }
  return ballMouse;
}

/**
 * Construct a unit quaternion from two points on unit sphere
 */
FQuaternion FArcball_Control::quatFromBallPoints (const FVector3& from, const FVector3& to)
{
  return FQuaternion (from % to, from * to);
}

/**
 * Convert a unit quaternion to two points on unit sphere
 * Assumes that the given quaternion is a unit quaternion
 */
void FArcball_Control::quatToBallPoints (const FQuaternion& q, FVector3& arcFrom, FVector3& arcTo)
{
  double s;
  s = sqrt (sqr (q[0]) + sqr (q[1]));

  if (fabs (s) < 1.0e-5) 
    arcFrom.set (0.0, 1.0, 0.0);
  else
    arcFrom.set (-q[1]/s, q[0]/s, 0.0);
  
  arcTo[0] = q[3]*arcFrom[0] - q[2]*arcFrom[1];
  arcTo[1] = q[3]*arcFrom[1] + q[2]*arcFrom[0];
  arcTo[2] = q[0]*arcFrom[1] - q[1]*arcFrom[0];
  if (q[3] < 0.0) arcFrom *= -1.0;
}

/**
 * Force sphere point to be perpendicular to axis.
 */
FVector3 FArcball_Control::constrainToAxis (const FVector3& loose, const FVector3& axis)
{
  FVector3 onPlane;
  register float norm;
  onPlane = loose - axis * (axis*loose);
  norm = normsqr(onPlane);
  if (norm > 0.0)
    {
      if (onPlane[2] < 0.0) onPlane *= -1.0;
      onPlane /= sqrt(norm);
    }
  else if ( fabs (axis[2]-1.0) < 1.0e-5 )
    {
      onPlane.set (1.0, 0.0, 0.0);
    }
  else
    {
      onPlane.set (-axis[1], axis[0], 0.0); 
      normalize (onPlane);
    }
  return onPlane;
}

/**
 * Find the index of nearest arc of axis set.
 */
int FArcball_Control::nearestConstraintAxis (const FVector3& loose, FVector3 * axes, int nAxes)
{
  FVector3 onPlane;
  register float max, dot;
  register int i, nearest;
  max = -1.0; nearest = 0;
  for (i=0; i < nAxes; i++)
    {
      onPlane = constrainToAxis(loose, axes[i]);
      dot = onPlane * loose;
      if ( dot > max )
	{
	  max = dot; nearest = i;
	}
    }
  return nearest;
}
