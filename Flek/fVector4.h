/* -*-C++-*-
 
   "$Id: fVector4.h,v 1.6 2000/02/11 14:10:38 jamespalmer Exp $"
   
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

#ifndef FVECTOR4_H_
#define FVECTOR4_H_

#include <Flek/fVector.h>

/** @package libflek_ui (The Flek User Interface Library)
 * fVector4 is a 4 dimensional vector represented internally as an array of 
 * doubles.  This class is related to fVector2 and fVector3 which are 
 * 2-D and 3-D versions of this class.  All fVector classes are forward
 * declared in fVector.h.
 */
class fVector4 : public fBase
{
public:

  typedef fVector4* Ptr;
  
  /**
   * The default constructor sets each element in the vector to 0.
   */
  fVector4 ()
    : fBase ()
    {
      elem[0] = elem[1] = elem[2] = elem[3] = 0.0;
    }
  
  /**
   * This one argument constructor intializes all elements in the vector
   * with the given value.
   */
  fVector4 (double val)
    : fBase ()
    {
      elem[0] = elem[1] = elem[2] = elem[3] = val;
    }
  
  /**
   * This one argument constructor initializes the vector with the first
   * three elements in the given array.
   */
  fVector4 (double * arr)
    : fBase ()
    {
      elem[0] = arr[0]; elem[1] = arr[1]; elem[2] = arr[2]; elem[3] = arr[3];
    }
  
  /**
   * This four argument constructor initializes the vector with the
   * passed values.
   */
  fVector4 (double val1, double val2, double val3, double val4)
    : fBase ()
    {
      elem[0] = val1; elem[1] = val2; elem[2] = val3; elem[3] = val4;
    }
  
  /**
   * The copy constructor initializes this vector with the contents 
   * of another vector.
   */
  fVector4 (const fVector4& vec)
    : fBase (vec)
    {
      elem[0] = vec.elem[0]; elem[1] = vec.elem[1];
      elem[2] = vec.elem[2]; elem[3] = vec.elem[3];
    }
  
  /**
   * This constructor initializes the vector from the contents of a
   * fVector2 (a 2D vector).  The third and forth elements are set to zero.
   */
  fVector4 (const fVector2& vec)
    : fBase ()
    {
      copyFrom (vec);
    }
  
  /**
   * This constructor initializes the vector from the contents of a
   * fVector2 (a 2D vector).  The third element is set to zero.
   */
  fVector4 (const fVector3& vec)
    : fBase ()
    {
      copyFrom (vec);
    }
  
  /**
   * The virtual destructor does nothing.
   */
  virtual ~fVector4 ()
    {}

  /**
   * Assignment operator from another fVector3.
   */
  fVector4& operator = (const fVector4& vec)
    {
      elem[0] = vec.elem[0]; elem[1] = vec.elem[1];
      elem[2] = vec.elem[2]; elem[3] = vec.elem[3];
      return (*this);
    }
  
  /** 
   * Assignment operator from a scalar.  All elements are set to 
   * the scalar value.
   */
  fVector4& operator = (double scalar)
    {
      elem[0] = elem[1] = elem[2] = elem[3] = scalar;
      return (*this);
    }
  
  /** 
   * Assignment operator from a fVector2.  The third and forth elements 
   * are set to 0.
   */
  fVector4& operator = (const fVector2& vec)
    {
      copyFrom (vec);
      return (*this);
    }
  
  /** 
   * Assignment operator from a fVector3.  The forth element is set to 0.
   */
  fVector4& operator = (const fVector3& vec)
    {
      copyFrom (vec);
      return (*this);
    }
  
  /**
   * Make a copy of the object.
   */
  virtual fBase::Ptr copy (void) const
    {
      Ptr vec = new fVector4 (*this);
      return vec;
    }
  
  /** 
   * Set each element vector to the given values.
   */
  void set (double v1, double v2, double v3, double v4)
    {
      elem[0] = v1; elem[1] = v2; elem[2] = v3; elem[3] = v4;
    }
  
  /** 
   * Set each element vector to the given value.
   */
  void set (double val)
    {
      elem[0] = elem[1] = elem[2] = elem[3] = val;
    }
  
  /** 
   * Set elements of vector to default values.
   */
  void reset (void)
    {
      set (0.0);
    }
  
  /** 
   * Get the elements of vector into given values.
   */
  void get (double& v1, double& v2, double& v3, double& v4) const
    {
      v1 = elem[0]; v2 = elem[1]; v3 = elem[2]; v4 = elem[3];
    }
  
  /**
   * Fill an array with the elements of the vector.
   */
  void fillArray (double arr[4]) const
    {
      arr[0] = elem[0]; arr[1] = elem[1]; arr[2] = elem[2]; arr[3] = elem[3];
    }
  
  /** 
   * Element access operator.  For efficiency, this doesn't check for 
   * valid indices
   */
  double& operator [] (uint index)
    {
      return elem[index];
    }
  
  /** 
   * Element access operator.  For efficiency, this doesn't check for 
   * valid indices
   */
  double operator [] (uint index) const
    {
      return elem[index];
    }
  
  /**
   * Arithmetic operator for additive assignment.
   */
  void operator += (const fVector4& vec)
    {
      elem[0] += vec.elem[0]; elem[1] += vec.elem[1];
      elem[2] += vec.elem[2]; elem[2] += vec.elem[2];
    }
  
  /**
   * Arithmetic operator for subtractive assignment.
   */
  void operator -= (const fVector4& vec)
    {
      elem[0] -= vec.elem[0]; elem[1] -= vec.elem[1];
      elem[2] -= vec.elem[2]; elem[3] -= vec.elem[3];
    }
  
  /**
   * Arithmetic operator for multiplicative (scalar) assignment.
   */
  void operator *= (double scalar)
    {
      elem[0] *= scalar; elem[1] *= scalar; elem[2] *= scalar; elem[3] *= scalar;
    }
  
  /**
   * Arithmetic operator for divisive (scalar) assignment.
   */
  void operator /= (double scalar)
    {
      elem[0] /= scalar; elem[1] /= scalar; elem[2] /= scalar; elem[3] /= scalar;
    }
  
  /**
   * Arithmetic operator for addition.
   */      
  fVector4 operator + (const fVector4& vec) const
    {
      fVector4 sum(*this);
      sum += vec;
      return sum;
    }
  
  /**
   * Arithmetic operator for subtraction.
   */ 
  fVector4 operator - (const fVector4& vec) const
    {
      fVector4 diff(*this);
      diff -= vec;
      return diff;
    }
  
  /**
   * Operator for scalar multiplication (dot product).
   */
  double operator * (const fVector4& vec) const
    {
      double dotprod = elem[0]*vec.elem[0] + elem[1]*vec.elem[1]
	+ elem[2]*vec.elem[2] + elem[3]*vec.elem[3];
      return dotprod;
    }
  
  /**
   * Friend operator for negation.
   */
  friend fVector4 operator - (const fVector4& vec)
    {
      fVector4 negv (-vec.elem[0], -vec.elem[1], -vec.elem[2], -vec.elem[3]);
      return negv;
    }
  
  /**
   * Friend operator for scalar pre-multiplication.
   */
  friend fVector4 operator * (double scalar, const fVector4& vec)
    {
      fVector4 prod (vec);
      
      prod *= scalar;
      return prod;
    }
  
  /**
   * Friend operator for scalar post-multiplication.
   */  
  friend fVector4 operator * (const fVector4& vec, double scalar)
    {
      fVector4 prod (vec);
      
      prod *= scalar;
      return prod;
    }
  
  /**
   * Friend operator for scalar division.
   */
  friend fVector4 operator / (const fVector4& vec, double scalar)
    {
      fVector4 prod (vec);
      
      prod /= scalar;
      return prod;
    }
  
  /**
   * Friend operator for element-by-element product.
   */
  friend fVector4 product(const fVector4& vec1, const fVector4& vec2)
    {
      fVector4 prod (vec1[0]*vec2[0], vec1[1]*vec2[1], vec1[2]*vec2[2], vec1[3]*vec2[3]);
      
      return prod;
    }
  
  /**
   * Boolean equality operator.
   */     
  bool operator == (const fVector4& vec) const
    {
      if ( (fabs(elem[0]-vec.elem[0]) > ZERO) ||
	   (fabs(elem[1]-vec.elem[1]) > ZERO) ||
	   (fabs(elem[2]-vec.elem[2]) > ZERO) ||
	   (fabs(elem[3]-vec.elem[3]) > ZERO) )
	return false;
      return true;
    }
  
  /**
   * Boolean ineqality operator.
   */
  bool operator != (const fVector4& vec) const
    {
      return !( (*this) == vec );
    }
  
  // Other functions
  
  /**
   * Square of the norm of the vector.
   */     
  friend double normsqr (const fVector4& vec)
    {
      double nsq = sqr (vec.elem[0]) + sqr (vec.elem[1]) + sqr (vec.elem[2]) + sqr (vec.elem[3]);
      return nsq;
    }
  
  /**
   * Norm of the vector.
   */
  friend double norm (const fVector4& vec)
    {
      return sqrt (normsqr (vec));
    }

  /** 
   * Length (norm) of the vector.
   */
  double length ()
    {
      return norm (*this);
    }

  /**
   * Normalize.  Returns previous norm.
   */
  friend double normalize(fVector4& vec)
    {
      double n = norm(vec);
      if ( isNonZero (n) == true ) vec /= n;
      return n;
    }
  
  /** 
   * Returns normalized vector.
   */
  friend fVector4 normalized (const fVector4& vec)
    {
      fVector4 nvec (vec);
      normalize (nvec);
      return nvec;
    }
  
  /**
   * Swap the elements of two fVector4s.
   */     
  friend void swap(fVector4& vec1, fVector4& vec2)
    {
      swap (vec1.elem[0], vec2.elem[0]);
      swap (vec1.elem[1], vec2.elem[1]);
      swap (vec1.elem[2], vec2.elem[2]);
      swap (vec1.elem[3], vec2.elem[3]);
    }
  
  /**
   * I/O Stream extraction operator.  Of the form "[ x y z ]". 
   */ 
  friend istream& operator >> (istream& i, fVector4& vec)
    {
      removeWhiteSpace(i);
      if ( i.peek() == '[' )
	{
	  // Correct format
	  int numread = 0;  // No. of elements read
	  double val;
	  char c;
	  
	  i >> c;  // Read opening square bracket
	  while ( numread < 4 )
	    {
	      i >> val; vec.elem[numread] = val;
	      numread++;
	    }
	  
	  // Read all characters till closing bracket is found
	  // If no. of chars read is more than 10 then print an error
	  // message and exit;
	  i >> c;
	  numread = 1;
	  while ( c != ']' && numread < 10 )
	    {
	      i >> c; numread++;
	    }
	  
	  if ( numread >= 10 )
	    {
	      cerr << "operator >> fVector4 : Incorrect format. Closing ']' not"
		   << " found upto 10 characters after 4th element of vector"
		   << endl;
	      exit(0);
	    }
	}
      
      return i;
    }
  
  /**
   * I/O Stream insertion operator.  Of the form "[ x y z ]". 
   */ 
  friend ostream& operator << (ostream& o, const fVector4& vec)
    {
      // User can set precision from 0 to 6
      o << setiosflags (ios::fixed) << setiosflags (ios::showpoint);
      
      int oldprec = o.precision ();
      if ( oldprec < 0 ) o << setprecision(0);
      if ( oldprec > 6 ) o << setprecision(6);
      
      o << "["
	<< vec.elem[0] << " "
	<< vec.elem[1] << " "
	<< vec.elem[2] << " "
	<< vec.elem[3]
	<< "]";
      
      o << setprecision (oldprec);
      return o;
    }

protected:
  
  double elem[4];
  
  /**
   * Initialize the elements from a fVector2,
   */
  void copyFrom (const fVector2& vec);
  
  /**
   * Initialize the elements from a fVector4,
   */
  void copyFrom (const fVector3& vec);
  
};

#endif // #ifndef FVECTOR_4_H

