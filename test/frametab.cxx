//  name	- Fl_ITest.C
//  programmer	- C Edwards
//  Incept	- 5/98
//  Description	-  This is to demonstate the use of the Fl_Dialog class and "C" calls

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Dial.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Pack.H>

#include <Flek/Fl_Frametab.H>

#include <stdio.h>
#include <stdlib.h>

int toggle_type =1;

//testing callback exit
void cb_exit(Fl_Widget *, void *v) 
{
 	exit(0);
}
void cb_redraw(Fl_Widget *, void *v) 
{
 Fl_Scroll* sco = ( Fl_Scroll*) v;
 sco->redraw(); 
}

//clear and remove all chrildren
void cb_clear(Fl_Widget *, void *v) 
{
  Fl_Pack* pko = (Fl_Pack*) v;
  
  printf("has children() %d\n", pko->children());
  pko->clear();
  pko->redraw();
  printf("after children() %d\n", pko->children());

}
//will loose pointer info, but its just a test
void cb_add(Fl_Widget *, void *v) 
{
  Fl_Pack* pko = (Fl_Pack*) v;
  pko->begin();
    Fl_Frametab* fto = new Fl_Frametab(0, 40, 240, 130, "Infomation #1");
	if(toggle_type == 1) toggle_type = 0;
	else {
             toggle_type =1;
             fto->labelsize(9);
	}
        fto->type(toggle_type);
      {Fl_Button* o = new Fl_Button (20, 130, 200, 30, "testButton");}
      {Fl_Input* o = new Fl_Input (120, 60, 100, 30, "input: 1"); }
      {Fl_Input* o = new Fl_Input (120, 95, 100, 30, "input: 2"); } 
      fto->end(); 
      fto->close();  
  pko->end();
  //pko->redraw();

}

int main(int argc, char **argv) 
{
 Fl_Window *w;
 {Fl_Window* o = new Fl_Window(240, 610);
  w = o;
 
 {Fl_Box* o = new Fl_Box(0, 535, 240, 75);
  o->box(FL_THIN_DOWN_BOX);
  o->color(48);
  o->color2(53);
  o->labelfont(1);
 }
 {Fl_Box* o = new Fl_Box(0, 0, 240, 40, "Tab Frame Demo");
  o->box(FL_THIN_DOWN_BOX);
  o->color(48);
  o->color2(53);
  o->labelfont(1);
 }
  Fl_Scroll* sco = new Fl_Scroll(0, 40, 240, 510);
  sco->type(Fl_Scroll::VERTICAL);
  sco->box(FL_THIN_DOWN_BOX);
 
  Fl_Pack* pko = new Fl_Pack(1, 41, 238, 528);
  pko->type(Fl_Pack::VERTICAL);
 
  cb_add(pko, pko);   //also in CALLBACK

   pko->end(); //pack
   sco->end(); //scroll
  Fl_Group::current()->resizable(sco);

 Fl_Button* addo = new Fl_Button(20, 555, 90, 20, "Add");
  addo->callback(cb_add,pko);

 Fl_Button* reo = new Fl_Button(130, 555, 90, 20, "Redraw");
  reo->callback(cb_redraw,sco);
 
 Fl_Button* clearo = new Fl_Button(130, 580, 90, 20, "Clear All");
  clearo->callback(cb_clear,pko);

 {Fl_Button* o = new Fl_Button(20, 580, 90, 20, "Exit");
  o->callback(cb_exit,o);
 }

 w->end();
 }
 w->show(argc,argv);
 return Fl::run();
 
}
