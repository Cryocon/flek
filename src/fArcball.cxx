/* -*-C++-*- 

   "$Id: fArcball.cxx,v 1.5 2000/02/09 22:33:20 jamespalmer Exp $"
   
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

#include <GL/gl.h>
#include <Flek/fArcball.h>
#include <Flek/fGl.h>

#define LG_NSEGS 4
#define NSEGS (1<<LG_NSEGS)
#define CIRCSEGS 32
#define HALFCIRCSEGS 16
#define RIMCOLOR()    glColor3ub (255, 255, 255)
#define FARCOLOR()    glColor3ub (195, 127, 31)
#define NEARCOLOR()   glColor3ub (255, 255, 63)
#define DRAGCOLOR()   glColor3ub (127, 255, 255)
#define RESCOLOR()    glColor3ub (195, 31, 31)

/**
 * Establish reasonable initial values for controller.
 */
fArcball::fArcball ()
{
  dRadius = 1.0;
  dragging = false;
  axisSet = NoAxes;
  
  sets[CameraAxes] = new fVector3[3];
  sets[BodyAxes] = new fVector3[3];
  
  // All matrices are initially identity matrices
  // Camera axes are simply the X,Y and Z axes. They don't change
  sets[CameraAxes][0].set (1.0, 0.0, 0.0); // X axis for camera
  sets[CameraAxes][1].set (0.0, 1.0, 0.0); // Y axis for camera
  sets[CameraAxes][2].set (0.0, 0.0, 1.0); // Z axis for camera
  
  // Body axes are same as camera axes initially. Body axes are the rows of the
  // Rotation matrix. Uses functions to convert Vector4d to fVector3
  // Need to use the vector library
  sets[BodyAxes][0] = mNow[0];
  sets[BodyAxes][1] = mNow[1];
  sets[BodyAxes][2] = mNow[2];
}

fArcball::fArcball (const fArcball& ab)
{
  // Copy only the center and radius. initialize to same as new arcball
  vCenter = ab.vCenter;
  dRadius = ab.dRadius;
  
  dragging = false;
  axisSet = NoAxes;
  
  sets[CameraAxes] = new fVector3[3];
  sets[BodyAxes] = new fVector3[3];
  
  // Camera axes are simply the X,Y and Z axes. They don't change
  sets[CameraAxes][0].set (1.0, 0.0, 0.0); // X axis for camera
  sets[CameraAxes][1].set (0.0, 1.0, 0.0); // Y axis for camera
  sets[CameraAxes][2].set (0.0, 0.0, 1.0); // Z axis for camera
  
  // Body axes are same as camera axes initially
  sets[BodyAxes][0] = mNow[0];
  sets[BodyAxes][1] = mNow[1];
  sets[BodyAxes][2] = mNow[2];
}

fArcball::~fArcball ()
{
  delete [] sets[CameraAxes];
  delete [] sets[BodyAxes];
}

fArcball& fArcball::operator = (const fArcball& ab)
{
  // Copy only the center and radius. Reset rest to same as new arcball
  vCenter = ab.vCenter;
  dRadius = ab.dRadius;
  
  dragging = false;
  axisSet = NoAxes;
  
  sets[CameraAxes] = new fVector3[3];
  sets[BodyAxes] = new fVector3[3];
  
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
 * Using vDown, vNow, dragging, and axisSet, compute rotation etc.
 */
void fArcball::update (void)
{
  vFrom = mouseOnSphere (vDown, vCenter, dRadius);
  vTo = mouseOnSphere (vNow, vCenter, dRadius);
  if (dragging)
    {
      if ( axisSet != NoAxes)
	{
	  vFrom = constrainToAxis (vFrom, sets[axisSet][axisIndex]);
	  vTo = constrainToAxis (vTo, sets[axisSet][axisIndex]);
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
      if ( axisSet != NoAxes)
	axisIndex = nearestConstraintAxis (vTo, sets[axisSet], 3);
    }
  mNow = toMatrix4 (conjugate (qNow));
}

static void unitCircle (void)
{
  // Draw a unit circle in the XY plane, centered at the origin
  float dtheta = 2.0*M_PI/32.0;
  
  glBegin (GL_LINE_LOOP);
  for (int i=0; i < 32; ++i)
    fGl::vertex (cosf (i*dtheta), sinf (i*dtheta), 0.0);
  glEnd ();
}

/**
 * Draw a circle with the given normal, center and radius 
 */
static void drawCircle (const fVector3& center, const fVector3& normal, double radius)
{
  // First find the coordinate axis centered at the circle center.
  // The normal will be the Z axis.
  fVector3 xaxis, yaxis, zaxis;
  
  zaxis = normalized (normal);
  xaxis = fVector3 (0,1,0) % zaxis;
  if ( normsqr(xaxis) < 1.0e-5 ) 
    xaxis.set (1,0,0);
  yaxis = zaxis % xaxis;
  
  // Circle will be on the XY plane, defined by the axis system 
  // just computed 
  fVector3 pts[CIRCSEGS+1];
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
      fGl::vertex (pts[i]);
  }
  glEnd ();
}

/**
 * Draw the controller with all its arcs. Parameter is the vector from 
 * the eye point to the center of interest. Default is -ve Z axis
 */
void fArcball::draw(const fVector3&) const
{
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
  
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  {
    RIMCOLOR();
    glScaled(dRadius,dRadius,dRadius);
    unitCircle();
    
    drawConstraints();
    drawDragArc();
  }
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}

/**
 *  Draw an arc defined by its ends.
 */
void fArcball::drawAnyArc(const fVector3& vFrom, const fVector3& vTo)
{
  int i;
  fVector3 pts[NSEGS+1];
  double dot;
  
  pts[0] = vFrom;
  pts[1] = pts[NSEGS] = vTo;
  for (i=0; i < LG_NSEGS; ++i) pts[1] = bisect(pts[0], pts[1]);
  
  dot = 2.0*(pts[0]*pts[1]);
  for (i=2; i < NSEGS; ++i)
    pts[i] = pts[i-1]*dot - pts[i-2];
  
  glBegin (GL_LINE_STRIP);
  for (i=0; i <= NSEGS; ++i)
    fGl::vertex (pts[i]);
  glEnd ();
}

/**
 * Draw the arc of a semi-circle defined by its axis.
 */
void fArcball::drawHalfArc(const fVector3& n)
{
  fVector3 p, m;
  
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
  drawAnyArc(p, m);
  drawAnyArc(m, -p);
}

/**
 * Draw all constraint arcs.
 */
void fArcball::drawConstraints (void) const
{
  if ( axisSet == NoAxes ) return;
  
  fVector3 axis;
  int i;
  
  for (i=0; i < 3; ++i)
    {
      if ( axisIndex != i)
	{
	  if (dragging) continue;
	  FARCOLOR();
	}
      else NEARCOLOR();
      axis = sets[axisSet][i];
      if ( fabs(axis[2]-1.0) < 1.0e-5 )
	unitCircle();
      //drawCircle(0.0, 0.0, 1.0);
      else
	drawHalfArc(axis);
    }
}

/**
 *  Draw "rubber band" arc during dragging.
 */
void fArcball::drawDragArc (void) const
{
  if ( dragging )
    {
      DRAGCOLOR();
      drawAnyArc (vFrom, vTo);
    }
}

fVector3 fArcball::mouseOnSphere (const fVector3& mouse, const fVector3& center, double radius)
{
  fVector3 ballMouse;
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
fQuaternion fArcball::quatFromBallPoints (const fVector3& from, const fVector3& to)
{
  return fQuaternion (from % to, from * to);
}

/**
 * Convert a unit quaternion to two points on unit sphere
 * Assumes that the given quaternion is a unit quaternion
 */
void fArcball::quatToBallPoints (const fQuaternion& q, fVector3& arcFrom, fVector3& arcTo)
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
fVector3 fArcball::constrainToAxis (const fVector3& loose, const fVector3& axis)
{
  fVector3 onPlane;
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
int fArcball::nearestConstraintAxis (const fVector3& loose, fVector3 * axes, int nAxes)
{
  fVector3 onPlane;
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

/**
 * Halve arc between unit vectors v1 and v2.
 * Assumes that v1 and v3 are unit vectors
 */
fVector3 fArcball::bisect (const fVector3& v1, const fVector3& v2)
{
  fVector3 v = v1 + v2;
  float Nv = normsqr (v);
  
  if (Nv < 1.0e-5) 
    v.set (0.0, 0.0, 1.0);
  else
    v /= sqrt(Nv);
  return v;
}
