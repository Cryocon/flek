/***** Ball.c *****/
/* Ken Shoemake, 1993 */
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include <Flek/fArcball.h>

#define LG_NSEGS 4
#define NSEGS (1<<LG_NSEGS)
#define RIMCOLOR()    glColor3f(0.0, 1.0, 1.0)
#define FARCOLOR()    glColor3f(0.8, 0.5, 0.0)
#define NEARCOLOR()   glColor3f(1.0, 0.8, 0.0)
#define DRAGCOLOR()   glColor3f(0.0, 1.0, 1.0)
#define RESCOLOR()    glColor3f(0.8, 0.0, 0.0)

fMatrix4x4 mId; // = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
double otherAxis[][4] = {{-0.48, 0.80, 0.36, 1}};

/* Establish reasonable initial values for controller. */
fArcball::fArcball ()
{
  center.set (0, 0, 0);
  radius = 1.0;
  vDown.set (0, 0, 0);
  vNow.set (0, 0, 0); 
  qDown.set (0, 0, 0, 1);
  qNow.set (0, 0, 0, 1);
  mNow.identity ();
  mDown.identity ();
  mId.identity ();
  dragging = 0;
  ShowResult = 1;
  axisSet = NoAxes;

  sets[CameraAxes] = mId.get_row_array (0); //&(mId.value ())[0*4]; 
  setSizes[CameraAxes] = 3;

  sets[BodyAxes] = mDown.get_row_array (0); //&(mDown.value ())[0*4]; 
  setSizes[BodyAxes] = 3;
  
  sets[OtherAxes] = otherAxis[0]; 
  setSizes[OtherAxes] = 1;
}

/* Set the center and size of the controller. */
void 
fArcball::place (fVector3 center_, double radius_)
{
  center = center_;
  radius = radius_;
}

/* Incorporate new mouse position. */
void 
fArcball::mouse (fVector3 vNow_)
{
  vNow = vNow_;
}

/* Choose a constraint set, or none. */
void 
fArcball::useSet (AxisSet axisSet_)
{
  if (!dragging) axisSet = axisSet_;
}

/* Begin drawing arc for all drags combined. */
void 
fArcball::showResult ()
{
  ShowResult = 1;
}

/* Stop drawing arc for all drags combined. */
void 
fArcball::hideResult ()
{
  ShowResult = 0;
}

/* Using vDown, vNow, dragging, and axisSet, compute rotation etc. */
void 
fArcball::update ()
{
  int setSize = setSizes[axisSet];
  fVector3 *set = (fVector3 *)(sets[axisSet]);
  vFrom = mouseOnSphere(vDown, center, radius);
  vTo = mouseOnSphere(vNow, center, radius);
  if (dragging) {
    if (axisSet!=NoAxes) {
      vFrom = constrainToAxis(vFrom, set[axisIndex]);
      vTo = constrainToAxis(vTo, set[axisIndex]);
    }
    qDrag = quatFromBallPoints (vFrom, vTo);
    qNow = qDrag * qDown;
  } else {
    if (axisSet!=NoAxes) {
      axisIndex = nearestConstraintAxis(vTo, set, setSize);
    }
  }
  quatToBallPoints (qDown, &vrFrom, &vrTo);
  //quatToMatrix (qNow.conjugate (), mNow); /* Gives transpose for GL. */
  mNow = qNow.to_matrix (); //(qNow.conjugate ()).to_matrix ();
}

/* Return rotation matrix defined by controller use. */
fMatrix4x4 fArcball::value ()
{
  return mNow; 
}

/* Begin drag sequence. */
void fArcball::beginDrag ()
{
  dragging = 1;
  vDown = vNow;
}

/* Stop drag sequence. */
void 
fArcball::endDrag ()
{
  dragging = 0;
  qDown = qNow;
  mDown = mNow;  
}

/* Draw the controller with all its arcs. */
void 
fArcball::draw ()
{
  double r = radius;
  glMatrixMode (GL_PROJECTION);
  glPushMatrix ();
  glLoadIdentity ();
    {
      glOrtho (-1.0,1.0,-1.0,1.0,-1.0,1.0);
      glMatrixMode (GL_MODELVIEW);
      glPushMatrix ();
      glLoadIdentity ();
      glScaled (r, r, r);
      
      RIMCOLOR ();
      glBegin (GL_LINE_LOOP);
      for (int i=0; i < 36; i++)
	glVertex3f (cosf((float)i*2.0*M_PI/36.0),
		    sinf((float)i*2.0*M_PI/36.0),0.0);
      glEnd ();
      //glScalef (r, r, r);
      // FIXME!! 
      //circ (0.0, 0.0, 0.0);
      drawResultArc ();
      drawConstraints ();
      drawDragArc ();
    }
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}

/* Draw an arc defined by its ends. (static) */
void 
fArcball::drawAnyArc (fVector3 vFrom, fVector3 vTo)
{
  int i;
  fVector3 pts[NSEGS+1];
  double dot;
  pts[0] = vFrom;
  pts[1] = pts[NSEGS] = vTo;
  for (i=0; i<LG_NSEGS; i++) 
    pts[1] = fVector3::bisect (pts[0], pts[1]);
  
  dot = 2.0 * (pts[0] * pts[1]); // dot product
  for (i=2; i<NSEGS; i++)
    pts[i] = (pts[i-1] * dot) - pts[i-2];

  glBegin (GL_LINE_STRIP);
    {
      for (i=0; i<=NSEGS; i++)
	glVertex3dv(pts[i].value ());
    }
  glEnd ();
}

/* Draw the arc of a semi-circle defined by its axis. (static) */
void 
fArcball::drawHalfArc (fVector3 n)
{
  fVector3 p, m;
  p[2] = 0;
  if (n[2] != 1.0) {
    p[0] = n[1]; p[1] = -n[0];
    p.normalize();
  } else {
    p[0] = 0; p[1] = 1;
  }
  m = p % n;
  drawAnyArc (p, m);
  drawAnyArc (m, -p);
}

/* Draw all constraint arcs. */
void 
fArcball::drawConstraints ()
{
  ConstraintSet set;
  fVector3 axis;
  int axisI, setSize = setSizes[axisSet];
  if (axisSet==NoAxes) return;
  set = sets[axisSet];
  for (axisI=0; axisI<setSize; axisI++) {
    if (axisIndex!=axisI) {
      if (dragging) continue;
      FARCOLOR();
    } else NEARCOLOR();
    axis = *(fVector3 *)&set[4*axisI];
    if (axis[2] == 1.0) {
      glBegin (GL_LINE_LOOP);
      for (int i=0; i < 36; i++)
	glVertex3f (cosf((float)i*2.0*M_PI/36.0),
		    sinf((float)i*2.0*M_PI/36.0),0.0);
      glEnd ();
    } else {
      drawHalfArc (axis);
    }
  }
}

/* Draw "rubber band" arc during dragging. */
void 
fArcball::drawDragArc ()
{
  DRAGCOLOR();
  if (dragging) 
    drawAnyArc (vFrom, vTo);
}

/* Draw arc for result of all drags. */
void 
fArcball::drawResultArc ()
{
  RESCOLOR();
  if (ShowResult) 
    drawAnyArc (vrFrom, vrTo);
}


/**** BallMath.c - Essential routines for fArcball.  ****/

/* Convert window coordinates to sphere coordinates. */
fVector3 
fArcball::mouseOnSphere(fVector3 mouse, fVector3 ballCenter, double ballRadius)
{
  fVector3 ballMouse;
  register double mag;
  ballMouse[0] = (mouse[0] - ballCenter[0]) / ballRadius;
  ballMouse[1] = (mouse[1] - ballCenter[1]) / ballRadius;
  mag = ballMouse[0]*ballMouse[0] + ballMouse[1]*ballMouse[1];
  if (mag > 1.0) {
    register double scale = 1.0/sqrt(mag);
    ballMouse[0] *= scale; ballMouse[1] *= scale;
    ballMouse[2] = 0.0;
  } else {
    ballMouse[2] = sqrt(1 - mag);
  }
  //ballMouse[3] = 0.0;
  return (ballMouse);
}

/* Construct a unit quaternion from two points on unit sphere */
fQuaternion 
fArcball::quatFromBallPoints(fVector3 from, fVector3 to)
{
  fQuaternion qu;
  qu[0] = from[1]*to[2] - from[2]*to[1];
  qu[1] = from[2]*to[0] - from[0]*to[2];
  qu[2] = from[0]*to[1] - from[1]*to[0];
  qu[3] = from[0]*to[0] + from[1]*to[1] + from[2]*to[2];
  return (qu);
}

/* Convert a unit quaternion to two points on unit sphere */
void 
fArcball::quatToBallPoints(fQuaternion q, fVector3 *arcFrom, fVector3 *arcTo)
{
  double s;
  s = sqrt(q[0]*q[0] + q[1]*q[1]);
  if (s == 0.0) {
    *arcFrom = fVector3 (0.0, 1.0, 0.0);
  } else {
    *arcFrom = fVector3 (-q[1]/s, q[0]/s, 0.0);
  }
  (*arcTo)[0] = q[3]*(*arcFrom)[0] - q[2]*(*arcFrom)[1];
  (*arcTo)[1] = q[3]*(*arcFrom)[1] + q[2]*(*arcFrom)[0];
  (*arcTo)[2] = q[0]*(*arcFrom)[1] - q[1]*(*arcFrom)[0];
  if (q[3] < 0.0) *arcFrom = fVector3 (-(*arcFrom)[0], -(*arcFrom)[1], 0.0);
}

/* Force sphere point to be perpendicular to axis. */
fVector3 
fArcball::constrainToAxis (fVector3 loose, fVector3 axis)
{
  fVector3 onPlane;
  register float norm;
  onPlane = loose - (axis * (axis * loose));
  norm = onPlane.norm ();
  if (norm > 0.0) {
    if (onPlane[2] < 0.0) onPlane = -onPlane;
    return onPlane * (1/sqrt(norm));
  }
  if (axis[2] == 1) {
    onPlane = fVector3 (1.0, 0.0, 0.0);
  } else {
    fVector3 tmp (-axis[1], axis[0], 0.0);
    tmp.normalize ();
    onPlane = tmp;
  }
  return (onPlane);
}

/* Find the index of nearest arc of axis set. */
int 
fArcball::nearestConstraintAxis(fVector3 loose, fVector3 *axes, int nAxes)
{
  fVector3 onPlane;
  register float max, dot;
  register int i, nearest;
  max = -1; 
  nearest = 0;
  for (i=0; i<nAxes; i++) {
    onPlane = constrainToAxis (loose, axes[i]);
    dot = onPlane * loose;
    if (dot > max) {
      max = dot; 
      nearest = i;
    }
  }
  return (nearest);
}
