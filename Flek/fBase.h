// $Id: fBase.h,v 1.3 2000/02/08 20:22:52 jamespalmer Exp $

#ifndef FBASE_H_
#define FBASE_H_

/** @package libflek_ui (The Flek User Interface Library)
 * fBase is the Abstract base class for all f classes.  The fBase
 * class can be used to build container classes which use object 
 * pointers.  The same container class can then be used with any
 * derived classes without the need of any additional code or templates.
 *
 * fBase has no member data.  It only has protected constructors (to 
 * prevent instantiation), virtual destructors and an assignment operator.
 */
class fBase
{
public:

  typedef fBase * Ptr;

  /**
   * Empty assignment operator.
   */
  fBase& operator = (const fBase&)
    {
      return *this;
    }

  /**
   * Virtual destructor.
   */
  virtual ~fBase()
    {}

  /**
   * Derived class should give a meaningful implementation
   * for the following functions.
   *
   * Classes such as List which use fBase pointers
   * will use these functions, for memory management
   * 
   * Make a copy of the fBase and return a pointer to the new one.
   */
  virtual Ptr copy(void) const = 0;

protected:
  
  /**
   * The default constructor is protected to prevent instantiation,
   */
  fBase ()
    {}

  /** 
   * The copy constructor is protected to prevent instantiation.
   */
  fBase (const fBase&)
    {}
};

#endif // #ifndef FBASE_H_

