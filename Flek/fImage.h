/* -*-C++-*- 

   "$Id: fImage.h,v 1.4 2000/03/04 01:39:00 jamespalmer Exp $"
   
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

#ifndef __FIMAGE__
#define __FIMAGE__

typedef unsigned char uchar;

class fImage;

class fImageIterator {

  friend class fImage;

  fImageIterator (uchar *p) : ptr (p)
    {
    }

 public:

  fImageIterator () : ptr (0)
    {
    }

  bool operator == (fImageIterator &p) const
    {
      return (ptr == p.ptr);
    }

  bool operator != (fImageIterator &p) const
    {
      return (ptr != p.ptr);
    }

  fImageIterator operator++ ()
    {
      ptr += 4;
      return *this;
    }

  fImageIterator operator++ (int)
    {
      fImageIterator tmp = *this;
      ptr += 4;
      return tmp;
    }

  fImageIterator operator-- ()
    {
      ptr -= 4;
      return *this;
    }

  fImageIterator operator-- (int)
    {
      fImageIterator tmp = *this;
      ptr -= 4;
      return tmp;
    }

  fImageIterator& operator = (const fImageIterator &p)
    {
      ptr = p.ptr;
      return *this;
    }

  uchar* operator* ()
    {
      return ptr;
    }

 protected:
  uchar *ptr;
};


/** @package libflek_core
 * fImage provides four 8 bit channels (Red, Green, Blue and Alpha).
 * The image is stored internally as an array of unsigned chars in
 * RGBA order.  The internal representation can be used directly by
 * OpenGL with the GL_RGBA format and the GL_UNSIGNED_BYTE type.
 */
class fImage
{
 public:

  typedef fImageIterator iterator;

  /**
   * The default constructor does not allocate any space for the image.
   */
  fImage ()
    {
      Data = 0;
      W = 0;
      H = 0;
    }

  /**
   * This constructor allocated W*H pixels for storing the image.
   */
  fImage (int w, int h)
    {
      W = w;
      H = h;
      Data = new uchar[W*H*4];
    }

  /** 
   * The destructor deallocated any allocated memory.
   */
  ~fImage ()
    {
      if (Data) delete[] Data;
    }

  //void width (int i) { W = i; }
  //void height (int i) { H = i; }

  /**
   * Gets the width of the image.
   */
  int width () { return W; }

  /**
   * Gets the height of the image.
   */
  int height () { return H; }

  /**
   * Return an iterator connected to the first pixel on row r of the image.
   */
  iterator begin (int r)
    {
      return iterator (Data+4*W*r);
    }

  /**
   * Return an iterator connected to the first pixel in the image.
   */
  iterator begin ()
    {
      return iterator (Data);
    }

  /**
   * Return an iterator connected to the last+1 pixel on row r of the image.
   */
  iterator end (int r)
    {
      return iterator (Data+(4*W*(r+1)));
    }

  /**
   * Return an iterator connected to the last+1 pixel in the image.
   */
  iterator end ()
    {
      return iterator (Data+(W*H*4));
    }

  /**
   * Return an iterator connected to position x, y.
   */
  iterator operator() (int x, int y)
    {
      return iterator (Data+((W*y)+x)*4);
    }

 protected:

  uchar *Data;
  int W;
  int H;

};

fImage* add (fImage *A, fImage *B, int xo=0, int yo=0, float o=1.0);

fImage* subtract (fImage *A, fImage *B, int xo=0, int yo=0);

fImage* difference (fImage *A, fImage *B, int xo=0, int yo=0);

fImage* lightenOnly (fImage *A, fImage *B, int xo=0, int yo=0);

fImage* darkenOnly (fImage *A, fImage *B, int xo=0, int yo=0);

fImage* divide (fImage *A, fImage *B, int xo=0, int yo=0);

fImage* multiply (fImage *A, fImage *B, int xo=0, int yo=0);

#endif
