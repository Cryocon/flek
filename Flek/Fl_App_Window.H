#ifndef _FL_APP_WINDOW_H
#define _FL_APP_WINDOW_H

#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>

#include <Flek/Fl_Dockable_Group.H>
#include <Flek/Fl_Pack_Fu.H>

class Fl_App_Window : public Fl_Window
{
 public:
  Fl_App_Window (int x, int y, int w, int h, const char *l = 0);
  Fl_App_Window (int w, int h, const char *l = 0);

  int handle (int);

  void add (Fl_Widget *w);
  void add_dockable (Fl_Dockable_Group *W, int position = 0);
  void pack_dock () 
    { 
      pack->pack(); 
      if ((pack->w() != w()) || (pack->h() != h()))
        size (pack->w(), pack->h());
    }
  void show ();
  void begin () { Fl_Group::current (contents); }
  void end () { Fl_Group::current ((Fl_Group*) parent ()); }
  
 protected:
  Fl_Pack_Fu    *pack;
  Fl_Window    *contents;
};

#endif
