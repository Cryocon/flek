/*
  "$Id: time.cxx,v 1.2 2001/05/15 17:08:06 jamespalmer Exp $"
  
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

#include <Flek/Fl_Time.H>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
  
  Fl_Window    *w = new Fl_Window (190, 100, "Widget Examples");
  w->resizable (w);
  (void) new Fl_Time (20, 20, 150, 22);
  Fl_Time *t = new Fl_Time (20, 50, 150, 22); 
  t->type(FL_TIME_24HOUR);
  w->end();
  w->show(argc, argv);
  
  return Fl::run();
}
