/* -*-C++-*- 

   "$Id: fGl.h,v 1.1 2000/02/06 08:39:17 jamespalmer Exp $"
   
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

class fGl : public fBase 
{
public:

  static inline void vertex (const fVector4& v)
    {
      glVertex4dv (v.elem);
    }
  static inline void vertex (const fVector3& v)
    {
      glVertex3dv (v.elem);
    }
  static inline void vertex (const fVector2& v)
    {
      glVertex2dv (v.elem);
    }

  static inline void vertex (const double& x, const double& y, const double& z, const double& w)
    {
      glVertex4d (x, y, z, w);
    }

  static inline void vertex (const double& x, const double& y, const double& z)
    {
      glVertex3d (x, y, z);
    }

  static inline void vertex (const double& x, const double& y)
    {
      glVertex2d (x, y);
    }
};

//fGl::vertex (x);

#endif
