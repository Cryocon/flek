/* -*-C++-*- 

   "$Id: fDom.h,v 1.11 2000/03/03 01:46:19 jamespalmer Exp $"
   
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

#ifndef _FDOM_H__
#define _FDOM_H__

#include <Flek/fBase.h>
#include <Flek/fDomAttr.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

//#include <ministl/vector>
#include <vector.h>

class fDomNode;

/** @package libflek_dom
 * The listener class is actually just a wrapper around a callback
 * function.  The callback function may be executed by whatever
 * fDomNode it gets connected to.
 */
class fDomListener : public fBase
{
 public:

  typedef fDomListener * Ptr;
  typedef vector<Ptr> Collection;
  
  typedef int (*Function)(fDomNode *, long, long);

  /**
   * The constructor takes the listener function as an argument.
   * The listener function must be of the form,
   * <br><pre>int function (fDomNode *n, long message, long argument);</pre>
   */
  fDomListener (Function f) { F = f; }

  /**
   * Invokes the listener function.
   */
  int listen (fDomNode *node, long message, long argument)
    {
      return (F)(node, message, argument);
    }

  /**
   * Sets the listener function.
   */
  void set (Function f) { F = f; }
 
  /**
   * Gets the listener function.
   */ 
  Function get () { return F; }
  
  fBase::Ptr copy (void) const { return (fBase::Ptr) new fDomListener (F); }

 protected:

  Function F;

};

/** 
 * xmlFile is a utility class used when parsing xml files.
 */
class xmlFile
{
 public:

  xmlFile () { Eof = 0; }
  
  enum 
  {
    DENADA=0,
    END_OF_PAIRED_TAG=1,
    END_OF_UNPAIRED_TAG=2,
    BEGIN_TAG=3,
    END_TAG=4,
    PARSE_ERROR=5
  };

  int open (const char *filename, const char *mode);

  int close ();

  int read ();

  int eof () { return Eof; }

  int isEndl ()
    {
      if (ch == '\n') return 1;
      return 0;
    }

  int isSpace ()
    {
      if (isspace (ch)) return 1;
      return 0;
    }

  int skipSpace ();

  int readKey (char *key);

  int readQuote (char *value);

  int readValue (char *value);

  int readText (char *text);

  int readAttribute (char *key, char *value);

  int readTag (char *tag);

  int isQuote ()
    {
      if ((ch == '"') || (ch == '\''))
	return 1;
      return 0;
    }

  char  ch;

 protected:
  FILE *fh;
  char *name;
  int  linecnt;
  int Eof;
};


/**
 * fDomNode is the base node type for fDom documents.
 */
class fDomNode : public fBase 
{
 public:

  typedef fDomNode * Ptr;
  typedef vector<Ptr> Collection;

  /**
   * Constructor.
   */
  fDomNode ()
    {
    }

  /**
   * Copy constructor.
   */
  fDomNode (const fDomNode & n) : fBase (n)
    {
      Children = n.Children;
      Attributes = n.Attributes;
      Listeners = n.Listeners;
    }

  /**
   * Returns the name or "type" of the node.  This is usually
   * defined on a per class level, and not per object instance.
   */
  virtual char * tagName () { return "node"; }

  enum {
    DAMAGE = 1,
    CONNECT = 2,
    DISCONNECT = 3
  };

  // Listener functions:

  /** 
   * Attach a listener to this node.
   */
  void addListener (fDomListener *o) { Listeners.push_back (o); }
  void addListener (fDomListener &o) { Listeners.push_back ((fDomListener *)o.copy ()); }

  /** 
   * Remove a listener from this node.
   */
  void removeListener (fDomListener *) { } //Listeners.erase (o); } FIXME

  /** 
   * Clear all listeners.
   */
  void clearListeners () { Listeners.clear (); }

  /**
   * Send a damage message to any listeners with the message,
   * dmg.
   */
  void damage (long dmg) { handleListeners (DAMAGE, dmg); }

  /**
   * Iterate through all listeners and invoke their listen
   * methods in turn with the given event and message.
   */
  virtual void handleListeners (int event, long argument);
  
  /**
   * Attributes are normally stored as strings in the Attributes list.
   * You can override this function to stick attributes wherever you like.
   */
  //virtual void xmlPushAttribute (char *key, char *value);
    
  // Attribute functions
  int xmlReadAttributes (xmlFile &xml);

  /** 
   * Override this function to deal with the text in between tags
   * in a non-default manner (stored in an fDomTextNode.)
   */
  virtual int xmlPushText (xmlFile &xml);

  /**
   * Read the xml file.
   */
  int xmlRead (char *filename)
    {
      xmlFile xml;
      xml.open (filename, "r");
      return xmlRead (xml);
    }

  int xmlRead (xmlFile &xml);

  /** 
   * Override this function to associate nodes with tags.
   */
  virtual fDomNode * nodeFromTag (char * tag);

  int xmlPushTag (xmlFile &xml, char *tag);
  
  virtual fDomAttr* newAttribute (char *key);

  virtual void writeAttributes ();

  /**
   * Set an attribute key to value.
   * Attributes are normally stored as strings in the Attributes list.
   * You can override this function to stick attributes wherever you like.
   */
  virtual void setAttribute (char *key, char *value);

  /** 
   * Get an attribute value from the key.
   */
  virtual fDomAttr* getAttribute (char *key);

  fBase::Ptr copy (void) const
    {
      return (new fDomNode (*this));
    }

  /**
   * Add a daughter node.
   */
  void add  (fDomNode *child) { Children.push_back (child); }
  void add  (fDomNode &child) { Children.push_back ((fDomNode *) child.copy ()); }

  /**
   * Write this node's children.
   */
  virtual void writeChildren ();

  /**
   * Write this node.
   */
  virtual void write ();

  const Collection & children () const { return Children; }
  const fDomAttr::Collection & attributes () const { return Attributes; }
  const fDomListener::Collection & listeners () const { return Listeners; }

 protected:

  Collection Children;
  fDomAttr::Collection Attributes;
  fDomListener::Collection Listeners;

};

/**
 * fDomTextNode provides a special kind of node that represents
 * a block of text with no markup symbols or child data.
 */

class fDomTextNode : public fDomNode
{
 public:
  fDomTextNode () { Text = 0; }
  fDomTextNode (const fDomTextNode & n) : fDomNode (n)
    {
      Text = strdup (n.Text);
    }

  char * tagName () { return "__text__"; }

  void write ()
    {
      printf (Text);
      printf ("\n");
    }

  /**
   * Sets the text block. 
   */
  void text (char *t) { if (Text) free (Text); Text = strdup (t); }

  /**
   * Gets the text block.
   */
  char *text () { return Text; }

  fBase::Ptr copy (void) const
   {
     return (new fDomTextNode (*this));
   }

 protected:
  char *Text;
};

/**
 * fDomDynamicNode is a special node designed to express 
 * any undefined node type.
 */
class fDomDynamicNode : public fDomNode
{
 public:
  fDomDynamicNode () { Name = 0; }
  fDomDynamicNode (const fDomDynamicNode & n) : fDomNode (n)
    {
      Name = strdup (n.Name);
    }

  /**
   * Gets the node name.
   */
  char * tagName () { return Name; }

  /** 
   * Sets the node name.
   */
  void tagName (char *n) { if (Name) free (Name); Name = strdup (n); }

  fBase::Ptr copy (void) const
    {
      return (new fDomDynamicNode (*this));
    }

 protected:
  char *Name;
};

#endif
