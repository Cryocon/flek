#include <Flek/math.h>
#include <Flek/fImage.h>
#include <iostream.h>
#include <fstream.h>

/*
 * All operations are done "in-place" on image A and do not return a 
 * new image for efficiency.  If you want a new image, copy image A
 * and then work on the copy.
 */

fImage* add (fImage *A, fImage *B, int xo, int yo, float value=1.0)
{
  unsigned char *Apixel;
  unsigned char *Bpixel;
  
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

/*
fImage* subtract (fImage *A, fImage *B, int x, int y)
{
  fImage *R;
  
  int Bw = B->width ();
  int Bh = B->height ();
  
  unsigned char *Apixel;
  unsigned char *Bpixel;
  unsigned char *Rpixel;
  
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
  
  unsigned char *Apixel;
  unsigned char *Bpixel;
  unsigned char *Rpixel;
  
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
  
  unsigned char *Apixel;
  unsigned char *Bpixel;
  unsigned char *Rpixel;
  
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
  
  unsigned char *Apixel;
  unsigned char *Bpixel;
  unsigned char *Rpixel;
  
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
  
  unsigned char *Apixel;
  unsigned char *Bpixel;
  unsigned char *Rpixel;
  
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
  
  unsigned char *Apixel;
  unsigned char *Bpixel;
  unsigned char *Rpixel;
  
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

static short readShort (ifstream &input)
{ 
  unsigned char b[2]; 
  input >> b[0];
  input >> b[1];
  return ((b[0] << 8) | b[1]); 
} 

static long readLong (ifstream &input)
{ 
  unsigned char b[4];
  input >> b[0];
  input >> b[1];
  input >> b[2];
  input >> b[3];
  return ((b[0] << 24) | (b[1] << 16) | (b[2] << 8) | b[3]); 
} 

/*
 * Read 8 bit run length encoded data.  row is the data location we are reading into.
 * and width is the width of the data location.
 */
static int 
readRLE8 (ifstream &input, unsigned short *row, int width)
{ 
  int i;
  unsigned char c;
  int count;  // RLE count
  int length; // Bytes read
 
 
  length = 0; 
 
  while (width > 0) 
    {
      input >> c;
      if (input.eof ())
	return -1;
      
      length++; 
      
      count = c & 127; 
      if (count == 0) 
	break; 
      
      if (c & 128) 
	for (i = 0; i < count; i++, row++, width--, length++) 
	  input >> *row;
      else 
	{ 
	  input >> c;
	  length++; 
	  for (i = 0; i < count; i++, row++, width--) 
	    *row = c;
	}
    }
  
  return (width > 0 ? -1 : length); 
}

static bool writeShort (ofstream &output, unsigned short n)
{
  output.put (n>>8);
  output.put (n);

  if (output.bad ())
    return true;

  return false;
}

static bool writeLong (ofstream &output, long n)
{
  output.put (n>>24);
  output.put (n>>16);
  output.put (n>>8);
  output.put (n);

  if (output.bad ())
    return true;

  return false;
}

/*
 * Write 8 bit run length encoded data.
 */
static int 
writeRLE8 (ofstream &output, unsigned short *row, int width)
{ 
  int length;  // Byte count of output line 
  int count;   // Number of repeated/non-repeated pixels
  int i, j;
  unsigned short *start, repeat;
   
  for (i = width, length = 0; i > 0; i-= 2) 
    { 
      start = row;
      row += 2;

      while (i > 0 && (row[-2] != row[-1] || row[-1] != row[0])) 
	{ 
	  row++; 
	  i--; 
	}
 
      row -= 2; 
      i += 2; 
      count = row - start; 
      while (count > 0) 
	{ 
	  j = count > 126 ? 126 : count; 
	  count -= j; 
	  
	  output.put (128 | j);
	  if (output.bad ())
	    return -1; 
	  length++; 
 
	  while (j > 0) 
	    { 
	      output.put (*start);
	      if (output.bad ()) 
		return -1;
	      start++; 
	      length++; 
	      j--; 
	    }
	}
 
      if (i <= 0) 
	break; 
 
      start = row; 
      repeat = row[0]; 
      
      row++; 
      i--; 
 
      while (i > 0 && *row == repeat) 
	{ 
	  row++; 
	  i--; 
	}
      
      count = row - start; 
      while (count > 0) 
	{ 
	  j = count > 126 ? 126 : count; 
	  count -= i; 
	  output.put (j);
	  if (output.bad ())
	    return -1;
	  length++; 
 
	  output.put (repeat);
	  if (output.bad ())
	    return -1;
	  length++; 
	}
    }
 
  length++; 
 
  output.put (0);
  if (output.bad ())
    return -1;

  return length; 
} 

typedef struct 
{ 
  int              bpc;         // Bytes per channel
  int              compression; // Compression 
  unsigned short   width,       // Width in pixels
                   height,      // Height in pixels
                   channels;    // Number of channels 
  long             firstRow,    // File offset for first row
                   nextRow,     // File offset for next row
                   **table,     // Offset table for compression
                   **length;    // Length table for compression 
  unsigned short   *arleRow;    // Advanced RLE compression buffer
  long             arleOffset,  // Advanced RLE buffer offset
                   arleLength;  // Advanced RLE buffer length
} sgiT;

// row = row, y = row #, z = channel
int 
sgiWriteRow (ofstream &output, sgiT *img, unsigned short *row, int y, int channel)
{ 
  int   x;
  long  offset; // File offset
 
 
  if (img == NULL || 
      row == NULL || 
      y < 0 || 
      y >= img->height || 
      channel < 0 || 
      channel >= img->channels) 
    return -1; 
 
  switch (img->compression) 
  { 
    case SGI_COMP_NONE : 
       /* 
        * Seek to the image row - optimize buffering by only seeking if 
        * necessary... 
        */ 
 
        offset = 512 + (y + channel * img->height) * img->width * img->bpp; 
        if (offset != ftell(img->file)) 
          fseek(img->file, offset, SEEK_SET); 
 
        if (img->bpp == 1) 
        { 
          for (x = img->width; x > 0; x --, row ++) 
            putc(*row, img->file); 
        } 
        else 
        { 
          for (x = img->width; x > 0; x --, row ++) 
            putshort(*row, img->file); 
        }; 
        break; 
 
    case SGI_COMP_ARLE : 
        if (img->table[channel][y] != 0) 
          return (-1); 
 
       /* 
        * First check the last row written... 
        */ 
 
        if (img->arle_offset > 0) 
        { 
          for (x = 0; x < img->width; x ++) 
            if (row[x] != img->arle_row[x]) 
              break; 
 
          if (x == img->width) 
          { 
            img->table[channel][y]  = img->arle_offset; 
            img->length[channel][y] = img->arle_length; 
            return (0); 
          }; 
        }; 
 
       /* 
        * If that didn't match, search all the previous rows... 
        */ 
 
        fseek(img->file, img->firstrow, SEEK_SET); 
 
        if (img->bpp == 1) 
        { 
          do 
          { 
            img->arle_offset = ftell(img->file); 
            if ((img->arle_length = read_rle8(img->file, img->arle_row, img->width)) < 0) 
            { 
              x = 0; 
              break; 
            }; 
 
            for (x = 0; x < img->width; x ++) 
              if (row[x] != img->arle_row[x]) 
                break; 
          } 
          while (x < img->width); 
        } 
        else 
        { 
          do 
          { 
            img->arle_offset = ftell(img->file); 
            if ((img->arle_length = read_rle16(img->file, img->arle_row, img->width)) < 0) 
            { 
              x = 0; 
              break; 
            }; 
 
            for (x = 0; x < img->width; x ++) 
              if (row[x] != img->arle_row[x]) 
                break; 
          } 
          while (x < img->width); 
        }; 
 
        if (x == img->width) 
        { 
          img->table[channel][y]  = img->arle_offset; 
          img->length[channel][y] = img->arle_length; 
          return (0); 
        } 
        else 
          fseek(img->file, 0, SEEK_END);       /* Clear EOF */ 
 
    case SGI_COMP_RLE : 
        if (img->table[channel][y] != 0) 
          return (-1); 
 
        offset = img->table[channel][y] = img->nextrow; 
 
        if (offset != ftell(img->file)) 
          fseek(img->file, offset, SEEK_SET); 
 
        if (img->bpp == 1) 
          x = write_rle8(img->file, row, img->width); 
        else 
          x = write_rle16(img->file, row, img->width); 
 
        if (img->compression == SGI_COMP_ARLE) 
        { 
          img->arle_offset = offset; 
          img->arle_length = x; 
          memcpy(img->arle_row, row, img->width * sizeof(short)); 
        }; 
 
        img->nextrow      = ftell(img->file); 
        img->length[channel][y] = x; 
 
        return x; 
  }; 
 
  return 0; 
} 
