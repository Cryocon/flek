#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Pixmap.H>
#include <FL/fl_draw.H>

#include <Flek/Fl_Stock.H>
#include "stock_button_ok.xpm"
#include "stock_button_cancel.xpm"
#include "stock_button_yes.xpm"
#include "stock_button_no.xpm"
#include "stock_button_apply.xpm"
#include "stock_button_close.xpm"

Fl_Stock_Button::Fl_Stock_Button (int x, int y, int w, int h, const char *l) : 
  Fl_Button (x, y, w, h, l)
{
}

void Fl_Stock_Button::draw()
{
  if (type() == FL_HIDDEN_BUTTON) {box(FL_NO_BOX); return;}
#ifdef FLTK_2
  Fl_Color col = draw_button();
#else
  Fl_Color col = value() ? selection_color() : color();
  draw_box(value() ? (down_box()?down_box():down(box())) : box(), col);
#endif
  draw_label (x(), y(), w(), h(), col, flags()); 
}

void
Fl_Stock_Button::draw_label (int X, int Y, int W, int H,
			     Fl_Color c, Fl_Flags f)
{
  int tw=0, th=0;
  int iw=0, ih=0;

  int w, h;

  Fl_Image*   image_ = image ();
  const char* label_ = label ();

  if (image_)
#ifdef FLTK_2
    image_->measure(iw, ih);
#else
    fl_measure_pixmap(image_->data, iw, ih);
#endif
  if (label_)
    {
#ifdef FLTK_2
      fl_font(label_font(), label_size());
      tw = fl_width(label_);
      th = label_size();
#else
      fl_font(labelfont(), labelsize());
      tw = fl_width(label_);
      th = labelsize();
#endif
    }

  int spacer = 5;

  if ((f & FL_TEXT_ALIGN_TOP) || (f & FL_TEXT_ALIGN_BOTTOM))
    {
      h = th + ih + spacer;
      w = ((tw > iw) ? tw : iw); // max
    }
  else
    { 
      w = tw + iw + spacer; 
      h = ((th > ih) ? th : ih); // max
    }
  
  int dx, dy;

  dx = X + (W/2) - (w/2);
  dy = Y + (H/2) - (h/2);

  if (f & FL_ALIGN_TOP) 
    {
      if (f & FL_ALIGN_INSIDE) 
	dy = Y;
      else
	dy = Y-h;
    }
  if (f & FL_ALIGN_BOTTOM) 
    {
      if (f & FL_ALIGN_INSIDE)
	dy = Y+H-h;
      else
	dy = Y+H;
    }
  if (f & FL_ALIGN_LEFT) 
    {
      if (f & FL_ALIGN_INSIDE)
	dx = X;
      else
	dx = X-dx;
    }
  if (f & FL_ALIGN_RIGHT)
    {
      if (f & FL_ALIGN_INSIDE)
	dx = X+W-w;
      else
	dx = X+W;
    }

  int tdx = dx, tdy = dy;
  int idx = dx, idy = dy;

  if (f & FL_TEXT_ALIGN_TOP)
    {  
      idy = dy + th + spacer;
      idx += (w - iw)/2;
      tdx += (w - tw)/2;
    }
  else if (f & FL_TEXT_ALIGN_BOTTOM) 
    { 
      tdy = dy + ih + spacer;
      idx += (w - iw)/2;
      tdx += (w - tw)/2;
    }
  else if (f & FL_TEXT_ALIGN_LEFT)
    {
      idx = dx + tw + spacer;
      idy += (h - ih)/2;
      tdy += (h - th)/2;
    }
  else // (f & FL_TEXT_ALIGN_RIGHT) // default
    {
      tdx = dx + iw + spacer;
      idy += (h - ih)/2;
      tdy += (h - th)/2;
    }

  int a = 0;
  if (!active_r()) a = FL_INACTIVE;
  if (image_) {
#ifdef FLTK_2
    fl_color((f&FL_INACTIVE) ? fl_inactive(c) : c);
#endif
    image_->draw(idx, idy, iw, ih, a);
    //printf ("image = %d, %d, %d, %d\n", idx, idy, iw, ih);
  }

  if (label_ && *label_) {
#ifdef FLTK2
    fl_font(label_font(), label_size());
    //if (flags() & FL_SHORTCUT_LABEL) fl_draw_shortcut = 1;
    //printf ("label = %d, %d, %d, %d\n", tdx, tdy, tw, th);
    label_type()->draw(label_, tdx, tdy, tw, th, c, a);
    //fl_draw_shortcut = 0;
#else
    fl_font(labelfont(), labelsize());
    Fl_Widget::draw_label (tdx, tdy, tw, th, (Fl_Align)a);
#endif
  }

}

static Fl_Pixmap* Stock_Button_Ok_Image = 0;

Fl_Stock_Button_Ok::Fl_Stock_Button_Ok(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "OK")
{
  if (!Stock_Button_Ok_Image)
    Stock_Button_Ok_Image = new Fl_Pixmap(stock_button_ok_xpm);
  image (Stock_Button_Ok_Image);
}

static Fl_Pixmap* Stock_Button_Cancel_Image = 0;

Fl_Stock_Button_Cancel::Fl_Stock_Button_Cancel(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "Cancel")
{
  if (!Stock_Button_Cancel_Image)
    Stock_Button_Cancel_Image = new Fl_Pixmap(stock_button_cancel_xpm);
  image (Stock_Button_Cancel_Image);
}

static Fl_Pixmap* Stock_Button_Yes_Image = 0;

Fl_Stock_Button_Yes::Fl_Stock_Button_Yes(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "Yes")
{
  if (!Stock_Button_Yes_Image)
    Stock_Button_Yes_Image = new Fl_Pixmap(stock_button_yes_xpm);
  image (Stock_Button_Yes_Image);
}

static Fl_Pixmap* Stock_Button_No_Image = 0;

Fl_Stock_Button_No::Fl_Stock_Button_No(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "No")
{
  if (!Stock_Button_No_Image)
    Stock_Button_No_Image = new Fl_Pixmap(stock_button_no_xpm);
  image (Stock_Button_No_Image);
}

static Fl_Pixmap* Stock_Button_Close_Image = 0;

Fl_Stock_Button_Close::Fl_Stock_Button_Close(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "Close")
{
  if (!Stock_Button_Close_Image)
    Stock_Button_Close_Image = new Fl_Pixmap(stock_button_close_xpm);
  image (Stock_Button_Close_Image);
}

static Fl_Pixmap* Stock_Button_Apply_Image = 0;

Fl_Stock_Button_Apply::Fl_Stock_Button_Apply(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "Apply")
{
  if (!Stock_Button_Apply_Image)
    Stock_Button_Apply_Image = new Fl_Pixmap(stock_button_apply_xpm);
  image (Stock_Button_Apply_Image);
}
