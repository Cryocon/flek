#include <FL/Fl.H>
#include <stdio.h>

#include <Flek/Fl_App_Window.H>
#include <FL/x.H>
#include <FL/fl_draw.H>

Fl_App_Window::Fl_App_Window(int x, int y, int w, int h, const char* l) : 
  Fl_Window (x, y, w, h, l), dockable_windows_size(0) {
  create_app_window(w, h, l);
}

Fl_App_Window::Fl_App_Window(int w, int h, const char* l) : 
  Fl_Window (w, h, l), dockable_windows_size(0) {
  create_app_window(w, h, l);
}

Fl_App_Window::~Fl_App_Window() {
  free (dockable_windows);
}

void Fl_App_Window::create_app_window(int w, int h, const char* l) {
  dockable_windows_capacity = 4;
  dockable_windows = (Fl_Dockable_Window**)malloc(sizeof(Fl_Dockable_Window*)*dockable_windows_capacity);

  // Create the pack that holds the contents window and docked windows.
  _pack = new Fl_Pack(0, 0, w, h, "Fl_App_Window::pack");
  _pack->type(Fl_Pack::VERTICAL);

  // Create the contents window.
  _contents = new Fl_Window(0, 0, w, h, "Fl_App_Window::contents");

  // Contents window and docked windows will complete obscure the toplevel window
  // and the pack area, so set them both to no box.
  Fl_Window::box(FL_NO_BOX);
  _pack->box(FL_NO_BOX);
}

int Fl_App_Window::handle (int event) {  
  if(event == FL_UNDOCK) {
    //_pack->draw ();
    //redraw();
    //if ((w() != _pack->w()) || (h() != pack->h()))
    //size (_pack->w(), pack->h());
    //damage (FL_DAMAGE_ALL);
    //size (w(), h() - Fl_Dockable_Window::current->h());
    _contents->size(_contents->w(), _contents->h() + Fl_Dockable_Window::current->h());
    redraw ();
    return 1;
  }
  
  if(event == FL_DOCK) {
    // Isn't it in this windows list of dockable widows?
    if(!may_dock(Fl_Dockable_Window::current))
      // Don't dock it.
      return 1;

    int dx = Fl::event_x_root ();
    int dy = Fl::event_y_root ();
    int ex = x_root ();
    int ey = y_root ();

    // printf ("Handling FL_DOCK event!!\n");
      
    // Check to see if we can dock along any of 
    // the pack boundaries.
      
    // This code should probably go into Pack_2's handle:
    Fl_Widget*const* a = _pack->array();
    for(int i=0; i <= _pack->children(); i++) {
      int cY;
	  
      if (i==_pack->children())
        cY = h();
      else {
        Fl_Widget* o = *a++;
        cY = o->y ();
      }
	  
      if((dx < (ex + FL_DOCK_DELTA + w()))      // xmax
         && (dx > (ex - FL_DOCK_DELTA))         // xmin 
         && (dy < (ey + FL_DOCK_DELTA + cY))    // ymax
         && (dy > (ey - FL_DOCK_DELTA + cY)) )  // ymin
	 {
	 // printf ("DOCK!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	 add_dockable(Fl_Dockable_Window::current, i);
	 return 1;
      }
    }
    return 0;
  }
  return Fl_Window::handle (event);
}

// Anything added to Fl_App should actually get 
// added to the contents group.

void Fl_App_Window::add (Fl_Widget *w) {
  //  w->position(w->x() + x(), w->y() + y());
  _contents->add(w);
}

bool Fl_App_Window::may_dock(Fl_Dockable_Window* W) {
  // Is the dockable window in the dockable_windows list?
  for(int i=0; i < dockable_windows_size; i++)
    if(dockable_windows[i] == W)
      return true;
  return false;
}

void Fl_App_Window::accept_dockable(Fl_Dockable_Window *W) {
  // Does this dockable window already have permission to dock?
  // In other words, is it already in the list?
  if(may_dock(W))
    // Already in the list, don't add it again.
    return;

  // Is there room left in the list?
  if(dockable_windows_size >= dockable_windows_capacity) {
    // Out of space.  That's okay.  We'll make more.
    dockable_windows_capacity *= 2;
    dockable_windows = (Fl_Dockable_Window**)realloc(dockable_windows,
      sizeof(Fl_Dockable_Window*)*dockable_windows_capacity);
  }
  
  // Add it to the list.
  dockable_windows[dockable_windows_size++] = W;
}

void Fl_App_Window::add_dockable(Fl_Dockable_Window *W, int pos) {
  // Add the dockable window to this window's list of dockable windows.
  accept_dockable(W);

  // Dock the dockable window on this window.
  Fl_Dockable_Window::current = W;
  Fl_Dockable_Window::current->hide();
  _pack->insert(*W, pos);
  W->set_docked(1);
  
  if(_pack->horizontal())
    // Fl_Dockable_Window::current->size(Fl_Dockable_Window::current->w(), h());
    _contents->size(w()-Fl_Dockable_Window::current->w(), h());
  else
    // Fl_Dockable_Window::current->size(w(), Fl_Dockable_Window::current->h());
    _contents->size(w(), h()-Fl_Dockable_Window::current->h());
  
  if(shown()) {
    Fl_Dockable_Window::current->show ();
    redraw();
  }
}

void Fl_App_Window::show() {
  Fl_Window::show();
  _pack->show();
  _contents->show();
  for(int i=0; i < dockable_windows_size; i++)
    dockable_windows[i]->show();
  redraw();
}

void Fl_App_Window::hide() {
  for(int i=0; i < dockable_windows_size; i++)
    dockable_windows[i]->hide();
  Fl_Window::hide();
}


void 
Fl_App_Window::draw() {
  //printf ("Fl_App_Window::draw()\n");
  // if _pack->w() and pack->h() change...
  _pack->draw();
  resize(x(), y(), _pack->w(), _pack->h());
  Fl_Window::draw ();
}

void Fl_App_Window::flush() {
  //Fl_Window::flush();
  //printf("Fl_App_Window::flush()\n");
  make_current();
  Fl_X *i = Fl_X::i(this);
  //if (damage() == FL_DAMAGE_EXPOSE && can_boxcheat(box())) fl_boxcheat = this;
  fl_clip_region(i->region); i->region = 0;
  draw ();
}

void Fl_App_Window::resize(int X, int Y, int W, int H) {
  int dw = W - w();
  int dh = H - h();
  int dx = X - x();
  int dy = Y - y();

  _pack->resize(0, 0, _pack->w() + dw, _pack->h());
  _contents->resize(_contents->x() + dx, _contents->y() + dy,
  _contents->w() + dw, _contents->h() + dh);
  Fl_Widget::resize(X, Y, W, H);
  redraw();
}
