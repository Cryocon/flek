#include <Flek/fVector2.h>
#include <Flek/fVector3.h>
#include <Flek/fVector4.h>

#include <Flek/fMatrix3x3.h>
#include <Flek/fMatrix4x4.h>

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

/*
  The following functions are defined outside the class so that they use the
  friend versions of member functions instead of the member functions themselves
*/

fMatrix4x4 operator * (const fMatrix4x4& mat1, const fMatrix4x4& mat2)
{
  fMatrix4x4 prod, trans;
  
  // Find the transpose of the 2nd matrix
  trans = transpose (mat2);
  
  // The columns of mat2 are now the rows of trans
  // Multiply appropriate rows and columns to get the product
  prod.row[0].set (mat1.row[0]*trans.row[0],
                   mat1.row[0]*trans.row[1],
                   mat1.row[0]*trans.row[2],
                   mat1.row[0]*trans.row[3]);
  prod.row[1].set (mat1.row[1]*trans.row[0],
                   mat1.row[1]*trans.row[1],
                   mat1.row[1]*trans.row[2],
                   mat1.row[1]*trans.row[3]);
  prod.row[2].set (mat1.row[2]*trans.row[0],
                   mat1.row[2]*trans.row[1],
                   mat1.row[2]*trans.row[2],
                   mat1.row[2]*trans.row[3]);
  prod.row[3].set (mat1.row[3]*trans.row[0],
                   mat1.row[3]*trans.row[1],
                   mat1.row[3]*trans.row[2],
                   mat1.row[3]*trans.row[3]);
  return prod;
}

fVector4 operator * (const fVector4& vec, const fMatrix4x4& mat)
{
  return (transpose(mat) * vec);
}

/*
  The following functions are defined outside the class so that they use the
  friend versions of member functions instead of the member functions themselves
*/

fMatrix3x3 operator * (const fMatrix3x3& mat1, const fMatrix3x3& mat2)
{
  fMatrix3x3 prod, trans;
  
  // Find the transpose of the 2nd matrix
  trans = transpose (mat2);
  
  // The columns of mat2 are now the rows of trans
  // Multiply appropriate rows and columns to get the product
  prod.row[0].set (mat1.row[0]*trans.row[0],
                   mat1.row[0]*trans.row[1],
                   mat1.row[0]*trans.row[2]);
  prod.row[1].set (mat1.row[1]*trans.row[0],
                   mat1.row[1]*trans.row[1],
                   mat1.row[1]*trans.row[2]);
  prod.row[2].set (mat1.row[2]*trans.row[0],
                   mat1.row[2]*trans.row[1],
                   mat1.row[2]*trans.row[2]);
  return prod;
}

fVector3 operator * (const fVector3& vec, const fMatrix3x3& mat)
{
  return (transpose(mat) * vec);
}

