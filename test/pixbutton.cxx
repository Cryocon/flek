//  name	- pixbutton.C
//  programmer	- Curtis Edwards
//  Incept	- 6/98
//  Description	- This is to demonstate the use of the Fl_Pix_Box and Fl_Pix_Button
//               class's needs the bitmaps for background and the buttons

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Window.H>
#include <stdio.h>
#include <stdlib.h>

#include <Flek/Fl_Pix_Button.H>
#include <Flek/Fl_Pix_Box.H>

#include "bitmaps.cxx"

//testing callbacks
void cb1(Fl_Widget *, void *v) 
{
}

//testing callbacks
void cb2(Fl_Widget *, void *v) 
{

}

//testing callback exit
void cb_exit(Fl_Widget *, void *v) 
{
 	exit(0);
}

int main(int argc, char **argv) 
{
 Fl_Window *w;
 {Fl_Window* o = new Fl_Window(373, 198, "Pix_Buttton/Pix_Box Example");
  w = o;
 {Fl_Pix_Box* o = new Fl_Pix_Box(10, 10, 350, 140, "", &pixmap_vgabg);
  o->box(FL_DOWN_FRAME);
 }
 {Fl_Return_Button* o = new Fl_Return_Button(10, 160, 350, 28, "Exit");
  o->color(49);
  o->labelfont(1);
  o->callback(cb_exit,o);
  }
 {Fl_Pix_Button* o = new Fl_Pix_Button(120, 40, 130, 30, "BUTTON1" ,&pixmap_rustNormal,&pixmap_rustDown,&pixmap_rustHilight);
  o->color(51);
  o->labelfont(4);
  o->labelcolor(131);
  o->callback(cb2,o);
  }
 {Fl_Pix_Button* o = new Fl_Pix_Button(120, 90, 130, 30, "BUTTON2" ,&pixmap_rustNormal,&pixmap_rustDown,&pixmap_rustHilight);
  o->color(51);
  o->labelfont(4);
  o->labelcolor(131);
  o->callback(cb2,o);
 }
 w->end();
 }
 Fl::visual(FL_RGB);
 w->show(argc,argv);
 return Fl::run();
}
