#include <Flek/fMatrix3x3.h>

fMatrix3x3::fMatrix3x3 ()
{
  for (int i=0; i<3; i++)
    for (int j=0; j<3; j++)
      data[i][j]=0;
}

void 
fMatrix3x3::identity ()
{
  for(int i=0; i<3; i++)
    for(int j=0; j<3; j++)
      {
	if (i==j)
	  data[i][j]=1;  
	else
	  data[i][j]=0;
      }
}

double 
fMatrix3x3::det ()
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

fMatrix3x3 
fMatrix3x3::invert ()
{
  double D;
  D=det();
  fMatrix3x3 Adjoint;
  
  if(D>=.001)
    { 
      //Here we divide by the determinant ans we find the adjoint
      Adjoint(0,0)=((data[1][1]*data[2][2]-data[1][2]*data[2][1])/D);
      Adjoint(1,0)=((data[1][2]*data[2][0]-data[1][0]*data[2][2])/D);
      Adjoint(2,0)=((data[1][0]*data[2][1]-data[1][1]*data[2][0])/D);
      
      Adjoint(0,1)=((data[0][2]*data[2][1]-data[0][1]*data[2][2])/D);
      Adjoint(1,1)=((data[0][0]*data[2][2]-data[0][2]*data[2][0])/D);
      Adjoint(2,1)=((data[0][1]*data[2][0]-data[0][0]*data[2][1])/D);
      
      Adjoint(0,2)=((data[0][1]*data[1][2]-data[0][2]*data[1][1])/D);
      Adjoint(1,2)=((data[0][2]*data[1][0]-data[0][0]*data[1][2])/D); 
      Adjoint(2,2)=((data[0][0]*data[1][1]-data[0][1]*data[1][0])/D);
    }
  else
    printf("fMatrix3x3 too close to singular. Not creating inverse!!!!\n\a"); 

  return Adjoint;
}

fMatrix3x3::fMatrix3x3 (const fMatrix3x3 &m)
{  
  for (int i=0; i<3; i++)
    for (int j=0; j<3; j++)
      data[i][j] = m.data[i][j];
}

fMatrix3x3::~fMatrix3x3 ()
{  
}

double & 
fMatrix3x3::operator() (int i,int j)
{
  return data[i][j];
}

fMatrix3x3 
fMatrix3x3::operator+ (fMatrix3x3 &m) const
{
  unsigned char i,j;
  
  fMatrix3x3 result;
  
  for(i = 0; i<3; i++)
    for(j = 0; j<3; j++)
      result(i,j) = data[i][j] + m(i,j);

  return result;
}

fMatrix3x3 
fMatrix3x3::operator* (fMatrix3x3 &m)
{
  fMatrix3x3 result;
  
  for(int k=0; k<3; k++)
    for (int i=0; i<3; i++)
      {
	double tmp = 0.0;
	for (int j=0; j<3; j++)
	  tmp += data[k][j] * m(j,i);
	result(k,i) = tmp;
      }

  return result;
}

fMatrix3x3 
fMatrix3x3::operator- (fMatrix3x3 &m) const
{
  fMatrix3x3 result;
  
  for (int i=0; i<3; i++)
    for (int j=0; j<3; j++)
      result (i,j) = data[i][j] - m(i,j);
  
  return result;
}

fMatrix3x3 
fMatrix3x3::operator* (double scalar)
{
  fMatrix3x3 result;
  
  for (int i=0; i<3; i++)
    for (int j=0; j<3; j++)
      result(i,j) = data[i][j] * scalar;
  
  return result;
}

void 
fMatrix3x3::print ()
{  
  for(int i=0; i<3; i++)
    {
      for(int j=0; j<3; j++)
	printf("%g ", data[i][j]);
      printf("\n");
    }
}

fMatrix3x3 
operator* (double &scalar,fMatrix3x3 &m)
{
  return m*scalar;
}

void 
fMatrix3x3::set_value (int i, int j, double value)
{
  data[i][j] = value;
}

double fMatrix3x3::get_value (int i, int j)
{
  return data[i][j];
}

fMatrix3x3 & 
fMatrix3x3::operator= (fMatrix3x3 &m)
{
  for (int i=0; i<3; i++)
    for (int j=0; j<3; j++)
      data[i][j] = m (i,j);
  
  return *this;   
}

fMatrix3x3 
operator*(double value, fMatrix3x3 &m)
{
  return m*value;
}

fMatrix3x3 
fMatrix3x3::transpose()
{
  fMatrix3x3 result;
  
  for (int i=0; i<3; i++)
    for (int j=0; j<3; j++)
      result (j,i) = data[i][j]; 

  return result;
}

void 
fMatrix3x3::set_row (int i, fVector3 &v)
{
  for (int j=0; j<3; j++)
    data[i][j] = v[j];
}

void 
fMatrix3x3::set_col (int j, fVector3 &v)
{
  for (int i=0; i<3; i++)
    data[i][j] = v[i];
}

void 
fMatrix3x3::set_row(int i, double array[])
{
  unsigned int size = sizeof(array) / sizeof(double);
  
  if (size == 3)
    {
      for (int j=0; j<3; j++)
	data[i][j] = array[j];
    }
  else
    printf("Array wrong size to be a row of this matrix!\n\a");
  
}

void 
fMatrix3x3::set_col(int j, double array[])
{  
  unsigned int size = sizeof (array) / sizeof (double);
  
  if (size==3)
    {
      for(int i=0;i<3;i++)
	data[i][j]=array[i];
    }
  else
    printf("Array wrong size to be a row of this matrix!\n\a");
}

fVector3 
fMatrix3x3::get_row (int i)
{
  fVector3 result;
  
  for (int j=0; j<3; j++)
    result[j] = data[i][j];
  
  return result;
}

fVector3
fMatrix3x3::get_col (int j)
{
  fVector3 result;
  
  for(int i=0; i<3; i++)
    result[i] = data[i][j];
  
  return result;
}

double* 
fMatrix3x3::get_row_array (int i)
{
  double *row = new double[3];
  for (int j = 0; j < 3; j++)
    row[j] = data[i][j];
  return row;
}

double* 
fMatrix3x3::get_col_array (int j)
{
  double *col = new double[3];
  for (int i = 0; i < 3; i++)
    col[i] = data[i][j];
  return col;
}

