/* Fl_NSlider for WidgetSet, Copyright (c) 1998 curtis Edwards (curt1@jps.net)
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appear in all copies and that both the
 * copyright notice and this permission notice appear in supporting
 * documentation.  All work developed as a consequence of the use of
 * this program should duly acknowledge such use. No representations are
 * made about the suitability of this software for any purpose.  It is
 * provided "as is" without express or implied warranty.

slider features are:
 -compatable with old FL_Slider
 -majorTick (main tick with number display)
 -minorTick (small ticks)
 -ramp (color ramps,RGB)
 -majorTickPrecision (set the precision of major tick print display(font)); 
 -alignTick ( align ticks TOP/CENTER/BOTOM/LEFT/RIGHT);   
 -slider    (set box type for slider); 
 -new type( FL_HOR_HALF_SLIDER guess!)
 -hilight control
 -hilight color
 -tick font
 -tick font size
 -tick color
 -cxx coding style
 -realtime updating
 -new demo (this) showing all styles
 */

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Value_Output.H>
#include <FL/Fl_Window.H>

#include <Flek/Fl_NSlider.H>

Fl_NSlider     *dhoz    = (Fl_NSlider *)0;
Fl_Value_Output *dcurrent= (Fl_Value_Output *)0;
Fl_Value_Input *dstart  = (Fl_Value_Input *)0;
Fl_Value_Input *dend    = (Fl_Value_Input *)0;
Fl_Value_Input *dmajor  = (Fl_Value_Input *)0;
Fl_Value_Input *dminor  = (Fl_Value_Input *)0;
Fl_Value_Input *dincr=(Fl_Value_Input *)0;
Fl_Value_Input *drounding=(Fl_Value_Input *)0;
Fl_NSlider *dvert1=(Fl_NSlider *)0;
Fl_NSlider *dvert2=(Fl_NSlider *)0;
Fl_NSlider *dvert3=(Fl_NSlider *)0;
Fl_NSlider *dvert4=(Fl_NSlider *)0;
Fl_NSlider *dvert5=(Fl_NSlider *)0;
Fl_NSlider *dvert6=(Fl_NSlider *)0;
Fl_Button *dexit=(Fl_Button *)0;

void cb_dcolor(Fl_Choice *o, int v)
{
  dhoz->colorTick((Fl_Color) v); 
  dhoz->redraw(); 
}

Fl_Choice *dcolor=(Fl_Choice *)0;
Fl_Menu_Item menu_dcolor[] = {
 {"FL_BLACK", 0,  (Fl_Callback*)cb_dcolor, (void*)(FL_BLACK), 0, 0, 0, 14, 0},
 {"FL_RED", 0,  (Fl_Callback*)cb_dcolor, (void*)(FL_RED), 0, 0, 0, 14, 0},
 {"FL_BLUE", 0,  (Fl_Callback*)cb_dcolor, (void*)(FL_BLUE), 0, 0, 0, 14, 0},
 {0}
};

void cb_dstyle(Fl_Choice *o, void *v)
{
  dhoz->type((int)v); 
  dhoz->redraw();     
}
Fl_Choice *dstyle=(Fl_Choice *)0;
Fl_Menu_Item menu_dstyle[] = {
 {"FL_HOR_SLIDER", 0,  (Fl_Callback*)cb_dstyle, (void*)(FL_HOR_SLIDER), 0, 0, 0, 14, 0},
 {"FL_HOR_FILL_SLIDER", 0,  (Fl_Callback*)cb_dstyle, (void*)(FL_HOR_FILL_SLIDER), 0, 0, 0, 14, 0},
 {"FL_HOR_NICE_SLIDER", 0,  (Fl_Callback*)cb_dstyle, (void*)(FL_HOR_NICE_SLIDER), 0, 0, 0, 14, 0},
 {"FL_HOR_HALF_SLIDER", 0,  (Fl_Callback*)cb_dstyle, (void*)(FL_HOR_HALF_SLIDER), 0, 0, 0, 14, 0},
 {0}
};

void cb_dtickbox(Fl_Choice *o, int v)
{
  dhoz->slider((Fl_Boxtype)v); 
  dhoz->redraw(); 
}
Fl_Choice *btickbox=(Fl_Choice *)0;
Fl_Menu_Item menu_btickbox[] = {
 {" FL_UP_BOX", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_UP_BOX), 0, 0, 0, 12, 0},
 {" FL_DOWN_BOX", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_DOWN_BOX), 0, 0, 0, 12, 0},
 {" FL_UP_FRAME", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_UP_FRAME  ), 0, 0, 0, 12, 0},    
 {" FL_DOWN_FRAME", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_DOWN_FRAME), 0, 0, 0, 12, 0},
 {" FL_THIN_UP_BOX", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_THIN_UP_BOX ), 0, 0, 0, 12,0},    
 {" FL_THIN_DOWN_BOX", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_THIN_DOWN_BOX), 0, 0, 0, 12, 0},
 {" FL_THIN_UP_FRAME", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_THIN_UP_FRAME ), 0, 0, 0, 12, 0}, 
 {" FL_THIN_DOWN_FRAME", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_THIN_DOWN_FRAME), 0, 0, 0, 12, 0},
 {" FL_ENGRAVED_BOX", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_ENGRAVED_BOX  ), 0, 0, 0, 12, 0},  
 {" FL_EMBOSSED_BOX", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_EMBOSSED_BOX), 0, 0, 0, 12, 0},
 {" FL_ENGRAVED_FRAME", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_ENGRAVED_FRAME ), 0, 0, 0, 12, 0}, 
 {" FL_EMBOSSED_FRAME", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_EMBOSSED_FRAME), 0, 0, 0, 12, 0},
 {" FL_BORDER_BOX", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_BORDER_BOX   ), 0, 0, 0, 12, 0},   
 {" FL_BORDER_FRAME", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_BORDER_FRAME ), 0, 0, 0, 12, 0},  
 {" FL_ROUND_UP_BOX", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_ROUND_UP_BOX), 0, 0, 0, 12, 0},
 {" FL_ROUND_DOWN_BOX", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_ROUND_DOWN_BOX), 0, 0, 0, 12, 0},
 {" FL_SHADOW_BOX", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_SHADOW_BOX), 0, 0, 0, 12, 0},
 {" FL_SHADOW_FRAME", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_SHADOW_FRAME), 0, 0, 0, 12, 0},
 {" FL_ROUNDED_BOX", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_ROUNDED_BOX), 0, 0, 0, 12, 0},
 {" FL_ROUNDED_FRAME", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_ROUNDED_FRAME), 0, 0, 0, 12, 0},
 {" FL_RFLAT_BOX", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_RFLAT_BOX), 0, 0, 0, 12, 0},
 {" FL_RSHADOW_BOX", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_RSHADOW_BOX), 0, 0, 0, 12, 0},
 {" FL_DIAMOND_DOWN_BOX", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_DIAMOND_DOWN_BOX), 0, 0, 0, 12, 0},
 {" FL_DIAMOND_UP_BOX", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_DIAMOND_UP_BOX), 0, 0, 0, 12, 0},
 {" FL_OSHADOW_BOX", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_OSHADOW_BOX), 0, 0, 0, 12, 0},
 {" FL_OVAL_FRAME", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_OVAL_FRAME), 0, 0, 0, 12, 0},
 {" FL_OFLAT_BOX", 0,  (Fl_Callback*)cb_dtickbox, (void*)( FL_OFLAT_BOX), 0, 0, 0, 12, 0},
 {0}
};



void cb_dalign(Fl_Choice *o, int v)
{
  dhoz->alignTick( (Fl_Align) v);   
  dhoz->redraw(); 
}
Fl_Choice *dalign=(Fl_Choice *)0;
Fl_Menu_Item menu_dalign[] = {
 {"FL_ALIGN_TOP", 0,  (Fl_Callback*)cb_dalign, (void*)(FL_ALIGN_TOP), 0, 0, 0, 14, 0},
 {"FL_ALIGN_CENTER", 0,  (Fl_Callback*)cb_dalign, (void*)(FL_ALIGN_CENTER), 0, 0, 0, 14, 0},
 {"FL_ALIGN_BOTTOM", 0,  (Fl_Callback*)cb_dalign, (void*)(FL_ALIGN_BOTTOM), 0, 0, 0, 14, 0},
 {0}
};


void cb_dend(Fl_Value_Input *o, void *v)
{
  dhoz->maximum( o->value());  
  dstart->maximum( o->value()); 
  dcurrent->value( dhoz->value()); 
  if( dhoz->value() > dhoz->maximum())  dhoz->value(dhoz->maximum());
  dcurrent->value( dhoz->value()); 
  dcurrent->redraw();
  dhoz->redraw();
}
void cb_dexit(Fl_Button *o, void *v)
{
 exit(1);   
}
void cb_dhoz(Fl_NSlider *o, void *v)
{
  dcurrent->value( dcurrent->round(o->value()));   
  dcurrent->redraw(); 
    
}
void cb_dincr(Fl_Value_Input *o, void *v)
{
  dhoz->step( o->value());   
  dhoz->redraw(); 
    
}
void cb_dcurrent(Fl_Value_Input *o, void *v)
{
  dhoz->value( o->value());   
  dhoz->redraw(); 
    
}
void cb_dmajor(Fl_Value_Input *o, void *v)
{
  dhoz->majorTick( o->value()); 
  dhoz->redraw(); 
    
}
void cb_dminor(Fl_Value_Input *o, void *v)
{
  dhoz->minorTick( o->value()); 
  dhoz->redraw(); 
    
}
void cb_drounding(Fl_Value_Input *o, void *v)
{
  dhoz->majorTickPrecision( (int) o->value()); 
  dhoz->redraw(); 
    
}
void cb_dstart(Fl_Value_Input *o, void *v)
{
  dhoz->minimum( o->value()); 
  dcurrent->minimum( o->value()); 
  dend->minimum( o->value()); 
  if( dhoz->value() < dhoz->minimum())   dhoz->value(dhoz->minimum());
  dcurrent->value( dhoz->value()); 
  dcurrent->redraw();
  dhoz->redraw(); 
    
}
void cb_1color(Fl_Value_Input *o, void *v)
{
   dvert1->ramp(o->value(),FL_BLACK); 
   dvert1->redraw();
}
void cb_2color(Fl_Value_Input *o, void *v)
{
   dvert2->ramp(o->value(),FL_BLACK); 
   dvert2->redraw();

}
void cb_3color(Fl_Value_Input *o, void *v)
{
   dvert3->ramp(o->value(),FL_BLACK); 
   dvert3->redraw();

}

int main(int argc, char **argv) {
  Fl_Window* w;
  { Fl_Window* o = new Fl_Window(495, 334, "New Slider Demo");
    w = o;
    o->color(48);
    { Fl_Group* o = new Fl_Group(10, 5, 475, 155);
      o->box(FL_DOWN_BOX);
      o->color(51);
      { Fl_NSlider* o = dhoz = new Fl_NSlider(20, 30, 455, 30, "Demo Slider");
        o->type(1);
        o->labelsize(12);
        o->minimum(-100);
        o->maximum(1000);
        o->callback((Fl_Callback*)cb_dhoz);
        o->align(5);
        o->majorTick(10);
        o->minorTick(1);
	o->ramp(47,52);
      }
      { Fl_Value_Output* o = dcurrent = new Fl_Value_Output(20, 75, 50, 25, "Current");
        o->labelsize(12);
        o->callback((Fl_Callback*)cb_dcurrent);
        o->step(1);
        o->minimum(-100);
        o->maximum(1000);
        o->align(5);
      }
      { Fl_Value_Input* o = dstart = new Fl_Value_Input(75, 75, 50, 25, "Start");
        o->labelsize(12);
        o->minimum(-100);
        o->maximum(1000);
        o->callback((Fl_Callback*)cb_dstart);
        o->align(5);
        o->step(1);
        o->value(-100);
      }
      { Fl_Value_Input* o = dend = new Fl_Value_Input(130, 75, 50, 25, "End");
        o->labelsize(12);
        o->minimum(-100);
        o->maximum(1000);
        o->value(1000);
        o->callback((Fl_Callback*)cb_dend);
        o->step(1);
        o->align(5);
      }
      { Fl_Value_Input* o = dmajor = new Fl_Value_Input(365, 75, 50, 25, "Major");
        o->labelsize(12);
        o->minimum(1);
        o->maximum(100);
        o->step(1);
        o->value(100);
        o->callback((Fl_Callback*)cb_dmajor);
        o->align(5);
      }
      { Fl_Value_Input* o = dminor = new Fl_Value_Input(310, 75, 50, 25, "Minor");
        o->labelsize(12);
        o->minimum(1);
        o->maximum(100);
        o->step(1);
        o->value(1);
        o->callback((Fl_Callback*)cb_dminor);
        o->align(5);
      }
      { Fl_Choice* o = dcolor = new Fl_Choice(310, 135, 165, 20, "Tick Color");
        o->labelsize(12);
        o->textfont(1);
        o->textsize(11);
        o->menu(menu_dcolor);
      }
      { Fl_Choice* o = dstyle = new Fl_Choice(85, 135, 160, 20, "Slider Style");
        o->labelsize(12);
        o->textfont(1);
        o->textsize(11);
        o->menu(menu_dstyle);
      }
      { Fl_Choice* o = btickbox = new Fl_Choice(85, 110, 160, 20, "Tick Box");
        o->labelsize(12);
        o->textfont(1);
        o->textsize(11);
        o->menu(menu_btickbox);
      }
      { Fl_Choice* o = dalign = new Fl_Choice(310, 110, 165, 20, "Tick Align");
        o->labelsize(12);
        o->textfont(1);
        o->textsize(11);
        o->menu(menu_dalign);
      }
      { Fl_Box* o = new Fl_Box(160, 10, 180, 20, "Horizontal");
        o->labelfont(1);
        o->labelsize(15);
        o->labelcolor(48);
      }
      { Fl_Value_Input* o = dincr = new Fl_Value_Input(185, 75, 60, 25, "Incr");
        o->labelsize(12);
        o->minimum(1);
        o->maximum(100);
        o->step(1);
        o->value(1);
        o->callback((Fl_Callback*)cb_dincr);
        o->align(5);
      }
      { Fl_Value_Input* o = drounding = new Fl_Value_Input(420, 75, 55, 25, "Precision");
        o->labelsize(12);
        o->maximum(6);
        o->step(1);
        o->callback((Fl_Callback*)cb_drounding);
        o->align(5);
      }
      o->end();
      Fl_Group::current()->resizable(o);
    }
    { Fl_Group* o = new Fl_Group(10, 165, 475, 160);
      o->box(FL_DOWN_BOX);
      o->color(51);
      { Fl_NSlider* o = dvert1 = new Fl_NSlider(FL_VERT_NICE_SLIDER,20, 175, 45, 140);
        o->maximum(1);
        o->minimum(0);
        o->step(.1);
        o->majorTickPrecision(1);
        o->majorTick(.5);
        o->minorTick(.1);
        o->alignTick( FL_ALIGN_LEFT); 
        o->colorTick(FL_WHITE);
        o->ramp(FL_RED,FL_BLACK);
        o->box(FL_DOWN_BOX);
      }
      { Fl_NSlider* o = dvert2 = new Fl_NSlider(FL_VERT_NICE_SLIDER,70, 175, 40, 140);
        o->maximum(1);
        o->minimum(0);
        o->step(.1);
        o->majorTickPrecision(1);
        o->majorTick(.5);
        o->minorTick(.1);
        o->alignTick( FL_ALIGN_LEFT); 
        o->colorTick(FL_WHITE);
        o->ramp(FL_GREEN,FL_BLACK);
        o->box(FL_DOWN_BOX);
      }
      { Fl_NSlider* o = dvert3 = new Fl_NSlider(FL_VERT_NICE_SLIDER,115, 175, 40, 140);
        o->maximum(1);
        o->minimum(0);
        o->step(.1);
        o->majorTickPrecision(1);
        o->majorTick(.5);
        o->minorTick(.1);
        o->alignTick( FL_ALIGN_LEFT); 
        o->colorTick(FL_WHITE);
        o->ramp(FL_BLUE,FL_BLACK);
        o->box(FL_DOWN_BOX);
      }
      { Fl_NSlider* o = dvert4 = new Fl_NSlider(FL_VERT_HALF_SLIDER,350, 175, 40, 140);
        o->minimum(0);
        o->maximum(100);
        o->step(5);
        o->value(0);
        o->majorTick(10);
        o->minorTick(1);
        o->box(FL_NO_BOX);
        o->alignTick( FL_ALIGN_CENTER); 
        o->slider(FL_ROUNDED_BOX); 
      }
      { Fl_NSlider* o = dvert5 = new Fl_NSlider(FL_VERT_HALF_SLIDER,395, 175, 40, 140);
        o->minimum(0);
        o->maximum(100);
        o->step(5);
        o->value(50);
        o->majorTick(10);
        o->minorTick(1);
        o->box(FL_NO_BOX);
        o->alignTick( FL_ALIGN_CENTER); 
        o->slider(FL_ROUNDED_BOX); 
  o->selection_color(12);
  o->hilight_color(FL_BLUE);
     }
      { Fl_NSlider* o = dvert6 = new Fl_NSlider(FL_VERT_HALF_SLIDER,440, 175, 35, 140);
        o->minimum(0);
        o->maximum(100);
        o->step(5);
        o->value(100);
        o->majorTick(10);
        o->minorTick(2);
        o->box(FL_NO_BOX);
        o->alignTick( FL_ALIGN_CENTER); 
        o->slider(FL_ROUNDED_BOX); 
  o->selection_color(10);
  o->hilight_color(FL_GREEN);
      }
      { Fl_Button* o = dexit = new Fl_Button(165, 290, 175, 25, "Exit");
        o->callback((Fl_Callback*)cb_dexit);
      }
      { Fl_Box* o = new Fl_Box(160, 175, 180, 20, "Vertical");
        o->labelfont(1);
        o->labelsize(15);
        o->labelcolor(48);
      }
      { Fl_Value_Input* o = new Fl_Value_Input(240, 200, 75, 20, "#1 Color");
        o->maximum(200);
        o->step(1);
        o->value(1);
        o->callback((Fl_Callback*)cb_1color);
      }
      { Fl_Value_Input* o = new Fl_Value_Input(240, 225, 75, 20, "#2 Color");
        o->labeltype(FL_SYMBOL_LABEL);
        o->maximum(200);
        o->step(1);
        o->value(2);
        o->callback((Fl_Callback*)cb_2color);
      }
      { Fl_Value_Input* o = new Fl_Value_Input(240, 250, 75, 20, "#3 Color");
        o->maximum(200);
        o->step(1);
        o->value(3);
        o->callback((Fl_Callback*)cb_3color);
      }
      o->end();
    }    o->end();
  }
  w->show(argc, argv);
  return Fl::run();
}
