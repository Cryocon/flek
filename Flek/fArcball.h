#ifndef FARCBALL_H
#define FARCBALL_H

#include <Flek/fVector3.h>
#include <Flek/fQuaternion.h>

typedef enum AxisSet {NoAxes, CameraAxes, BodyAxes, OtherAxes, NSets} AxisSet;
typedef double *ConstraintSet;

class fArcball {
 public:
  fArcball ();
  void fArcball::place (fVector3 center, double radius);
  void fArcball::mouse (fVector3 vNow);
  void fArcball::useSet (AxisSet axisSet);
  void fArcball::showResult ();
  void fArcball::hideResult ();
  void fArcball::update ();
  fMatrix4x4 fArcball::value ();
  void fArcball::beginDrag ();
  void fArcball::endDrag ();
  void fArcball::draw ();
  
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
  void fArcball::drawAnyArc (fVector3 vFrom, fVector3 vTo);
  void fArcball::drawHalfArc (fVector3 n);
  void fArcball::drawConstraints ();
  void fArcball::drawDragArc ();
  void fArcball::drawResultArc ();
  
  fVector3 mouseOnSphere (fVector3 mouse, fVector3 ballCenter, double ballRadius);
  fVector3 constrainToAxis (fVector3 loose, fVector3 axis);
  int nearestConstraintAxis (fVector3 loose, fVector3 *axes, int nAxes);
  fQuaternion quatFromBallPoints (fVector3 from, fVector3 to);
  void quatToBallPoints (fQuaternion q, fVector3 *arcFrom, fVector3 *arcTo);
};

#endif
