#ifndef QUATERNION_H
#define QUATERNION_H

#ifndef PI
#define PI 3.14159265359
#endif

#define RAD2DEG (180.0/PI)  
#define DEG2RAD (PI/180.0)

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <Flek/fVector3.h>
#include <Flek/fMatrix4x4.h>

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

  fQuaternion (double x, double y, double z, double w)
    {
      set (x, y, z, w);
    }

  ~fQuaternion () {};

  void set (double x, double y, double z, double w)
    {
      s = w;
      v[0] = x;
      v[1] = y;
      v[2] = z;
    }

  fQuaternion inverse ();

  fQuaternion conjugate ();

  fQuaternion Qprime (fVector3 &wt);

  void print ();  

  double norm ();

  void normalize ();

  fQuaternion from_matrix (fMatrix4x4 &M);

  fMatrix4x4 to_matrix ();

  double & operator[] (unsigned int i);

  fQuaternion & operator= (const fQuaternion &Q);

  fQuaternion & operator= (double array[]);

  fQuaternion operator+ (const fQuaternion &Q) const;

  fQuaternion operator- (const fQuaternion &Q) const;

  fQuaternion operator* (fQuaternion &Q);

  fQuaternion operator* (double scalar);
};
#endif
