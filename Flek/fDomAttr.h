/* -*-C++-*- 

   "$Id: fDomAttr.h,v 1.2 2000/02/26 02:38:36 jamespalmer Exp $"
   
   Copyright 1999-2000 by the Flek development team.
   
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.
   
   You should have received a copy of the GNU Library General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA.
   
   Please report all bugs and problems to "flek-devel@sourceforge.net".

*/

#ifndef __FDOM_ATTR_H__
#define __FDOM_ATTR_H__

#include <Flek/fBase.h>

class fDomNode;
typedef fDomNode fDomElement;

/** @package libflek_dom
 * fDomAttr provides a class with a name-value pair.  Both the name and 
 * the value are strings.  Specialized subclasses may extend fDomAttr to 
 * provide more appropriate data structures.
 *
 * fDomAttr is the analog of <tt>Attr</tt> as defined in DOM L2.
 * fDomAttr includes virtual conversion methods as part of the class 
 * so that subclasses may provide more efficient and more appropriate
 * conversions.
 */
class fDomAttr : public fBase
{
 public:

  typedef fDomAttr* Ptr;

  /**
   * Default constructor.
   */
  fDomAttr ();

  /**
   * Copy constructor.
   */
  fDomAttr (const fDomAttr&);
  
  fBase::Ptr copy (void) const;

  virtual bool klass (char* k) { if (k==Klass) return true; return false; }
  static char* Klass;

  // DOM L2 Required Methods:

  virtual char* name () { return Name; }
  virtual void  name (char*);

  virtual char* value () { return Value; }
  virtual void  value (char*);

  /**
   * If this attribute was given a value in the original document or the
   * attribute is specified by the user the value is true.  If the value 
   * is unset and has an implied or default value given by the DTD, then
   * the value is false.  In order to flip the value from true to false
   * the attribute must be removed.
   */
  bool specified () { return Specified; }
  
  fDomElement* ownerElement () { return OwnerElement; }
  void ownerElement (fDomElement *o) { OwnerElement = o; }


  // XPath Conversion Methods:
  //
  // Within XPath there are 4 syntactic constructs:
  //
  // node-set (an unordered collection of nodes without duplicates) 
  // boolean (true or false) 
  // number (a floating-point number) 
  // string (a sequence of UCS characters) 
  //
  // All attributes should be convertable to the last three data
  // types.  XPath defines these as conversion functions, but fDom
  // defines these as virtual methods so that subclasses may implement 
  // the conversions efficiently for that subclass's data.
  //
  // http://www.w3.org/1999/07/WD-xpath-19990709#section-Introduction

  virtual double valueNumber ();
  virtual void   valueNumber (double);
  virtual bool   valueBoolean ();
  virtual void   valueBoolean (bool);

 protected:

  char*        Name;
  char*        Value; 
  fDomElement* OwnerElement;
  bool         Specified;
};

/**
 * fDomAttrNumber provides a class with key-value pairs.
 * While the key is a string, the value is a double.
 */
class fDomAttrNumber : public fDomAttr
{
 public:

  /**
   * Default constructor.
   */
  fDomAttrNumber ();

  /**
   * Copy constructor.
   */
  fDomAttrNumber (const fDomAttrNumber &n);

  fBase::Ptr copy (void) const;

  virtual bool klass (char *k) { if (k==Klass) return true; return fDomAttr::klass (k); }
  static char * Klass;

  char*  value ();
  void   value (char*);
  double valueNumber () { return Number; }
  void   valueNumber (double d) { Number = d; }
  bool   valueBoolean () { if (Number == 0) return false; return true; }
  void   valueBoolean (bool d) { if (d) Number = 1.0; else Number = 0; }

 protected:
  double Number;
};

/**
 * fDomAttrInteger provides a class with key-value pairs.
 * While the key is a string, the value is an integer.
 */
class fDomAttrInteger : public fDomAttr
{
 public:

  /**
   * Default constructor.
   */
  fDomAttrInteger ();

  /**
   * Copy constructor.
   */
  fDomAttrInteger (const fDomAttrInteger &);

  fBase::Ptr copy (void) const;

  virtual bool klass (char *k) { if (k==Klass) return true; return fDomAttr::klass (k); }
  static char * Klass;

  char*  value ();
  void   value (char*);
  double valueNumber () { return Number; }
  void   valueNumber (double d) { Number = (long)d; }
  bool   valueBoolean () { if (Number == 0) return false; return true; }
  void   valueBoolean (bool d) { if (d) Number = 1; else Number = 0; }
  long   valueInteger () { return Number; }
  void   valueInteger (long d) { Number = d; }

 protected:
  long Number;
};

#include <Flek/fDate.h>

/** 
 * This fDomAttr subclass provides a date attribute type.
 */
class fDomAttrDate : public fDomAttr
{
 public:

  /**
   * Default constructor.
   */
  fDomAttrDate ();

  /**
   * Copy constructor.
   */
  fDomAttrDate (const fDomAttrDate &);

  fBase::Ptr copy (void) const;

  virtual bool klass (char *k) { if (k==Klass) return true; return fDomAttr::klass (k); }
  static char * Klass;

  char*  value ();
  void   value (char*);
  double valueNumber ();
  void   valueNumber (double);
  bool   valueBoolean ();
  void   valueBoolean (bool);
  fDate  valueDate ();
  void   valueDate (const fDate &);

 protected:
  fDate Date;
};


#endif
