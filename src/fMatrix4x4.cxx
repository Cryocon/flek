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
fMatrix4x4::operator= (fMatrix4x4 M)
{
  for (int i=0; i<COLUMNS; i++)
    for (int j=0; j<ROWS; j++)
      data[i][j] = M (i,j);
  
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

void 
fMatrix4x4::rotation_x (double value)
{
  double ca = double (cos (value));
  double sa = double (sin (value));
  data[0][0] = 1;   data[0][1] = 0;    data[0][2] = 0;
  data[1][0] = 0;   data[1][1] = ca;   data[1][2] = -sa;
  data[2][0] = 0;   data[2][1] = sa;   data[2][2] = ca;
}

void 
fMatrix4x4::rotation_y (double value)
{
  double ca = double (cos (value));
  double sa = double (sin (value));
  data[0][0] = ca;  data[0][1] = 0;    data[0][2] = sa;
  data[1][0] = 0;   data[1][1] = 1;    data[1][2] = 0;
  data[2][0] = -sa; data[2][1] = 0;    data[2][2] = ca;
}

void 
fMatrix4x4::rotation_z (double value)
{
  double ca = double (cos (value));
  double sa = double (sin (value));
  data[0][0] = ca;  data[0][1] = -sa;  data[0][2] = 0;
  data[1][0] = sa;  data[1][1] = ca;   data[1][2] = 0;
  data[2][0] = 0;   data[2][1] = 0;    data[2][2] = 1;
}

/* rotation creates a rotation matrix using an equivalent angle-axis 
 * representation.  That is to say, if the axis provided (a vector) is a 
 * general axis (and not one of the unit directions) any orientation can 
 * be obtained through proper axis and angle selection.  This is called the 
 * angle-axis representation. (Craig 51)
 */

void 
fMatrix4x4::rotation (double a, fVector3 v) 
{
  if ((v.x() == 0.0) && (v.y() == 0.0) && (v.z() == 0.0)) 
    {
      a = 0;
      v.set (1, 0, 0);
    }
  double ca = double (cos (a));
  double sa = double (sin (a));
  double va = 1.0f - ca;
  double x2 = v.x () * v.x ();
  double y2 = v.y () * v.y ();
  double z2 = v.z () * v.z ();
  double xyv = v.x () * v.y () * va;
  double xzv = v.x () * v.z () * va;
  double yzv = v.y () * v.z () * va;
  double xsa = v.x () * sa;
  double ysa = v.y () * sa;
  double zsa = v.z () * sa;
    
  data[0][0] = x2*va+ca;
  data[0][1] = xyv+zsa;
  data[0][2] = xzv-ysa;
  data[0][3] = 0.0;
  data[1][0] = xyv-zsa;
  data[1][1] = y2*va+ca;
  data[1][2] = yzv+xsa;
  data[1][3] = 0.0;
  data[2][0] = xzv+ysa;
  data[2][1] = yzv-xsa;
  data[2][2] = z2*va+ca;
  data[2][3] = data[3][0] = data[3][1] = data[3][2] = 0.0;
  data[3][3] = 1.0;
}

void 
fMatrix4x4::rotation (double ax, double ay, double az) 
{
  double cax = cos (ax);
  double cay = cos (ay);
  double caz = cos (az);
  double sax = sin (ax);
  double say = sin (ay);
  double saz = sin (az);
  
  data[0][0] = caz*cay;   
  data[0][1] = caz*say*sax - saz*cax;
  data[0][2] = caz*say*cax + saz*sax;
  data[0][3] = 0.0;
  data[1][0] = saz*cay;
  data[1][1] = saz*say*sax + caz*cax;
  data[1][2] = saz*say*cax - caz*sax;
  data[1][3] = 0.0;
  data[2][0] = -say;
  data[2][1] = cay*sax;
  data[2][2] = cay*cax;
  data[2][3] = data[3][0] = data[3][1] = data[3][2] = 0.0;
  data[3][3] = 1.0;
}

void 
fMatrix4x4::translation (fVector3 v) 
{
    data[0][0] = 1.0;
    data[1][0] = 0.0;
    data[2][0] = 0.0;
    data[3][0] = v.x ();
    data[0][1] = 0.0;
    data[1][1] = 1.0;
    data[2][1] = 0.0;
    data[3][1] = v.y ();
    data[0][2] = 0.0;
    data[1][2] = 0.0;
    data[2][2] = 0.0;
    data[3][2] = v.z ();
    data[0][3] = 0.0;
    data[1][3] = 0.0;
    data[2][3] = 0.0;
    data[3][3] = 1.0;  
}
