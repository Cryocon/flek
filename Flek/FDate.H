/* -*-C++-*- 

   "$Id: FDate.H,v 1.1 2000/04/13 13:56:28 jamespalmer Exp $"
   
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

#ifndef __FDATE_H__
#define __FDATE_H__

#include <Flek/FBase.H>
#include <iostream.h>

typedef enum {
  SUNDAY,
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY
} FWeekday;

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
} FMonth;

/** @package libflek_core
 * FDate provides a date class that stores the day, month and year.
 */
class FDate : public FBase
{

 public:

  /**
   * Default constructor.
   */
  FDate ();

  /**
   * Constructor that takes the year, month and day as it's arguments.
   */
  FDate (int y, int m, int d);

  /**
   * The copy constructor.
   */
  FDate (const FDate &);

  virtual FBase::Ptr copy (void) const;

  /**
   * Set the date value given a year y, a month m, and a day d.
   */
  void set_date (int y, int m, int d);

  /**
   * Set the date value from another FDate object.
   */
  void set_date (const FDate &);

  /**
   * Set the format.
   */
  void set_format (int);

  /**
   * Set the date value to today's date.
   */
  void today ();

  /**
   * Sets the year.
   */
  void year (int);

  /** 
   * Gets the year.
   */
  int  year ();

  /**
   * Sets the month.
   */
  void month (int);

  /**
   * Gets the month.
   */
  int  month ();

  /**
   * Sets the day.
   */
  void day (int);

  /**
   * Gets the day.
   */
  int  day ();

  /**
   * Gets the Julian date.
   */
  double julian_date ();

  /**
   * Equality comparison of two dates.
   */
  bool operator== (const FDate &);

  /**
   * Inequality comparison of two dates.
   */
  bool operator!= (const FDate &);

  /**
   * Comparison of two dates.
   */
  bool operator< (const FDate &);

  /**
   * Comparison of two dates.
   */
  bool operator> (const FDate &);

  /**
   * Set one date equal to another date.
   */
  void operator= (const FDate &);

  /**
   * Adds days to the date.
   */
  const FDate &operator+= (int);

  /**
   * Pre-increment operator.
   */
  FDate &operator++ ();

  /**
   * Post-increment operator.
   */
  FDate operator++ (int);

  /**
   * ostream operator.
   */
  friend ostream& operator << (ostream &, const FDate &);

  /**
   * Returns wether day d is at the end of the month.
   */
  bool end_of_month (int m);

  /**
   * Returns wether year y is a leap year.
   */
  bool leap_year (int y);
  bool leap_year ()
    { return leap_year (Year); }

  /**
   * Returns wether the date y-m-d is valid.
   */
  bool is_valid (int y, int m, int d);
  bool is_valid ()
    { return is_valid (Year, Month, Day); }
  
  int days_in_month (int, int);
  int days_in_month () 
    { return days_in_month (Month, leap_year (Year)); }
  
  int day_of_year (int, int, int);
  int day_of_year () 
    { return day_of_year (Year, Month, Day); }
  
  int day_of_epoch (int, int, int);
  int day_of_epoch () 
    { return day_of_epoch (Year, Month, Day); }
    
  int day_of_week (int, int, int);
  int day_of_week () 
    { return day_of_week (Year, Month, Day); }
  
  void previous_month ();
  void next_month ();

  void previous_year ();
  void next_year ();
  
  char *to_string (int) const;
  char *to_string () const;

  static const int   days[];
  static const int   julian_days[];
  static const char* month_name[];
  
private:

  int  Year;
  int  Month;
  int  Day;
  int  Fmt;
  void help_increment ();

};

#endif
