#ifndef FARCBALL_H
#define FARCBALL_H

#include <Flek/fVector3.h>
#include <Flek/fQuaternion.h>

typedef enum AxisSet {NoAxes, CameraAxes, BodyAxes, OtherAxes, NSets} AxisSet;
typedef double *ConstraintSet;

class fArcball {
 public:
  fArcball ();
  void place (fVector3 center, double radius);
  void mouse (fVector3 vNow);
  void use_set (AxisSet set) { if (!dragging) axisSet = set; }
  void show_result () { ShowResult = 1; }
  void hide_result () { ShowResult = 0; }
  void update ();
  fMatrix4x4 value () { return mNow; }
  void begin_drag ();
  void end_drag ();
  void draw ();
  
 protected:
  fVector3 center;
  double radius;
  fQuaternion qNow, qDown, qDrag;
  fVector3 vNow, vDown, vFrom, vTo, vrFrom, vrTo;
  fMatrix4x4 mNow, mDown;
  short ShowResult, dragging;
  ConstraintSet sets[NSets];
  int setSizes[NSets];
  AxisSet axisSet;
  int axisIndex;
  
 private:
  void draw_any_arc (fVector3 vFrom, fVector3 vTo);
  void draw_half_arc (fVector3 n);
  void draw_constraints ();
  void draw_drag_arc ();
  void draw_result_arc ();
  
  fVector3 mouse_on_sphere (fVector3 mouse, fVector3 ballCenter, double ballRadius);
  fVector3 constrain_to_axis (fVector3 loose, fVector3 axis);
  int nearest_constraint_axis (fVector3 loose, fVector3 *axes, int nAxes);
  fQuaternion quaternion_from_ball_points (fVector3 from, fVector3 to);
  void quaternion_to_ball_points (fQuaternion q, fVector3 *arcFrom, fVector3 *arcTo);
};

#endif
