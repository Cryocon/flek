#ifndef Fl_Tree_H
#define Fl_Tree_H

#include <FL/fl_draw.H>
#include <FL/Fl_Scroll.H>

#include <Flek/Fl_Toggle_Node_Base.H>

#define FL_DAMAGE_TREE 0x40

enum sort_order {
  NORMAL_SORT = 0,
  REVERSE_SORT = 1
};

class Fl_Toggle_Tree_Base : public Fl_Widget {

public:

  Fl_Toggle_Tree_Base (int x, int y, int w, int h);

  Fl_Toggle_Node_Base* first(void) {
    return first_;
  }

  Fl_Toggle_Node_Base* find(int fy, int& depth, int& ry);

  void traverse_start(Fl_Toggle_Node_Base * a);
  Fl_Toggle_Node_Base * traverse_start();
  void traverse_up (void);
  Fl_Toggle_Node_Base * traverse_forward(int visible, int &depth);
  Fl_Toggle_Node_Base * traverse_forward();
  Fl_Toggle_Node_Base * traverse_backward();

  void add_next (Fl_Toggle_Node_Base* node);
  void add_sub (Fl_Toggle_Node_Base* node);
  int remove (Fl_Toggle_Node_Base * a);
  int clear();

  virtual void draw(void);
  void update_height(void);

  int open(Fl_Toggle_Node_Base* node);
  int close(Fl_Toggle_Node_Base* node);

  Fl_Toggle_Node_Base* top() {
    return top_;
  }
protected:

  Fl_Toggle_Node_Base* first_;
  Fl_Toggle_Node_Base* top_;
  Fl_Toggle_Node_Base* t_current_;
  Fl_Toggle_Node_Base* current_;

  int top_depth_;
  int top_yoffset_;

  Fl_Toggle_Node_Base* damaged_;

  virtual int height(Fl_Toggle_Node_Base* node);
  int height_(Fl_Toggle_Node_Base* node) {
    return height(node) | 1;
    // height must be |1 , so Fl_ToggleTree can do color-swapping
    // with &1 on y coordinate
  }
  int total_height(Fl_Toggle_Node_Base* node);
  void update_top(void);
  virtual void draw_node(int depth, int cy, Fl_Toggle_Node_Base* node);
  virtual int handle(int) { return 1; }

  Fl_Toggle_Node_Base* sort_( Fl_Toggle_Node_Base* start,
                  int (*compar)(Fl_Toggle_Node_Base *, Fl_Toggle_Node_Base *),
                  int down, sort_order order = NORMAL_SORT);

public:
  static int s_compare_(void* a, void *b);
  static int s_compare_reverse_(void* a, void *b);

  Fl_Toggle_Node_Base* sort(Fl_Toggle_Node_Base* start, int (*compar)(Fl_Toggle_Node_Base *, Fl_Toggle_Node_Base *),
                sort_order order = NORMAL_SORT);
  Fl_Toggle_Node_Base* sort_tree(Fl_Toggle_Node_Base* start, int (*compar)(Fl_Toggle_Node_Base *, Fl_Toggle_Node_Base *),
                     sort_order order = NORMAL_SORT);

  void sort(int (*compar)(Fl_Toggle_Node_Base *, Fl_Toggle_Node_Base *),
            sort_order order = NORMAL_SORT);
  void sort_tree(int (*compar)(Fl_Toggle_Node_Base *, Fl_Toggle_Node_Base *),
                 sort_order order = NORMAL_SORT);
};

#endif
