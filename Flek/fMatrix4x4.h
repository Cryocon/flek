#ifndef FMATRIX3X3_H
#define FMATRIX3X3_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <Flek/fVector3.h>
#include <GL/gl.h>

class fMatrix4x4
{
 public:
  fMatrix4x4 () {}
  fMatrix4x4 (double);
  fMatrix4x4 (const fMatrix4x4 &M);
  ~fMatrix4x4 () {}

  double & operator () (int i, int j) { return data[i][j]; }
  fMatrix4x4 operator* (fMatrix4x4 &M);
  fMatrix4x4 operator+ (fMatrix4x4 &M1)const;
  fMatrix4x4 operator- (fMatrix4x4 &M)const;
  fMatrix4x4 operator* (double scalar);
  fMatrix4x4 & operator= (fMatrix4x4 &M);

  void zero ();
  void identity ();
  fMatrix4x4 transpose ();
  fMatrix4x4 invert ();
  double determinant ();
  void print ();

  inline void set (int i, int j, double value) { data[i][j] = value; }
  inline double get (int i, int j) { return data[i][j]; }
  
  void set_row (int i, fVector3 &V);
  void set_col (int j, fVector3 &V);
  void set_row (int i, double array[]);
  void set_col (int i, double array[]);

  fVector3 get_row_v3 (int i);
  fVector3 get_col_v3 (int j);
  double* get_row_array (int i) { return &data[i][0]; }
  double* value () { return &data[0][0]; }
  //double* get_col_array (int j);

  friend fMatrix4x4 operator* (double scalar, fMatrix4x4 &M);
  friend void scalar_mult (double scalar, fMatrix4x4 &M, fMatrix4x4 &result);
  friend fMatrix4x4 multiply (fMatrix4x4 &A, fMatrix4x4 &B, fMatrix4x4 &result);
  friend fMatrix4x4 add (fMatrix4x4 &A, fMatrix4x4 &B, fMatrix4x4 &result);
  friend fMatrix4x4 subtract (fMatrix4x4 &A, fMatrix4x4 &B, fMatrix4x4 &result);
  friend fMatrix4x4 invert (fMatrix4x4 &A, fMatrix4x4 &result);
  friend fMatrix4x4 transpose (fMatrix4x4 &A, fMatrix4x4 &result);

 protected:
  double data[4][4];
};

#endif
