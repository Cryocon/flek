#include <Flek/fBase.h>
#include <Flek/fList.h>
#include <string.h>
#include <stdlib.h>

class fDomNode;

class fDomListener : public fBase
{
 public:

  typedef fDomListener * Ptr;
  
  typedef int (*Function)(fDomNode *, long, long);
  
  fDomListener (Function f) { F = f; }

  int listen (fDomNode *node, long message, long argument)
    {
      return (F)(node, message, argument);
    }

  void set (Function f) { F = f; }
  
  Function get () { return F; }
  
  fBase::Ptr copy (void) const
    {
      return (fBase::Ptr) new fDomListener (F);
    }

 protected:

  Function F;

};

class fDomAttribute : public fBase
{
 public:

  fDomAttribute () 
    {
      key = 0;
      value = 0;
    }

  typedef fDomAttribute * Ptr;

  fBase::Ptr copy (void) const
    {
      Ptr o = new fDomAttribute;
      o->key = strdup (key);
      o->value = strdup (value);
      return o;
    }

  char *key;
  char *value; 

};

class fDomNode : public fBase 
{
 public:

  typedef fDomNode * Ptr;

  fDomNode ()
    {
    }

  int type () { return 1; }

  virtual char * name () { return "node"; }

  enum {
    DAMAGE = 1,
    CONNECT = 2,
    DISCONNECT = 3
  };

  // Listener functions:
  void addListener (fDomListener *o)
    { Listeners.push_back (o); }

  void removeListener (fDomListener *o)
    { Listeners.erase (o); }

  void clearListeners ()
    { Listeners.erase (); }

  void damage (long dmg)
    { handleListeners (DAMAGE, dmg); }

  virtual void handleListeners (int event, long argument)
    {
      fIterator p, last;
      fDomListener *q;
      last = Listeners.end ();
      for (p = Listeners.begin (); p != last; p++)
	{
	  q = (fDomListener *)(*p);
	  q->listen (this, event, argument);
	}
    }

  // Attribute functions
  void readAttributes () {}
  void writeAttributes () 
    {
      fIterator p, last;
      fDomAttribute *att;

      last = Attributes.end ();
      for (p = Attributes.begin (); p != last; p++)
	{
	  att = ((fDomAttribute *)(*p));
	  // Need code to escape special characters and quotes..
	  printf ("%s=\"%s\" ", att->key, att->value);
	}      
    }

  void setAttribute (char *key, char *value)
    {
      fIterator p, last;
      fDomAttribute *att;
      int set = 0;
      last = Attributes.end ();
      for (p = Attributes.begin (); p != last; p++)
	{
	  att = ((fDomAttribute *)(*p));
	  if (!strcmp (att->key, key))
	    {
	      free (att->value);
	      att->value = strdup (value);
	      set = 1;
	    }
	}
      if (!set)
	{
	  att = new fDomAttribute;
	  att->key = strdup (key);
	  att->value = strdup (value);
	  Attributes.push_back (att);
	}
      damage (0);
    }

  char * getAttribute (char *key) 
    {
      fIterator p, last;
      fDomAttribute *att;
      last = Attributes.end ();
      for (p = Attributes.begin (); p != last; p++)
	{
	  att = ((fDomAttribute *)(*p));
	  if (!strcmp (att->key, key))
	    {
	      return att->value;
	    }
	}
      return 0;
    }

  fBase::Ptr copy (void) const
    {
      Ptr o = new fDomNode;
      // Add children..
      o->Children = Children;
      // Add attributes..
      o->Attributes = Attributes;
      // Add listeners..
      o->Listeners = Listeners;
      return o;
    }

  // Child functions
  void add  (fDomNode *child) { Children.push_back (child); }
  void writeChildren () 
    {
      fIterator p, last;
      fDomNode *node;
      last = Children.end ();
      for (p = Children.begin (); p != last; p++)
	{
	  node = ((fDomNode *)(*p));
	  node->write ();
	}
    }

  void write ()
    {
      printf ("<%s", name ());
      if (Attributes.size () > 0)
	{
	  printf (" ");
	  writeAttributes ();
	}
      if (Children.size () == 0)
	printf ("/>\n");
      else
	{
	  printf (">\n");
	  writeChildren ();
	  printf ("</%s>\n", name ());
	}
    }

 protected:

  fList Children;    // A list of fDomNodes.
  fList Attributes;  // A list of strings.
  fList Listeners;   // A list of listener functions.

};


