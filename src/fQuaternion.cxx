#include <Flek/fQuaternion.h>

double & fQuaternion::operator[] (unsigned int i)
{
  if (i == 3)
    return s;
  return v[i];
}

fQuaternion & 
fQuaternion::operator= (const fQuaternion &Q)
{
  if (this == &Q) return *this;
  s=Q.s;
  v=Q.v;
  return *this;
}

fQuaternion & 
fQuaternion::operator= (double array[])
{
  s=array[0];
  v[0]=array[1];
  v[1]=array[2];
  v[2]=array[3];
  return *this;
}

fQuaternion  
fQuaternion::operator+ (const fQuaternion &Q) const  
{
  fQuaternion result;
  result.s=(s+Q.s);
  result.v=(v+Q.v);
  return result;
}

fQuaternion  
fQuaternion::operator- (const fQuaternion &Q) const
{
  fQuaternion result;
  
  result.s=s-Q.s;
  result.v=(v-Q.v);
  
  return result;
}

fQuaternion  
fQuaternion::operator* (fQuaternion &Q) 
{
  //fQuaternion result;
  //result.s = (s*Q.s - Q.v*v);
  //result.v = (s*Q.v + Q.s*v + (v % Q.v));
  //return result;
  fQuaternion qq;
  qq.s = s*Q.s - v[0]*Q.v[0] - v[1]*Q.v[1] - v[2]*Q.v[2];
  qq.v[0] = s*Q.v[0] + v[0]*Q.s + v[1]*Q.v[2] - v[2]*Q.v[1];
  qq.v[1] = s*Q.v[1] + v[1]*Q.s + v[2]*Q.v[0] - v[0]*Q.v[2];
  qq.v[2] = s*Q.v[2] + v[2]*Q.s + v[0]*Q.v[1] - v[1]*Q.v[0];
  return (qq);
  
}

fQuaternion  
fQuaternion::operator* (double scalar)
{
  fQuaternion result;
  result.s=scalar*s;
  result.v=scalar*v;
  return result;
}

fQuaternion
fQuaternion::inverse ()
{
  fQuaternion result;
  fQuaternion numer = this->conjugate ();
  fQuaternion denom = numer*(*this);
  double denom2 = denom.s + denom.v[0] + denom.v[1] + denom.v[2];
  result.s = numer.s * (1.0f / denom2);
  result.v = (1.0f / denom2) * numer.v;
  return result;
}

fQuaternion  
fQuaternion::conjugate ()
{
  fQuaternion result;
  result.s = s;
  result.v[0] = -1*v[0];
  result.v[1] = -1*v[1];
  result.v[2] = -1*v[2];
  return result;
}

fQuaternion  
fQuaternion::Qprime (fVector3 &wt)
{
  fQuaternion result;
  fQuaternion w;
  w.s = 0;
  w.v = wt;
  result = ((w*(*this)) * 0.5);
  return result;
}

void 
fQuaternion::print ()  
{
  printf("<%g %g %g %g>", v[0], v[1], v[2], s);
}

void 
fQuaternion::normalize ()
{
  double n;
  n = norm ();
  s = s / n;
  v[0] = v[0] / n;
  v[1] = v[1] / n;
  v[2] = v[2] / n;
}

double 
fQuaternion::norm ()
{
  double result;
  result = sqrt (s*s + v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);  
  return result; 
}

fQuaternion  
fQuaternion::from_matrix (fMatrix4x4 &M)
{
  fQuaternion result;
  
  double t01, t02;
  
  t01 = M (0, 0) + M (1, 1) + M (2, 2);
  if (t01 >= 0)
    {
      t02 = sqrt (t01 + 1);
      result.s = .5 * t02;
      t02 = .5 / t02;
      result.v[0] = (M (2, 1) - M (1, 2)) * t02;
      result.v[1] = (M (0, 2) - M (2, 0)) * t02;
      result.v[2] = (M (1, 0) - M (0, 1)) * t02;
    }
  else
    {
      int i = 0;
      
      if (M (1, 1) > M (0, 0))
	i = 1;
      if (M (2, 2) > M (i, i))
	i = 2;
      
      switch(i)
	{
	case 0:
	  
	  t02 = sqrt (M (0, 0) - (M (1, 1) + M (2, 2)) + 1);  
	  result.v[0] = .5 * t02;
	  t02 = .5 / t02;
	  result.v[1] = (M (0, 1) - M (1, 0)) * t02;
	  result.v[2] = (M (2, 0) - M (0, 2)) * t02;
	  result.s = (M (2, 1) - M (1, 2)) * t02;
	  break; 
	  
	case 1:
	  
	  t02 = sqrt (M (1, 1)-(M (2, 2) + M (0, 0))+1);  
	  result.v[1] = .5 * t02;
	  t02 = .5 / t02;
	  result.v[2] = (M (1, 2) - M (2, 1)) * t02;
	  result.v[0] = (M (0, 1) - M (1, 0)) * t02;
	  result.s = (M (0, 2) - M (2, 0)) * t02;
	  break;
	  
	case 2:
	  
	  t02 = sqrt (M (2, 2) - (M (0, 0) + M (1, 1)) + 1);  
	  result.v[2] = .5 * t02;
	  t02 = .5 / t02;
	  result.v[0] = (M (2, 0) - M (0, 2)) * t02;
	  result.v[1] = (M (1, 2) - M (2, 1)) * t02;
	  result.s = (M (1, 0) - M (0, 1)) * t02;
	  break;
	}
    } 
  return result; 
}

fMatrix4x4 fQuaternion::to_matrix ()
{ 
  fMatrix4x4 out;
  double Nq = v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + s * s; 
  double ss = (Nq > 0.0) ? (2.0 / Nq) : 0.0;
  double xs = v[0]*ss,         ys = v[1]*ss,    zs = v[2]*ss;
  double wx = (s)*xs,          wy = (s)*ys,     wz = (s)*zs;
  double xx = v[0]*xs,         xy = v[0]*ys,    xz = v[0]*zs;
  double yy = v[1]*ys,         yz = v[1]*zs,    zz = v[2]*zs;
  out.zero ();
  out.set (0, 0, 1.0 - (yy + zz));
  out.set (1, 0, xy + wz);
  out.set (2, 0, xz - wy);
  out.set (0, 1, xy - wz);
  out.set (1, 1, 1.0 - (xx + zz));
  out.set (2, 1, yz + wx);
  out.set (0, 2, xz + wy);
  out.set (1, 2, yz - wx);
  out.set (2, 2, 1.0 - (xx + yy));
  out.set (3, 3, 1.0);
  return out;
}

