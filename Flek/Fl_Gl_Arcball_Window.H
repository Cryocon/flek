#include <FL/Fl_Gl_Window.h>
#include <Flek/fArcball.h>

class Fl_Gl_Arcball_Window : public Fl_Gl_Window
{
public:
  Fl_Gl_Arcball_Window(int x, int y, int w, int h, const char *l=0) :
     Fl_Gl_Window (x, y, w, h, l) 
     {
       arcball.place (origin_, radius_);
     }
  void arcball_draw ();
  void arcball_transform ();
  int handle(int event);
  void origin (fVector3 o) { origin_ = o; arcball.place (origin_, radius_); }
  fVector3 origin () { return origin_; }
  void radius (double o) { radius_ = o; arcball.place (origin_, radius_); }
  double radius () { return radius_; }
protected:
  fArcball arcball;
  fVector3 origin_;
  double radius_;
private:
  fVector3 drag;
};

