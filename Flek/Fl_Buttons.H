
// This will work for Fltk 2.0:

class Fl_Okay_Button : public Fl_Button
{
  public:
  Fl_Okay_Button (int x, int y, int w, int h, char *l = "Okay") :
  Fl_Button (x, y, w, h, l) 
  {
    align (FL_ALIGN_WRAP);
    image (Okay_Pixmap); // new Fl_Pixmap(okay_xpm));
  }
}

