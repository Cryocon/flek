/* Fl_Frametab for WidgetSet, Copyright (c) 1998 curtis Edwards (curt1@jps.net)
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appear in all copies and that both the
 * copyright notice and this permission notice appear in supporting
 * documentation.  All work developed as a consequence of the use of
 * this program should duly acknowledge such use. No representations are
 * made about the suitability of this software for any purpose.  It is
 * provided "as is" without express or implied warranty.
   Description	- subclass of Fl_Button that draws pixmaps with lables
                  each pixmap will draw UP/DOWN/HILIGHT 
*/
#include <FL/fl_draw.H>
#include <FL/Fl_Frametab.H>
#include <FL/Fl_Pixmap.H>
//bitmaps for V2-Curtis99
static unsigned char *image_HozUp[] = {
(unsigned char *)"36 8 -5 1",
(unsigned char *)" \306qs\"\316\313\316#10c$ce\316%\377\377\377",
(unsigned char *)"%%%%%%%%%%%%%%%%%%%%%%%%%%%%#       ",
(unsigned char *)"%\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"#      ",
(unsigned char *)"%\"\"#\"\"\"\"\"\"\"\"%\"\"%\"\"%\"\"%\"\"%\"\"%\"\"#     ",
(unsigned char *)"%\"\"##\"\"\"\"\"\"\"\"#\"\"#\"\"#\"\"#\"\"#\"\"\"\"\"#    ",
(unsigned char *)"%\"\"#$#\"\"\"%\"\"%\"\"%\"\"%\"\"%\"\"%\"\"\"\"\"\"\"#   ",
(unsigned char *)"%\"\"#$%\"\"\"\"#\"\"#\"\"#\"\"#\"\"#\"\"#\"\"\"\"\"\"\"#  ",
(unsigned char *)"%\"\"#%\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"# ",
(unsigned char *)"%###################################"
};
static Fl_Pixmap pixmap_HozUp(image_HozUp);

static unsigned char *image_HozHilight[] = {
(unsigned char *)"36 8 -5 1",
(unsigned char *)" \306qs\"10c#uw\356$\316\317\377%\377\377\377",
(unsigned char *)"%%%%%%%%%%%%%%%%%%%%%%%%%%%%\"       ",
(unsigned char *)"%$$$$$$$$$$$$$$$$$$$$$$$$$$$$\"      ",
(unsigned char *)"%$$\"$$$$$$$$%$$%$$%$$%$$%$$%$$\"     ",
(unsigned char *)"%$$\"\"$$$$$$$$\"$$\"$$\"$$\"$$\"$$$$$\"    ",
(unsigned char *)"%$$\"#\"$$$%$$%$$%$$%$$%$$%$$$$$$$\"   ",
(unsigned char *)"%$$\"#%$$$$\"$$\"$$\"$$\"$$\"$$\"$$$$$$$\"  ",
(unsigned char *)"%$$\"%$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\" ",
(unsigned char *)"%\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\""
};
static Fl_Pixmap pixmap_HozHilight(image_HozHilight);

static unsigned char *image_VertUp[] = {
(unsigned char *)"8 36 -7 1",
(unsigned char *)" \306qs\"\316\313\316#10c$FE|%\354\354\377&ce\316\'\377\377\377",
(unsigned char *)"\'\'\'\'\'\'\'%",
(unsigned char *)"\'\"\"\"\"\"\"#",
(unsigned char *)"\'\"\"\"\"\"\"#",
(unsigned char *)"\'#####\"#",
(unsigned char *)"\'\'&&#\"\"#",
(unsigned char *)"\'\"\'#\"\"\"#",
(unsigned char *)"\'\"\"\"\"\"\"#",
(unsigned char *)"\'\"\"\"\"\"\"#",
(unsigned char *)"\'\"\"\"\"\"\"#",
(unsigned char *)"\'\"\"\'\"\"\"#",
(unsigned char *)"\'\"#\"\"\"\"#",
(unsigned char *)"\'\"\"\"\"\"\"#",
(unsigned char *)"\'\"\"\'\"\'\"#",
(unsigned char *)"\'\"#\"#\"\"#",
(unsigned char *)"\'\"\"\"\"\"\"#",
(unsigned char *)"\'\"\"\'\"\'\"#",
(unsigned char *)"\'\"#\"#\"\"#",
(unsigned char *)"\'\"\"\"\"\"\"#",
(unsigned char *)"\'\"\"\'\"\'\"#",
(unsigned char *)"\'\"#\"#\"\"#",
(unsigned char *)"\'\"\"\"\"\"\"#",
(unsigned char *)"\'\"\"\'\"\'\"#",
(unsigned char *)"\'\"#\"#\"\"#",
(unsigned char *)"\'\"\"\"\"\"\"#",
(unsigned char *)"\'\"\"\'\"\'\"#",
(unsigned char *)"\'\"#\"#\"\"#",
(unsigned char *)"\'\"\"\"\"\"\"#",
(unsigned char *)"\'\"\"\"\"\'\"#",
(unsigned char *)"\'\"\"\"\"\"\"#",
(unsigned char *)"\'\"\"\"\"\"# ",
(unsigned char *)"\'\"\"\"\"#  ",
(unsigned char *)"\'\"\"\"#   ",
(unsigned char *)"\'\"\"#    ",
(unsigned char *)"\'\"#     ",
(unsigned char *)"\'#      ",
(unsigned char *)"$       "
};
static Fl_Pixmap pixmap_VertUp(image_VertUp);

static unsigned char *image_VertHilight[] = {
(unsigned char *)"8 36 -7 1",
(unsigned char *)" \306qs\"10c#FE|$\354\354\377%uw\356&\316\317\377\'\377\377\377",
(unsigned char *)"\'\'\'\'\'\'\'$",
(unsigned char *)"\'&&&&&&\"",
(unsigned char *)"\'&&&&&&\"",
(unsigned char *)"\'\"\"\"\"\"&\"",
(unsigned char *)"\'\'%%\"&&\"",
(unsigned char *)"\'&\'\"&&&\"",
(unsigned char *)"\'&&&&&&\"",
(unsigned char *)"\'&&&&&&\"",
(unsigned char *)"\'&&&&&&\"",
(unsigned char *)"\'&&\'&&&\"",
(unsigned char *)"\'&\"&&&&\"",
(unsigned char *)"\'&&&&&&\"",
(unsigned char *)"\'&&\'&\'&\"",
(unsigned char *)"\'&\"&\"&&\"",
(unsigned char *)"\'&&&&&&\"",
(unsigned char *)"\'&&\'&\'&\"",
(unsigned char *)"\'&\"&\"&&\"",
(unsigned char *)"\'&&&&&&\"",
(unsigned char *)"\'&&\'&\'&\"",
(unsigned char *)"\'&\"&\"&&\"",
(unsigned char *)"\'&&&&&&\"",
(unsigned char *)"\'&&\'&\'&\"",
(unsigned char *)"\'&\"&\"&&\"",
(unsigned char *)"\'&&&&&&\"",
(unsigned char *)"\'&&\'&\'&\"",
(unsigned char *)"\'&\"&\"&&\"",
(unsigned char *)"\'&&&&&&\"",
(unsigned char *)"\'&&&&\'&\"",
(unsigned char *)"\'&&&&&&\"",
(unsigned char *)"\'&&&&&\" ",
(unsigned char *)"\'&&&&\"  ",
(unsigned char *)"\'&&&\"   ",
(unsigned char *)"\'&&\"    ",
(unsigned char *)"\'&\"     ",
(unsigned char *)"\'\"      ",
(unsigned char *)"#       "
};
static Fl_Pixmap pixmap_VertHilight(image_VertHilight);

////constructor
Fl_Frametab::Fl_Frametab(int x,int y,int w, int h, char *fname)
: Fl_Group(x, y, w, h<MINFRAMEHEIGHT ? MINFRAMEHEIGHT : h,fname)
{
  box(FL_ENGRAVED_BOX);
  align(20);
  selection_color(FL_LIGHT2);
  hilight_color(FL_WHITE);
  openLabelHide(1);        //set to hide on open
  _isopen  = 1;            //TRUE/FALSE
  _hilight = 0;            //TRUE/FLASE
  type(0);
  openSize(h<MINFRAMEHEIGHT ? MINFRAMEHEIGHT : h);
}

////draw the button
void Fl_Frametab::draw()
{
  int Hsize =  type() ? MINFRAMEPIXHEIGHT : MINFRAMEHEIGHT;
  int Isize =  type() ? MINFRAMEPIXINDENT  : MINFRAMEINDENT;
  int midX=16+x(), midY=y()+(Hsize/2)+Fl::box_dh(box())-1;
 
 if(_isopen) 
 {
 
	 Fl_Widget*const* a = array();
   if (damage() & ~FL_DAMAGE_CHILD) // redraw the entire thing:
   { 
       draw_box();
       for (int i=children(); i--;) 
	   {
           Fl_Widget& o = **a++;
           draw_child(o);
           draw_outside_label(o);
	   }
   } 
   else 
   {  for (int i=children(); i--;) update_child(**a++); }// only redraw the children that need it:
 } else draw_box();

 if(type())  //bitmap Netscape style - Curtis99
 {
    if(_isopen) {
    if(_hilight) pixmap_VertHilight.draw(x()+ Fl::box_dx(box()),y()+ Fl::box_dy(box())); 
    else pixmap_VertUp.draw(x()+ Fl::box_dx(box()),y()+ Fl::box_dy(box())); 
  
 } 
 else{
    if(_hilight) pixmap_HozHilight.draw(x()+ Fl::box_dx(box()),y()+ Fl::box_dy(box())); 
    else pixmap_HozUp.draw(x()+ Fl::box_dx(box()),y()+ Fl::box_dy(box())); 
 }
}else {
  if(_isopen) 
  {
     if(_hilight) fl_color(hilight_color());
     else fl_color(selection_color());
     fl_polygon(midX+5, midY-2, midX, midY+3, midX-5, midY-2); 
     fl_color(FL_BLACK);
     fl_loop(midX+5, midY-2, midX, midY+3, midX-5, midY-2); 
  }
  else
  {
    if(_hilight) fl_color(hilight_color());
    else fl_color(selection_color());
    fl_polygon(midX-2, midY-5, midX+3, midY, midX-2, midY+5); 
    fl_color(FL_BLACK);
    fl_loop(midX-2, midY-5, midX+3, midY, midX-2, midY+5); 
  }
}
 if(openLabelHide() && _isopen) return;
 draw_label(midX+Isize,y(),w()-Isize,Hsize, FL_ALIGN_LEFT);
}

////handel the events
int Fl_Frametab::handle(int event)
{
   int Hsize,Wsize;
   if(type()) { 
        if(_isopen) { Wsize = MINFRAMEPIXHEIGHT; Hsize=MINFRAMEPIXWIDTH; }
        else { Wsize = MINFRAMEPIXWIDTH; Hsize=MINFRAMEPIXHEIGHT; }
   }
   else {
        if(_isopen) { Wsize = MINFRAMEHEIGHT; Hsize = MINFRAMEHEIGHT; }
        else { Wsize = w(); Hsize=MINFRAMEHEIGHT; }
   }
   switch (event)  {
           case FL_ENTER:
                _hilight = 1;
                damage(~1,x(), y(), Wsize+Fl::box_dw(box()), Hsize+Fl::box_dh(box()));
		return 1;
	   case FL_LEAVE:
               _hilight = 0;
               damage(~1,x(), y(), Wsize+Fl::box_dw(box()), Hsize+Fl::box_dh(box()));
               return 1;
	   case FL_PUSH:
               if (Fl::event_inside(x(), y(), Wsize+Fl::box_dw(box()), Hsize+Fl::box_dh(box())))
               {
                  if(_isopen) close();
                  else open();
                  return 1;
               }
               break;
         }
  if(_isopen) return Fl_Group::handle(event);
  else return 1;
}

//// close the frame 
void Fl_Frametab::close()
{
   int Hsize =  (type() ? MINFRAMEPIXHEIGHT : MINFRAMEHEIGHT) + Fl::box_dh(box());
   _isopen=0;
    if(parent()->parent()) parent()->damage(~1,x(),y(),w(),parent()->parent()->h());   //kludge to force redraw
   else parent()->damage(~1,x(),y(),w(),parent()->h());
   size(w(),Hsize);
   do_callback();
}

//// close the frame 
void Fl_Frametab::open()
{
    _isopen=1;
   size(w(),openSize());
   if(parent()->parent()) parent()->damage(~1,x(),y(),w(),parent()->parent()->h());   //kludge to force redraw
   else parent()->damage(~1,x(),y(),w(),parent()->h());
   do_callback();
}
