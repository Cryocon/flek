/* -*-C++-*- 

   "$Id: fMatrix3x3.h,v 1.2 2000/02/06 08:39:17 jamespalmer Exp $"
   
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

#ifndef FMATRIX_3x3_H_
#define FMATRIX_3x3_H_

#include <Flek/fBase.h>
#include <Flek/fVector3.h>

/** Class for a 3x3 matrix. Built from Vector3d
 * Row-major form is used. (ie) each row of the matrix
 * is a Vector3d. This makes inversion easier, since elementary
 * row operations are simplified
 */

class fMatrix3x3 : public fBase
{
public:
  
  typedef fMatrix3x3 * Ptr;
  
  /**
   * Default constructor - creates an identity matrix
   */
  fMatrix3x3 ()
    : fBase ()
    {
      row[0].set (1.0, 0.0, 0.0);
      row[1].set (0.0, 1.0, 0.0);
      row[2].set (0.0, 0.0, 1.0);
    }

  /**
   * 1 argument constructor - from scalar, set all elements to given value
   */
  fMatrix3x3 (double scalar)
    : fBase ()
    {
      row[0] = scalar; row[1] = scalar; row[2] = scalar;
    }
  
  /**
   * 3 argument constructor - from 3 fVector3s
   */
  fMatrix3x3 (const fVector3& r0, const fVector3& r1, const fVector3& r2)
    : fBase ()
    {
      row[0] = r0; row[1] = r1; row[2] = r2;
    }

  /**
   * Copy constructor
   */
  fMatrix3x3 (const fMatrix3x3& mat)
    : fBase ()
    {
      copyFrom (mat);
    }

  /**
   * Destructor
   */
  virtual ~fMatrix3x3 ()
    {}
  
  /**
   *  Assignment operator
   */
  fMatrix3x3& operator = (const fMatrix3x3& mat)
    {
      copyFrom (mat);
      return (*this);
    }
  
  /**
   * Assignment from a scalar
   */
  void operator = (double scalar)
    {
      row[0] = scalar; row[1] = scalar; row[2] = scalar;
    }
  
  /**
   * Set the rows of the matrix to the given fVector3s
   */
  void set(const fVector3& r0, const fVector3& r1, const fVector3& r2)
    {
      row[0] = r0; row[1] = r1; row[2] = r2;
    }
  
  void set(double scalar)
    {
      row[0] = scalar; row[1] = scalar; row[2] = scalar;
    }
     
  /**
   *  Reset the matrix to it's default state - identity
   */
  void reset(void)
    {
      row[0].set (1.0, 0.0, 0.0);
      row[1].set (0.0, 1.0, 0.0);
      row[2].set (0.0, 0.0, 1.0);
    }
  
  /** 
   * Make a copy of the object
   * implement fBase class pure virtual function
   */
  virtual fBase::Ptr copy (void) const
    {
      Ptr mat = new fMatrix3x3 (*this);
      return mat;
    }

  /**
   * Access a row of the matrix - no range checks
   */
  fVector3& operator [] (uint index)
    {
      return row[index];
    }

  /**
   * Access a row of the matrix - no range checks : const version
   */
  const fVector3& operator [] (uint index) const
    {
      return row[index];
    }

  /**
   * Class member functions which return the identity matrix
   */
  static fMatrix3x3 identity (void)
    {
      fMatrix3x3 imat;  // Default constructor creates an identity matrix
      return imat;
    }
     
  static fMatrix3x3 I (void)
    {
      fMatrix3x3 imat;  // Default constructor creates an identity matrix
      return imat;
    }
  
  //--- Arithmetic assignment operators ---//
  
  void operator += (const fMatrix3x3& mat)
    {
      for (int i=0; i < 3; ++i)
	row[i] += mat.row[i];
    }
  
  void operator -= (const fMatrix3x3& mat)
    {
      for (int i=0; i < 3; ++i)
	row[i] -= mat.row[i];
    }
  
  void operator *= (double scalar)
    {
      for (int i=0; i < 3; ++i)
	row[i] *= scalar;
    }
  
  void operator /= (double scalar)
    {
      for (int i=0; i < 3; ++i)
	row[i] /= scalar;
    }
  
  /**
   * Find the transpose of a given matrix.
   */
  void transpose (void)
    {
      for (int i=0; i < 3; ++i)
	for (int j=i+1; j < 3; ++j)
	  swap (row[i][j], row[j][i]);
    }

  /**
   * Find the transpose of a given matrix.
   */
  friend fMatrix3x3 transpose (const fMatrix3x3& mat)
    {
      fMatrix3x3 trans (mat); trans.transpose ();
      return trans;
    }

  /**
   * Find the determinant of a given matrix.
   */  
  friend double determinant(const fMatrix3x3& mat)
    {
      double det = 0.0;
      
      det =   mat[0][0] * mat[1][1] * mat[2][2] 
	+ mat[0][1] * mat[1][2] * mat[2][0] 
	+ mat[0][2] * mat[1][0] * mat[2][1] 
	- mat[2][0] * mat[1][1] * mat[0][2] 
	- mat[2][1] * mat[1][2] * mat[0][0] 
	- mat[2][2] * mat[1][0] * mat[0][1];
      return det;
    }
  
  /**
   * Invert the matrix, using elementary row operations.
   */
  void invert (void)
    {
      fVector3 inv[3];
      int i,j,swaprow;
      
      // inv will be identity initially and will become the inverse at the end
      for (i=0; i < 3; ++i)
	{
	  // i is column
	  // Find row in this column which has largest element (magnitude)
	  swaprow = i;
	  for (j=i+1; j < 3; ++j)
	    if ( fabs (row[j][i]) > fabs (row[i][i]) ) swaprow = j;
	  
	  if ( swaprow != i )
	    {
	      // Swap the two rows to get largest element in main diagonal
	      // Do this for the RHS also
	      swap (row[i],row[swaprow]); 
	      swap (inv[i],inv[swaprow]);
	    }
	  
	  // Check if pivot is non-zero
	  if ( !isNonZero(row[i][i]) )
	    {
	      cerr << "fMatrix3x3 inverse(const fMatrix3x3&) : Singular matrix!" << endl;
	      // Return original matrix without change
	      return;
	    }
	  
	  // Divide matrix by main diagonal element to make it 1.0
	  double fact = row[i][i];
	  for (j=0; j < 3; ++j)
	    {
	      row[j] /= fact;
	      inv[j] /= fact;
	    }
	  
	  // Make non-main-diagonal elements in this column 0 using main-diagonal row
	  for (j=0; j < 3; ++j)
	    {
	      if ( j != i )
		{
		  double temp = row[j][i];
		  row[j] -= row[i]*temp;
		  inv[j] -= inv[i]*temp;
		}
	    }
	}
      
      // Main-diagonal elements on LHS may not be 1.0 now. Divide to make LHS identity
      // Last row will be 1.0
      for (i=0; i < 2; ++i)
	{
	  double pivot = row[i][i];
	  row[i] /= pivot;
	  inv[i] /= pivot;
	}
      for (i=0; i < 3; ++i)
	row[i] = inv[i];
    }
  
  /**
   * Find the inverse of a given matrix using elementary row operations
   */
  friend fMatrix3x3 inverse (const fMatrix3x3& mat)
    {
      fMatrix3x3 inv (mat); inv.invert ();
      return inv;
    }
  
  //--- Arithmetic operators, implemented as friend functions ---//
  
  /**
   * Negation
   */
  friend fMatrix3x3 operator - (const fMatrix3x3& mat)
    {
      fMatrix3x3 neg;
      
      for (int i=0; i < 3; ++i)
	neg.row[i] = -mat.row[i];
      
      return neg;
    }
  
  friend fMatrix3x3 operator + (const fMatrix3x3& mat1, const fMatrix3x3& mat2)
    {
      fMatrix3x3 sum (mat1);
      sum += mat2;
      return sum;
    }
  
  friend fMatrix3x3 operator - (const fMatrix3x3& mat1, const fMatrix3x3& mat2)
    {
      fMatrix3x3 diff (mat1);
      diff -= mat2;
      return diff;
    }
  
  /**
   * Post-multiplication by a scalar.
   */
  friend fMatrix3x3 operator * (const fMatrix3x3& mat, double scalar)
    {
      fMatrix3x3 prod (mat);
      prod *= scalar;
      return prod;
    }
  
  /**
   * Pre-multiplication by a scalar.
   */
  friend fMatrix3x3 operator * (double scalar, const fMatrix3x3& mat)
    {
      fMatrix3x3 prod (mat);
      prod *= scalar;
      return prod;
    }
  
  /**
   * Division by a scalar.
   */
  friend fMatrix3x3 operator / (const fMatrix3x3& mat, double scalar)
    {
      fMatrix3x3 quot (mat);
      quot /= scalar;
      return quot;
    }
  
  /**
   * Multiplication of 2 matrices - outer product.
   */
  friend fMatrix3x3 operator * (const fMatrix3x3& mat1, const fMatrix3x3& mat2);
  
  /** 
   * Element-by-element multiplication of 2 matrices.
   */
  friend fMatrix3x3 product (const fMatrix3x3& mat1, const fMatrix3x3& mat2)
    {
      fMatrix3x3 prod;
      
      prod.row[0] = product (mat1[0], mat2[0]);
      prod.row[1] = product (mat1[1], mat2[1]);
      prod.row[2] = product (mat1[2], mat2[2]);
      
      return prod;
    }
  
  /**
   * Post-multiplication by a fVector3. Vector is assumed to be a column vector.
   */
  friend fVector3 operator * (const fMatrix3x3& mat, const fVector3& vec)
    {
      fVector3 prod;
      
      prod.set (mat.row[0]*vec, mat.row[1]*vec, mat.row[2]*vec);
      return prod;
    }
  
  /**
   * Pre-multiplication by a fVector3. Vector is assumed to be a row vector.
   */
  friend fVector3 operator * (const fVector3& vec, const fMatrix3x3& mat);
  
  /** 
   * Multiplication of two fVector3s to produce a fMatrix3x3 - outer product
   * or tensor product of two Vectors.  Same as multiplying row vector (v1) 
   * with column vector (v2) 
   */
  friend fMatrix3x3 operator ^ (const fVector3& v1, const fVector3& v2)
    {
      fMatrix3x3 prod;
      
      prod.row[0] = v1[0]*v2;
      prod.row[1] = v1[1]*v2;
      prod.row[2] = v1[2]*v2;
      
      return prod;
    }
  
  friend void swap (fMatrix3x3& mat1, fMatrix3x3& mat2)
    {
      for (int i=0; i < 3; ++i)
	swap (mat1.row[i], mat2.row[i]);
    }
  
  /**
   * Multiply self with another matrix. Simply calls above defined 
   * friend function.
   */
  void operator *= (const fMatrix3x3& mat)
    {
      fMatrix3x3 prod = (*this) * mat;
      *this = prod;
    }
  
  friend ostream& operator << (ostream& o, const fMatrix3x3& mat)
    {
      o << "[ " << mat.row[0] << "," << endl
	<< "  " << mat.row[1] << "," << endl
	<< "  " << mat.row[2] << " ]" << endl;
      return o;
    }
  
  friend istream& operator >> (istream& i, fMatrix3x3& mat)
    {
      char rowsep, dummy;
      i >> dummy >> mat.row[0] >> rowsep
	>> mat.row[1] >> rowsep
	>> mat.row[2] >> dummy;
      return i;
    }
  
protected:
  
  /**
   * 3 rows of the matrix
   */
  fVector3 row[3];
  
  /**
   * Copy values from another matrix.
   */
  void copyFrom (const fMatrix3x3& mat)
    {
      for (int i=0; i < 3; ++i)
	row[i] = mat.row[i];
    }
};

/*
  The following functions are defined outside the class so that they use the
  friend versions of member functions instead of the member functions themselves
*/

/**
 * Multiplication of 2 matrices - outer product
 */
inline fMatrix3x3 operator * (const fMatrix3x3& mat1, const fMatrix3x3& mat2)
{
  fMatrix3x3 prod, trans;
  
  // Find the transpose of the 2nd matrix
  trans = transpose (mat2);
  
  // The columns of mat2 are now the rows of trans
  // Multiply appropriate rows and columns to get the product
  prod.row[0].set (mat1.row[0]*trans.row[0],
                   mat1.row[0]*trans.row[1],
                   mat1.row[0]*trans.row[2]);
  prod.row[1].set (mat1.row[1]*trans.row[0],
                   mat1.row[1]*trans.row[1],
                   mat1.row[1]*trans.row[2]);
  prod.row[2].set (mat1.row[2]*trans.row[0],
                   mat1.row[2]*trans.row[1],
                   mat1.row[2]*trans.row[2]);
  return prod;
}

/**
 * Pre-multiplication by a fVector3. Vector is assumed to be a row vector.
 */
inline fVector3 operator * (const fVector3& vec, const fMatrix3x3& mat)
{
  return (transpose(mat) * vec);
}

#endif // #ifndef FMATRIX_3x3_H_ 
