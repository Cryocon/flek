/* -*-C++-*- 

   "$Id: Fl_Calendar.H,v 1.5 2000/04/13 13:56:28 jamespalmer Exp $"
   
   Copyright 1999-2000 by the Flek development team.
   
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.
   
   You should have received a copy of the GNU Library General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA.
   
   Please report all bugs and problems to "flek-devel@sourceforge.net".

*/

#ifndef _FL_CALENDAR_H_
#define _FL_CALENDAR_H_

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

/** @package libflek_ui
 * Fl_Calendar_Base is a widget that allows a user to select a date
 * (day, month, and year) with a wall style calendar. 
 */
class Fl_Calendar_Base : public Fl_Group 
{
public:
  /**
   * The constructor for an empty Fl_Calendar_Base.
   */
  Fl_Calendar_Base (int x, int y, int w = (7*20), int h = (6*20),   
		    const char *l = 0);

  /**
   * Set the calendar date to y/m/d.
   */
  short set_date (int y, int m, int d);

  /** 
   * Set the month to M (valid range 1-12).
   */
  short set_month (int m);  

  /** 
   * Get the month (valid range 1-12).
   */
  int get_month () { return month; }

  /** 
   * Set the year to Y.
   */
  short set_year (int y);  

  /** 
   * Get the year.
   */
  int get_year () { return year; }

  /** 
   * Set the day to D.
   */
  short set_day (int d);

  /** 
   * Get the day.
   */
  int get_day () { return mday; }

  /**
   * Move forward to the next month.
   */  
  void next_month ();

  /**
   * Move backward to the previous month.
   */  
  void previous_month ();

  /**
   * Determines if any specified year is a leap year.
   */  
  static short isleapyear (int year);

  /**
   * Determines the number of days in the month based on the month and 
   * wether or not it is a leap year.
   */  
  static int daysinmonth (int month, short leap);

  /**
   * Determines if the date Y/M/D is valid.
   */  
  static short datevalid (int year, int mon, int mday);

  /**
   * Determines what day of the year it is for the date Y-M-D.
   */  
  static int dayofyear (int year, int mon, int mday);

  /**
   * Determines what day of the epoch it is for the date Y-M-D. 
   */  
  static int dayofepoch (int year, int mon, int mday);

  /**
   * Determines what day of the week it is for the date Y-M-D.
   */  
  static int dayofweek (int year, int mon, int mday);

  /**
   * Determines if the currently selected year is a leap year.
   */
  short isleapyear () { return isleapyear (year); }

  /**
   * Determines the number of days in the month for the currently 
   * selected month and year.
   */
  int daysinmonth () { return daysinmonth (month, isleapyear (year)); }

  /**
   * Determines if the currently selected date is valid.
   */
  short datevalid () { return datevalid (year, month, mday); }

  /**
   * Determines what the day of the year is for the
     currently selected date.
   */
  int dayofyear () { return dayofyear (year, month, mday); }

  /**
   * Determines what the day of the epoch is for
     the currently selected date.
   */
  int dayofepoch () { return dayofepoch (year, month, mday); }

  /**
   * Determines what the day of the week is for the
     currently selected date.
   */
  int dayofweek () { return dayofweek (year, month, mday); }
  
  virtual void update ();

  void csize (int cx, int cy, int cw, int ch);

  /**
   * Returns a pointer to the button for the day D in the Fl_Calendar. 
   */
  Fl_Button * day_button (int i);
  
 protected:
  int year;
  int month;
  int mday;

  int cal_x;
  int cal_y;
  int cal_w;
  int cal_h;

  Fl_Button * days[6*7];
};

/** @package libflek_ui
 * Fl_Calendar is a subclass of Fl_Calendar.  This widget adds 
 * day labels and controllers to the base calendar class.
 * <p><img src="Fl_Calendar.png">
 */
class Fl_Calendar : public Fl_Calendar_Base 
{
public:
  /**
   * The constructor for an empty Fl_Calendar.
   */
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
