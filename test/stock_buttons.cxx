#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include <Flek/Fl_Stock.H>

#include <stdio.h>

void
main ()
{
  Fl_Window *W = new Fl_Window (358, 100, "Stock Buttons Demo");
  
  (void) new Fl_Stock_Button_Ok (10, 10, 108, 28);
  (void) new Fl_Stock_Button_Cancel (125, 10, 108, 28);
  (void) new Fl_Stock_Button_Apply (240, 10, 108, 28);
  (void) new Fl_Stock_Button_Yes (10, 55, 108, 28);
  (void) new Fl_Stock_Button_No (125, 55, 108, 28);
  (void) new Fl_Stock_Button_Close (240, 55, 108, 28);

  W->show ();

  Fl::run();  
}

 
