#include <Flek/FImage.H>
#include <Flek/FPNM.H>
#include <Flek/FSGI.H>
#include <Flek/FJPEG.H>
#include <stdio.h>

#define TEST

void main ()
{
  FImage *imgA, *imgB; 

  //imgA = FPNM::read ("./test1.ppm");
  //imgB = FSGI::read ("./test.rgb");
  imgB = FJPEG::read ("./test.jpg");
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
  //overlay   (imgA, imgB, 0, 0, 1.0);

  imgA = imgB->scale (100, 100);
  imgA->channels (3);
  //imgA->channels (4);
  //FSGI::write ("image_scale.rgb", imgA, FSGI::RLE, 3);
  FJPEG::write ("image_scale.jpg", imgA, 90);
  delete imgA;
  delete imgB;  
}
