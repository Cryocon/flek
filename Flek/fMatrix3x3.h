#ifndef FMATRIX3X3_H
#define FMATRIX3X3_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <Flek/fVector3.h>

class fMatrix3x3
{
 public:
  fMatrix3x3 (); 
  fMatrix3x3 (const fMatrix3x3 &M);
  ~fMatrix3x3 ();

  double & operator () (int i,int j);
  double det ();
  fMatrix3x3 operator* (fMatrix3x3 &M);
  fMatrix3x3 operator+ (fMatrix3x3 &M1)const;
  fMatrix3x3 operator- (fMatrix3x3 &M)const;
  fMatrix3x3 operator* (double scalar);
  fMatrix3x3 & operator= (fMatrix3x3 &M);

  void print ();
  
  void identity ();
  fMatrix3x3 transpose ();
  fMatrix3x3  invert ();

  void set_row (int i, fVector3 &V);
  void set_col (int j, fVector3 &V);
  void set_row (int i, double array[]);
  void set_col (int i, double array[]);

  fVector3 get_row (int i);
  fVector3 get_col (int j);
  
  double* get_row_array (int i);
  double* get_col_array (int j);

  void set_value (int i, int j, double thevalue);
  double get_value (int i, int j);
 
  friend fMatrix3x3 operator* (double scalar, fMatrix3x3 &M);
  friend void scalar_mult (double scalar, fMatrix3x3 &M, fMatrix3x3 &result);
  friend fMatrix3x3 multiply (fMatrix3x3 &A, fMatrix3x3 &B, fMatrix3x3 &result);
  friend fMatrix3x3 add (fMatrix3x3 &A, fMatrix3x3 &B, fMatrix3x3 &result);
  friend fMatrix3x3 subtract (fMatrix3x3 &A, fMatrix3x3 &B, fMatrix3x3 &result);
  friend fMatrix3x3 invert (fMatrix3x3 &A, fMatrix3x3 &result);
  friend fMatrix3x3 transpose (fMatrix3x3 &A, fMatrix3x3 &result);

 protected:
  double data[3][3];
};

#endif
