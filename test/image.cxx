#include <Flek/fImage.h>
#include <Flek/fPNM.h>
#include <Flek/fSGI.h>
#include <stdio.h>

#define TEST

void main ()
{
  fImage *imgA, *imgB; 

  imgA = fPNM::read ("./test1.ppm");
  imgB = fSGI::read ("./test2.rgb");
  printf ("Testing layer operations..\n");
  //normal (imgA, imgB, 0, 0, 0.5);
  //add    (imgA, imgB, 0, 0, 0.5);
  //subtract    (imgA, imgB, 0, 0, 0.5);
  //difference    (imgA, imgB, 0, 0, 0.5);
  //lightenOnly    (imgA, imgB, 0, 0, 0.5);
  //darkenOnly    (imgA, imgB, 0, 0, 0.5);
  //multiply    (imgA, imgB, 0, 0, 0.5);
  //divide    (imgA, imgB, 0, 0, 0.5);
  //screen    (imgA, imgB, 0, 0, 0.5);
  overlay   (imgA, imgB, 0, 0, 1.0);

  fSGI::write ("out.sgi", imgA, fSGI::RLE, 3);
   
  delete imgA;
  delete imgB;  
}
