/* -*-C++-*- 

   "$Id: Fl_App_Window.H,v 1.11 2000/05/11 23:17:33 brad Exp $"
   
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

#ifndef _FL_APP_WINDOW_H_
#define _FL_APP_WINDOW_H_

#include <vector>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Pack.H>

#include <Flek/Fl_Dockable_Group.H>

/** @package libflek_ui
 * Fl_App_Window is a window that can have Fl_Dockable_Groups 
 * "docked" either vertically or horizontally to the contents of the window.
 * An Fl_App_Window starts with a top-level "application" window.
 * Flek creates an Fl_Pack group that fills the application window.
 * The pack group contains the child "contents" window and any
 * "docked" groups.
 * You might think of the contents window as the "client" area of the application.
 */
class Fl_App_Window : public Fl_Window {
private:
  Fl_Pack* _pack;
  Fl_Window* _contents;
  vector<Fl_Dockable_Group*> dockable_groups;

protected:
  virtual FL_EXPORT void draw();
  virtual FL_EXPORT void flush();
  int handle(int);

public:
  /**
   * Construct an Fl_App_Window.
   */
  Fl_App_Window(int w, int h, const char *l = 0);

  /**
   * Construct an Fl_App_Window, forcing a specific position.
   * This probably isn't what you want.  Try the other constructor instead.
   */
  Fl_App_Window(int x, int y, int w, int h, const char *l = 0);

  /**
   * Return a pointer to the Fl_Pack group, which contains the contents window
   * and any docked groups.
   * From what I can tell, this is only used by the dockable_group sample.
   */
  Fl_Pack* tpack() { return _pack; }

  /**
   * Return a pointer to the contents window.
   */
  Fl_Window* contents() { return _contents; }

  /**
   * Set the box type and color for the contents window.
   */
  void box(Fl_Boxtype b) { _contents->box(b); }
  void color(Fl_Color a) { _contents->color(a); }
  void color(Fl_Color a, Fl_Color b) { _contents->color(a, b); }

  /**
   * Add a widget to the contents window.
   */
  void add(Fl_Widget *w);

  /**
   * Resize the contents window.
   */
  void resize(int x, int y, int w, int h);
  
  /**
   * Dock an Fl_Dockable_Group to the window.
   * Docking an Fl_Dockable_Group to an Fl_App_Window does not change
   * the size of the Fl_App_Window.  Rather, the size of the contents
   * window is adjusted to accomodate the Fl_Dockable_Group.
   */
  void add_dockable(Fl_Dockable_Group* W, int position = 0);

  /**
   * Makes the contents window the current group.
   */
  void begin() { Fl_Group::current(_contents); }

  /**
   * Show or hide the application window.
   */
  void show();
  void hide();
};

#endif
