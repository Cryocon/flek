#ifndef FL_PACK_2_H_
#define FL_PACK_2_H_

#include <FL/Fl_Group.H>

class Fl_Pack_Fu : public Fl_Group
{
  int spacing_;

public:
  enum { // values for type(int)
    VERTICAL = 0,
    HORIZONTAL = 1
  };
  
  Fl_Pack_Fu (int x, int y, int w, int h, const char *l = 0);

  void pack ();
  void draw ();
  int spacing () const { return spacing_; }
  void spacing (int i) { spacing_ = i; }
  uchar horizontal () const { return type(); }
};

#endif
