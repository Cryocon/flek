#include <FL/Fl.H>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <Flek/Fl_Calendar.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Pixmap.H>

static void fl_calendar_button_cb (Fl_Button *a, void *b)
{
  long j=0;
  Fl_Calendar *c = (Fl_Calendar *)b;
  Fl_Button   *sb;
  int numdays = c->days_in_month () + 1;
  for (int i=1; i < numdays; i++) {
    sb = c->day_button(i);
    sb->color (52);
    if (a == sb) {
	    c->day (i);
	    j = i;
      sb->color (sb->selection_color());
    }
  }
  c->redraw();
  c->do_callback(c, j);
}

Fl_Calendar_Base::Fl_Calendar_Base (int x, int y, int w, int h, 
				    const char *l) : Fl_Group (x, y, w, h, l), FDate () 
{
  int i;  
  
  for (i = 0; i<(7*6); i++) {
    days[i] = new Fl_Button ((w/7)*(i%7) + x,
			     (h/6)*(i/7) + y,
			     (w/7),
			     (h/6));
#ifndef FLTK_2
    days[i]->down_box (FL_THIN_DOWN_BOX);
    days[i]->labelsize (10);
#else
    days[i]->label_size (10);
#endif
    days[i]->box (FL_THIN_UP_BOX);
    days[i]->color (52);
//      days[i]->type (FL_RADIO_BUTTON);
    days[i]->callback ((Fl_Callback*)&fl_calendar_button_cb, (void *)this);
  }
}

void Fl_Calendar_Base::csize (int cx, int cy, int cw, int ch)
{
  int i;
  for (i = 0; i<(7*6); i++) {
    days[i]->resize ((cw/7)*(i%7) + cx,
		     (ch/6)*(i/7) + cy,
		     (cw/7),
		     (ch/6));
  }
}


void
Fl_Calendar_Base::update ()
{
  int dow = day_of_week (year (), month (), 1);
  int dim = days_in_month (month (), leap_year (year ()));
  int i;

  for (i=0; i<dow; i++) {
    days[i]->hide ();
  }

  for (i=(dim+dow); i<(6*7); i++) {
    days[i]->hide ();
  }
  
  for (i=dow; i<(dim+dow); i++) {
    char t[8];
    sprintf (t, "%d", (i-dow+1));
    days[i]->label (strdup(t));
    days[i]->color (52);
    if ((i-dow+1) == day ())
      //	      days[i]->setonly ();
      days[i]->color (selection_color());
    days[i]->show ();
  }
}

Fl_Button *
Fl_Calendar_Base::day_button (int i)
{
  if ((i > 0) && (i <= days_in_month ()))
    return days[i + day_of_week (year (), month (), 1) - 1];
  return 0;
}



static void 
fl_calendar_prv_month_cb (Fl_Button *, void *b) {
  Fl_Calendar *c = (Fl_Calendar *)b;
  c->previous_month ();
  c->do_callback(c, (long)0);
}

static void 
fl_calendar_nxt_month_cb (Fl_Button *, void *b) {
  Fl_Calendar *c = (Fl_Calendar *)b;
  c->next_month ();
  c->do_callback(c, (long)0);
}

static void 
fl_calendar_prv_year_cb (Fl_Button *, void *b) {
  Fl_Calendar *c = (Fl_Calendar *)b;
  c->previous_year ();
  c->do_callback(c, (long)0);
}

static void 
fl_calendar_nxt_year_cb (Fl_Button *, void *b) {
  Fl_Calendar *c = (Fl_Calendar *)b;
  c->next_year ();
  c->do_callback(c, (long)0);
}

Fl_Calendar::Fl_Calendar (int x, int y, int w, int h, 
			  const char *l) : Fl_Calendar_Base (x, y, w, h, l) 
{
  int i;
  for (i = 0; i<7; i++)
    {
      weekdays[i] = new Fl_Button ((w/7)*(i%7) + x,
				   (h/8)*((i/7)+1) + y,
				   (w/7),
				   (h/8));
      weekdays[i]->box (FL_THIN_UP_BOX);  
#ifndef FLTK_2
      weekdays[i]->labelsize (10);
#else
      weekdays[i]->label_size (10);
#endif
      weekdays[i]->color (52);
      
    }
  
  weekdays[SUNDAY]->label ("S");
  weekdays[MONDAY]->label ("M");
  weekdays[TUESDAY]->label ("T");
  weekdays[WEDNESDAY]->label ("W");
  weekdays[THURSDAY]->label ("R");
  weekdays[FRIDAY]->label ("F");
  weekdays[SATURDAY]->label ("S");
  
  prv_year = new Fl_Button (x, y, (w/10), (h/8), "@#<<");
  prv_year->box (FL_THIN_UP_BOX);
#ifndef FLTK_2
  prv_year->labeltype (FL_SYMBOL_LABEL);
  prv_year->labelsize (10);
  prv_year->down_box (FL_THIN_DOWN_BOX);
#else
  prv_year->label_type (FL_SYMBOL_LABEL);
  prv_year->label_size (10);
#endif
  prv_year->callback ((Fl_Callback*)&fl_calendar_prv_year_cb, (void *)this);  

  prv_month = new Fl_Button (x + (w/10), y, (w/10), (h/8), "@#<");
  prv_month->box (FL_THIN_UP_BOX);
#ifndef FLTK_2
  prv_month->labeltype (FL_SYMBOL_LABEL);
  prv_month->labelsize (10);
  prv_month->down_box (FL_THIN_DOWN_BOX);
#else
  prv_month->label_type (FL_SYMBOL_LABEL);
  prv_month->label_size (10);
#endif
  prv_month->callback ((Fl_Callback*)&fl_calendar_prv_month_cb, (void *)this);  

  nxt_month = new Fl_Button (x + (w/10)*8, y, (w/10), (h/8), "@#>");
  nxt_month->box (FL_THIN_UP_BOX);
#ifndef FLTK_2
  nxt_month->labeltype (FL_SYMBOL_LABEL);
  nxt_month->labelsize (10);
  nxt_month->down_box (FL_THIN_DOWN_BOX);
#else
  nxt_month->label_type (FL_SYMBOL_LABEL);
  nxt_month->label_size (10);
#endif
  nxt_month->callback ((Fl_Callback*)&fl_calendar_nxt_month_cb, (void *)this);
  
  nxt_year = new Fl_Button (x + (w/10)*9, y, (w/10), (h/8), "@#>>");
  nxt_year->box (FL_THIN_UP_BOX);
#ifndef FLTK_2
  nxt_year->labeltype (FL_SYMBOL_LABEL);
  nxt_year->labelsize (10);
  nxt_year->down_box (FL_THIN_DOWN_BOX);
#else
  nxt_year->label_type (FL_SYMBOL_LABEL);
  nxt_year->label_size (10);
#endif
  nxt_year->callback ((Fl_Callback*)&fl_calendar_nxt_year_cb, (void *)this);

    caption = new Fl_Button (x + (w/10)*2, y, (w/10)*6, (h/8));
  caption->box (FL_THIN_UP_BOX);
#ifndef FLTK_2
  caption->labeltype (FL_SYMBOL_LABEL);
  caption->labelfont (3);
  caption->labelsize (10);
  caption->down_box (FL_THIN_DOWN_BOX);
#else
  caption->label_type (FL_SYMBOL_LABEL);
  // caption->label_font (3);
  caption->label_size (10);
#endif
      
  Fl_Calendar_Base::csize (x, y + (2*h/8), w, (6*h/8));

  update ();
}

void Fl_Calendar::csize (int cx, int cy, int cw, int ch)
{
  int i;
  for (i = 0; i<7; i++)
    {
      weekdays[i] = new Fl_Button ((cw/7)*(i%7) + cx,
				   (ch/8)*((i/7)+1) + cy,
				   (cw/7),
				   (ch/8));
    }

  prv_month->resize (cx + (cw/10), cy, (cw/10), (ch/8));
  nxt_month->resize (cx + (cw/10)*8, cy, (cw/10), (ch/8));
  prv_year->resize (cx, cy, (cw/10), (ch/8));
  nxt_year->resize (cx + (cw/10)*9, cy, (cw/10), (ch/8));
  caption->resize (cx + (cw/10)*2, cy, (cw/10)*6, (ch/8));
  
  Fl_Calendar_Base::csize (cx, cy + (2*ch/8), cw, (6*ch/8));  
}

void 
Fl_Calendar::update ()
{
  int dow = day_of_week (year (), month (), 1);
  int dim = days_in_month (month (), leap_year (year ()));
  int i;
  
  for (i=dow; i<(dim+dow); i++)
    {
      char t[8];
      sprintf (t, "%d", (i-dow+1));
      days[i]->label (strdup(t));
    }

  char tmp[32];
  sprintf (tmp, "%s %d", month_name[month ()-1], year ());
  Fl_Calendar_Base::update ();
  if (caption->label ())
    free ((void *) caption->label ());
  caption->label (strdup(tmp));
  redraw ();
}

void Fl_Calendar::previous_month ()
{
  FDate::previous_month ();
  update ();
}

void
Fl_Calendar::next_month ()
{
  FDate::next_month ();
  update ();
}

void
Fl_Calendar::previous_year ()
{
  FDate::previous_year ();
  update ();
}

void Fl_Calendar::next_year ()
{
  FDate::next_year ();
  update ();
}

int 
Fl_Calendar::handle (int event) 
{ 
  int m, d, y, o=0, md; 
  
  switch (event) 
    { 
    case FL_FOCUS: 
    case FL_UNFOCUS: 
      return 1; 
      
    case FL_KEYBOARD: 
      m = month (); 
      d = day (); 
      y = year (); 
      switch(Fl::event_key ()) 
	{ 
  case FL_Enter:
    do_callback(this, d);
    break;
	case FL_Up: 
	  o = -7; 
	  break; 
	case FL_Down: 
	  o = 7; 
	  break; 
	case FL_Right: 
	  o = 1; 
	  break; 
	case FL_Left: 
	  o = -1; 
	  break; 
	case FL_Page_Up:
	  previous_month (); 
	  return 1; 
	case FL_Page_Down: 
	  next_month (); 
	  return 1; 
	default: 
	  return Fl_Group::handle (event); 
	} 
      if (valid (y, m, d + o))
	set_date (y, m, d + o); 
      else  { 
	if (o < 0) { 
	  previous_month (); 
	  m = month (); 
	  y = year (); 
	  md = days_in_month (m, leap_year (y)); 
	  d = d + o + md; 
	  set_date (y, m, d);
	} 
	else { 
	  md = days_in_month (m, leap_year (y)); 
	  next_month (); 
	  m = month (); 
	  y = year (); 
	  d = d + o - md;
	  set_date (y, m, d); 
	} 
      } 
      update ();
      return 1;
    }
  return Fl_Group::handle (event);
}


// The following can be static since the popup calendar behaves
// as a modal dialog

struct datestruct { int flag; int m; int d; int y; char szDte[20]; };

static  datestruct seldate;
static  Fl_Window *popcal_form;
static  Fl_Calendar *popcal;

static void popcal_cb (Fl_Calendar *c, long d)
{
  if (d) {
    seldate.flag = 1;
    seldate.m = c->month ();
    seldate.d = c->day ();
    seldate.y = c->year ();
  } 
}

static void makepopcal() {
  if (popcal_form) return;
  Fl_Window *w = popcal_form = new Fl_Window(7*20+4,8*20+4);
  w->clear_border();
  w->box(FL_UP_BOX);
  (popcal = new Fl_Calendar(2, 2));
  popcal->callback ( (Fl_Callback*)popcal_cb);
  w->end();
  w->set_modal();
  return;
}

static datestruct * fl_popcal(int popcalfmt)
{
  makepopcal();
  seldate.flag = -1;
  popcal_form->show();
  for (;;) {
    Fl::wait();
    if (seldate.flag > -1)
      break;
  }
  popcal_form->hide();
  if (seldate.flag == 1 )
    strcpy (seldate.szDte, popcal->to_string (popcalfmt));
  else
    seldate.szDte[0] = 0; 
  return &seldate;
}

#include "pixmaps/calendar.xpm"

void Fl_Date_Input::btnDate_Input_cb_i ()
{
  datestruct *retdate = fl_popcal(popcalfmt);
  if (retdate->flag == 1)
    Input.value (retdate->szDte);
  return;
}

// button callback has to execute the real callback contained in
// the parent Group widget

void btnDate_Input_cb (Fl_Widget *v, void *d)
{
  ((Fl_Date_Input *)(v->parent()))->btnDate_Input_cb_i ();
  return;
}


Fl_Date_Input::Fl_Date_Input (int X,int Y,int W,int H, char *L)
 : Fl_Group (X, Y, W, H, L),
   Input (X, Y, W - H, H),
   Btn (X + W - H + 1, Y + 1, H - 2, H - 2)
{
  xpos = X; 
  ypos = Y; 
  width = W; 
  height = H;

  (new Fl_Pixmap (calendar_xpm))->label (&Btn);
  Btn.callback ((Fl_Callback *)btnDate_Input_cb, 0);
  popcalfmt = 0;
  end();
}

// Date_Input value is contained in the Input widget

void Fl_Date_Input::value( const char *s )
{
  Input.value (s);
}

const char *Fl_Date_Input::value()
{
  return (Input.value ());
}

#ifndef FLTK_2
void Fl_Date_Input::text_font (int tf) { Input.textfont (tf); }
#else
void Fl_Date_Input::text_font (Fl_Font tf) { Input.text_font (tf); }
#endif

#ifndef FLTK_2
void Fl_Date_Input::text_size(int sz) { Input.textsize (sz); }
#else
void Fl_Date_Input::text_size(int sz) { Input.text_size (sz); }
#endif

void Fl_Date_Input::format (int fmt)
{
  switch (fmt) {
    case 0: 
    case 1: 
    case 2:
    case 3:
    case 4: 
      popcalfmt = fmt; 
      break;
    default : 
      popcalfmt = 0;
  }
}
