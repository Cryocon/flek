#include <FL/Fl.H>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <Flek/Fl_Calendar.H>

char * month_name[12] =
{
  "January",
  "Febuary",
  "March",
  "April",
  "May",
  "June",
  "July",
  "August",
  "September",
  "October",
  "November",
  "December"
};

static const int doylookup[2][13] = {
  { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
  { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
};

static void fl_calendar_button_cb (Fl_Button *a, void *b)
{
  long j=0;
  Fl_Calendar *c = (Fl_Calendar *)b;
  for (int i=1; i<32; i++)
    if (a == c->day_button (i))
      {
	c->set_day (i);
	j = i;
      }
  c->do_callback(c, j);
}

Fl_Calendar_Base::Fl_Calendar_Base (int x, int y, int w, int h, 
				    const char *l) : Fl_Group (x, y, w, h, l) 
{
  int i;  
  
  for (i = 0; i<(7*6); i++)
    {
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
      days[i]->type (FL_RADIO_BUTTON);
      days[i]->callback ((Fl_Callback*)&fl_calendar_button_cb, (void *)this);
    }
  
  set_date (1999, DECEMBER, 10);
}

void
Fl_Calendar_Base::csize (int cx, int cy, int cw, int ch)
{
  int i;
  for (i = 0; i<(7*6); i++)
    {
      days[i]->resize ((cw/7)*(i%7) + cx,
		     (ch/6)*(i/7) + cy,
		     (cw/7),
		     (ch/6));
    }
}

short 
Fl_Calendar_Base::set_date (int y, int m, int d)
{
  if (datevalid (y, m, d))
    {
      year = y;
      month = m;
      mday = d;
      update ();
      return 0;
    }
  return 1;
}

short 
Fl_Calendar_Base::set_month (int m) 
{ 
  if (datevalid (year, m, mday)) 
    {
      month = m;
      return 0;
    }
  return 1;
}

short 
Fl_Calendar_Base::set_year (int y) 
{ 
  if (datevalid (y, month, mday)) 
    {
      year = y; 
      return 0;
    }
  return 1;
}

short 
Fl_Calendar_Base::set_day (int d) 
{ 
  if (datevalid (year, month, d)) 
    {
      mday = d; 
      return 0;
    }
  return 1;
}

short
Fl_Calendar_Base::isleapyear (int year)
{
  /* Leap year every 4th year, except every 100th year,
   * not including every 400th year.
   */
  return !(year % 4) && ((year % 100) || !(year % 400));
}

int
Fl_Calendar_Base::daysinmonth (int month, short leap)
{
  /* Validate the month. */
  if (month < JANUARY || month > DECEMBER)
    return -1;
  
  /* Return 28, 29, 30, or 31 based on month/leap. */
  switch (month) {
  case FEBRUARY:
    return leap ? 29 : 28;
  case APRIL:
  case JUNE:
  case SEPTEMBER:
  case NOVEMBER:
    return 30;
  default:
    return 31;
  }
}

short
Fl_Calendar_Base::datevalid (int year, int mon, int mday)
{
  /* Years may be between YEAR_MIN-YEAR_MAX; months JANUARY-DECEMBER,
   * and days must be validated based on year and month.
   */
  if (year < YEAR_MIN || year > YEAR_MAX)
    return false;
  if (mon < JANUARY || mon > DECEMBER)
    return false;
  if (mday < 1 || mday > daysinmonth(mon, isleapyear(year)))
    return false;
  return true;
}

int
Fl_Calendar_Base::dayofyear (int year, int mon, int mday)
{
  /* Return day of year. */
  return mday + doylookup[isleapyear (year) ? 1 : 0][mon - 1];
}

int
Fl_Calendar_Base::dayofepoch (int year, int mon, int mday)
{
  int             doe;
  int             era, cent, quad, rest;
  
  /* break down the year into 400, 100, 4, and 1 year multiples */
  rest = year - 1;
  quad = rest / 4;        rest %= 4;
  cent = quad / 25;       quad %= 25;
  era = cent / 4;         cent %= 4;
  
  /* set up doe */
  doe = dayofyear (year, mon, mday);
  doe += era * (400 * 365 + 97);
  doe += cent * (100 * 365 + 24);
  doe += quad * (4 * 365 + 1);
  doe += rest * 365;
  
  return doe;
}

int
Fl_Calendar_Base::dayofweek (int year, int mon, int mday)
{
  return dayofepoch (year, mon, mday) % 7;
}

void
Fl_Calendar_Base::previous_month ()
{
  if (month == 1)
    {
      month = 12;
      year--;
    }
  else
    month--;

  while ((mday >= 1) && (!datevalid ()))
    mday--;

  update ();
}

void
Fl_Calendar_Base::next_month ()
{
  if (month == 12)
    {
      month = 1;
      year++;
    }
  else
    month++;

  while ((mday >= 1) && (!datevalid ()))
    mday--;

  update ();
}

void
Fl_Calendar_Base::update ()
{
  int dow = dayofweek (year, month, 1);
  int dim = daysinmonth (month, isleapyear (year));
  int i;

  for (i=0; i<dow; i++)
    {
      days[i]->hide ();
    }

  for (i=(dim+dow); i<(6*7); i++)
    {
      days[i]->hide ();
    }
  
  for (i=dow; i<(dim+dow); i++)
    {
      char t[8];
      sprintf (t, "%d", (i-dow+1));
      days[i]->label (strdup(t));
      days[i]->show ();
      if ((i-dow+1) == mday)
	days[i]->setonly ();
    }
}

Fl_Button *
Fl_Calendar_Base::day_button (int i)
{
  if ((i > 0) && (i <= daysinmonth ()))
    return days[i + dayofweek (year, month, 1) - 1];
  return 0;
}

static void 
fl_calendar_previous_cb (Fl_Button *, void *b)
{
  Fl_Calendar *c = (Fl_Calendar *)b;
  c->previous_month ();
  c->do_callback(c, (long)0);
}

static void 
fl_calendar_next_cb (Fl_Button *, void *b)
{
  Fl_Calendar *c = (Fl_Calendar *)b;
  c->next_month ();
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

  previous = new Fl_Button (x, y, (w/7), (h/8), "@<-");
  previous->box (FL_THIN_UP_BOX);
#ifndef FLTK_2
  previous->labeltype (FL_SYMBOL_LABEL);
  previous->labelsize (10);
  previous->down_box (FL_THIN_DOWN_BOX);
#else
  previous->label_type (FL_SYMBOL_LABEL);
  previous->label_size (10);
#endif
  previous->callback ((Fl_Callback*)&fl_calendar_previous_cb, (void *)this);  

  next = new Fl_Button (x + (w/7)*6, y, (w/7), (h/8), "@->");
  next->box (FL_THIN_UP_BOX);
#ifndef FLTK_2
  next->labeltype (FL_SYMBOL_LABEL);
  next->labelsize (10);
  next->down_box (FL_THIN_DOWN_BOX);
#else
  previous->label_type (FL_SYMBOL_LABEL);
  previous->label_size (10);
#endif
  next->callback ((Fl_Callback*)&fl_calendar_next_cb, (void *)this);
  
  caption = new Fl_Button (x + (w/7), y, (w/7)*5, (h/8));
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

void
Fl_Calendar::csize (int cx, int cy, int cw, int ch)
{
  int i;
  for (i = 0; i<7; i++)
    {
      weekdays[i] = new Fl_Button ((cw/7)*(i%7) + cx,
				   (ch/8)*((i/7)+1) + cy,
				   (cw/7),
				   (ch/8));
    }

  previous->resize (cx, cy, (cw/7), (ch/8));
  next->resize (cx + (cw/7)*6, cy, (cw/7), (ch/8));
  caption->resize (cx + (cw/7), cy, (cw/7)*5, (ch/8));
  Fl_Calendar_Base::csize (cx, cy + (2*ch/8), cw, (6*ch/8));  
}

void 
Fl_Calendar::update ()
{
  int dow = dayofweek (year, month, 1);
  int dim = daysinmonth (month, isleapyear (year));
  int i;
  
  for (i=dow; i<(dim+dow); i++)
    {
      char t[8];
      sprintf (t, "%d", (i-dow+1));
      days[i]->label (strdup(t));
    }

  char tmp[32];
  sprintf (tmp, "%s %d", month_name[month-1], year);
  Fl_Calendar_Base::update ();
  if (caption->label ())
    free ((void *) caption->label ());
  caption->label (strdup(tmp));
  redraw ();
}

int 
Fl_Calendar::handle (int event) 
{ 
  int m, d, y, o, md; 

  switch (event) 
    { 
    case FL_FOCUS: 
    case FL_UNFOCUS: 
      return 1; 
      
    case FL_KEYBOARD: 
      m = get_month (); 
      d = get_day (); 
      y = get_year (); 
      switch(Fl::event_key ()) 
	{ 
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
      if (datevalid (y, m, d + o)) 
	set_date (y, m, d + o); 
      else 
	{ 
	  if (o < 0) 
	    { 
	      previous_month (); 
	      m = get_month (); 
	      y = get_year (); 
	      md = daysinmonth (m, isleapyear (y)); 
	      d = d + o + md; 
	      set_date (y, m, d); 
	    } 
	  else 
	    { 
	      md = daysinmonth (m, isleapyear (y)); 
	      next_month (); 
	      m = get_month (); 
	      y = get_year (); 
	      d = d + o - md; 
	      set_date (y, m, d); 
	    } 
	} 
      return 1;
    }
  return Fl_Group::handle (event);
}
