#include <Flek/fImage.h>
#include <Flek/fPNM.h>
#include <stdio.h>

#define TEST

void main ()
{
  fImageRGBA *img; 
  uchar *pixel;

  img = fPNM::readRGBA ("test.ppm");

  int test = 0;

  fImageRGBA::iterator begin = img->begin ();
  fImageRGBA::iterator end = img->end ();
  fImageRGBA::iterator i;

  // Lets invert the image.
  for (i = begin; i != end; i++)
    {
      pixel = *i;
      pixel[0] = 255 - pixel[0]; // RED
      pixel[1] = 255 - pixel[1]; // GREEN
      pixel[2] = 255 - pixel[2]; // BLUE
      // pixel[3]; ALPHA
      test++;
    }


  fPNM::writeRGBA ("output.ppm", img);

  printf ("total pixels processed = %d\n", test);
}
