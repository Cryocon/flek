#ifndef FVEC3D_
#define FVEC3D_

#include <limits.h>
#include <stdio.h>
#include <math.h>

#if HAVE_GL
#include <GL/gl.h>
#endif

#define INFINITY 9999999999.0

class fVec3d
{
 public:
  fVec3d () {}

  fVec3d (const double x, const double y, const double z) { set (x, y, z); }

  fVec3d (double f) { set (f, f, f); }

  const double * value () { return data; }
    
  void print ()
    {
      printf ("<%g, %g, %g>", data[0], data[1], data[2]);
    }

  void set (double x, double y, double z) 
    { 
      data[0] = x; 
      data[1] = y; 
      data[2] = z; 
    }

  double & operator [](const int i) { return data[i]; }

  double x() { return data[0]; }

  void x(double t) { data[0] = t; }

  double y() { return data[1]; }

  void y(double t) { data[1] = t; }

  double z() { return data[2]; }

  void z(double t) { data[2] = t; }
  
  void normalize ()
    {
      double z  = (1 / length ());
      data[0] *= z;
      data[1] *= z;
      data[2] *= z;
    }

  double norm ()
    {
      return data[0]*data[0] + data[1]*data[1] + data[2]*data[2];
    }
  
  double length ()
    {
      return sqrt (norm ());
    }

  static fVec3d bisect (fVec3d v1, fVec3d v2)
    {
      fVec3d v = v1 + v2;
      double Nv = v.norm ();
      if (Nv < 1.0e-5) {
	v.set (0, 0, 1);
      } else {
	v *= 1 / sqrt (Nv);
      }
      return v;
    }

  static double distance (fVec3d v1, fVec3d v2)
    {
      fVec3d t = v2 - v1;
      return t.length ();
    }
  
  void operator+= (const fVec3d& v) 
    { 
      data[0] += v.data[0]; 
      data[1] += v.data[1]; 
      data[2] += v.data[2]; 
    }

  void operator-= (const fVec3d& v) 
    { 
      data[0] -= v.data[0]; 
      data[1] -= v.data[1]; 
      data[2] -= v.data[2]; 
    }

  void operator/= (const double& v) 
    { 
      data[0] /= v; 
      data[1] /= v; 
      data[2] /= v; 
    }

  void operator*= (const double& v) 
    { 
      data[0] *= v; 
      data[1] *= v; 
      data[2] *= v; 
    }

  fVec3d operator + () const;

  fVec3d operator - () const;

  friend fVec3d operator + (const fVec3d& v1, const fVec3d& v2);

  friend fVec3d operator - (const fVec3d& v1, const fVec3d& v2);

  friend double operator * (const fVec3d& v1, const fVec3d& v2);

  friend fVec3d operator % (const fVec3d& v1, const fVec3d& v2);

  friend fVec3d operator * (const fVec3d& v, double f);

  friend fVec3d operator * (double f, const fVec3d& v);

  friend fVec3d operator / (const fVec3d& v, double f);

  inline void gl_vertex ()
    {
#if HAVE_GL
      glVertex3dv (data);
#endif
    }

  inline void gl_normal ()
    {
#if HAVE_GL
      glNormal3dv (data);
#endif
    }

  inline void gl_tex_coord ()
    {
#if HAVE_GL
      glTexCoord3dv (data);
#endif
    }

  inline void gl_color ()
    {
#if HAVE_GL
      glColor3dv (data);
#endif
    }

  inline void gl_clear_color ()
    {
#if HAVE_GL
      glClearColor (data[0], data[1], data[2], 1.0);
#endif
    }

  inline void gl_rotate (double angle)
    {
#if HAVE_GL
      glRotated (angle, data[0], data[1], data[2]);
#endif
    }

  inline void gl_scale ()
    {
#if HAVE_GL
      glScaled (data[0], data[1], data[2]);
#endif
    }

  inline void gl_translate ()
    {
#if HAVE_GL
      glTranslated (data[0], data[1], data[2]);
#endif
    }

 protected:

  double data[3];
};

inline fVec3d fVec3d::operator + () const { return *this; }

inline fVec3d fVec3d::operator - () const { return fVec3d(-data[0], -data[1], -data[2]); }

inline short 
operator == (const fVec3d& v1, const fVec3d& v2)
{ 
  if ((v1.data[0] == v2.data[0]) &&
      (v1.data[1] == v2.data[1]) &&
      (v1.data[2] == v2.data[2]))
    return 1;
  return 0;
}

inline fVec3d 
operator + (const fVec3d& v1, const fVec3d& v2)
{ 
  return fVec3d (v1.data[0]+v2.data[0], v1.data[1]+v2.data[1], v1.data[2]+v2.data[2]);
}

inline fVec3d 
operator - (const fVec3d& v1, const fVec3d& v2)
{ 
  return fVec3d (v1.data[0]-v2.data[0], v1.data[1]-v2.data[1], v1.data[2]-v2.data[2]); 
}

inline fVec3d 
operator % (const fVec3d& v1, const fVec3d& v2)
{ 
  return fVec3d (v1.data[1] * v2.data[2] - v1.data[2] * v2.data[1], 
		 v1.data[2] * v2.data[0] - v1.data[0] * v2.data[2], 
		 v1.data[0] * v2.data[1] - v1.data[1] * v2.data[0] ); 
}

inline double 
operator * (const fVec3d& v1, const fVec3d& v2)
{ 
  return (v1.data[0] * v2.data[0] +
	  v1.data[1] * v2.data[1] +
	  v1.data[2] * v2.data[2]);
}

inline fVec3d 
operator * (const fVec3d& v, double f)
{ 
  return fVec3d (v.data[0]*f, v.data[1]*f, v.data[2]*f); 
}

inline fVec3d 
operator * (double f, const fVec3d& v)
{ 
  return fVec3d (v.data[0]*f, v.data[1]*f, v.data[2]*f); 
}

inline fVec3d 
operator / (const fVec3d& v, double d)
{
  if ( d != 0.0f ) 
    {
      double e = 1.0f/d;
      return fVec3d (v.data[0]*e, v.data[1]*e, v.data[2]*e); 
    } 
  else 
    {
      return fVec3d (INFINITY, INFINITY, INFINITY);
    }
}

#endif
