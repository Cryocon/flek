/* -*-C++-*- 

   "$Id: Fl_Dockable_Group.H,v 1.3 2000/02/06 20:40:44 jamespalmer Exp $"
   
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

#ifndef FL_DOCKABLE_GROUP_H_
#define FL_DOCKABLE_GROUP_H_

#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>

#define FL_UNDOCK     999999999
#define FL_DOCK       99999999
#define FL_PACK_DOCK  9999999
#define FL_DOCK_DELTA 10

class Fl_Gripper : public Fl_Button
{
 public:
  Fl_Gripper (int x, int y, int w, int h, const char *l = 0) : 
    Fl_Button (x, y, w, h, l) 
    {
      color(52);
    }
  void draw();  
  int handle (int event);
  
 private:
  int x_down;
  int y_down;
  int x_first;
  int y_first;
};

/** @package libflek_ui (The Flek User Interface Library)
 * Fl_Dockable_Group is a window that can be docked onto a window 
 * that accepts Fl_Dockable_Groups, have Fl_Dockable_Groups, such
 * as Fl_App_Window. 
 * <p><img src="Fl_Dockable_Group.png">
 */
class Fl_Dockable_Group : public Fl_Window
{
 public:

  /**
   * The constructor for an empty Fl_Dockable_Group.
   */
  Fl_Dockable_Group (int x, int y, int w, int h, const char *l = 0);

  /**
   * The constructor for an empty Fl_Dockable_Group.
   */
  Fl_Dockable_Group (int w, int h, const char *l = 0);

  ~Fl_Dockable_Group ();

  void draw ();  
  void show ();
  int handle (int);
  void begin () { Fl_Group::current (contents); }
  void end () { Fl_Group::current ((Fl_Group*) parent ()); }

  /**
   * Undock the group to screen coordinates (x, y).
   */
  void undock (int x=-1, int y=-1);  
  short get_docked () { return docked; }
  void  set_docked (short r) { docked = r; }  
  static Fl_Dockable_Group *current;
  int uw () { return uw_; }
  int uh () { return uh_; }
  void usize (int tw, int th) { uw_ = tw; uh_ = th; }
  
 protected:
  Fl_Gripper *gripper;
  Fl_Window *contents;
  static long gripper_width;
  short docked;
  int uw_;
  int uh_;
};

#endif
