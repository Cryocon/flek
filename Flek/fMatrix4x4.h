#ifndef FMATRIX4X4_H
#define FMATRIX4X4_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <Flek/fVec4d.h>

class fMatrix4x4
{
 public:
  fMatrix4x4 (); 
  fMatrix4x4 (const fMatrix4x4 &M);
  ~fMatrix4x4 ();

  double & operator () (int i,int j);
  double det ();
  fMatrix4x4 operator* (fMatrix4x4 &M);
  fMatrix4x4 operator+ (fMatrix4x4 &M1)const;
  fMatrix4x4 operator- (fMatrix4x4 &M)const;
  fMatrix4x4 operator* (double scalar);
  fMatrix4x4 & operator= (fMatrix4x4 &M);

  void print ();
  
  void identity ();
  fMatrix4x4 transpose ();
  fMatrix4x4  invert ();

  void set_row (int i, fVec4d &V);
  void set_col (int j, fVec4d &V);
  void set_row (int i, double array[]);
  void set_col (int i, double array[]);

  fVec4d get_row (int i);
  fVec4d get_col (int j);
  
  double* get_row_array (int i);
  double* get_col_array (int j);

  void set_value (int i, int j, double thevalue);
  double get_value (int i, int j);
 
  friend fMatrix4x4 operator* (double scalar, fMatrix4x4 &M);
  friend void scalar_mult (double scalar, fMatrix4x4 &M, fMatrix4x4 &result);
  friend fMatrix4x4 multiply (fMatrix4x4 &A, fMatrix4x4 &B, fMatrix4x4 &result);
  friend fMatrix4x4 add (fMatrix4x4 &A, fMatrix4x4 &B, fMatrix4x4 &result);
  friend fMatrix4x4 subtract (fMatrix4x4 &A, fMatrix4x4 &B, fMatrix4x4 &result);
  friend fMatrix4x4 invert (fMatrix4x4 &A, fMatrix4x4 &result);
  friend fMatrix4x4 transpose (fMatrix4x4 &A, fMatrix4x4 &result);

  Matrix4x4 lu_decomp (Matrix4x4 &M, int *indx);
  void lu_backsub (Matrix4x4 &M, int *indx, double col[]);

 protected:
  double data[4][4];
};

#endif
