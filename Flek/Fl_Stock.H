#ifndef _FL_STOCK_H
#define _FL_STOCK_H

#include <FL/Fl_Button.H>

// Values used to align the text in the widget.

#ifndef FLTK_2
#include <FL/Fl_Pixmap.H>
#define Fl_Flags long
#define Fl_Image Fl_Pixmap
#define FL_INACTIVE 0x00000100
#endif

#define FL_TEXT_ALIGN_LEFT   0x00100000
#define FL_TEXT_ALIGN_RIGHT  0x00200000
#define FL_TEXT_ALIGN_TOP    0x00400000
#define FL_TEXT_ALIGN_BOTTOM 0x00800000

class Fl_Stock_Button : public Fl_Button
{
public:
  FL_EXPORT Fl_Stock_Button (int,int,int,int,const char * = 0);
  void Fl_Stock_Button::draw_label(int X, int Y, int W, int H, Fl_Color c, Fl_Flags f);
  void draw ();
#ifndef FLTK_2
protected:
  Fl_Pixmap * image() { return image_; }
  void image (Fl_Pixmap*p) {image_ = p; }
  Fl_Pixmap *image_;
#endif
};

class Fl_Stock_Button_Ok : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Ok (int,int,int,int,const char * = 0);
};

class Fl_Stock_Button_Cancel : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Cancel (int,int,int,int,const char * = 0);
};

class Fl_Stock_Button_Yes : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Yes (int,int,int,int,const char * = 0);
};

class Fl_Stock_Button_No : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_No (int,int,int,int,const char * = 0);
};

class Fl_Stock_Button_Apply : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Apply (int,int,int,int,const char * = 0);
};

class Fl_Stock_Button_Close : public Fl_Stock_Button
{
  public:
  FL_EXPORT Fl_Stock_Button_Close (int,int,int,int,const char * = 0);
};

#endif
