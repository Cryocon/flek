#include <Flek/Fl_Better_Window.H>
#include <FL/x.H>

// get_window_borders by "Jason Ertel" <jertel@simulation.com>

int Fl_Better_Window::get_window_borders (Fl_Window *win, int &left, int &right, int &top, int &bottom) 
{ 
#ifdef _WIN32 
  RECT myRect; 
  int result; 
  
  result = GetWindowRect(fl_xid(win), &myRect); 
  left = win->x() - myRect.left; 
  right = myRect.right - (win->x() + win->w()); 
  top = win->y() - myRect.top; 
  bottom = myRect.bottom - (win->y() + win->h()); 
  
  return result; 
#else 
  Window root, parent, *children, current; 
  unsigned int childrenCount; 
  XWindowAttributes attrs; 
  int status = 1; 
  
  current = fl_xid (win); 
  
  while (status) 
    { 
      status = XQueryTree(fl_display, current, &root, &parent, &children, &childrenCount); 
      if (parent == root) 
	break; 
      current = parent; 
    }
  if (status) 
    { 
      XGetWindowAttributes(fl_display, current, &attrs); 
      left = win->x() - attrs.x; 
      right = attrs.width - win->w() - left; 
      top = win->y() - attrs.y; 
      bottom = attrs.height - win->h() - top; 
      return 1; 
    } 
  else 
    { 
      left = 0; 
      right = 0; 
      top = 0; 
      bottom = 0; 
      return 0; 
    } 
#endif 
}

