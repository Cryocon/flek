// Fl_Time.h
// Header file for the time Widget class
//
// Copyright (C) 2000 Softfield Research Ltd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef __TIME_WIDGET_H
#define __TIME_WIDGET_H

#include "sys/time.h"
#include "unistd.h"
#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Repeat_Button.H>
#include <FL/Fl_Input.H>

#define FL_TIME_24HOUR 0
#define FL_TIME_12HOUR 1

class Fl_Time : public Fl_Group {
private:
	Fl_Repeat_Button* button_decrease_hour;
	Fl_Repeat_Button* button_decrease_minute;
	Fl_Input*  input_time;
	Fl_Repeat_Button* button_increase_minute;
	Fl_Repeat_Button* button_increase_hour;

	struct timeval current_tv;
	struct timeval display_tv;
	char time_string[20];
	bool last_valid;
	
	int look_;

	static void input_changed_cb(Fl_Widget* widget, void* data);
	static void button_cb(Fl_Widget* widget, void* data);

public:
	Fl_Time(int x, int y, int w, int h, char *l=0); 
	~Fl_Time();

	int hour();
	void hour(int value);

	int minute();
	void minute(int value);

	// Be sure to run this after using hour and min to change the clock value.
	void redisplay();

	void value(int h, int m);
	void current_time();
	void refresh();

	void labelsize(int size);
	void labelfont(Fl_Font);
	void labelcolor(Fl_Color);

	void textsize(int size);
	void textfont(Fl_Font);
	void textcolor(Fl_Color);

	int labelsize();
	Fl_Font labelfont();
	Fl_Color labelcolor();

	int textsize();
	Fl_Font textfont();
	Fl_Color textcolor();

	bool valid();	
};

#endif
