/* -*-C++-*- 
   "$Id: math.h,v 1.3 2000/02/13 01:02:32 jamespalmer Exp $"
   
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

#ifndef _INLINES_HH_ // Here for Vinod!
#define _INLINES_HH_

#ifndef FMATH_H_
#define FMATH_H_

#include <math.h>

/*
 * Predefined constants, and macros
 * To change the values of some of these macros, define them before including
 * this file. Or dont include this file at all and define them on your own
 */

/** @package libflek_core
 * Returns the absolute value.
 */
inline int Abs(int x)
{
  return (x < 0) ? -x : x;
}

/**
 * Returns the absolute value.
 */
inline float Abs(float x)
{
  return (x < 0.0) ? -x : x;
}

/**
 * Returns the absolute value.
 */
inline double Abs(double x)
{
  return (x < 0.0) ? -x : x;
}


/**
 * Zero '0' value to be used for comparison and assignment
 */
#ifndef ZERO
#define ZERO 1.0e-10
#endif

/**
 * float infinity to be used for comparison and assignment
 */
#ifndef FLT_INF
#define FLT_INF 1.0e35
#endif

/**
 * double infinity to be used for comparison and assignment
 */
#ifndef DBL_INF
#define DBL_INF 1.0e100
#endif

typedef unsigned int uint;

/**
 * Check if passed number is non-zero.
 */
inline bool isNonZero (int num)
{
  if ( num != 0 ) return true;
  return false;
}

/**
 * Check if passed number is non-zero.  (Uses ZERO bounds).
 */
inline bool isNonZero (double num)
{
  if ( (num < -ZERO) || (num > ZERO) ) return true;
  return false;
}

/**
 * Check if passed number is odd.
 */
inline bool isOdd (int num)
{
  if ( num % 2 ) return true;
  return false;
}

/**
 * Check if passed number is even.
 */
inline bool isEven (int num)
{
  if ( num % 2 ) return false;
  return true;
}

/**
 * Check if passed number is odd.
 */
inline bool isOdd (uint num)
{
  if ( num % 2 ) return true;
  return false;
}

/**
 * Check if passed number is even.
 */
inline bool isEven (uint num)
{
  if ( num % 2 ) return false;
  return true;
}

/**
 * Square the number.
 */
inline int sqr (int x)
{
  return x*x;
}

/**
 * Cube the number.
 */
inline int cube (int x)
{
  return x*x*x;
}

/**
 * Square the number.
 */
inline uint sqr (uint x)
{
  return x*x;
}

/**
 * Cube the number.
 */
inline uint cube (uint x)
{
  return x*x*x;
}

/**
 * Square the number.
 */
inline float sqr (float x)
{
  return x*x;
}

/**
 * Cube the number.
 */
inline float cube (float x)
{
  return x*x*x;
}

/**
 * Square the number.
 */
inline double sqr (double x)
{
  return x*x;
}

/**
 * Cube the number.
 */
inline double cube (double x)
{
  return x*x*x;
}

/**
 * Minimum of two numbers.
 */
inline int min (int x, int y)
{
  return ( (x < y) ? x : y );
}

/**
 * Maximum of two numbers.
 */
inline int max (int x, int y)
{
  return ( (x > y) ? x : y );
}

/**
 * Minimum of two numbers.
 */
inline uint min (uint x, uint y)
{
  return ( (x < y) ? x : y );
}

/**
 * Maximum of two numbers.
 */
inline uint max (uint x, uint y)
{
  return ( (x > y) ? x : y );
}

/**
 * Minimum of two numbers.
 */
inline float min (float x, float y)
{
  return ( (x < y) ? x : y );
}

/**
 * Maximum of two numbers.
 */
inline float max (float x, float y)
{
  return ( (x > y) ? x : y );
}

/**
 * Minimum of two numbers.
 */
inline double min (double x, double y)
{
  return ( (x < y) ? x : y );
}

/**
 * Maximum of two numbers.
 */
inline double max (double x, double y)
{
  return ( (x > y) ? x : y );
}

/**
 * Swap two numbers.
 */
inline void swap (int& x, int& y)
{
  int t = x;
  x = y; y = t;
}

/**
 * Swap two numbers.
 */
inline void swap (uint& x, uint& y)
{
  uint t = x;
  x = y; y = t;
}

/**
 * Swap two numbers.
 */
inline void swap (float& x, float& y)
{
  float t = x;
  x = y; y = t;
}

/**
 * Swap two numbers.
 */
inline void swap (double& x, double& y)
{
  double t = x;
  x = y; y = t;
}

/**
 * Degrees to radians.
 */
inline float deg2rad (float deg)
{
  return deg*M_PI/180.0;
}

/**
 * Degrees to radians.
 */
inline double deg2rad (double deg)
{
  return deg*M_PI/180.0;
}

/**
 * Radians to degrees.
 */
inline float rad2deg (float rad)
{
  return rad*180.0/M_PI;
}

/**
 * Radians to degrees.
 */
inline double rad2deg (double rad)
{
  return rad*180.0/M_PI;
}

/**
 * Return the sign of a number.  1, 0, or -1.
 */
inline int sign (int x)
{
  return ( (x < 0) ? -1 : ((x > 0) ? 1 : 0) );
}

/**
 * Return the sign of a number.  1, 0, or -1.
 */
inline float sign (float x)
{
  return ( (x < 0.0) ? -1.0 : ((x > 0.0) ? 1.0 : 0.0) );
}

/**
 * Return the sign of a number.  1, 0, or -1.
 */
inline double sign (double x)
{
  return ( (x < 0.0) ? -1.0 : ((x > 0.0) ? 1.0 : 0.0) );
}

/**
 * For matrices - sign of cofactor. 1 if i+j is even, -1 if i+j is odd
 */
inline int cofsign (uint i, uint j)
{
  return ( ((i+j)%2) ? -1 : 1 );
}

#endif // #ifndef FMATH_H_
#endif // #ifndef _INLINES_HH_