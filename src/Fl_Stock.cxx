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

#include "stock_add.xpm"
#include "stock_bottom.xpm"
#include "stock_top.xpm"
#include "stock_clear.xpm"
#include "stock_down_arrow.xpm"
#include "stock_up_arrow.xpm"
#include "stock_left_arrow.xpm"
#include "stock_right_arrow.xpm"
#include "stock_remove.xpm"
#include "stock_open.xpm"
#include "stock_new.xpm"

#include "stock_copy.xpm"
#include "stock_cut.xpm"
#include "stock_exec.xpm"
#include "stock_first.xpm"
#include "stock_help.xpm"
#include "stock_last.xpm"
#include "stock_save.xpm"
#include "stock_save_as.xpm"
#include "stock_search.xpm"
#include "stock_search_replace.xpm"

Fl_Stock_Button::Fl_Stock_Button (int x, int y, int w, int h, const char *l) : 
  Fl_Button (x, y, w, h, l)
{
  // Scheme this :
#ifdef FLTK_2
  label_size (10);
#else
  labelsize (10);
#endif
  color (52);
  box (FL_FLAT_BOX);
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
  printf ("Drawing with flags == %d\n", f);
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
      printf("align top\n");
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
#ifdef FLTK_2
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


static Fl_Pixmap* Stock_Button_Add_Image = 0;

Fl_Stock_Button_Add::Fl_Stock_Button_Add(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "Add")
{
  if (!Stock_Button_Add_Image)
    Stock_Button_Add_Image = new Fl_Pixmap(stock_add_xpm);
  image (Stock_Button_Add_Image);
  set_flag (FL_TEXT_ALIGN_BOTTOM);
}

static Fl_Pixmap* Stock_Button_Bottom_Image = 0;

Fl_Stock_Button_Bottom::Fl_Stock_Button_Bottom(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "Bottom")
{
  if (!Stock_Button_Bottom_Image)
    Stock_Button_Bottom_Image = new Fl_Pixmap(stock_bottom_xpm);
  image (Stock_Button_Bottom_Image);
  set_flag (FL_TEXT_ALIGN_BOTTOM);
}

static Fl_Pixmap* Stock_Button_Clear_Image = 0;

Fl_Stock_Button_Clear::Fl_Stock_Button_Clear(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "Clear")
{
  if (!Stock_Button_Clear_Image)
    Stock_Button_Clear_Image = new Fl_Pixmap(stock_clear_xpm);
  image (Stock_Button_Clear_Image);
  set_flag (FL_TEXT_ALIGN_BOTTOM);
}

static Fl_Pixmap* Stock_Button_Down_Image = 0;

Fl_Stock_Button_Down::Fl_Stock_Button_Down(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "Down")
{
  if (!Stock_Button_Down_Image)
    Stock_Button_Down_Image = new Fl_Pixmap(stock_down_arrow_xpm);
  image (Stock_Button_Down_Image);
  set_flag (FL_TEXT_ALIGN_BOTTOM);
}

static Fl_Pixmap* Stock_Button_Up_Image = 0;

Fl_Stock_Button_Up::Fl_Stock_Button_Up(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "Up")
{
  if (!Stock_Button_Up_Image)
    Stock_Button_Up_Image = new Fl_Pixmap(stock_up_arrow_xpm);
  image (Stock_Button_Up_Image);
  set_flag (FL_TEXT_ALIGN_BOTTOM);
}

static Fl_Pixmap* Stock_Button_Left_Image = 0;

Fl_Stock_Button_Left::Fl_Stock_Button_Left(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "Left")
{
  if (!Stock_Button_Left_Image)
    Stock_Button_Left_Image = new Fl_Pixmap(stock_left_arrow_xpm);
  image (Stock_Button_Left_Image);
  set_flag (FL_TEXT_ALIGN_BOTTOM);
}

static Fl_Pixmap* Stock_Button_Right_Image = 0;

Fl_Stock_Button_Right::Fl_Stock_Button_Right(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "Right")
{
  if (!Stock_Button_Right_Image)
    Stock_Button_Right_Image = new Fl_Pixmap(stock_right_arrow_xpm);
  image (Stock_Button_Right_Image);
  set_flag (FL_TEXT_ALIGN_BOTTOM);
}

static Fl_Pixmap* Stock_Button_Previous_Image = 0;

Fl_Stock_Button_Previous::Fl_Stock_Button_Previous(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "Previous")
{
  if (!Stock_Button_Previous_Image)
    Stock_Button_Previous_Image = new Fl_Pixmap(stock_left_arrow_xpm);
  image (Stock_Button_Previous_Image);
  set_flag (FL_TEXT_ALIGN_BOTTOM);
}

static Fl_Pixmap* Stock_Button_Next_Image = 0;

Fl_Stock_Button_Next::Fl_Stock_Button_Next(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "Next")
{
  if (!Stock_Button_Next_Image)
    Stock_Button_Next_Image = new Fl_Pixmap(stock_right_arrow_xpm);
  image (Stock_Button_Next_Image);
  set_flag (FL_TEXT_ALIGN_BOTTOM);
  printf ("Fl_Next flags = %d -- FL_ALIGN_BOTTOM = %d\n", flags(), FL_TEXT_ALIGN_BOTTOM);
}

static Fl_Pixmap* Stock_Button_New_Image = 0;

Fl_Stock_Button_New::Fl_Stock_Button_New(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "New")
{
  if (!Stock_Button_New_Image)
    Stock_Button_New_Image = new Fl_Pixmap(stock_new_xpm);
  image (Stock_Button_New_Image);
  set_flag (FL_TEXT_ALIGN_BOTTOM);
}

static Fl_Pixmap* Stock_Button_Open_Image = 0;

Fl_Stock_Button_Open::Fl_Stock_Button_Open(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "Open")
{
  if (!Stock_Button_Open_Image)
    Stock_Button_Open_Image = new Fl_Pixmap(stock_open_xpm);
  image (Stock_Button_Open_Image);
  set_flag (FL_TEXT_ALIGN_BOTTOM);
}

static Fl_Pixmap* Stock_Button_Remove_Image = 0;

Fl_Stock_Button_Remove::Fl_Stock_Button_Remove(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "Remove")
{
  if (!Stock_Button_Remove_Image)
    Stock_Button_Remove_Image = new Fl_Pixmap(stock_remove_xpm);
  image (Stock_Button_Remove_Image);
  set_flag (FL_TEXT_ALIGN_BOTTOM);
}

static Fl_Pixmap* Stock_Button_Top_Image = 0;

Fl_Stock_Button_Top::Fl_Stock_Button_Top(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "Top")
{
  if (!Stock_Button_Top_Image)
    Stock_Button_Top_Image = new Fl_Pixmap(stock_top_xpm);
  image (Stock_Button_Top_Image);
  set_flag (FL_TEXT_ALIGN_BOTTOM);
}

static Fl_Pixmap* Stock_Button_Copy_Image = 0;

Fl_Stock_Button_Copy::Fl_Stock_Button_Copy(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "Copy")
{
  if (!Stock_Button_Copy_Image)
    Stock_Button_Copy_Image = new Fl_Pixmap(stock_copy_xpm);
  image (Stock_Button_Copy_Image);
  set_flag (FL_TEXT_ALIGN_BOTTOM);
}

static Fl_Pixmap* Stock_Button_Cut_Image = 0;

Fl_Stock_Button_Cut::Fl_Stock_Button_Cut(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "Cut")
{
  if (!Stock_Button_Cut_Image)
    Stock_Button_Cut_Image = new Fl_Pixmap(stock_cut_xpm);
  image (Stock_Button_Cut_Image);
  set_flag (FL_TEXT_ALIGN_BOTTOM);
}

static Fl_Pixmap* Stock_Button_Exec_Image = 0;

Fl_Stock_Button_Exec::Fl_Stock_Button_Exec(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "Exec")
{
  if (!Stock_Button_Exec_Image)
    Stock_Button_Exec_Image = new Fl_Pixmap(stock_exec_xpm);
  image (Stock_Button_Exec_Image);
  set_flag (FL_TEXT_ALIGN_BOTTOM);
}

static Fl_Pixmap* Stock_Button_First_Image = 0;

Fl_Stock_Button_First::Fl_Stock_Button_First(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "First")
{
  if (!Stock_Button_First_Image)
    Stock_Button_First_Image = new Fl_Pixmap(stock_first_xpm);
  image (Stock_Button_First_Image);
  set_flag (FL_TEXT_ALIGN_BOTTOM);
}

static Fl_Pixmap* Stock_Button_Help_Image = 0;

Fl_Stock_Button_Help::Fl_Stock_Button_Help(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "Help")
{
  if (!Stock_Button_Help_Image)
    Stock_Button_Help_Image = new Fl_Pixmap(stock_help_xpm);
  image (Stock_Button_Help_Image);
  set_flag (FL_TEXT_ALIGN_BOTTOM);
}

static Fl_Pixmap* Stock_Button_Last_Image = 0;

Fl_Stock_Button_Last::Fl_Stock_Button_Last(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "Last")
{
  if (!Stock_Button_Last_Image)
    Stock_Button_Last_Image = new Fl_Pixmap(stock_last_xpm);
  image (Stock_Button_Last_Image);
  set_flag (FL_TEXT_ALIGN_BOTTOM);
}

static Fl_Pixmap* Stock_Button_Save_Image = 0;

Fl_Stock_Button_Save::Fl_Stock_Button_Save(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "Save")
{
  if (!Stock_Button_Save_Image)
    Stock_Button_Save_Image = new Fl_Pixmap(stock_save_xpm);
  image (Stock_Button_Save_Image);
  set_flag (FL_TEXT_ALIGN_BOTTOM);
}

static Fl_Pixmap* Stock_Button_Save_As_Image = 0;

Fl_Stock_Button_Save_As::Fl_Stock_Button_Save_As(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "Save_As")
{
  if (!Stock_Button_Save_As_Image)
    Stock_Button_Save_As_Image = new Fl_Pixmap(stock_save_as_xpm);
  image (Stock_Button_Save_As_Image);
  set_flag (FL_TEXT_ALIGN_BOTTOM);
}

static Fl_Pixmap* Stock_Button_Search_Image = 0;

Fl_Stock_Button_Search::Fl_Stock_Button_Search(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "Search")
{
  if (!Stock_Button_Search_Image)
    Stock_Button_Search_Image = new Fl_Pixmap(stock_search_xpm);
  image (Stock_Button_Search_Image);
  set_flag (FL_TEXT_ALIGN_BOTTOM);
}

static Fl_Pixmap* Stock_Button_Search_Replace_Image = 0;

Fl_Stock_Button_Search_Replace::Fl_Stock_Button_Search_Replace(int x, int y, int w, int h, 
				       const char *l) : 
  Fl_Stock_Button (x, y, w, h, "Search_Replace")
{
  if (!Stock_Button_Search_Replace_Image)
    Stock_Button_Search_Replace_Image = new Fl_Pixmap(stock_search_replace_xpm);
  image (Stock_Button_Search_Replace_Image);
  set_flag (FL_TEXT_ALIGN_BOTTOM);
}
