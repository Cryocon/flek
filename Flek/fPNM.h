/* -*-C++-*- 

   "$Id: fPNM.h,v 1.4 2000/04/07 19:40:20 jamespalmer Exp $"
   
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

#ifndef __FPNM__
#define __FPNM__

#include <Flek/fImage.h>

/** @package libflek_image
 * The fPNM class provides static methods that read, write and test PNM images.
 * fPNM supports PBM (Portable Bitmap - ASCII (P1) and RAW (P4)), 
 * PGM (Portable Graymap - ASCII (P2) and RAW (P5)), and
 * PPM (Portable Pixmap - ASCII (P3) and RAW (P6)),  fPNM also supports the
 * oft used but very <i>non-standard</i> PPM-P7, which is basically the P6 format
 * with an alpha channel.
 */
class fPNM {
 public:

  /**
   * Check the PBM/PGM/PPM magic number to see if this image matches any of
   * the recognized formats.
   */
  static bool isPNM (char *filename);

  /**
   * Read a PPM from disk and return a new fImage object.
   */
  static fImage * read (char *filename);

  /**
   * Write a PPM to disk from an fImage object.
   */  
  static int write (char *filename, fImage* img);

};

#endif
