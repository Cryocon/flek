#ifndef _FL_DOCKABLE_GROUP_H
#define _FL_DOCKABLE_GROUP_H

#include <FL/Fl_Button.H>
#include <Fl/Fl_Window.H>

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

class Fl_Dockable_Group : public Fl_Window
{
 public:
  Fl_Dockable_Group (int x, int y, int w, int h, const char *l = 0);  
  Fl_Dockable_Group (int w, int h, const char *l = 0);  
  ~Fl_Dockable_Group ();

  void draw ();  
  void show ();
  int handle (int);
  void begin () { Fl_Group::current (contents); }
  void end () { Fl_Group::current ((Fl_Group*) parent ()); }
  void undock (int x, int y);  
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
