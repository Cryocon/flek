/* Fl_Pix_Button for WidgetSet, Copyright (c) 1998 curtis Edwards (curt1@jps.net)
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
#include <FL/Fl.H>
#include <FL/Fl_Pix_Button.H>
#include <FL/fl_draw.H>
#include <math.h>

////constructor
Fl_Pix_Button::Fl_Pix_Button(int x,int y,int w,int h,const char *l,Fl_Pixmap* bUp,Fl_Pixmap* bDown,Fl_Pixmap* bHilight)
: Fl_Button(x,y,w,h,l) 
{
 bUp_     = bUp;
 bDown_   = bDown;
 bHilight_= bHilight;
 hilight  = 0;
 int maxW=0, maxH=0;
 if(bUp)                       //check size of bitmaps and log biggest sizes
 {   fl_measure_pixmap(bUp->data, bUp->w, bUp->h); 
    if(bUp->w > maxW ) maxW = bUp->w; 
    if(bUp->h > maxH)  maxH = bUp->h;
 }
 if(bDown)
 {   fl_measure_pixmap(bDown->data, bDown->w, bDown->h);
    if(bDown->w > maxW) maxW = bDown->w; 
    if(bDown->h > maxH) maxH = bDown->h;
 }
 if(bHilight) 
 {   fl_measure_pixmap(bHilight->data, bHilight->w, bHilight->h);
     if(bHilight->w > maxW) maxW = bHilight->w; 
     if(bHilight->h > maxH) maxH = bHilight->h;
 }
 Fl_Button::w(maxW);
 Fl_Button::h(maxH);

}

////draw the button
void Fl_Pix_Button::draw()
{
  if (type() == FL_HIDDEN_BUTTON) return;
  switch(value())
  {
      case 0: if(hilight && bHilight_) bHilight_->draw(x(),y(), w(), h());
              else if(bUp_) bUp_->draw(x(),y(), w(), h()); 
              break;
      case 1: if(bDown_) bDown_->draw(x(),y(), w(), h()); 
              break;
      default: if(bUp_) bUp_->draw(x(),y(), w(), h()); 
              break;
  }
  draw_label();
}

////handel the events
int Fl_Pix_Button::handle(int event)
{
    switch (event) 
    {
       case FL_ENTER:
            hilight=1;
            redraw();
            break;
       case FL_LEAVE:
	        hilight=0;
                redraw();
                break;
   }
 return Fl_Button::handle(event);
}
