/* -*-C++-*- 

   "$Id: gl.h,v 1.3 2000/02/13 01:02:32 jamespalmer Exp $"
   
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

#ifndef FGL_H_
#define FGL_H_

#include <Flek/fVector2.h>
#include <Flek/fVector3.h>
#include <Flek/fVector4.h>
#include <Flek/fMatrix4x4.h>
#include <Flek/fMatrix3x3.h>
#include <Flek/fArcball.h>

#include <GL/gl.h>
#include <FL/gl.h>

/** @package libflek_gl
 * Multiply the current GL matrix by the fMatrix M. 
 * This function is a wrapper around the GL function,
 * glMultMatrixd.
 */
void glMultMatrix (const fMatrix4x4& M);

/** 
 * Multiply the current GL matrix by an arcball rotation 
 * matrix.
 */
inline void glMultMatrix (const fArcball& a)
{
  glMultMatrix (a.value ());
}

/**
 * glVertex is used within glBegin - glEnd pairs to specify point, 
 * line, and polygon vertices.  This form takes an fVector4 as
 * it's argument.
 */
inline void glVertex (const fVector4& v)
{
  glVertex4d (v[0], v[1], v[2], v[3]);
}

/**
 * This form of glVertex takes an fVector3 as it's argument.
 */
inline void glVertex (const fVector3& v)
{
  glVertex3d (v[0], v[1], v[2]);
}

/**
 * This form of glVertex takes an fVector2 as it's argument.
 */
inline void glVertex (const fVector2& v)
{
  glVertex2d (v[0], v[1]);
}

/**
 * This form of glVertex takes 4 doubles as it's arguments.
 */
inline void glVertex (const double& x, const double& y, const double& z, const double& w)
{
  glVertex4d (x, y, z, w);
}

/**
 * This form of glVertex takes 3 doubles as it's arguments.
 */
inline void glVertex (const double& x, const double& y, const double& z)
{
  glVertex3d (x, y, z);
}

/**
 * This form of glVertex takes 2 doubles as it's arguments.
 */
inline void glVertex (const double& x, const double& y)
{
  glVertex2d (x, y);
}

/**
 * glColor is used to specify the current color. 
 * This form takes an fVector4 as it's argument (RGBA).
 */
inline void glColor (const fVector4& v)
{
  glColor4d (v[0], v[1], v[2], v[3]);
}

/**
 * This form takes an fVector3 as it's argument (RGB).
 */
inline void glColor (const fVector3& v)
{
  glColor3d (v[0], v[1], v[2]);
}

/**
 * This form takes 4 doubles as it's arguments (RGBA).
 */
inline void glColor (const double& x, const double& y, const double& z, const double& w)
{
  glColor4d (x, y, z, w);
}

/**
 * This form takes 3 doubles as it's arguments (RGB).
 */
inline void glColor (const double& x, const double& y, const double& z)
{
  glColor3d (x, y, z);
}

/**
 * glNormal is used to specify the current normal. 
 * This form takes an fVector4 as it's argument.
 * It ignores the w, or 4th term in the fVector4.
 */
inline void glNormal (const fVector4& v)
{
  glNormal3d (v[0], v[1], v[2]);
}

/**
 * This form takes an fVector3 as it's argument.
 */
inline void glNormal (const fVector3& v)
{
  glNormal3d (v[0], v[1], v[2]);
}

/**
 * This form takes an fVector2 and a z value as it's arguments.
 */
inline void glNormal (const fVector2& v, const double &z)
{
  glNormal3d (v[0], v[1], z);
}

/**
 * This form takes 3 doubles as it's arguments.
 */
inline void glNormal (const double& x, const double& y, const double& z)
{
  glNormal3d (x, y, z);
}

/**
 * glScale scales the current transforamtion matrix by
 * an x, y and z scale component.
 * This form takes an fVector3 as it's argument.
 */
inline void glScale (const fVector3& v)
{
  glScaled (v[0], v[1], v[2]);
}

/**
 * This form takes 3 doubles as it's argument.
 */
inline void glScale (const double &x, const double &y=1, const double &z=1)
{
  glScaled (x, y, z);
}

/**
 * glTranslate translates the current transforamtion matrix by
 * an x, y and z translation component.
 * This form takes an fVector3 as it's argument.
 */
inline void glTranslate (const fVector3& v)
{
  glTranslated (v[0], v[1], v[2]);
}

/**
 * This form takes 3 doubles as it's arguments.
 */
inline void glTranslate (const double &x, const double &y=0, const double &z=0)
{
  glTranslated (x, y, z);
}

#endif