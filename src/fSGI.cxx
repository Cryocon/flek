#include <Flek/math.h>
#include <Flek/fFile.h>
#include <Flek/fImage.h>
#include <Flek/fSGI.h>
#include <iostream.h>

/*
 * Reads 8 bit run length encoded data of size width from input.  
 * The read data is stored in the array row.
 */
static int 
getRLE8 (fFile &input, int width, uchar *row)
{ 
  int i;
  uchar c;
  int runCount; // RLE runs
  int length; // Bytes read 
 
  length = 0; 
 
  while (width > 0) 
    {
      input.getHi (c);
      if (input.bad ())
	{
	  cerr << "ERROR" << endl;
	  return -1;
	}

      length++; 
      
      runCount = c & 127; 
      if (runCount == 0) 
	break; 
      
      if (c & 128) 
	{
	  input.read (row, runCount);
	  length += runCount;
	  width -= runCount;
	  row += runCount;
	}
      else 
	{ 
	  input.getHi (c);
	  length++; 
	  for (i = 0; i < runCount; i++, row++, width--) 
	    *row = c;
	}
    }
  return (width > 0 ? -1 : length); 
}

static int 
putRLE8 (fFile &output, int width, uchar *row)
{ 
  int length;  // Byte count of output line 
  int runCount;   // Number of repeated/non-repeated pixels
  int x;
  int i;
  uchar *start, repeat;
   
  for (x = width, length = 0; x > 0;) 
    { 
      start = row;
      row += 2;
      x -= 2;
      
      while (x > 0 && (row[-2] != row[-1] || row[-1] != row[0])) 
	{ 
	  row++; 
	  x--; 
	}
 
      row -= 2; 
      x += 2; 
      
      runCount = row - start; 
      while (runCount > 0) 
	{ 
	  i = runCount > 126 ? 126 : runCount; 
	  runCount -= i; 
	  
	  output.putHi ((uchar)(128|i));
	  length++;
 
	  while (i > 0) 
	    { 
	      output.putHi ((uchar)*start);

	      start++; 
	      length++; 
	      i--; 
	    }
	}
 
      if (x <= 0) 
	break; 
 
      start = row; 
      repeat = row[0]; 
      
      row++; 
      x--; 
      
      while (x > 0 && *row == repeat) 
	{ 
	  row++; 
	  x--; 
	}
      
      runCount = row - start; 
      while (runCount > 0) 
	{ 
	  i = runCount > 126 ? 126 : runCount; 
	  runCount -= i; 

	  output.putHi ((uchar)i);

	  output.putHi ((uchar)repeat);

	  length += 2; 
	}
    }
 
  length++; 
 
  output.putHi ((char) 0);
  if (output.bad ())
    return -1;

  return length; 
} 

typedef struct 
{ 
  int              bpc;         // Bytes per channel
  int              compression; // Compression 
  ushort           width,       // Width in pixels
                   height,      // Height in pixels
                   channels;    // Number of channels 
  ulong            firstRow,    // File offset for first row
                   nextRow,     // File offset for next row
                   **table,     // Offset table for compression
                   **length;    // Length table for compression 
  uchar            *arleRow;    // Advanced RLE compression buffer
  long             arleOffset,  // Advanced RLE buffer offset
                   arleLength;  // Advanced RLE buffer length
} sgiT;

int 
sgiPutRow (fFile &output, sgiT &img, uchar *row, int y, int channel)
{ 
  int   x;
  long  offset;
 
  if (!row)
    return -1; 
  
  switch (img.compression) 
    { 
    case fSGI::NONE: 
      
      offset = 512 + (y + channel * img.height) * img.width * img.bpc;
      if (offset != output.tell ()) 
	output.seek (offset); 
      
      if (img.bpc == 1) 
	output.write ((char*)row, img.width);

      break; 
 
    case fSGI::ARLE: 

      // Check the last row written.
      if (img.arleOffset > 0) 
        {
          for (x = 0; x < img.width; x++) 
            if (row[x] != img.arleRow[x]) 
              break; 
	  
          if (x == img.width) 
	    { 
	      img.table[channel][y]  = img.arleOffset; 
	      img.length[channel][y] = img.arleLength; 
	      return (0); 
	    }
        }
      
      // If that didn't match, search the previous rows.
      output.seek (img.firstRow);
      
      if (img.bpc == 1) 
        { 
          do 
	    { 
	      img.arleOffset = output.tell (); 
	      if ((img.arleLength = getRLE8 (output, img.width, img.arleRow)) < 0) 
		{ 
		  x = 0; 
		  break; 
		}
	      
	      for (x = 0; x < img.width; x ++) 
		if (row[x] != img.arleRow[x]) 
		  break; 
	    } 
          while (x < img.width); 
        } 
      else
	{
	  cerr << "SGI files larger than 1 byte per channel are not supported." << endl;
	  return -1;
	}

      if (x == img.width) 
        { 
          img.table[channel][y]  = img.arleOffset; 
          img.length[channel][y] = img.arleLength; 
          return 0; 
        } 
      else 
	output.seek (0);
 
    case fSGI::RLE: 

      offset = img.table[channel][y] = img.nextRow;
      if (offset != output.tell ()) 
	output.seek (offset); 
 
      if (img.bpc == 1) 
	x = putRLE8 (output, img.width, row); 
      else 
	{
	  cerr << "SGI files larger than 1 byte per channel are not supported." << endl;
	  return -1;
	}
 
      if (img.compression == fSGI::ARLE) 
        { 
          img.arleOffset = offset; 
          img.arleLength = x; 
          memcpy(img.arleRow, row, img.width); 
        }
 
      img.nextRow = output.tell (); 
      img.length[channel][y] = x; 
      
      return x; 
    }
 
  return 0; 
} 

int
sgiGetRow (fFile &input, sgiT& img, uchar* row, int y, int channel)
{
  ulong offset;
  
  if ( (!row) || 
       (y < 0) || (y >= img.height) ||
       (channel < 0) || (channel >= img.channels) )
    return -1;
  
  switch (img.compression)
    {
    case fSGI::NONE:
      
      offset = 512 + (y + channel * img.height) * img.width * img.bpc;

      if (offset != (ulong)input.tell ())
	input.seek (offset);

      if (img.bpc == 1)
	{
	  input.read (row, img.width);
	  row += img.width;
	}
      else
	{
	  cerr << "Not supported" << endl;
	  return -1;
	}
      break;

    case fSGI::RLE:
        offset = img.table[channel][y];
        if (offset != (ulong)input.tell ())
	  input.seek (offset);
	if (input.bad())
	  cerr << "ERROR: Bad seek" << endl;

	if (input.bad())
	  cerr << "ERROR: Bad seek (EOF)" << endl;

        if (img.bpc == 1)
          return (getRLE8 (input, img.width, row));

	cerr << "SGI files larger than 1 byte per channel are not supported." << endl;
	return -1;
  }

  return 0;
}

#include <stdlib.h>

fImage * fSGI::read (char *filename)
{
  fFile input;
  sgiT img;
  input.open (filename, "r");
  uchar c;

  short magic;
  input.getHi (magic);

  if (magic != MAGIC)
    return 0;
  
  input.getHi (c);
  img.compression = c;
  input.getHi (c);
  img.bpc = c;
  input.getHi (img.width); // Dimensions (ignore)
  input.getHi (img.width);
  input.getHi (img.height);
  input.getHi (img.channels);
  unsigned long t;
  input.getHi (t); // Minimum pixel 
  input.getHi (t); // Maximum pixel 

  fImage *Nimg = new fImage (img.width, img.height);
  
  if (img.compression)
    {
      int i, j;

      input.seek (512);

      if (input.bad ())
	cerr << "ERROR @sgiReadFile." << endl;

      img.table = new ulongPtr [img.channels];
      img.table[0] = new ulong [img.height * img.channels];

      for (i = 1; i < img.channels; i++)
	img.table[i] = img.table[0] + i * img.height;
      
      for (i = 0; i < img.channels; i ++)
	for (j = 0; j < img.height; j ++)
	  {
	    ulong offset;
	    input.getHi (offset);
	    img.table[i][j] = offset;
	  }
    }

  uchar *pixel = *(Nimg->begin());

  // Allocate enough memory for one line of the image.
  uchar **rows = new ucharPtr [img.channels];
  rows[0] = new uchar [img.width * img.channels];
  for (int z=0; z<img.channels; z++)
    rows[z] = rows[0] + z * img.width;

  if (img.channels == 4)
    {
      for (int y=0; y < img.height; y++)
	{
	  sgiGetRow (input, img, rows[0], y, 0);
	  sgiGetRow (input, img, rows[1], y, 1);
	  sgiGetRow (input, img, rows[2], y, 2);
	  sgiGetRow (input, img, rows[3], y, 3);

	  for (int x=0; x < img.width; x++, pixel += 4)
	    {
	      pixel[0] = rows[0][x];
	      pixel[1] = rows[1][x];
	      pixel[2] = rows[2][x];
	      pixel[3] = rows[3][x];
	    }
	}
    }
  else if (img.channels == 3)
    {
      for (int y=0; y < img.height; y++)
	{
	  sgiGetRow (input, img, rows[0], y, 0);
	  sgiGetRow (input, img, rows[1], y, 1);
	  sgiGetRow (input, img, rows[2], y, 2);

	  for (int x=0; x < img.width; x++, pixel += 4)
	    {
	      pixel[0] = rows[0][x];
	      pixel[1] = rows[1][x];
	      pixel[2] = rows[2][x];
	      pixel[3] = 255;
	    }
	}
    }
  else if (img.channels == 2)
    {
      for (int y=0; y < img.height; y++)
	{
	  sgiGetRow (input, img, rows[0], y, 0);
	  sgiGetRow (input, img, rows[1], y, 1);

	  for (int x=0; x < img.width; x++, pixel += 4)
	    {
	      pixel[0] = rows[0][x];
	      pixel[1] = rows[1][x];
	      pixel[2] = 0;
	      pixel[3] = 255;
	    }
	}
    }
  else if (img.channels == 1) // Gray
    {
      for (int y=0; y < img.height; y++)
	{
	  sgiGetRow (input, img, rows[0], y, 0);

	  for (int x=0; x < img.width; x++, pixel += 4)
	    {
	      pixel[0] = 
		pixel[1] = 
		pixel[2] = rows[0][x];
	      pixel[3] = 255;
	    }
	}
    }
  
  if (img.compression)
    {
      delete img.table[0];
      img.table[0] = 0;
      delete [] img.table;
    }
  delete [] rows[0];
  delete [] rows;
  
  return Nimg;
}

#include <string.h>

int fSGI::write (char *filename, fImage *data, int compression, int channels)
{
  fFile output;
  output.open (filename, "w+");

  sgiT img;
  uchar c;
  int i;

  img.bpc = 1;
  img.compression = compression;
  img.width = data->width ();
  img.height = data->height ();
  img.channels = channels;
  img.firstRow = 0;
  img.nextRow = 0;
  img.table = 0;
  img.length = 0;
  img.arleRow = 0;
  img.arleOffset = 0;
  img.arleLength = 0;

  output.putHi ((unsigned short)MAGIC);
  c = (img.compression != 0);
  output.putHi (c); // compression
  c = img.bpc;
  output.putHi (c); // bpc
  output.putHi ((unsigned short)3); // dimensions
  output.putHi (img.width);
  output.putHi (img.height);
  output.putHi (img.channels);
  output.putHi ((long)0); // Minimum pixel 
  output.putHi ((long)255); // Maximum pixel 
  output.putHi ((long)0); // Reserved

  // This bit helps stop us from wasting processor time on blank space.
  int   blankSize = max ((unsigned short)max ((unsigned short)488, (unsigned short)(img.width*img.channels)), (unsigned short)(img.height*img.channels*4));
  char *blank = new char [blankSize];
  memset (blank, 0, blankSize);

  output.write (blank, 488);  // 80+102*4 = 488

  switch (compression)
    {
    case fSGI::NONE:

      for (i = img.height; i > 0; i--)
	output.write (blank, img.width*img.channels);

      break;
      
    case fSGI::ARLE:

      // Allocate an extra row for ARLE
      img.arleRow  = new uchar [img.width];
      img.arleOffset = 0;
      
    case fSGI::RLE:

      // Write blank scanline tables for RLE and ARLE
      // Write 0s for img.height * img.channels * 2 * sizeof (long)
      output.write (blank, img.height * sizeof(long) * img.channels);
      output.write (blank, img.height * sizeof(long) * img.channels);

      img.firstRow = output.tell ();
      img.nextRow = output.tell ();

      img.table = new ulongPtr [img.channels];
      img.table[0] = new ulong [img.height * img.channels];
      
      img.length = new ulongPtr [img.channels];
      img.length[0] = new ulong [img.height * img.channels];

      for (i = 1; i < img.channels; i ++)
	{
	  img.table[i] = img.table[0] + (i * img.height);
	  img.length[i] = img.length[0] + (i * img.height);
	}

      break;
    }

  uchar *pixel;

  uchar **rows = new ucharPtr [img.channels];
  rows[0] = new uchar [img.width * img.channels];

  for (int z = 1; z < img.channels; z++)
    rows[z] = rows[0] + z * img.width;

  pixel = *(data->begin ());

  if (img.channels == 4)
    {
      for (int y=0; y < img.height; y++)
	{
	  for (int x=0; x < img.width; x++, pixel += 4)
	    {
	      rows[0][x] = pixel[0];
	      rows[1][x] = pixel[1];
	      rows[2][x] = pixel[2];
	      rows[3][x] = pixel[3];
	    }
	  
	  sgiPutRow (output, img, rows[0], y, 0);
	  sgiPutRow (output, img, rows[1], y, 1);
	  sgiPutRow (output, img, rows[2], y, 2);
	  sgiPutRow (output, img, rows[3], y, 3);
	}
    }
  else if (img.channels == 3)
    {
      for (int y=0; y < img.height; y++)
	{
	  for (int x=0; x < img.width; x++, pixel += 4)
	    {
	      rows[0][x] = pixel[0];
	      rows[1][x] = pixel[1];
	      rows[2][x] = pixel[2];
	    }
	  
	  sgiPutRow (output, img, rows[0], y, 0);
	  sgiPutRow (output, img, rows[1], y, 1);
	  sgiPutRow (output, img, rows[2], y, 2);
	}
    }
  else if (img.channels == 2)
    {
      for (int y=0; y < img.height; y++)
	{
	  for (int x=0; x < img.width; x++, pixel += 4)
	    {
	      rows[0][x] = pixel[0];
	      rows[1][x] = pixel[1];
	    }
	  
	  sgiPutRow (output, img, rows[0], y, 0);
	  sgiPutRow (output, img, rows[1], y, 1);
	}
    }
  else if (img.channels == 1)
    {
      for (int y=0; y < img.height; y++)
	{
	  for (int x=0; x < img.width; x++, pixel += 4)
	    {
	      rows[0][x] = pixel[0];
	    }
	  
	  sgiPutRow (output, img, rows[0], y, 0);
	}
    }

  if (img.compression != NONE)
    {
      output.seek (512);

      // Write the offset table.
      LoToHi (img.table[0], img.channels * img.height);
      output.write ((char*)img.table[0], img.height * img.channels * 4);

      // Write the length table.
      LoToHi (img.length[0], img.channels * img.height);
      output.write ((char*)img.length[0], img.height * img.channels * 4);

    }

  output.close ();

  if (compression == fSGI::ARLE)
    delete [] img.arleRow;

  if (compression)
    {
      delete [] img.table[0];
      delete [] img.table;
      delete [] img.length[0];
      delete [] img.length;
    }

  delete [] rows[0];
  delete [] rows;
  delete [] blank;
}

bool fSGI::isSGI (char *filename)
{
  fFile input;
  input.open (filename, "r");

  short magic;
  input.getHi (magic);

  input.close ();

  if (magic != MAGIC)
    return false;

  return true;
}
