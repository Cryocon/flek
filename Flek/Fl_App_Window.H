/* -*-C++-*- 

   "$Id: Fl_App_Window.H,v 1.4 2000/02/06 20:40:44 jamespalmer Exp $"
   
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

#ifndef FL_APP_WINDOW_H_
#define FL_APP_WINDOW_H_

#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>

#include <Flek/Fl_Dockable_Group.H>
#include <Flek/Fl_Pack_Fu.H>

/** @package libflek_ui (The Flek User Interface Library)
 * Fl_App_Window is a window that can have Fl_Dockable_Groups 
 * "docked" either vertically or horizontally to the contents of the window.
 */
class Fl_App_Window : public Fl_Window
{
public:
  
  /**
   * The constructor for an empty Fl_App_Window.
   */
  Fl_App_Window (int x, int y, int w, int h, const char *l = 0);
  /**
   * The constructor for an empty Fl_App_Window.
   */
  Fl_App_Window (int w, int h, const char *l = 0);

  int handle (int);

  void add (Fl_Widget *w);

  /**
   * Dock the Fl_Dockable_Group W to the window.
   */
  void add_dockable (Fl_Dockable_Group *W, int position = 0);
  void pack_dock () 
    { 
      /// pack->pack(); 
      if ((pack->w() != w()) || (pack->h() != h()))
        size (pack->w(), pack->h());
    }
  void show ();
  void begin () { Fl_Group::current (contents); }
  void end () { Fl_Group::current ((Fl_Group*) parent ()); }
  Fl_Pack_Fu *tpack () {return pack; }
  
 protected:
  virtual FL_EXPORT void draw ();
  virtual FL_EXPORT void flush ();
  
  Fl_Pack_Fu    *pack;
  Fl_Window    *contents;
};

#endif
