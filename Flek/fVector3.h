/* -*-C++-*- 

   "$Id: fVector3.h,v 1.7 2000/02/10 16:55:35 jamespalmer Exp $"
   
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

#ifndef FVECTOR3_H_
#define FVECTOR3_H_

#include <Flek/fVector.h>

/** @package libflek_ui (The Flek User Interface Library)
 * fVector3 is a 3 dimensional vector represented internally as an array of 
 * doubles.  This class is related to fVector2 and fVector4 which are 
 * 2-D and 4-D versions of this class.  All fVector classes are forward
 * declared in fVector.h.
 */

class fVector3 : public fBase
{
public:

  typedef fVector3* Ptr;
  
  /**
   * The default constructor sets each element in the vector to 0.
   */
  fVector3 () 
    : fBase ()
    {
      elem[0] = elem[1] = elem[2] = 0.0;
    }

  /**
   * This one argument constructor intializes all elements in the vector
   * with the given value.
   */
  fVector3 (double val) 
    : fBase ()
    {
      elem[0] = elem[1] = elem[2] = val;
    }
     
  /**
   * This one argument constructor initializes the vector with the first
   * three elements in the given array.
   */
  fVector3 (double * arr)
    : fBase ()
    {
      elem[0] = arr[0]; elem[1] = arr[1]; elem[2] = arr[2];
    }

  /**
   * This three argument constructor initializes the vector with the
   * passed values.
   */
  fVector3 (double val1, double val2, double val3=0.0)
    : fBase ()
    {
      elem[0] = val1; elem[1] = val2; elem[2] = val3;
    }
     
  /**
   * The copy constructor initializes this vector with the contents 
   * of another vector.
   */
  fVector3 (const fVector3& vec)
    : fBase (vec)
    {
      elem[0] = vec.elem[0]; elem[1] = vec.elem[1]; elem[2] = vec.elem[2];
    }

  /**
   * This constructor initializes the vector from the contents of a
   * fVector2 (a 2D vector).  The third element is set to zero.
   */
  fVector3 (const fVector2& vec)
    : fBase ()
    {
      copyFrom (vec);
    }
     
  /**
   * This constructor initializes the vector from the contents of a
   * fVector4.  The third element in the fVector4 is ignored.
   */
  fVector3 (const fVector4& vec)
    : fBase ()
    {
      copyFrom (vec);
    }
     
  /**
   * The virtual destructor does nothing.
   */
  virtual ~fVector3 ()
    {}

  /**
   * Assignment operator from another fVector3.
   */
  fVector3& operator = (const fVector3& vec)
    {
      elem[0] = vec.elem[0]; elem[1] = vec.elem[1]; elem[2] = vec.elem[2];
      return (*this);
    }
  
  /** 
   * Assignment operator from a scalar.  All elements are set to 
   * the scalar value.
   */
  fVector3& operator = (double scalar)
    {
      elem[0] = elem[1] = elem[2] = scalar;
      return (*this);
    }

  /** 
   * Assignment operator from a fVector2.  The third element set to 0.
   */
  fVector3& operator = (const fVector2& vec)
    {
      copyFrom (vec);
      return (*this);
    }
  
  /**
   * Assignment operator from a fVector4.  Copies first 3 elements.
   */
  fVector3& operator = (const fVector4& vec)
    {
      copyFrom (vec);
      return (*this);
    }

  /**
   * Make a copy of the object.
   */
  virtual fBase::Ptr copy (void) const
    {
      Ptr vec = new fVector3 (*this);
      return vec;
    }

  /** 
   * Set each element vector to the given values.
   */
  void set (double v1, double v2, double v3)
    {
      elem[0] = v1; elem[1] = v2; elem[2] = v3;
    }

  /** 
   * Set each element vector to the given value.
   */
  void set (double val)
    {
      elem[0] = elem[1] = elem[2] = val;
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
  void get (double& v1, double& v2, double& v3) const
    {
      v1 = elem[0]; v2 = elem[1]; v3 = elem[2];
    }
     
  /**
   * Fill an array with the elements of the vector.
   */
  void fillArray (double arr[3]) const
    {
      arr[0] = elem[0]; arr[1] = elem[1]; arr[2] = elem[2];
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
  void operator += (const fVector3& vec)
    {
      elem[0] += vec.elem[0]; elem[1] += vec.elem[1]; elem[2] += vec.elem[2];
    }

  /**
   * Arithmetic operator for subtractive assignment.
   */
  void operator -= (const fVector3& vec)
    {
      elem[0] -= vec.elem[0]; elem[1] -= vec.elem[1]; elem[2] -= vec.elem[2];
    }

  /**
   * Arithmetic operator for multiplicative (scalar) assignment.
   */
  void operator *= (double scalar)
    {
      elem[0] *= scalar; elem[1] *= scalar; elem[2] *= scalar;
    }
  
  /**
   * Arithmetic operator for divisive (scalar) assignment.
   */
  void operator /= (double scalar)
    {
      elem[0] /= scalar; elem[1] /= scalar; elem[2] /= scalar;
    }

  /**
   * Arithmetic operator for addition.
   */ 
  fVector3 operator + (const fVector3& vec) const
    {
      fVector3 sum(*this);
      sum += vec;
      return sum;
    }

  /**
   * Arithmetic operator for subtraction.
   */ 
  fVector3 operator - (const fVector3& vec) const
    {
      fVector3 diff(*this);
      diff -= vec;
      return diff;
    }

  /**
   * Operator for scalar multiplication (dot product).
   */
  double operator * (const fVector3& vec) const
    {
      double dotprod = elem[0]*vec.elem[0] + elem[1]*vec.elem[1] + elem[2]*vec.elem[2];
      return dotprod;
    }

  /**
   * Operator for vector multiplication (cross product).
   */
  fVector3 operator % (const fVector3& vec) const
    {
      fVector3 crossp;
      
      crossp.elem[0] = elem[1]*vec.elem[2] - elem[2]*vec.elem[1];
      crossp.elem[1] = elem[2]*vec.elem[0] - elem[0]*vec.elem[2];
      crossp.elem[2] = elem[0]*vec.elem[1] - elem[1]*vec.elem[0];
      
      return crossp;
    }
  
  /**
   * Friend operator for negation.
   */
  friend fVector3 operator - (const fVector3& vec)
    {
      fVector3 negv (-vec.elem[0], -vec.elem[1], -vec.elem[2]);
      return negv;
    }

  /**
   * Friend operator for scalar pre-multiplication.
   */
  friend fVector3 operator * (double scalar, const fVector3& vec)
    {
      fVector3 prod (vec);
      
      prod *= scalar;
      return prod;
    }

  /**
   * Friend operator for scalar post-multiplication.
   */  
  friend fVector3 operator * (const fVector3& vec, double scalar)
    {
      fVector3 prod (vec);
      
      prod *= scalar;
      return prod;
    }

  /**
   * Friend operator for scalar division.
   */
  friend fVector3 operator / (const fVector3& vec, double scalar)
    {
      fVector3 prod (vec);
      
      prod /= scalar;
      return prod;
    }

  /**
   * Friend operator for element-by-element product.
   */
  friend fVector3 product(const fVector3& vec1, const fVector3& vec2)
    {
      fVector3 prod (vec1[0]*vec2[0],vec1[1]*vec2[1],vec1[2]*vec2[2]);
      
      return prod;
    }
    
  /**
   * Boolean equality operator.
   */
  bool operator == (const fVector3& vec) const
    {
      if ( (fabs(elem[0]-vec.elem[0]) > ZERO) ||
	   (fabs(elem[1]-vec.elem[1]) > ZERO) ||
	   (fabs(elem[2]-vec.elem[2]) > ZERO) )
	return false;
      return true;
    }

  /**
   * Boolean ineqality operator.
   */
  bool operator != (const fVector3& vec) const
    {
      return !( (*this) == vec );
    }

  // Other functions
  
  /**
   * Square of the norm of the vector.
   */
  friend double normsqr (const fVector3& vec)
    {
      double nsq = sqr (vec.elem[0]) + sqr (vec.elem[1]) + sqr (vec.elem[2]);
      return nsq;
    }
  
  /**
   * Norm of the vector.
   */
  friend double norm (const fVector3& vec)
    {
      return sqrt (normsqr (vec));
    }

  /**
   * Normalize.  Returns previous norm.
   */
  friend double normalize (fVector3& vec)
    {
      double n = norm (vec);
      if (isNonZero (n) == true) vec /= n;
      return n;
    }
  
  /** 
   * Returns normalized vector.
   */
  friend fVector3 normalized (const fVector3& vec)
    {
      fVector3 nvec (vec);
      normalize (nvec);
      return nvec;
    } 
     
  /**
   * Swap the elements of two fVector3s.
   */
  friend void swap (fVector3& vec1, fVector3& vec2)
    {
      swap (vec1.elem[0], vec2.elem[0]);
      swap (vec1.elem[1], vec2.elem[1]);
      swap (vec1.elem[2], vec2.elem[2]);
    }

  /**
   * I/O Stream extraction operator.  Of the form "[ x y z ]". 
   */ 
  friend istream& operator >> (istream& i, fVector3& vec)
    {
      removeWhiteSpace (i);
      if ( i.peek() == '[' )
	{
	  // Correct format
	  int numread = 0; // No. of elements read
	  double val;
	  char c;
	  
	  i >> c;   // Read opening square bracket
	  while ( numread < 3 )
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
	      cerr << "operator >> fVector3 : Incorrect format. Closing ']' not"
		   << " found upto 10 characters after 3rd element of vector"
		   << endl;
	      exit(0);
	    }
	}
      
      return i;
    }

  /**
   * I/O Stream insertion operator.  Of the form "[ x y z ]". 
   */ 
  friend ostream& operator << (ostream& o, const fVector3& vec) // Insertion operator
    {
      // User can set precision from 0 to 6
      o << setiosflags (ios::fixed) << setiosflags (ios::showpoint);
      
      int oldprec = o.precision ();
      if ( oldprec < 0 ) o << setprecision(0);
      if ( oldprec > 6 ) o << setprecision(6);
      
      o << "["
	<< vec.elem[0] << " "
	<< vec.elem[1] << " "
	<< vec.elem[2]
	<< "]";
      
      o << setprecision(oldprec);
      return o;
    }

 protected:
     
     double elem[3];
  
     /**
      * Initialize the elements from a fVector2,
      */
     void copyFrom (const fVector2& vec);

     /**
      * Initialize the elements from a fVector4,
      */
     void copyFrom (const fVector4& vec);
};

#endif // #ifndef FVECTOR3_H

