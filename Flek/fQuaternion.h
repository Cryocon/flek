#ifndef QUATERNION_H
#define QUATERNION_H

#define PI 3.14159265359

#define RAD2DEG (180.0/PI)  
#define DEG2RAD (PI/180.0)

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <Flek/fVector3.h>
#include <Flek/fMatrix3x3.h>

class fQuaternion
{
 public:
  fVector3 v;   
  double s;
  
  fQuaternion ()
    {
      s = 1.0;
      v[0] = 0;
      v[1] = 0;
      v[2] = 0;
    }

  fQuaternion (double S, double x, double y, double z)
    {
      s = S;
      v[0] = x;
      v[1] = y;
      v[2] = z;
    }

  ~fQuaternion () {};

  fQuaternion inverse ();

  fQuaternion conjugate ();

  fQuaternion Qprime (fVector3 &wt);

  void print ();  

  double norm ();

  void normalize ();

  fQuaternion matrix_to_quaternion (fMatrix3x3 &M);

  fMatrix3x3 quaternion_to_matrix ();

  double & operator[] (unsigned int i);

  fQuaternion & operator= (const fQuaternion &Q);

  fQuaternion & operator= (double array[]);

  fQuaternion operator+ (const fQuaternion &Q) const;

  fQuaternion operator- (const fQuaternion &Q) const;

  fQuaternion operator* (fQuaternion &Q);

  fQuaternion operator* (double scalar);
};
#endif
