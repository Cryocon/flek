#include <Flek/FVector2.H>
#include <Flek/FVector3.H>
#include <Flek/FVector4.H>

#include <Flek/FMatrix3x3.H>
#include <Flek/FMatrix4x4.H>

#include <Flek/gl.H>

void glMultMatrix (const FMatrix4x4 &M)
{
  double m[16];
  M.fill_array_row_major (m);
  glMultMatrixd (m);
}

