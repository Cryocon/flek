/* -*-C++-*- 
   
   "$Id: fMatrix4x4.h,v 1.7 2000/02/06 20:40:44 jamespalmer Exp $"
   
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

#ifndef FMATRIX_4x4_H_
#define FMATRIX_4x4_H_

#include <Flek/fBase.h>
#include <Flek/fVector4.h>
#include <Flek/fMatrix3x3.h>

/** @package libflek_ui (The Flek User Interface Library) 
 * Class for a 4x4 matrix. Built from Vector4d
 * Row-major form is used. (ie) each row of the matrix
 * is a Vector3d. This makes inversion easier, since elementary
 * row operations are simplified
 */

class fMatrix4x4 : public fBase
{
public:
  
  typedef fMatrix4x4 * Ptr;
  
  /**
   * Default constructor - creates an identity matrix.
   */
  fMatrix4x4 ()
    : fBase ()
    {
      row[0].set (1.0, 0.0, 0.0, 0.0);
      row[1].set (0.0, 1.0, 0.0, 0.0);
      row[2].set (0.0, 0.0, 1.0, 0.0);
      row[3].set (0.0, 0.0, 0.0, 1.0);
    }
  
  /**
   * 1 argument constructor - from scalar, set all elements to given value
   */
  fMatrix4x4 (double scalar)
    : fBase ()
    {
      row[0] = scalar; row[1] = scalar; row[2] = scalar; row[3] = scalar;
    }
  
  /**
   * 4 argument constructor - from 4 fVector4s
   */
  fMatrix4x4 (const fVector4& r0, const fVector4& r1, const fVector4& r2, const fVector4& r3)
    : fBase ()
    {
      row[0] = r0; row[1] = r1; row[2] = r2; row[3] = r3;
    }
  
  /**
   * Copy constructor
   */
  fMatrix4x4 (const fMatrix4x4& mat)
    : fBase ()
    {
      copyFrom (mat);
    }
  
  /**
   * Constructor from a 3x3 matrix
   */
  fMatrix4x4 (const fMatrix3x3& mat3)
    : fBase ()
    {
      copyFrom (mat3);
    }
  
  /**
   * Destructor
   */
  virtual ~fMatrix4x4 ()
    {}
  
  /**
   * Assignment operator
   */
  fMatrix4x4& operator = (const fMatrix4x4& mat)
    {
      copyFrom (mat);
      return (*this);
    }
  
  /**
   * Assignment from a fMatrix3x3
   */
  fMatrix4x4& operator = (const fMatrix3x3& mat3)
    {
      copyFrom (mat3);
      return (*this);
    }
  
  /**
   * Assignment from a scalar
   */
  void operator = (double scalar)
    {
      row[0] = scalar; row[1] = scalar; row[2] = scalar; row[3] = scalar;
    }
  
  /**
   * Set the rows of the matrix to the given fVector4s
   */
  void set (const fVector4& r0, const fVector4& r1, const fVector4& r2, const fVector4& r3)
    {
      row[0] = r0; row[1] = r1; row[2] = r2; row[3] = r3;
    }
  
  void set (double scalar)
    {
      row[0] = scalar; row[1] = scalar; row[2] = scalar; row[3] = scalar;
    }
  
  /**
   * Reset the matrix to it's default state - identity
   */
  void reset (void)
    {
      row[0].set (1.0, 0.0, 0.0, 0.0);
      row[1].set (0.0, 1.0, 0.0, 0.0);
      row[2].set (0.0, 0.0, 1.0, 0.0);
      row[3].set (0.0, 0.0, 0.0, 1.0);
    }
  
  /** 
   * Make a copy of the object implement fBase class pure virtual function
   */
  virtual fBase::Ptr copy (void) const
    {
      Ptr mat = new fMatrix4x4 (*this);
      return mat;
    }
  
  /**
   * Access a row of the matrix - no range checks.
   */
  fVector4& operator [] (uint index)
    {
      return row[index];
    }
  
  /**
   * Access a row of the matrix - no range checks : const version
   */
  const fVector4& operator [] (uint index) const
    {
      return row[index];
    }
  
  /**
   * Class member functions which return the identity matrix
   */
  static fMatrix4x4 identity (void)
    {
      fMatrix4x4 imat;  // Default constructor creates an identity matrix
      return imat;
    }
  
  /**
   * Class member functions which return the identity matrix
   */
  static fMatrix4x4 I (void)
    {
      fMatrix4x4 imat;  // Default constructor creates an identity matrix
      return imat;
    }
  
  // Arithmetic assignment operators
  
  void operator += (const fMatrix4x4& mat)
    {
      for (int i=0; i < 4; ++i)
	row[i] += mat.row[i];
    }
  
  void operator -= (const fMatrix4x4& mat)
    {
      for (int i=0; i < 4; ++i)
	row[i] -= mat.row[i];
    }
  
  void operator *= (double scalar)
    {
      for (int i=0; i < 4; ++i)
	row[i] *= scalar;
    }
  
  void operator /= (double scalar)
    {
      for (int i=0; i < 4; ++i)
	row[i] /= scalar;
    }
  
  // Special functions - inverse, transpose, etc.
  
  /**
   * Find the 3x3 sub-matrix which is the co-factor for the given element
   */
  fMatrix3x3 cofactor(uint r, uint c) const
    {
      fMatrix3x3 cof;
      fVector3 cofrow;
      uint cfcol, cfrow;
      
      if ( (r > 3) || (c > 3) )
	{
	  cerr << "fMatrix3x3 fMatrix4x4 :: cofactor(int,int) : Index out of range!" << endl;
	  return cof;
	}
      
      cfrow = 0;
      for (uint i=0; i < 4; ++i)
	{
	  if ( i != r )
	    {
	      cfcol = 0;
	      for (uint j=0; j < 4; ++j)
		if ( j != c ) cofrow[cfcol++] = row[i][j];
	      cof[cfrow++] = cofrow;
	    }
	}
      return cof;
    }
  
  void transpose(void)
    {
      for (int i=0; i < 4; ++i)
	for (int j=i+1; j < 4; ++j)
	  swap(row[i][j],row[j][i]);
    }
  
  /**
   * Find the transpose of a given matrix.
   */
  friend fMatrix4x4 transpose(const fMatrix4x4& mat)
    {
      fMatrix4x4 trans (mat); trans.transpose ();
      return trans;
    }
  
  friend double determinant(const fMatrix4x4& mat)
    {
      double det = 0.0;
      
      for (int i=0; i < 3; ++i)
	det += mat[0][i] * cofsign (0, i) * determinant (mat.cofactor (0, i));
      return det;
    }
  
  /**
   * Invert the matrix. Using elementary row operations
   */
  void invert(void)
    {
      fVector4 inv[4];
      int i,j,swaprow;
      
      for (i=0; i < 4; ++i)
	inv[i][i] = 1.0;
      
      // inv will be identity initially and will become the inverse at the end
      for (i=0; i < 4; ++i)
	{
	  // i is column
	  // Find row in this column which has largest element (magnitude)
	  swaprow = i;
	  for (j=i+1; j < 4; ++j)
	    if ( fabs (row[j][i]) > fabs (row[i][i]) ) swaprow = j;
	  
	  if ( swaprow != i )
	    {
	      // Swap the two rows to get largest element in main diagonal
	      // Do this for the RHS also
	      swap (row[i], row[swaprow]); swap (inv[i], inv[swaprow]);
	    }
	  
	  // Check if pivot is non-zero
	  if ( !isNonZero (row[i][i]) )
	    {
	      cerr << "fMatrix4x4 inverse(const fMatrix4x4&) : Singular matrix!" << endl;
	      // Return original matrix without change
	      return;
	    }
	  
	  // Divide matrix by main diagonal element to make it 1.0
	  double fact = row[i][i];
	  for (j=0; j < 4; ++j)
	    {
	      row[j] /= fact;
	      inv[j] /= fact;
	    }
	  
	  // Make non-main-diagonal elements in this column 0 using main-diagonal row
	  for (j=0; j < 4; ++j)
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
      for (i=0; i < 3; ++i)
	{
	  double pivot = row[i][i];
	  row[i] /= pivot;
	  inv[i] /= pivot;
	}
      for (i=0; i < 4; ++i)
	row[i] = inv[i];
    }
  
  /** 
   * Find the inverse of a given matrix using elementary row operations
   */
  friend fMatrix4x4 inverse(const fMatrix4x4& mat)
    {
      fMatrix4x4 inv (mat); inv.invert ();
      return inv;
    }
  
  // Arithmetic operators, implemented as friend functions
  
  /**
   * Negation
   */
  friend fMatrix4x4 operator - (const fMatrix4x4& mat)
    {
      fMatrix4x4 neg;
      
      for (int i=0; i < 4; ++i)
	neg.row[i] = -mat.row[i];
      
      return neg;
    }
  
  friend fMatrix4x4 operator + (const fMatrix4x4& mat1, const fMatrix4x4& mat2)
    {
      fMatrix4x4 sum (mat1);
      sum += mat2;
      return sum;
    }
  
  friend fMatrix4x4 operator - (const fMatrix4x4& mat1, const fMatrix4x4& mat2)
    {
      fMatrix4x4 diff (mat1);
      diff -= mat2;
      return diff;
    }
  
  /**
   * Post-multiplication by a scalar.
   */
  friend fMatrix4x4 operator * (const fMatrix4x4& mat, double scalar)
    {
      fMatrix4x4 prod (mat);
      prod *= scalar;
      return prod;
    }
  
  /**
   * Pre-multiplication by a scalar.
   */
  friend fMatrix4x4 operator * (double scalar, const fMatrix4x4& mat)
    {
      fMatrix4x4 prod (mat);
      prod *= scalar;
      return prod;
    }
  
  /**
   * Division by a scalar.
   */
  friend fMatrix4x4 operator / (const fMatrix4x4& mat, double scalar)
    {
      fMatrix4x4 quot (mat);
      quot /= scalar;
      return quot;
    }
  
  /**
   * Multiplication of 2 matrices - outer product.
   */
  friend fMatrix4x4 operator * (const fMatrix4x4& mat1, const fMatrix4x4& mat2);
  
  /**
   * Element-by-element multiplication of 2 matrices.
   */
  friend fMatrix4x4 product (const fMatrix4x4& mat1, const fMatrix4x4& mat2)
    {
      fMatrix4x4 prod;
      
      prod.row[0] = product (mat1[0], mat2[0]);
      prod.row[1] = product (mat1[1], mat2[1]);
      prod.row[2] = product (mat1[2], mat2[2]);
      prod.row[3] = product (mat1[3], mat2[3]);
      
      return prod;
    }
  
  /**
   * Post-multiplication by a fVector4. Vector is assumed to be a column vector.
   */
  friend fVector4 operator * (const fMatrix4x4& mat, const fVector4& vec)
    {
      fVector4 prod;
      
      prod.set (mat.row[0]*vec, 
		mat.row[1]*vec, 
		mat.row[2]*vec, 
		mat.row[3]*vec);
      return prod;
    }
  
  /**
   * Pre-multiplication by a fVector4. Vector is assumed to be a row vector.
   */
  friend fVector4 operator * (const fVector4& vec, const fMatrix4x4& mat);
  
  /**
   * Multiplication of two fVector4s to produce a fMatrix4x4 - outer product
   * or tensor product of two Vectors.  
   * Same as multiplying row vector (v1) with column vector (v2)
   */
  friend fMatrix4x4 operator ^ (const fVector4& v1, const fVector4& v2)
    {
      fMatrix4x4 prod;
      
      prod.row[0] = v1[0]*v2;
      prod.row[1] = v1[1]*v2;
      prod.row[2] = v1[2]*v2;
      prod.row[3] = v1[3]*v2;
      
      return prod;
    }
  
  friend void swap (fMatrix4x4& mat1, fMatrix4x4& mat2)
    {
      for (int i=0; i < 4; ++i)
	swap (mat1.row[i], mat2.row[i]);
    }
  
  /** 
   * Multiply self with another matrix. Simply calls above defined friend 
   * function.
   */
  void operator *= (const fMatrix4x4& mat)
    {
      fMatrix4x4 prod = (*this) * mat;
      *this = prod;
    }

  /**
   * Fill an array with contents of the matrix
   * Row - major form -> Row 1 == { array[0], array[1], array[2], array[3] }
   */
  void fillArrayRowMajor (double array[16]) const
    {
      int index=0;
      for (int i=0; i < 4; ++i)
	{
	  row[i].get (array[index],
		      array[index+1],
		      array[index+2],
		      array[index+3]);
	  index += 4;
	}
    }

  /**
   * Fill an array with contents of the matrix
   * Row - major form -> Column 1 == { array[0], array[1], array[2], array[3] }  
   */
  void fillArrayColumnMajor (double array[16]) const
    {
      int index=0;
      for (int i=0; i < 4; ++i)
	{
	  row[i].get (array[index], 
		      array[index+4], 
		      array[index+8], 
		      array[index+12]);
	  index += 1;
	}
    }
  
  friend ostream& operator << (ostream& o, const fMatrix4x4& mat)
    {
      o << "[ " << mat.row[0] << "," << endl
	<< "  " << mat.row[1] << "," << endl
	<< "  " << mat.row[2] << "," << endl
	<< "  " << mat.row[3] << " ]" << endl;
      return o;
    }
  
  friend istream& operator >> (istream& i, fMatrix4x4& mat)
    {
      char rowsep, dummy;
      i >> dummy >> mat.row[0] >> rowsep
	>> mat.row[1] >> rowsep
	>> mat.row[2] >> rowsep
	>> mat.row[3] >> dummy;
      return i;
    }
protected:
  
  fVector4   row[4];                                // 4 rows of the matrix
  
  /**
   * Copy values from another matrix
   */
  void copyFrom (const fMatrix4x4& mat)
    {
      for (int i=0; i < 4; ++i)
	row[i] = mat.row[i];
    }
  
  /**
   * Copy from a 3x3 matrix. 4th row and column elements are all set to 0
   */
  void copyFrom (const fMatrix3x3& mat3)
    {
      for (int i=0; i < 3; ++i)
	row[i] = mat3[i];
    }
};

/*
  The following functions are defined outside the class so that they use the
  friend versions of member functions instead of the member functions themselves
*/

/**
 *  Multiplication of 2 matrices - outer product
 */
inline fMatrix4x4 operator * (const fMatrix4x4& mat1, const fMatrix4x4& mat2)
{
  fMatrix4x4 prod, trans;
  
  // Find the transpose of the 2nd matrix
  trans = transpose (mat2);
  
  // The columns of mat2 are now the rows of trans
  // Multiply appropriate rows and columns to get the product
  prod.row[0].set (mat1.row[0]*trans.row[0],
                   mat1.row[0]*trans.row[1],
                   mat1.row[0]*trans.row[2],
                   mat1.row[0]*trans.row[3]);
  prod.row[1].set (mat1.row[1]*trans.row[0],
                   mat1.row[1]*trans.row[1],
                   mat1.row[1]*trans.row[2],
                   mat1.row[1]*trans.row[3]);
  prod.row[2].set (mat1.row[2]*trans.row[0],
                   mat1.row[2]*trans.row[1],
                   mat1.row[2]*trans.row[2],
                   mat1.row[2]*trans.row[3]);
  prod.row[3].set (mat1.row[3]*trans.row[0],
                   mat1.row[3]*trans.row[1],
                   mat1.row[3]*trans.row[2],
                   mat1.row[3]*trans.row[3]);
  return prod;
}

/**
 * Pre-multiplication by a fVector4. Vector is assumed to be a row vector.
 */
inline fVector4 operator * (const fVector4& vec, const fMatrix4x4& mat)
{
  return (transpose(mat) * vec);
}

#endif // #ifndef FMATRIX_4x4_H_
