/* -*-C++-*- 

   "$Id: fQuaternion.h,v 1.7 2000/02/13 01:02:32 jamespalmer Exp $"
  
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

#ifndef FQUATERNION_H_
#define FQUATERNION_H_

#include <Flek/fBase.h>
#include <Flek/fVector3.h>
#include <Flek/fMatrix4x4.h>

/** @package libflek_core
 * The Quaternion class.
 */
class fQuaternion : public fBase
{
public:

  /**
   * Default constructor - create an identity quaternion
   */
  fQuaternion ()
    : fBase (), v (), w (1.0)
    {}

  /** 
   * Construct from a vector. Scalar is set to 0
   */
  fQuaternion (const fVector3& vec)
    : fBase (), v (vec), w (0.0)
    {}
  
  /**
   * Constructor from a vector and a scalar
   */
  fQuaternion (const fVector3& vec, double scalar)
    : fBase (), v (vec), w (scalar)
    {}

  /**
   * Same as above, but with reverse order
   */
  fQuaternion (double scalar, const fVector3& vec)
    : fBase (), v (vec), w (scalar)
    {}

  /**
   * Construct from 3/4 individual values. Scalar is set to 0 by default
   */
  fQuaternion (double x, double y, double z, double scalar=0.0)
    : fBase (), v (x, y, z), w (scalar)
    {}

  /**
   * Copy constructor
   */
  fQuaternion (const fQuaternion& quat)
    : fBase (quat), v (quat.v), w (quat.w)
    {}

  /**
   * Destructor
   */
  ~fQuaternion ()
    {}

  /**
   * Assignment operator
   */
  fQuaternion& operator = (const fQuaternion& quat)
    {
      fBase :: operator = (quat);
      v = quat.v; w = quat.w;
      return (*this);
    }

  /**
   * Assignment from fVector3
   */
  fQuaternion& operator = (const fVector3& vec)
    {
      v = vec; w = 0.0;
      return (*this);
    }
     
  /**
   * Set the vector and scalar parts of the quaternion
   */
  void set (const fVector3& vec, double scalar=0.0)
    {
      v = vec; w = scalar;
    }

  /**
   * Set the vector and scalar parts of the quaternion
   */
  void set (double x, double y, double z, double scalar=0.0)
    {
      v.set (x, y, z); w = scalar;
    }

  /**
   * Reset the quaternion to its default state - identity.
   */
  void reset (void)
    {
      v.reset (); w = 1.0;
    }

  /**
   *  Make a copy of the object implement fBase class pure virtual function
   */
  virtual fBase * copy (void) const
    {
      fQuaternion * quat = new fQuaternion (*this);
      return quat;
    }
  
  /**
   * Access the elements of the quaternion. Indices start at 0 and the
   *  scalar is at index=3
   */
  double& operator [] (uint index)
    {
      if ( index == 3 ) return w;
      return v[index];
    }
     
  double operator [] (uint index) const
    {
      if ( index == 3 ) return w;
      return v[index];
    }

  /**
   * Class member functions which return the identity quaternion
   * Identity quaternion is with the all vector components=0 and scalar=1
   */
  static fQuaternion identity(void)
    {
      fQuaternion ident;  // Default constructor creates an identity quaternion
      return ident;
    }

  /**
   * Class member functions which return the identity quaternion
   * Identity quaternion is with the all vector components=0 and scalar=1
   */     
  static fQuaternion I (void)
    {
      fQuaternion ident;  // Default constructor creates an identity quaternion
      return ident;
    }

  void operator += (const fQuaternion& quat)
    {
      w += quat.w;
      v += quat.v;
    }
  
  void operator -= (const fQuaternion& quat)
    {
      w -= quat.w;
      v -= quat.v;
    }
  
  void operator *= (const fQuaternion& quat)
    {
      fVector3 vec;
      double s;
      
      s   = w*quat.w - v*quat.v;
      vec = quat.v*w + v*quat.w + (v % quat.v);
      
      w = s; v = vec;
    }
  
  void operator *= (const fVector3& vec)
    {
      fQuaternion v2q (vec);
      
      this->operator *= (v2q);
    }
  
  void operator *= (double scalar)
    {
      w *= scalar;
      v *= scalar;
    }
  
  void operator /= (double scalar)
    {
      w /= scalar;
      v /= scalar;
    }
  
  /**
   * Square of the length of a quaternion
   */
  friend double lengthsqr(const fQuaternion& quat)
    {
      double lensqr = quat.v*quat.v + quat.w*quat.w;
      return lensqr;
    }
  
  /**
   * Length of a quaternion
   */
  friend double length(const fQuaternion& quat)
    {
      return sqrt(lengthsqr(quat));
    }
  
  /**
   * For consistency define norm and normsqr also
   */
  friend double normsqr(const fQuaternion& quat)
    {
      return lengthsqr(quat);
    }

  friend double norm(const fQuaternion& quat)
    {
      return length(quat);
    }
  
  /**
   * Compute conjugate of this quaternion which -v,s
   */
  friend fQuaternion conjugate(const fQuaternion& quat)
    {
      return fQuaternion(-quat.v,quat.w);
    }
  
  /**
   * Normalize a quaternion - make it a unit quaternion
   * Returns the original length of the quaternion
   * If length is 0, nothing is changed
   */
  friend double normalize(fQuaternion& quat)
    {
      double len = length(quat);
      if ( isNonZero(len) == true )
	quat /= len;
      return len;
    }

  friend fQuaternion normalized(const fQuaternion& quat)
    {
      fQuaternion unitq = quat;
      normalize(unitq);
      return unitq;
    }

  /**
   * Negation
   */
  friend fQuaternion operator - (const fQuaternion& q)
    {
      fQuaternion neg(-q.w, -q.v);
      return neg;
    }
  
  friend fQuaternion operator + (const fQuaternion& q1, const fQuaternion& q2)
    {
      fQuaternion sum = q1;
      sum += q2;
      return sum;
    }
  
  friend fQuaternion operator - (const fQuaternion& q1, const fQuaternion& q2)
    {
      fQuaternion diff = q1;
      diff -= q2;
      return diff;
    }
  
  /**
   * Post-multiplication by a scalar
   */
  friend fQuaternion operator * (const fQuaternion& q, double scalar)
    {
      fQuaternion prod = q;
      prod *= scalar;
      return prod;
    }
  
  /**
   * Pre-multiplication by a scalara
   */
  friend fQuaternion operator * (double scalar, const fQuaternion& q)
    {
      fQuaternion prod = q;
      prod *= scalar;
      return prod;
    }

  /** 
   * Division by a scalar
   */
  friend fQuaternion operator / (const fQuaternion& q, double scalar)
    {
      fQuaternion quot = q;
      quot /= scalar;
      return quot;
    }
  
  /**
   * Multiplication of 2 quaternions
   */
  friend fQuaternion operator * (const fQuaternion& q1, const fQuaternion& q2)
    {
      fQuaternion prod = q1;
      prod *= q2;
      return prod;
    }

  /**
   * Post-multiplication of a quaternion by a fVector3
   * Same as above, except fVector3 is promoted to quaternion with 
   * scalar value 0.0
   */
  friend fQuaternion operator * (const fQuaternion& q, const fVector3& v)
    {
      fQuaternion prod = q;
      prod *= v;
      return prod;
    }
  
  /**
   * Pre-multiplication of a quaternion by a fVector3
   */
  friend fQuaternion operator * (const fVector3& v, const fQuaternion& q)
    {
      fQuaternion prod = q;
      prod *= v;
      return prod;
    }

  /**
   * Convert to a rotation matrix. Assumes that quaternion has been normalized
   */
  fMatrix3x3 toMatrix(void) const
    {
      fMatrix3x3 mat;
      double x,y,z,s;
      
      v.get(x,y,z); s = w;
      
      mat[0].set( 1.0 - 2.0*(y*y + z*z), 2.0*(x*y - s*z), 2.0*(x*z + s*y) );
      mat[1].set( 2.0*(x*y + s*z), 1.0 - 2.0*(x*x + z*z), 2.0*(y*z - s*x) );
      mat[2].set( 2.0*(x*z - s*y), 2.0*(y*z + s*x), 1.0 - 2.0*(x*x + y*y) );
      
      return mat;
    }
  
  fMatrix4x4 toMatrix4(void) const
    {
      fMatrix4x4 mat4 = toMatrix();
      mat4[3][3] = 1.0;
      return mat4;
    }
  
  void toMatrix(double array[16]) const
    {
      // Similar to toMatrix4, but fills a given array of 16 elements with the
      // rotation matrix corresponding to this quaternion in column major form
      fMatrix4x4 mat4 = toMatrix4();
      mat4.fillArrayColumnMajor(array);
    }
     
  friend fMatrix3x3 toMatrix(const fQuaternion& quat)
    {
      return quat.toMatrix();
    }
  
  friend fMatrix4x4 toMatrix4(const fQuaternion& quat)
    {
      return quat.toMatrix4();
    }
  
  //--- Conversion to and from axis and angle ---
  //--- All angles are specified in radians ---
  
  /**
   * Get the angle of rotation. Returns value between 0 and PI
   */
  double getAngle(void) const
    {
      return 2.0 * acos(w);
    }
  
  /**
   * Get the angle of rotation. Returns value between 0 and PI
   * Computes angle after normalizing the quaternion
   */
  friend double getAngle(const fQuaternion& quat)
    {
      // Make the quaternion a unit quaternion first
      fQuaternion nq = normalized(quat);
      
      return nq.getAngle();
    }
     
  /**
   *  Get the axis of rotation. Returns unit axis
   */
  friend fVector3 getAxis(const fQuaternion& quat)
    {
      // Make the quaternion a unit quaternion first
      fQuaternion nq = normalized(quat);
      
      fVector3 axis = normalized(nq.v);
      return axis;
    }
     
  /**
   * Get the axis and angle.
   */
  void getAxisAndAngle(fVector3& axis, double& theta) const
    {
      fQuaternion nq = normalized(*this);
      
      theta = 2.0 * acos(nq.w);
      axis = normalized(nq.v);
    }
  
  /**
   * Set the axis and angle.
   */
  void setAxisAndAngle(const fVector3& axis, double theta)
    {
      w = cos(theta/2.0);
      v = normalized(axis);
      v *= sin(theta/2.0);
    }

  /**
   * Change the angle to a new value. Use same axis as before
   */
  void setAngle(double theta)
    {
      w = cos(theta/2.0);
      normalize(v);
      v *= sin(theta/2.0);
    }
  
  /**
   * Scale the angle by the given scale factor
   */
  void scaleAngle(double scale_factor)
    {
      setAngle(getAngle()*scale_factor);
    }
  
  /**
   * Insertion and extraction operators
   */
  friend ostream& operator << (ostream& o, const fQuaternion& quat)
    {
      o << "{ " << quat.v << "," << quat.w << " }";
      return o;
    }

  /**
   * Insertion and extraction operators
   */  
  friend istream& operator >> (istream& i, fQuaternion& quat)
    {
      char c;
      i >> c >> quat.v >> c >> quat.w >> c;
      return i;
    }

protected:

  /**
   * Vector component
   */
  fVector3 v;
  
  /**
   * Scalar component
   */
  double w;

};

#endif // #ifndef FQUATERNION_H_
