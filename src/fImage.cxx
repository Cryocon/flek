#include <Flek/math.h>
#include <Flek/fImage.h>

/*
 * Speedup -- always do operations in place!  If we want to do it on a copy
 * we can always copy it with a faster memset function.  Skip to just
 * the area that needs compositing done.
 */

fImageRGBA* add (fImageRGBA *A, fImageRGBA *B, int x, int y, bool inplace)
{
  fImageRGBA *R;

  if (!inplace)
    R = new fImageRGBA (A->width (), A->height ());
  else
    R = A;
  
  int Bw = B->width ();
  int Bh = B->height ();
  
  unsigned char *Apixel;
  unsigned char *Bpixel;
  unsigned char *Rpixel;
  
  fImageRGBA::iterator Rend;
  fImageRGBA::iterator Aend;
  fImageRGBA::iterator Ri;
  fImageRGBA::iterator Ai;
  fImageRGBA::iterator Bi;
  
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
	      Rpixel[0] = clampUpper (Apixel[0] + Bpixel[0], 255);
	      Rpixel[1] = clampUpper (Apixel[1] + Bpixel[1], 255);
	      Rpixel[2] = clampUpper (Apixel[2] + Bpixel[2], 255);
	      Rpixel[3] = clampUpper (Apixel[3] + Bpixel[3], 255);
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

fImageRGBA* subtract (fImageRGBA *A, fImageRGBA *B, int x, int y, bool inplace)
{
  fImageRGBA *R;

  if (!inplace)
    R = new fImageRGBA (A->width (), A->height ());
  else
    R = A;
  
  int Bw = B->width ();
  int Bh = B->height ();
  
  unsigned char *Apixel;
  unsigned char *Bpixel;
  unsigned char *Rpixel;
  
  fImageRGBA::iterator Rend;
  fImageRGBA::iterator Aend;
  fImageRGBA::iterator Ri;
  fImageRGBA::iterator Ai;
  fImageRGBA::iterator Bi;
  
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

fImageRGBA* difference (fImageRGBA *A, fImageRGBA *B, int x, int y, bool inplace)
{
  fImageRGBA *R;

  if (!inplace)
    R = new fImageRGBA (A->width (), A->height ());
  else
    R = A;
  
  int Bw = B->width ();
  int Bh = B->height ();
  
  unsigned char *Apixel;
  unsigned char *Bpixel;
  unsigned char *Rpixel;
  
  fImageRGBA::iterator Rend;
  fImageRGBA::iterator Aend;
  fImageRGBA::iterator Ri;
  fImageRGBA::iterator Ai;
  fImageRGBA::iterator Bi;
  
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


fImageRGBA* lightenOnly (fImageRGBA *A, fImageRGBA *B, int x, int y, bool inplace)
{
  fImageRGBA *R;

  if (!inplace)
    R = new fImageRGBA (A->width (), A->height ());
  else
    R = A;
  
  int Bw = B->width ();
  int Bh = B->height ();
  
  unsigned char *Apixel;
  unsigned char *Bpixel;
  unsigned char *Rpixel;
  
  fImageRGBA::iterator Rend;
  fImageRGBA::iterator Aend;
  fImageRGBA::iterator Ri;
  fImageRGBA::iterator Ai;
  fImageRGBA::iterator Bi;
  
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

fImageRGBA* darkenOnly (fImageRGBA *A, fImageRGBA *B, int x, int y, bool inplace)
{
  fImageRGBA *R;

  if (!inplace)
    R = new fImageRGBA (A->width (), A->height ());
  else
    R = A;
  
  int Bw = B->width ();
  int Bh = B->height ();
  
  unsigned char *Apixel;
  unsigned char *Bpixel;
  unsigned char *Rpixel;
  
  fImageRGBA::iterator Rend;
  fImageRGBA::iterator Aend;
  fImageRGBA::iterator Ri;
  fImageRGBA::iterator Ai;
  fImageRGBA::iterator Bi;
  
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


fImageRGBA* divide (fImageRGBA *A, fImageRGBA *B, int x, int y, bool inplace)
{
  fImageRGBA *R;

  if (!inplace)
    R = new fImageRGBA (A->width (), A->height ());
  else
    R = A;
  
  int Bw = B->width ();
  int Bh = B->height ();
  
  unsigned char *Apixel;
  unsigned char *Bpixel;
  unsigned char *Rpixel;
  
  fImageRGBA::iterator Rend;
  fImageRGBA::iterator Aend;
  fImageRGBA::iterator Ri;
  fImageRGBA::iterator Ai;
  fImageRGBA::iterator Bi;
  
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

fImageRGBA* multiply (fImageRGBA *A, fImageRGBA *B, int x, int y, bool inplace)
{
  fImageRGBA *R;

  if (!inplace)
    R = new fImageRGBA (A->width (), A->height ());
  else
    R = A;
  
  int Bw = B->width ();
  int Bh = B->height ();
  
  unsigned char *Apixel;
  unsigned char *Bpixel;
  unsigned char *Rpixel;
  
  fImageRGBA::iterator Rend;
  fImageRGBA::iterator Aend;
  fImageRGBA::iterator Ri;
  fImageRGBA::iterator Ai;
  fImageRGBA::iterator Bi;
  
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
