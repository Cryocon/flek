#include <Flek/fVector2.h>
#include <Flek/fVector3.h>
#include <Flek/fVector4.h>

void fVector3::copyFrom (fVector4 const &v)
{
  elem[0] = v[0];
  elem[1] = v[1];
  elem[2] = v[2];
}

void fVector3::copyFrom (fVector2 const &v)
{
  elem[0] = v[0];
  elem[1] = v[1];
  elem[0] = 0;
}

void fVector2::copyFrom (fVector4 const &v)
{
  elem[0] = v[0];
  elem[1] = v[1];
}

void fVector2::copyFrom (fVector3 const &v)
{
  elem[0] = v[0];
  elem[1] = v[1];
}

void fVector4::copyFrom (fVector3 const &v)
{
  elem[0] = v[0];
  elem[1] = v[1];
  elem[2] = v[2];
}

void fVector4::copyFrom (fVector2 const &v)
{
  elem[0] = v[0];
  elem[1] = v[1];
}
