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

#define INT_MULT(a,b,t)  ((t) = (a) * (b) + 0x80, ((((t) >> 8) + (t)) >> 8))
#define INT_BLEND(a,b,alpha,tmp)  (INT_MULT((a)-(b), alpha, tmp) + (b))

fImage::fImage ()
{
  Data = 0;
  W = 0;
  H = 0;
}

fImage::fImage (int w, int h)
{
  W = w;
  H = h;
  Data = new uchar [W*H*4];
}

fImage::~fImage ()
{
  if (Data) delete [] Data;
}

/*
 * All operations are done "in-place" on image A and do not return a 
 * new image for efficiency.  If you want a new image, copy image A
 * and then work on the copy.
 */

void composite (unsigned char* dest,
		const unsigned char* src,
		int opacity,
		int length)
{
  int a;
  register long t1;
  unsigned char* end = dest + 4*length;
  for (; dest<end; dest+=4, src+=4)
    {
      a = INT_MULT(src[3], opacity, t1);
      dest[0] = INT_BLEND(src[0], dest[0], a, t1);
      dest[1] = INT_BLEND(src[1], dest[1], a, t1);
      dest[2] = INT_BLEND(src[2], dest[2], a, t1);
      dest[3] = 255;
    }
}

fImage* composite (fImage *A, fImage *B, int xo, int yo, float value)
{
  int xi = max (xo, 0);
  int yi = max (yo, 0);    
  int xf = min (max (xo + B->width (), 0), A->width ());
  int yf = min (max (yo + B->height (), 0), A->height ());

  for (int row=yi; row < yf; row++)
    composite ( *(*A)(xi, row), *(*B)(xi-xo, row-yo), (int)(value*255), xf-xi );
  return A;
}

void add (unsigned char* dest,
	  const unsigned char* src,
	  int opacity,
	  int length)
{
  int a;
  register long t1;
  unsigned char* end = dest + 4*length;
  for (; dest<end; dest+=4, src+=4)
    {
      a = INT_MULT(src[3], opacity, t1);
      dest[0] = INT_BLEND(clampUpper(src[0]+dest[0], 255), dest[0], a, t1);
      dest[1] = INT_BLEND(clampUpper(src[1]+dest[1], 255), dest[1], a, t1);
      dest[2] = INT_BLEND(clampUpper(src[2]+dest[2], 255), dest[2], a, t1);
      dest[3] = 255;
    }
}

fImage* add (fImage *A, fImage *B, int xo, int yo, float value)
{
  int xi = max (xo, 0);
  int yi = max (yo, 0);    
  int xf = min (max (xo + B->width (), 0), A->width ());
  int yf = min (max (yo + B->height (), 0), A->height ());

  for (int row=yi; row < yf; row++)
    add ( *(*A)(xi, row), *(*B)(xi-xo, row-yo), (int)(value*255), xf-xi );
  return A;
}

void subtract (unsigned char* dest,
	       const unsigned char* src,
	       int opacity,
	       int length)
{
  int a;
  register long t1;
  unsigned char* end = dest + 4*length;
  for (; dest<end; dest+=4, src+=4)
    {
      a = INT_MULT(src[3], opacity, t1);
      dest[0] = INT_BLEND(clampLower(dest[0]-src[0], 0), dest[0], a, t1);
      dest[1] = INT_BLEND(clampLower(dest[1]-src[1], 0), dest[1], a, t1);
      dest[2] = INT_BLEND(clampLower(dest[2]-src[2], 0), dest[2], a, t1);
      dest[3] = 255;
    }
}

fImage* subtract (fImage *A, fImage *B, int xo, int yo, float value)
{
  int xi = max (xo, 0);
  int yi = max (yo, 0);    
  int xf = min (max (xo + B->width (), 0), A->width ());
  int yf = min (max (yo + B->height (), 0), A->height ());

  for (int row=yi; row < yf; row++)
    subtract ( *(*A)(xi, row), *(*B)(xi-xo, row-yo), (int)(value*255), xf-xi );
  return A;
}

void difference (unsigned char* dest,
		 const unsigned char* src,
		 int opacity,
		 int length)
{
  int a;
  register long t1;
  unsigned char* end = dest + 4*length;
  for (; dest<end; dest+=4, src+=4)
    {
      a = INT_MULT(src[3], opacity, t1);
      dest[0] = INT_BLEND(max(dest[0],src[0]) - min(dest[0],src[0]), dest[0], a, t1);
      dest[1] = INT_BLEND(max(dest[1],src[1]) - min(dest[1],src[1]), dest[1], a, t1);
      dest[2] = INT_BLEND(max(dest[2],src[2]) - min(dest[2],src[2]), dest[2], a, t1);
      dest[3] = 255;
    }
}

fImage* difference (fImage *A, fImage *B, int xo, int yo, float value)
{
  int xi = max (xo, 0);
  int yi = max (yo, 0);    
  int xf = min (max (xo + B->width (), 0), A->width ());
  int yf = min (max (yo + B->height (), 0), A->height ());

  for (int row=yi; row < yf; row++)
    difference ( *(*A)(xi, row), *(*B)(xi-xo, row-yo), (int)(value*255), xf-xi );
  return A;
}

void lightenOnly (unsigned char* dest,
		  const unsigned char* src,
		  int opacity,
		  int length)
{
  int a;
  register long t1;
  unsigned char* end = dest + 4*length;
  for (; dest<end; dest+=4, src+=4)
    {
      a = INT_MULT(src[3], opacity, t1);
      dest[0] = INT_BLEND(max(dest[0],src[0]), dest[0], a, t1);
      dest[1] = INT_BLEND(max(dest[1],src[1]), dest[1], a, t1);
      dest[2] = INT_BLEND(max(dest[2],src[2]), dest[2], a, t1);
      dest[3] = 255;
    }
}

fImage* lightenOnly (fImage *A, fImage *B, int xo, int yo, float value)
{
  int xi = max (xo, 0);
  int yi = max (yo, 0);    
  int xf = min (max (xo + B->width (), 0), A->width ());
  int yf = min (max (yo + B->height (), 0), A->height ());

  for (int row=yi; row < yf; row++)
    lightenOnly ( *(*A)(xi, row), *(*B)(xi-xo, row-yo), (int)(value*255), xf-xi );
  return A;
}

void darkenOnly (unsigned char* dest,
		 const unsigned char* src,
		 int opacity,
		 int length)
{
  int a;
  register long t1;
  unsigned char* end = dest + 4*length;
  for (; dest<end; dest+=4, src+=4)
    {
      a = INT_MULT(src[3], opacity, t1);
      dest[0] = INT_BLEND(min(dest[0],src[0]), dest[0], a, t1);
      dest[1] = INT_BLEND(min(dest[1],src[1]), dest[1], a, t1);
      dest[2] = INT_BLEND(min(dest[2],src[2]), dest[2], a, t1);
      dest[3] = 255;
    }
}

fImage* darkenOnly (fImage *A, fImage *B, int xo, int yo, float value)
{
  int xi = max (xo, 0);
  int yi = max (yo, 0);    
  int xf = min (max (xo + B->width (), 0), A->width ());
  int yf = min (max (yo + B->height (), 0), A->height ());
  
  for (int row=yi; row < yf; row++)
    darkenOnly ( *(*A)(xi, row), *(*B)(xi-xo, row-yo), (int)(value*255), xf-xi );
  return A;
}

void divide (unsigned char* dest,
	     const unsigned char* src,
	     int opacity,
	     int length)
{
  int a;
  register long t1;
  unsigned char* end = dest + 4*length;
  for (; dest<end; dest+=4, src+=4)
    {
      a = INT_MULT(src[3], opacity, t1);
      dest[0] = INT_BLEND(min((dest[0]*256)/(1+src[0]), 255), dest[0], a, t1);
      dest[1] = INT_BLEND(min((dest[1]*256)/(1+src[1]), 255), dest[1], a, t1);
      dest[2] = INT_BLEND(min((dest[2]*256)/(1+src[2]), 255), dest[2], a, t1);
      dest[3] = min(dest[3], src[3]);
    }
}

fImage* divide (fImage *A, fImage *B, int xo, int yo, float value)
{
  int xi = max (xo, 0);
  int yi = max (yo, 0);    
  int xf = min (max (xo + B->width (), 0), A->width ());
  int yf = min (max (yo + B->height (), 0), A->height ());
  
  for (int row=yi; row < yf; row++)
    divide ( *(*A)(xi, row), *(*B)(xi-xo, row-yo), (int)(value*255), xf-xi );
  return A;
}

void multiply (unsigned char* dest,
	       const unsigned char* src,
	       int opacity,
	       int length)
{
  int a;
  register long t1;
  unsigned char* end = dest + 4*length;
  for (; dest<end; dest+=4, src+=4)
    {
      a = INT_MULT(src[3], opacity, t1);
      dest[0] = INT_BLEND(INT_MULT(src[0], dest[0], t1), dest[0], a, t1);
      dest[1] = INT_BLEND(INT_MULT(src[1], dest[1], t1), dest[1], a, t1);
      dest[2] = INT_BLEND(INT_MULT(src[2], dest[2], t1), dest[2], a, t1);
      dest[3] = min(dest[3], src[3]);
    }
}

fImage* multiply (fImage *A, fImage *B, int xo, int yo, float value)
{
  int xi = max (xo, 0);
  int yi = max (yo, 0);
  int xf = min (max (xo + B->width (), 0), A->width ());
  int yf = min (max (yo + B->height (), 0), A->height ());
  
  for (int row=yi; row < yf; row++)
    multiply ( *(*A)(xi, row), *(*B)(xi-xo, row-yo), (int)(value*255), xf-xi );
  return A;
}

void screen (unsigned char* dest,
	     const unsigned char* src,
	     int opacity,
	     int length)
{
  int a;
  register long t1;
  unsigned char* end = dest + 4*length;
  for (; dest<end; dest+=4, src+=4)
    {
      a = INT_MULT(src[3], opacity, t1);
      dest[0] = INT_BLEND(255-INT_MULT(255-src[0], 255-dest[0], t1), dest[0], a, t1);
      dest[1] = INT_BLEND(255-INT_MULT(255-src[1], 255-dest[1], t1), dest[1], a, t1);
      dest[2] = INT_BLEND(255-INT_MULT(255-src[2], 255-dest[2], t1), dest[2], a, t1);
      dest[3] = min(dest[3], src[3]);
    }
}

fImage* screen (fImage *A, fImage *B, int xo, int yo, float value)
{
  int xi = max (xo, 0);
  int yi = max (yo, 0);    
  int xf = min (max (xo + B->width (), 0), A->width ());
  int yf = min (max (yo + B->height (), 0), A->height ());
  
  for (int row=yi; row < yf; row++)
    screen ( *(*A)(xi, row), *(*B)(xi-xo, row-yo), (int)(value*255), xf-xi );
  return A;
}

void overlay (unsigned char* dest,
	      const unsigned char* src,
	      int opacity,
	      int length)
{
  int a;
  register long t1;
  unsigned char* end = dest + 4*length;
  for (; dest<end; dest+=4, src+=4)
    {
      a = INT_MULT(src[3], opacity, t1);
      dest[0] = INT_BLEND(INT_MULT(dest[0], dest[0]+INT_MULT(2*src[0],255-dest[0],t1), t1), dest[0], a, t1);
      dest[1] = INT_BLEND(INT_MULT(dest[1], dest[0]+INT_MULT(2*src[1],255-dest[1],t1), t1), dest[1], a, t1);
      dest[2] = INT_BLEND(INT_MULT(dest[2], dest[0]+INT_MULT(2*src[2],255-dest[2],t1), t1), dest[2], a, t1);

      dest[3] = min(dest[3], src[3]);
    }
}

fImage* overlay (fImage *A, fImage *B, int xo, int yo, float value)
{
  int xi = max (xo, 0);
  int yi = max (yo, 0);    
  int xf = min (max (xo + B->width (), 0), A->width ());
  int yf = min (max (yo + B->height (), 0), A->height ());
  
  for (int row=yi; row < yf; row++)
    overlay ( *(*A)(xi, row), *(*B)(xi-xo, row-yo), (int)(value*255), xf-xi );
  return A;
}
