#ifndef _FL_CALENDAR_H
#define _FL_CALENDAR_H

#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>

typedef enum {
  SUNDAY,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
} weekday_t;

typedef enum {
  JANUARY = 1,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
} month_t;

extern char * month_name[12];

#define	DOE_MIN		1		/* January 1, 1 */
#define	DOE_MAX		3652059		/* December 31, 9999 */
#define	YEAR_MIN	1
#define	YEAR_MAX	9999

class Fl_Calendar_Base : public Fl_Group 
{
public:
  Fl_Calendar_Base (int x, int y, int w = (7*20), int h = (6*20), 
  		    const char *l = 0);
 
  short set_date (int y, int m, int d);

  short set_month (int m);  
  int get_month () { return month; }
  short set_year (int y);  
  int get_year () { return year; }
  short set_day (int d);
  int get_day () { return mday; }
  
  void next_month ();
  void previous_month ();

  static short isleapyear (int year);
  static int daysinmonth (int month, short leap);
  static short datevalid (int year, int mon, int mday);
  static int dayofyear (int year, int mon, int mday);
  static int dayofepoch (int year, int mon, int mday);
  static int dayofweek (int year, int mon, int mday);
  
  short isleapyear () { return isleapyear (year); }
  int daysinmonth () { return daysinmonth (month, isleapyear (year)); }
  short datevalid () { return datevalid (year, month, mday); }
  int dayofyear () { return dayofyear (year, month, mday); }
  int dayofepoch () { return dayofepoch (year, month, mday); }
  int dayofweek () { return dayofweek (year, month, mday); }
  
  virtual void update ();
  void csize (int cx, int cy, int cw, int ch);
  Fl_Button * day_button (int i);
  
 protected:
  int year;
  int month;
  int mday;

  int cal_x;
  int cal_y;
  int cal_w;
  int cal_h;

  Fl_Button * days[(6*7)];
};

class Fl_Calendar : public Fl_Calendar_Base 
{
public:
  Fl_Calendar (int x, int y, int w = (7*20), int h = (8*20), 
  		    const char *l = 0);
 
  void update ();
  void csize (int cx, int cy, int cw, int ch);
  int  handle (int);

protected:
  Fl_Button * weekdays[7];
  Fl_Button * caption;
  Fl_Button * next;
  Fl_Button * previous;
};

#endif
