#ifndef _FL_STOCK_H
#define _FL_STOCK_H

#include <FL/Fl_Button.H>

// Values used to align the text in the widget.

#ifndef FLTK_2
#include <FL/Fl_Pixmap.H>
#define Fl_Flags int
#define Fl_Image Fl_Pixmap
#define FL_INACTIVE 4096
#endif

#define FL_TEXT_ALIGN_LEFT   0x00100000
#define FL_TEXT_ALIGN_RIGHT  0x00200000
#define FL_TEXT_ALIGN_TOP    0x00400000
#define FL_TEXT_ALIGN_BOTTOM 0x00800000

class Fl_Stock_Button : public Fl_Button
{
public:
  FL_EXPORT Fl_Stock_Button (int,int,int,int,const char * = 0);
  void draw_label(int X, int Y, int W, int H, Fl_Color c, Fl_Flags f);
  void draw ();
#ifndef FLTK_2
protected:
  Fl_Pixmap * image() { return image_; }
  void image (Fl_Pixmap*p) {image_ = p; }
  Fl_Pixmap *image_;
  void set_flag (int f) {flags_ |= f; Fl_Widget::set_flag(f);}
  void clear_flag (int f) {flags_ &= ~f; Fl_Widget::clear_flag(f);}
  int flags () {return (Fl_Widget::flags() | flags_); }
  int flags_;
#endif
};

class Fl_Stock_Button_Ok : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Ok (int,int,int,int,const char*l="Ok");
};

class Fl_Stock_Button_Cancel : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Cancel (int,int,int,int,const char*l="Cancel");
};

class Fl_Stock_Button_Yes : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Yes (int,int,int,int,const char*l="Yes");
};

class Fl_Stock_Button_No : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_No (int,int,int,int,const char*l="No");
};

class Fl_Stock_Button_Apply : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Apply (int,int,int,int,const char*l="Apply");
};

class Fl_Stock_Button_Close : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Close (int,int,int,int,const char*l="Close");
};

class Fl_Stock_Button_Add : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Add (int,int,int,int,const char*l="Add");
};

class Fl_Stock_Button_Remove : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Remove (int,int,int,int,const char*l="Remove");
};

class Fl_Stock_Button_New : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_New (int,int,int,int,const char*l="New");
};

class Fl_Stock_Button_Previous : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Previous (int,int,int,int,const char*l="Previous");
};

class Fl_Stock_Button_Next : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Next (int,int,int,int,const char*l="Next");
};

class Fl_Stock_Button_Left : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Left (int,int,int,int,const char*l="Left");
};

class Fl_Stock_Button_Right : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Right (int,int,int,int,const char*l="Right");
};

class Fl_Stock_Button_Up : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Up (int,int,int,int,const char*l="Up");
};

class Fl_Stock_Button_Down : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Down (int,int,int,int,const char*l="Down");
};

class Fl_Stock_Button_Top : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Top (int,int,int,int,const char*l="Top");
};

class Fl_Stock_Button_Bottom : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Bottom (int,int,int,int,const char*l="Bottom");
};

class Fl_Stock_Button_Clear : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Clear (int,int,int,int,const char*l="Clear");
};

class Fl_Stock_Button_Open : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Open (int,int,int,int,const char*l="Open");
};

class Fl_Stock_Button_Copy : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Copy (int,int,int,int,const char*l="Copy");
};

class Fl_Stock_Button_Cut : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Cut (int,int,int,int,const char*l="Cut");
};

class Fl_Stock_Button_Exec : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Exec (int,int,int,int,const char*l="Exec");
};

class Fl_Stock_Button_First : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_First (int,int,int,int,const char*l="First");
};

class Fl_Stock_Button_Help : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Help (int,int,int,int,const char*l="Help");
};

class Fl_Stock_Button_Last : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Last (int,int,int,int,const char*l="Last");
};

class Fl_Stock_Button_Save : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Save (int,int,int,int,const char*l="Save");
};

class Fl_Stock_Button_Save_As : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Save_As (int,int,int,int,const char*l="Save As");
};

class Fl_Stock_Button_Search : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Search (int,int,int,int,const char*l="Search");
};

class Fl_Stock_Button_Search_Replace : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Search_Replace (int,int,int,int,const char*l="Search and Replace");
};

#endif
