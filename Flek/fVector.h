/* -*-C++-*- 
   "$Id: fVector.h,v 1.1 2000/02/06 08:39:17 jamespalmer Exp $"
   
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

#ifndef FVECTOR_H_
#define FVECTOR_H_

/*
 * Common stuff for all the static Vector classes
 * Forward declarations for all the classes is included here, along with 
 * common include files and prototypes for functions that use different kinds
 * of Vectors.
 */

// Common include files
#include <stdlib.h>
#include <Flek/math.h>
#include <Flek/iostream.h>
#include <Flek/fBase.h>

// Forward declarations
class fVector2;
class fVector3;
class fVector4;
class fGl;

// Function prototypes
fVector3 operator % (const fVector2& vec1, const fVector2& vec2);
fVector3 operator % (const fVector3& vec1, const fVector2& vec2);
fVector3 operator % (const fVector2& vec1, const fVector3& vec2);

#endif // #ifndef FVECTOR_H_

