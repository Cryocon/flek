/* -*-C++-*- 

   "$Id: fVector2.h,v 1.6 2000/02/13 01:02:32 jamespalmer Exp $"
   
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

#ifndef FVECTOR2_H_
#define FVECTOR2_H_

#include <Flek/fVector.h>

/** @package libflek_core
 * fVector2 is a 2 dimensional vector represented internally as an array of 
 * doubles.  This class is related to fVector3 and fVector4 which are 
 * 3-D and 4-D versions of this class.  All fVector classes are forward
 * declared in fVector.h.
 */

class fVector2 : public fBase
{
public:

  typedef fVector2* Ptr;
  
  /**
   * The default constructor sets each element in the vector to 0.
   */
  fVector2 ()
    : fBase ()
    {
      elem[0] = elem[1] = 0.0;
    }
  
  /**
   * This one argument constructor intializes all elements in the vector
   * with the given value.
   */
  fVector2 (double val)
    : fBase ()
    {
      elem[0] = elem[1] = val;
    }

  /**
   * This one argument constructor initializes the vector with the first
   * three elements in the given array.
   */     
  fVector2 (double * arr)
    : fBase ()
    {
      elem[0] = arr[0]; elem[1] = arr[1];
    }
  
  /**
   * This two argument constructor initializes the vector with the
   * passed values.
   */
  fVector2 (double val1, double val2)
    : fBase ()
    {
      elem[0] = val1; elem[1] = val2;
    }

  /**
   * The copy constructor initializes this vector with the contents 
   * of another vector.
   */     
  fVector2 (const fVector2& vec)
    : fBase (vec)
    {
      elem[0] = vec.elem[0]; elem[1] = vec.elem[1];
    }

  /**
   * This constructor initializes the vector from the contents of a
   * fVector3.  The third element in the fVector3 is ignored.
   */
  fVector2 (const fVector3& vec)
    : fBase ()
    {
      copyFrom (vec);
    }
     
  /**
   * This constructor initializes the vector from the contents of a
   * fVector4.  The third element in the fVector4 is ignored.
   */
  fVector2 (const fVector4& vec)
    : fBase ()
    {
      copyFrom (vec);
    }

  /**
   * The virtual destructor does nothing.
   */
  virtual ~fVector2 ()
    {}

  /**
   * Assignment operator from another fVector2.
   */
  fVector2& operator = (const fVector2& vec)
    {
      elem[0] = vec.elem[0]; elem[1] = vec.elem[1];
      return (*this);
    }

  /** 
   * Assignment operator from a scalar.  All elements are set to 
   * the scalar value.
   */
  fVector2& operator = (double scalar)
    {
      elem[0] = elem[1] = scalar;
      return (*this);
    }

  /**
   * Assignment operator from a fVector3.  Copies first 2 elements.
   */
  fVector2& operator = (const fVector3& vec)
    {
      copyFrom (vec);
      return (*this);
    }

  /**
   * Assignment operator from a fVector4.  Copies first 2 elements.
   */
  fVector2& operator = (const fVector4& vec)
    {
      copyFrom (vec);
      return (*this);
    }

  /**
   * Make a copy of the object.
   */
  virtual fBase::Ptr copy (void) const
    {
      Ptr vec = new fVector2 (*this);
      return vec;
    }

  /** 
   * Set each element vector to the given values.
   */
  void set (double v1, double v2)
    {
      elem[0] = v1; elem[1] = v2;
    }
  
  /** 
   * Set each element vector to the given value.
   */
  void set (double val)
    {
      elem[0] = elem[1] = val;
    }
     
  /** 
   * Set elements of vector to default values.
   */
  void reset (void)
    {
      set(0.0);
    }

  /** 
   * Get the elements of vector into given values.
   */
  void get (double& v1, double& v2) const
    {
      v1 = elem[0]; v2 = elem[1];
    }

  /**
   * Fill an array with the elements of the vector.
   */
  void fillArray (double arr[2]) const
    {
      arr[0] = elem[0]; arr[1] = elem[1];
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
  void operator += (const fVector2& vec)
    {
      elem[0] += vec.elem[0]; elem[1] += vec.elem[1];
    }

  /**
   * Arithmetic operator for subtractive assignment.
   */
  void operator -= (const fVector2& vec) 
    {
      elem[0] -= vec.elem[0]; elem[1] -= vec.elem[1];
    }
  
  /**
   * Arithmetic operator for multiplicative (scalar) assignment.
   */
  void operator *= (double scalar)
    {
      elem[0] *= scalar; elem[1] *= scalar;
    }
    
  /**
   * Arithmetic operator for divisive (scalar) assignment.
   */ 
  void operator /= (double scalar)
    {
      elem[0] /= scalar; elem[1] /= scalar;
    }
    
  /**
   * Arithmetic operator for addition.
   */
  fVector2 operator + (const fVector2& vec) const
    {
      fVector2 sum(*this);
      sum += vec;
      return sum;
    }
  
  /**
   * Arithmetic operator for subtraction.
   */ 
  fVector2 operator - (const fVector2& vec) const
    {
      fVector2 diff(*this);
      diff -= vec;
      return diff;
    }
  
  /**
   * Operator for scalar multiplication (dot product).
   */
  double operator * (const fVector2& vec) const
    {
      double dotprod = elem[0]*vec.elem[0] + elem[1]*vec.elem[1];
      return dotprod;
    }

  /**
   * Friend operator for negation.
   */
  friend fVector2 operator - (const fVector2& vec)
    {
      fVector2 negv (-vec.elem[0], -vec.elem[1]);
      return negv;
    }
  
  /**
   * Friend operator for scalar pre-multiplication.
   */
  friend fVector2 operator * (double scalar, const fVector2& vec)
    {
      fVector2 prod (vec);
      
      prod *= scalar;
      return prod;
    }

  /**
   * Friend operator for scalar post-multiplication.
   */  
  friend fVector2 operator * (const fVector2& vec, double scalar)
    {
      fVector2 prod (vec);
      
      prod *= scalar;
      return prod;
    }

  /**
   * Friend operator for scalar division.
   */
  friend fVector2 operator / (const fVector2& vec, double scalar)
    {
      fVector2 prod (vec);
      
      prod /= scalar;
      return prod;
    }

  /**
   * Friend operator for element-by-element product.
   */ 
  friend fVector2 product(const fVector2& vec1, const fVector2& vec2)
    {
      fVector2 prod(vec1[0]*vec2[0],vec1[1]*vec2[1]);
      
      return prod;
    }
     
  /**
   * Boolean equality operator.
   */       
  bool operator == (const fVector2& vec) const
    {
      if ( (fabs(elem[0]-vec.elem[0]) > ZERO) ||
	   (fabs(elem[1]-vec.elem[1]) > ZERO) )
	return false;
      return true;
    }

  /**
   * Boolean ineqality operator.
   */
  bool operator != (const fVector2& vec) const
    {
      return !( (*this) == vec );
    }

  /**
   * Square of the norm of the vector.
   */ 
  friend double normsqr(const fVector2& vec)
    {
      double nsq = sqr (vec.elem[0]) + sqr (vec.elem[1]);
      return nsq;
    }
     
  /**
   * Norm of the vector.
   */
  friend double norm (const fVector2& vec)
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
  friend double normalize (fVector2& vec)
    {
      double n = norm (vec);
      if ( isNonZero (n) == true ) vec /= n;
      return n;
    }

  /** 
   * Returns normalized vector.
   */
  friend fVector2 normalized (const fVector2& vec)
    {
      fVector2 nvec (vec);
      normalize (nvec);
      return nvec;
    }

  /**
   * Swap the elements of two fVector2s.
   */     
  friend void swap (fVector2& vec1, fVector2& vec2)
    {
      swap (vec1.elem[0], vec2.elem[0]);
      swap (vec1.elem[1], vec2.elem[1]);
    }

  /**
   * I/O Stream extraction operator.  Of the form "[ x y ]". 
   */ 
  friend istream& operator >> (istream& i, fVector2& vec)
    {
      removeWhiteSpace (i);
      if ( i.peek() == '[' )
	{
	  // Correct format
	  int numread = 0;  // No. of elements read
	  double val;
	  char c;
	  
	  i >> c;  // Read opening square bracket
	  while ( numread < 2 )
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
	      cerr << "operator >> fVector2 : Incorrect format. Closing ']' not"
		   << " found upto 10 characters after 2nd element of vector"
		   << endl;
	      exit(0);
	    }
	}
      
      return i;
    }

  /**
   * I/O Stream insertion operator.  Of the form "[ x y z ]". 
   */ 
  friend ostream& operator << (ostream& o, const fVector2& vec)
    {
      // User can set precision from 0 to 6
      o << setiosflags(ios::fixed) << setiosflags (ios::showpoint);
      
      int oldprec = o.precision ();
      if ( oldprec < 0 ) o << setprecision(0);
      if ( oldprec > 6 ) o << setprecision(6);
      
      o << "["
	<< vec.elem[0] << " "
	<< vec.elem[1]
	<< "]";
      
      o << setprecision (oldprec);
      return o;
    }
  
protected:
  
  double elem[2];

  /**
   * Initialize the elements from a fVector3,
   */
  void copyFrom (const fVector3& vec);

  /**
   * Initialize the elements from a fVector4,
   */
  void copyFrom (const fVector4& vec);

};

#endif // #ifndef FVECTOR2_H_

