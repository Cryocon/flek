#include <Flek/math.h>
#include <Flek/fImage.h>
#include <iostream.h>
#include <fstream.h>

typedef unsigned long ulong;
typedef unsigned long * ulongPtr;
typedef unsigned short ushort;
typedef unsigned short * ushortPtr;
typedef unsigned char uchar;
typedef unsigned char * ucharPtr;

/*
 * All operations are done "in-place" on image A and do not return a 
 * new image for efficiency.  If you want a new image, copy image A
 * and then work on the copy.
 */

fImage* add (fImage *A, fImage *B, int xo, int yo, float value=1.0)
{
  uchar *Apixel;
  uchar *Bpixel;
  
  fImage::iterator Ai;
  fImage::iterator Bi;
  
  int xi = max (xo, 0); // Initial position.
  int yi = max (yo, 0);    
  int xf = min (max (xo + B->width (), 0), A->width ()); // Final position.
  int yf = min (max (yo + B->height (), 0), A->height ());
  int col;    

  for (int row=yi; row < yf; row++)
    {
      for (Ai = (*A)(xi, row), Bi = (*B)(xi-xo, row-yo), col=xi; col < xf; Ai++, Bi++, col++)
	{
	  Apixel = *Ai;
	  Bpixel = *Bi;
	  float m = Bpixel[3] / 255.;
	  Apixel[0] = clampUpper (Apixel[0] + (int)(value*m*Bpixel[0]), 255);
	  Apixel[1] = clampUpper (Apixel[1] + (int)(value*m*Bpixel[1]), 255);
	  Apixel[2] = clampUpper (Apixel[2] + (int)(value*m*Bpixel[2]), 255);
	  Apixel[3] = clampUpper (Apixel[3] + (int)(value*m*Apixel[3]), 255);
	}
    }
  return A;
}

fImage* subtract (fImage *A, fImage *B, int xo, int yo, float value=1.0)
{
  uchar *Apixel;
  uchar *Bpixel;
  
  fImage::iterator Ai;
  fImage::iterator Bi;
  
  int xi = max (xo, 0); // Initial position.
  int yi = max (yo, 0);    
  int xf = min (max (xo + B->width (), 0), A->width ()); // Final position.
  int yf = min (max (yo + B->height (), 0), A->height ());
  int col;    

  for (int row=yi; row < yf; row++)
    {
      for (Ai = (*A)(xi, row), Bi = (*B)(xi-xo, row-yo), col=xi; col < xf; Ai++, Bi++, col++)
	{
	  Apixel = *Ai;
	  Bpixel = *Bi;
	  float m = Bpixel[3] / 255.;
	  Apixel[0] = clampLower (Apixel[0] - (int)(value*m*Bpixel[0]), 0);
	  Apixel[1] = clampLower (Apixel[1] - (int)(value*m*Bpixel[1]), 0);
	  Apixel[2] = clampLower (Apixel[2] - (int)(value*m*Bpixel[2]), 0);
	  Apixel[3] = clampUpper (Apixel[3] + (int)(value*m*Apixel[3]), 255);
	}
    }
  return A;
}

fImage* difference (fImage *A, fImage *B, int xo, int yo, float value=1.0)
{
  uchar *Apixel;
  uchar *Bpixel;
  
  fImage::iterator Ai;
  fImage::iterator Bi;
  
  int xi = max (xo, 0); // Initial position.
  int yi = max (yo, 0);    
  int xf = min (max (xo + B->width (), 0), A->width ()); // Final position.
  int yf = min (max (yo + B->height (), 0), A->height ());
  int col;    

  for (int row=yi; row < yf; row++)
    {
      for (Ai = (*A)(xi, row), Bi = (*B)(xi-xo, row-yo), col=xi; col < xf; Ai++, Bi++, col++)
	{
	  Apixel = *Ai;
	  Bpixel = *Bi;
	  float m = (float)Bpixel[3] / 255.0;
	  Apixel[0] = max ((int)(Apixel[0]*(1-m*value)), (int)(Bpixel[0]*value*m)) - min ((int)(Apixel[0]*(1-m*value)), (int)(Bpixel[0]*value*m));
	  Apixel[1] = max ((int)(Apixel[1]*(1-m*value)), (int)(Bpixel[1]*value*m)) - min ((int)(Apixel[1]*(1-m*value)), (int)(Bpixel[1]*value*m));
	  Apixel[2] = max ((int)(Apixel[2]*(1-m*value)), (int)(Bpixel[2]*value*m)) - min ((int)(Apixel[2]*(1-m*value)), (int)(Bpixel[2]*value*m));
	  //	  Apixel[1] = (uchar)(Apixel[1]*(1-m*value) + value*m*max ((int)Apixel[1], (int)Bpixel[1]) - min ((int)Apixel[1], (int)Bpixel[1]));
	  //Apixel[2] = (uchar)(Apixel[2]*(1-m*value) + value*m*max ((int)Apixel[2], (int)Bpixel[2]) - min ((int)Apixel[2], (int)Bpixel[2]));
	  Apixel[3] = clampUpper (Apixel[3] + (int)(value*m*Apixel[3]), 255);
	}
    }
  return A;
}


/*
fImage* subtract (fImage *A, fImage *B, int x, int y)
{
  fImage *R;
  
  int Bw = B->width ();
  int Bh = B->height ();
  
  uchar *Apixel;
  uchar *Bpixel;
  uchar *Rpixel;
  
  fImage::iterator Rend;
  fImage::iterator Aend;
  fImage::iterator Ri;
  fImage::iterator Ai;
  fImage::iterator Bi;
  
  for (int row=0; row < A->height (); row++)
    {
      Rend = R->end (row);
      Aend = A->end (row);
      int col;
      
      for (Ri = R->begin (row), Ai = A->begin (row), col=0; Ri != Rend; Ai++, Ri++, col++)
	{
	  Rpixel = *Ri;
	  Apixel = *Ai;
	  if ((col > x) && (col < (x+Bw)) && (row > y) && (row < (y+Bh)))
	    {
	      Bi = (*B)(col-x, row-y);
	      Bpixel = *Bi;
	      Rpixel[0] = clampLower (Apixel[0] - Bpixel[0], 0);
	      Rpixel[1] = clampLower (Apixel[1] - Bpixel[1], 0);
	      Rpixel[2] = clampLower (Apixel[2] - Bpixel[2], 0);
	      Rpixel[3] = clampLower (Apixel[3] - Bpixel[3], 0);
	    }
	  else
	    {
	      Rpixel[0] = Apixel[0];
	      Rpixel[1] = Apixel[1];
	      Rpixel[2] = Apixel[2];
	      Rpixel[3] = Apixel[3];
	    }
	}
    }
  return R;
}

fImage* difference (fImage *A, fImage *B, int x, int y)
{
  fImage *R;
  
  int Bw = B->width ();
  int Bh = B->height ();
  
  uchar *Apixel;
  uchar *Bpixel;
  uchar *Rpixel;
  
  fImage::iterator Rend;
  fImage::iterator Aend;
  fImage::iterator Ri;
  fImage::iterator Ai;
  fImage::iterator Bi;
  
  for (int row=0; row < A->height (); row++)
    {
      Rend = R->end (row);
      Aend = A->end (row);
      int col;
      
      for (Ri = R->begin (row), Ai = A->begin (row), col=0; Ri != Rend; Ai++, Ri++, col++)
	{
	  Rpixel = *Ri;
	  Apixel = *Ai;
	  if ((col > x) && (col < (x+Bw)) && (row > y) && (row < (y+Bh)))
	    {
	      Bi = (*B)(col-x, row-y);
	      Bpixel = *Bi;
	      Rpixel[0] = max ((int)Apixel[0], (int)Bpixel[0]) - min ((int)Apixel[0], (int)Bpixel[0]);
	      Rpixel[1] = max ((int)Apixel[1], (int)Bpixel[1]) - min ((int)Apixel[1], (int)Bpixel[1]);
	      Rpixel[2] = max ((int)Apixel[2], (int)Bpixel[2]) - min ((int)Apixel[2], (int)Bpixel[2]);
	      Rpixel[3] = max ((int)Apixel[3], (int)Bpixel[3]) - min ((int)Apixel[3], (int)Bpixel[3]);
	    }
	  else
	    {
	      Rpixel[0] = Apixel[0];
	      Rpixel[1] = Apixel[1];
	      Rpixel[2] = Apixel[2];
	      Rpixel[3] = Apixel[3];
	    }
	}
    }
  return R;
}


fImage* lightenOnly (fImage *A, fImage *B, int x, int y)
{
  fImage *R;
  
  int Bw = B->width ();
  int Bh = B->height ();
  
  uchar *Apixel;
  uchar *Bpixel;
  uchar *Rpixel;
  
  fImage::iterator Rend;
  fImage::iterator Aend;
  fImage::iterator Ri;
  fImage::iterator Ai;
  fImage::iterator Bi;
  
  for (int row=0; row < A->height (); row++)
    {
      Rend = R->end (row);
      Aend = A->end (row);
      int col;
      
      for (Ri = R->begin (row), Ai = A->begin (row), col=0; Ri != Rend; Ai++, Ri++, col++)
	{
	  Rpixel = *Ri;
	  Apixel = *Ai;
	  if ((col > x) && (col < (x+Bw)) && (row > y) && (row < (y+Bh)))
	    {
	      Bi = (*B)(col-x, row-y);
	      Bpixel = *Bi;
	      Rpixel[0] = max ((int)Apixel[0], (int)Bpixel[0]);
	      Rpixel[1] = max ((int)Apixel[1], (int)Bpixel[1]);
	      Rpixel[2] = max ((int)Apixel[2], (int)Bpixel[2]);
	      Rpixel[3] = max ((int)Apixel[3], (int)Bpixel[3]);
	    }
	  else
	    {
	      Rpixel[0] = Apixel[0];
	      Rpixel[1] = Apixel[1];
	      Rpixel[2] = Apixel[2];
	      Rpixel[3] = Apixel[3];
	    }
	}
    }
  return R;
}

fImage* darkenOnly (fImage *A, fImage *B, int x, int y)
{
  fImage *R;
  
  int Bw = B->width ();
  int Bh = B->height ();
  
  uchar *Apixel;
  uchar *Bpixel;
  uchar *Rpixel;
  
  fImage::iterator Rend;
  fImage::iterator Aend;
  fImage::iterator Ri;
  fImage::iterator Ai;
  fImage::iterator Bi;
  
  for (int row=0; row < A->height (); row++)
    {
      Rend = R->end (row);
      Aend = A->end (row);
      int col;
      
      for (Ri = R->begin (row), Ai = A->begin (row), col=0; Ri != Rend; Ai++, Ri++, col++)
	{
	  Rpixel = *Ri;
	  Apixel = *Ai;
	  if ((col > x) && (col < (x+Bw)) && (row > y) && (row < (y+Bh)))
	    {
	      Bi = (*B)(col-x, row-y);
	      Bpixel = *Bi;
	      Rpixel[0] = min ((int)Apixel[0], (int)Bpixel[0]);
	      Rpixel[1] = min ((int)Apixel[1], (int)Bpixel[1]);
	      Rpixel[2] = min ((int)Apixel[2], (int)Bpixel[2]);
	      Rpixel[3] = min ((int)Apixel[3], (int)Bpixel[3]);
	    }
	  else
	    {
	      Rpixel[0] = Apixel[0];
	      Rpixel[1] = Apixel[1];
	      Rpixel[2] = Apixel[2];
	      Rpixel[3] = Apixel[3];
	    }
	}
    }
  return R;
}


fImage* divide (fImage *A, fImage *B, int x, int y)
{
  fImage *R;
  
  int Bw = B->width ();
  int Bh = B->height ();
  
  uchar *Apixel;
  uchar *Bpixel;
  uchar *Rpixel;
  
  fImage::iterator Rend;
  fImage::iterator Aend;
  fImage::iterator Ri;
  fImage::iterator Ai;
  fImage::iterator Bi;
  
  for (int row=0; row < A->height (); row++)
    {
      Rend = R->end (row);
      Aend = A->end (row);
      int col;
      
      for (Ri = R->begin (row), Ai = A->begin (row), col=0; Ri != Rend; Ai++, Ri++, col++)
	{
	  Rpixel = *Ri;
	  Apixel = *Ai;
	  if ((col > x) && (col < (x+Bw)) && (row > y) && (row < (y+Bh)))
	    {
	      Bi = (*B)(col-x, row-y);
	      Bpixel = *Bi;
	      float t0 = (Bpixel[0]/255.);
	      float t1 = (Bpixel[1]/255.);
	      float t2 = (Bpixel[2]/255.);
	      
	      if (t0 <= 0)
		Rpixel[0] = 255;
	      else
		Rpixel[0] = clampUpper ((int)(Apixel[0]/t0), 255);
	      if (t1 <= 0)
		Rpixel[1] = 255;
	      else
		Rpixel[1] = clampUpper ((int)(Apixel[1]/t1), 255);
	      if (t2 <= 0)
		Rpixel[2] = 255;
	      else
	      Rpixel[2] = clampUpper ((int)(Apixel[2]/t2), 255);
	      Rpixel[3] = 255; //(int)(t*Bpixel[3]);
	    }
	  else
	    {
	      Rpixel[0] = Apixel[0];
	      Rpixel[1] = Apixel[1];
	      Rpixel[2] = Apixel[2];
	      Rpixel[3] = Apixel[3];
	    }
	}
    }
  return R;
}

fImage* multiply (fImage *A, fImage *B, int x, int y)
{
  fImage *R;
  
  int Bw = B->width ();
  int Bh = B->height ();
  
  uchar *Apixel;
  uchar *Bpixel;
  uchar *Rpixel;
  
  fImage::iterator Rend;
  fImage::iterator Aend;
  fImage::iterator Ri;
  fImage::iterator Ai;
  fImage::iterator Bi;
  
  for (int row=0; row < A->height (); row++)
    {
      Rend = R->end (row);
      Aend = A->end (row);
      int col;
      
      for (Ri = R->begin (row), Ai = A->begin (row), col=0; Ri != Rend; Ai++, Ri++, col++)
	{
	  Rpixel = *Ri;
	  Apixel = *Ai;
	  if ((col > x) && (col < (x+Bw)) && (row > y) && (row < (y+Bh)))
	    {
	      Bi = (*B)(col-x, row-y);
	      Bpixel = *Bi;
	      float t0 = (Bpixel[0]/255.);
	      float t1 = (Bpixel[1]/255.);
	      float t2 = (Bpixel[2]/255.);
	      
	      Rpixel[0] = (int)(Apixel[0]*t0);
	      Rpixel[1] = (int)(Apixel[1]*t1);
	      Rpixel[2] = (int)(Apixel[2]*t2);
	      Rpixel[3] = 255; //(int)(t*Bpixel[3]);
	    }
	  else
	    {
	      Rpixel[0] = Apixel[0];
	      Rpixel[1] = Apixel[1];
	      Rpixel[2] = Apixel[2];
	      Rpixel[3] = Apixel[3];
	    }
	}
    }
  return R;
}
*/


