/* -*-C++-*- 

   "$Id: Fl_Dockable_Window.H,v 1.4 2000/05/17 00:36:14 brad Exp $"
   
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

#ifndef _FL_DOCKABLE_WINDOW_H_
#define _FL_DOCKABLE_WINDOW_H_

#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>

#define FL_UNDOCK     999999999
#define FL_DOCK       99999999
#define FL_PACK_DOCK  9999999
#define FL_DOCK_DELTA 10

#define FL_SHOVABLE 1
#define FL_DRAGABLE 2

/** @package libflek_ui
 * Fl_Gripper is a little button that looks like you can grab it
 * and drag something around with it.  Used by Fl_Dockable_Window.
 */
class Fl_Gripper : public Fl_Button {
private:
  int x_down;
  int y_down;
  int x_first;
  int y_first;

public:
  Fl_Gripper(int x, int y, int w, int h, const char *l = 0) : 
    Fl_Button(x, y, w, h, l) {
      color(FL_LIGHT2);
      label("@-92<->");
      labeltype(FL_SYMBOL_LABEL);      
  }
  void draw();
  int handle(int event);
};

/** @package libflek_ui
 * Fl_Dockable_Window is a window that can be docked onto a window 
 * that accepts Fl_Dockable_Windows, such as Fl_App_Window. 
 * <p><img src="Fl_Dockable_Window.png">
 */
class Fl_Dockable_Window : public Fl_Window {
protected:
  Fl_Gripper* gripper;
  Fl_Window* contents;
  static long gripper_width;
  short docked;
  int uw_;
  int uh_;
  unsigned char type_;
  Fl_Dockable_Window::create_dockable_window();

public:
  static Fl_Dockable_Window* current;

  /**
   * Construct a dockable window.
   */
  Fl_Dockable_Window(int w, int h, const char *l = 0);
  Fl_Dockable_Window(int x, int y, int w, int h, const char *l = 0);

  ~Fl_Dockable_Window ();

  void show();
  int handle(int);

  /**
   * Add new widgets to the contents window.
   */
  void begin() { Fl_Group::current(contents); }

  /**
   * Undock the group to screen coordinates (x, y).
   */
  void undock(int x=-1, int y=-1);  
  short get_docked() { return docked; }
  void  set_docked(short r) { docked = r; }  
  
  void type(unsigned char t); 
  unsigned char type();
};

#endif
