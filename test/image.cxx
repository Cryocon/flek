#include <Flek/fImage.h>
#include <Flek/fPNM.h>
#include <Flek/fSGI.h>
#include <stdio.h>

#define TEST

void main ()
{
  fImage *imgA, *imgB; 

  imgA = fPNM::read ("~/vfs/www.tiger-marmalade.com/test.ppm");
  imgB = fSGI::read ("./test.rgb");

  // add (imgA, imgB, 0, 0, 1.0);   
  // subtract (imgA, imgB, 0, 0, 1.0);   
  difference (imgA, imgB, 0, 0, 1.0);   

  
  fSGI::write ("out.sgi", imgA, fSGI::RLE, 3);

  delete imgA;
  delete imgB;

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

  //fImage *result;
  
  //result = add (imgA, imgB, 500, 250, .10);   
  //fPNM::write ("out_add.ppm", imgA);
  //delete result;

  /*
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
*/
  /*
  result = divide (imgA, imgB);
  fPNM::writeRGBA ("out_divide.ppm", result);
  delete result;

  result = multiply (imgA, imgB);
  fPNM::writeRGBA ("out_multiply.ppm", result);
  delete result;
  */
  //delete imgA;
  //delete imgB;
  
}
