/* -*-C++-*- 
   "$Id: fDate.h,v 1.1 2000/02/25 01:43:48 jamespalmer Exp $"
   
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

#include <Flek/fBase.h>
#include <iostream.h>

/** @package libflek_core
 * fDate provides a date class that stores the day, month and year.
 */
class fDate : public fBase
{
public:

  /**
   * Default constructor.
   */
  fDate ();

  /**
   * Constructor that takes the year, month and day as it's arguments.
   */
  fDate (int y, int m, int d);

  /**
   * The copy constructor.
   */
  fDate (const fDate &);

  virtual fBase::Ptr copy (void) const;

  /**
   * Set the date value given a year y, a month m, and a day d.
   */
  void setDate (int y, int m, int d);

  /**
   * Set the date value from another fDate object.
   */
  void setDate (const fDate &);

  /**
   * Set the format.
   */
  void setFormat (int);

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
  double dJulian ();

  /**
   * Equality comparison of two dates.
   */
  bool operator== (const fDate &);

  /**
   * Inequality comparison of two dates.
   */
  bool operator!= (const fDate &);

  /**
   * Comparison of two dates.
   */
  bool operator< (const fDate &);

  /**
   * Comparison of two dates.
   */
  bool operator> (const fDate &);

  /**
   * Set one date equal to another date.
   */
  void operator= (const fDate &);

  /**
   * Adds days to the date.
   */
  const fDate &operator+= (int);

  /**
   * Pre-increment operator.
   */
  fDate &operator++ ();

  /**
   * Post-increment operator.
   */
  fDate operator++ (int);

  /**
   * Returns wether day d is at the end of the month.
   */
  bool endOfMonth (int m);

  /**
   * Returns wether year y is a leap year.
   */
  bool leapYear (int y);

  /**
   * Returns wether the date y-m-d is valid.
   */
  bool isValid (int y, int m, int d);

  /**
   * ostream operator.
   */
  friend ostream& operator << (ostream &, const fDate &);

private:

  int  Year;
  int  Month;
  int  Day;
  int  Fmt;
  static const int Days[];
  static const int JDays[];
  void helpIncrement();

};

#endif
