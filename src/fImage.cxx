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
	  Apixel[0] = max ((int)Apixel[0], (int)Bpixel[0]) - min ((int)Apixel[0], (int)Bpixel[0]);
	  Apixel[1] = max ((int)Apixel[1], (int)Bpixel[1]) - min ((int)Apixel[1], (int)Bpixel[1]);
	  Apixel[2] = max ((int)Apixel[2], (int)Bpixel[2]) - min ((int)Apixel[2], (int)Bpixel[2]);
	  Apixel[3] = clampUpper (Apixel[3] + (int)(value*m*Apixel[3]), 255);
	}
    }
  return A;
}

fImage* lightenOnly (fImage *A, fImage *B, int xo, int yo, float value=1.0)
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
	  Apixel[0] = max ((int)Apixel[0], (int)Bpixel[0]);
	  Apixel[1] = max ((int)Apixel[1], (int)Bpixel[1]);
	  Apixel[2] = max ((int)Apixel[2], (int)Bpixel[2]);
	  Apixel[3] = clampUpper (Apixel[3] + (int)(value*m*Apixel[3]), 255);
	}
    }
  return A;
}

fImage* darkenOnly (fImage *A, fImage *B, int xo, int yo, float value=1.0)
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
	  Apixel[0] = min ((int)Apixel[0], (int)Bpixel[0]);
	  Apixel[1] = min ((int)Apixel[1], (int)Bpixel[1]);
	  Apixel[2] = min ((int)Apixel[2], (int)Bpixel[2]);
	  Apixel[3] = clampUpper (Apixel[3] + (int)(value*m*Apixel[3]), 255);
	}
    }
  return A;
}

fImage* divide (fImage *A, fImage *B, int xo, int yo, float value=1.0)
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
	  float t0 = (Bpixel[0]/255.);
	  float t1 = (Bpixel[1]/255.);
	  float t2 = (Bpixel[2]/255.);
	  
	  if (t0 <= 0)
	    Apixel[0] = 255;
	  else
	    Apixel[0] = clampUpper ((int)(Apixel[0]/t0), 255);
	  if (t1 <= 0)
	    Apixel[1] = 255;
	  else
	    Apixel[1] = clampUpper ((int)(Apixel[1]/t1), 255);
	  if (t2 <= 0)
	    Apixel[2] = 255;
	  else
	    Apixel[2] = clampUpper ((int)(Apixel[2]/t2), 255);

	  Apixel[3] = clampUpper (Apixel[3] + (int)(value*m*Apixel[3]), 255);
	}
    }
  return A;
}

fImage* multiply (fImage *A, fImage *B, int xo, int yo, float value=1.0)
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
	  float t0 = (Bpixel[0]/255.);
	  float t1 = (Bpixel[1]/255.);
	  float t2 = (Bpixel[2]/255.);
	  
	  Apixel[0] = (int)(Apixel[0]*t0);
	  Apixel[1] = (int)(Apixel[1]*t1);
	  Apixel[2] = (int)(Apixel[2]*t2);

	  Apixel[3] = clampUpper (Apixel[3] + (int)(value*m*Apixel[3]), 255);
	}
    }
  return A;
}
