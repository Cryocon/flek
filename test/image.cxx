#include <Flek/fImage.h>
#include <Flek/fPNM.h>
#include <stdio.h>

#define TEST

void main ()
{
  fImageRGBA *imgA, *imgB; 
//  uchar *pixel;

  imgA = fPNM::readRGBA ("test1.ppm");
  imgB = fPNM::readRGBA ("test2.ppm");

  int test = 0;

  //fImageRGBA::iterator begin = img->begin ();
  //fImageRGBA::iterator end = img->end ();
  //fImageRGBA::iterator i;

  /* Lets invert the image.
  for (i = begin; i != end; i++)
    {
      pixel = *i;
      pixel[0] = 255 - pixel[0]; // RED
      pixel[1] = 255 - pixel[1]; // GREEN
      pixel[2] = 255 - pixel[2]; // BLUE
      // pixel[3]; ALPHA
      test++;
    }
*/

  fImageRGBA *result = add (imgA, imgB);   
  fPNM::writeRGBA ("out_add.ppm", result);
  delete result;
  
  result = subtract (imgA, imgB);   
  fPNM::writeRGBA ("out_subtract.ppm", result);
  delete result;
  
  result = difference (imgA, imgB);
  fPNM::writeRGBA ("out_difference.ppm", result);
  delete result;
  
  result = lightenOnly (imgA, imgB);
  fPNM::writeRGBA ("out_lightenOnly.ppm", result);
  delete result;
  
  result = darkenOnly (imgA, imgB);
  fPNM::writeRGBA ("out_darkenOnly.ppm", result);
  delete result;

  /*
  result = divide (imgA, imgB);
  fPNM::writeRGBA ("out_divide.ppm", result);
  delete result;

  result = multiply (imgA, imgB);
  fPNM::writeRGBA ("out_multiply.ppm", result);
  delete result;
  */
  delete imgA;
  delete imgB;
  
}
