#include <Flek/fVector2.h>
#include <Flek/fVector3.h>
#include <Flek/fVector4.h>

#include <Flek/fMatrix3x3.h>
#include <Flek/fMatrix4x4.h>

#include <Flek/gl.h>

void glMultMatrix (const fMatrix4x4 &M)
{
  double m[16];
  M.fillArrayRowMajor (m);
  glMultMatrixd (m);
}

