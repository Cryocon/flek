#include <Flek/fMatrix4x4.h>

#define COLUMNS 4
#define ROWS    4

fMatrix4x4::fMatrix4x4 (const fMatrix4x4 &m)
{  
  for (int i=0; i<COLUMNS; i++)
    for (int j=0; j<ROWS; j++)
      data[i][j] = m.data[i][j];
}

fMatrix4x4::fMatrix4x4 (double initial)
{
  for (int i=0; i<COLUMNS; i++)
    for (int j=0; j<ROWS; j++)
      data[i][j]=initial;
}

void 
fMatrix4x4::identity ()
{
  zero ();
  for (int i=0; i<COLUMNS; i++)
    data[i][i] = 1.;
}

void
fMatrix4x4::zero ()
{
  for (int i=0; i<COLUMNS; i++)
    for (int j=0; j<ROWS; j++)
      data[i][j] = 0.;
}

double 
fMatrix4x4::determinant ()  // The 3x3 determinant!!
{
  double D;
  D=data[0][0]*data[1][1]*data[2][2]+
    data[0][1]*data[1][2]*data[2][0]+
    data[0][2]*data[2][1]*data[1][0]-
    data[0][2]*data[1][1]*data[2][0]-
    data[0][1]*data[1][0]*data[2][2]-
    data[0][0]*data[2][1]*data[1][2];
  return D;
}

fMatrix4x4 
fMatrix4x4::invert () // The 3x3 inverse!!
{
  double D;
  D = determinant ();
  fMatrix4x4 R;
  
  if (D > 0)
    { 
      R (0, 0) = ((data[1][1]*data[2][2] - data[1][2]*data[2][1]) / D);
      R (1, 0) = ((data[1][2]*data[2][0] - data[1][0]*data[2][2]) / D);
      R (2, 0) = ((data[1][0]*data[2][1] - data[1][1]*data[2][0]) / D);
      
      R (0, 1) = ((data[0][2]*data[2][1] - data[0][1]*data[2][2]) / D);
      R (1, 1) = ((data[0][0]*data[2][2] - data[0][2]*data[2][0]) / D);
      R (2, 1) = ((data[0][1]*data[2][0] - data[0][0]*data[2][1]) / D);
      
      R (0, 2) = ((data[0][1]*data[1][2] - data[0][2]*data[1][1]) / D);
      R (1, 2) = ((data[0][2]*data[1][0] - data[0][0]*data[1][2]) / D); 
      R (2, 2) = ((data[0][0]*data[1][1] - data[0][1]*data[1][0]) / D);
    }
  else
    printf("fMatrix4x4::invert () could not create inverse matrix.\n"); 

  return R;
}

fMatrix4x4 
fMatrix4x4::operator+ (fMatrix4x4 &M) const
{
  fMatrix4x4 R;
  
  for (int i = 0; i<COLUMNS; i++)
    for (int j = 0; j<ROWS; j++)
      R (i, j) = data[i][j] + M (i,j);

  return R;
}

fMatrix4x4 
fMatrix4x4::operator* (fMatrix4x4 &m)
{
  fMatrix4x4 R;
  
  for(int k=0; k<COLUMNS; k++)
    for (int i=0; i<ROWS; i++)
      {
	double tmp = 0.0;
	for (int j=0; j<ROWS; j++)
	  tmp += data[k][j] * m(j,i);
	R (k, i) = tmp;
      }

  return R;
}

fMatrix4x4 
fMatrix4x4::operator- (fMatrix4x4 &M) const
{
  fMatrix4x4 R;
  
  for (int i=0; i<COLUMNS; i++)
    for (int j=0; j<ROWS; j++)
      R (i, j) = data[i][j] - M (i, j);
  
  return R;
}

fMatrix4x4 
fMatrix4x4::operator* (double scalar)
{
  fMatrix4x4 R;
  
  for (int i=0; i<COLUMNS; i++)
    for (int j=0; j<ROWS; j++)
      R (i, j) = data[i][j] * scalar;
  
  return R;
}

void 
fMatrix4x4::print ()
{  
  for (int i=0; i<COLUMNS; i++)
    {
      for (int j=0; j<ROWS; j++)
	printf ("%g ", data[i][j]);
      printf ("\n");
    }
}

fMatrix4x4 
operator* (double &scalar,fMatrix4x4 &m)
{
  return m*scalar;
}

fMatrix4x4 & 
fMatrix4x4::operator= (fMatrix4x4 &m)
{
  for (int i=0; i<COLUMNS; i++)
    for (int j=0; j<ROWS; j++)
      data[i][j] = m (i,j);
  
  return *this;   
}

fMatrix4x4 
operator*(double value, fMatrix4x4 &m)
{
  return m*value;
}

fMatrix4x4 
fMatrix4x4::transpose()
{
  fMatrix4x4 R;
  
  for (int i=0; i<COLUMNS; i++)
    for (int j=0; j<ROWS; j++)
      R (j, i) = data[i][j]; 

  return R;
}

void 
fMatrix4x4::set_row (int i, fVector3 &v)
{
  for (int j=0; j<3; j++)
    data[i][j] = v[j];
}

void 
fMatrix4x4::set_col (int j, fVector3 &v)
{
  for (int i=0; i<3; i++)
    data[i][j] = v[i];
}

void 
fMatrix4x4::set_row(int i, double array[])
{
  for (int j=0; j<ROWS; j++)
    data[i][j] = array[j];
}

void 
fMatrix4x4::set_col(int j, double array[])
{  
  for (int i=0; i<COLUMNS; i++)
    data[i][j]=array[i];
}

fVector3 
fMatrix4x4::get_row_v3 (int i)
{
  fVector3 v;
  
  for (int j=0; j<3; j++)
    v[j] = data[i][j];
  
  return v;
}

fVector3
fMatrix4x4::get_col_v3 (int j)
{
  fVector3 v;
  
  for(int i=0; i<3; i++)
    v[i] = data[i][j];
  
  return v;
}

/*
 
 Arcball wants a pointer into the array!! 
 
double* 
fMatrix4x4::get_row_array (int i)
{
  double *row = new double[ROWS];
  for (int j = 0; j < ROWS; j++)
    row[j] = data[i][j];
  return row;
}

double* 
fMatrix4x4::get_col_array (int j)
{
  double *col = new double[COLUMNS];
  for (int i = 0; i < COLUMNS; i++)
    col[i] = data[i][j];
  return col;
}

*/
