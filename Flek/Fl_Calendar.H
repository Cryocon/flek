/* -*-C++-*- 

   "$Id: Fl_Calendar.H,v 1.11 2000/10/06 17:22:22 clip Exp $"
   
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
#include <FL/Fl_Input.H>

#include <Flek/FDate.H>

#define	DOE_MIN		1		/* January 1, 1 */
#define	DOE_MAX		3652059		/* December 31, 9999 */
#define	YEAR_MIN	1
#define	YEAR_MAX	9999

#ifndef FL_LOOK_CLASSIC
#define FL_LOOK_CLASSIC 0
#endif
#ifndef FL_LOOK_MODERN
#define FL_LOOK_MODERN 1
#endif

/** @package libflek_ui
 * Fl_Calendar_Base is a widget that allows a user to select a date
 * (day, month, and year) with a wall style calendar. 
 */
class Fl_Calendar_Base : public Fl_Group, public FDate {
  
public:
  /**
   * The constructor for an empty Fl_Calendar_Base.
   */
  Fl_Calendar_Base (int x, int y, int w = (7*20), int h = (6*20),   
		    const char *l = 0);

  void update ();

  void csize (int cx, int cy, int cw, int ch);

  /**
   * Returns a pointer to the button for the day D in the Fl_Calendar. 
   */
  Fl_Button * day_button (int i);
  void normal_callback() { cb_return_value = false; }
  void calendar_value_callback() { cb_return_value = true; }
  bool cb_return_value;
 protected:
  
  int cal_x;
  int cal_y;
  int cal_w;
  int cal_h;

  Fl_Button * days[6*7];
};

/**
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
  		    const char *l = 0, int title_height = -1, int look = FL_LOOK_CLASSIC);

  void previous_month ();
  void next_month ();
  void previous_year ();
  void next_year ();
  
  void update ();
  void csize (int cx, int cy, int cw, int ch);
  int  handle (int);

  void selection_color(Fl_Color c) {
	Fl_Widget::selection_color(c);
	for(int i = 0; i < 6*7; i++) {
		if(days[i]->color() == days[i]->selection_color()) {
			days[i]->color(c);
		}
		days[i]->selection_color(c);
	}
  }

  Fl_Color selection_color() const {
	return 	Fl_Group::selection_color();
  }

  int button_value() {return last_button_value;}
  int last_button_value;


 protected:
  
  Fl_Button * weekdays[7];
  Fl_Button * caption;
  Fl_Button * nxt_month;
  Fl_Button * prv_month;
  Fl_Button * nxt_year;
  Fl_Button * prv_year;
  
 private:
  int look;

};

/**
 * An input for getting and setting a date.
 */
class Fl_Date_Input : public Fl_Group  {

 protected:
  
  Fl_Input   Input;
  Fl_Button  Btn;
  
  int xpos;
  int ypos;
  int width;
  int height;
  int popcalfmt;
  
 public:

  /**
   * Default constructor.
   * 
   * @param x The x coordinate.
   * @param y The y coordinate.
   * @param w The width of this widget.
   * @param h The height of this widget.
   * @param l The label.
   */
  Fl_Date_Input (int x, int y, int w, int h, char * = 0);
  
  void format (int);
  
  /**
   * Gets the date value.
   * 
   * @return The date string.
   */
  const char *value ();

  /**
   * Sets the date value.
   * 
   * @param date The date string.
   */
  void value (const char* date);

#ifndef FLEK_FLTK_2
  void text_font (int);
  void textfont (int t) { text_font(t); }
  void textsize (int t) { text_size(t); }
#else
  void text_font (Fl_Font);
#endif
  void text_size (int);
  
  void btnDate_Input_cb_i ();
  
};


#endif
