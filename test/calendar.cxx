/*
  "$Id: calendar.cxx,v 1.2 2000/04/19 18:19:47 jamespalmer Exp $"
  
  This program tests Fl_Calendar.

  Copyright 1999-2000 by James Dean Palmer and others.
  
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

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include <Flek/Fl_Calendar.H>

/*int main (int argc, char **argv) 
{
  Fl_Window window (300, 370);
  
  Fl_Calendar *calendar = new Fl_Calendar (10, 10, window.w()-20, window.h()-20);
  window.resizable (calendar);

  window.end ();
  window.show (argc,argv);
  
  return Fl::run ();
}
*/

void calendar_cb (Fl_Calendar *c, void *) {
  for (int i = 0; i < 5; i++) {
    c->set_format (i);
    cout << *c << endl;
  }
}

void exit_cb (Fl_Button *b, void *) {
  exit(0);
}

int main (int argc, char **argv) {
  
  Fl_Window    *w = new Fl_Window (360, 240, "Widget Examples");
  //Fl_Date_Input *dinput0 =
  new Fl_Date_Input (20, 20, 150, 22);
  Fl_Date_Input *dinput1 = new Fl_Date_Input (20, 50, 150, 22);
  dinput1->format(1);
  
  Fl_Date_Input *dinput2 = new Fl_Date_Input (20, 80, 150, 22);
  dinput2->format(2);
  
  Fl_Date_Input *dinput3 = new Fl_Date_Input (20, 110, 150, 22);
  dinput3->format(3);
  
  Fl_Date_Input *dinput4 = new Fl_Date_Input (20, 140, 150, 22);
  dinput4->format(4);
  
  Fl_Calendar *c = new Fl_Calendar (200, 20);
  w->resizable (c);
  c->callback ( (Fl_Callback*)calendar_cb);
  c->end();
  
  Fl_Button *b = new Fl_Button (300, 210, 50, 20, "Exit");
  b->callback ( (Fl_Callback*)exit_cb);
  w->end();
  w->show(argc, argv);
  
  return Fl::run();
}
