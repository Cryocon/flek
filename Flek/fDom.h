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

    fDomAttribute (char *k, char *v) 
    {
      key = strdup (k);
      value = strdup (v);
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

  int xmlSkipWS (char *c)
    {
      int rc = 1;
      
      // Skip whitespace
      while (is_ws (*c) && (rc = fread (c, 1, 1, f))) { }
     
      // Return if there is nothing to be read.
      if (!rc)
	return 0;

      if (*c == '>')
	return END_OF_PAIRED_TAG;
      
      if (*c == '/')
	{
	  // Skip whitespace
	  while (is_ws (c) && (rc = fread (c, 1, 1, f))) { }
	  if (*c == '>')
	    return END_OF_UNPAIRED_TAG;
	  return PARSE_ERROR;
	}
      return 0;
    }
  
  int xmlReadAttribute (char *curr, char *key, char *value)
    {
      int rc, i = 0;
      //char c = ' ';
      key[0] = 0;
      value[0] = 0;
      
      rc = xmlSkipWS (curr);
      if (rc)
	return rc;
      
      // Read the key name.
      key[i] = *curr;
      while ((*curr != '=') && not_ws (curr) && (rc = fread (curr, 1, 1, f))) { i++; key[i] = *curr; }
      key[i+1] = 0;
      
      // Skip the equals.
      rc = xmlSkipWS (curr);
      if (rc)
	return rc;
      
      if (*curr != '=')
	return 0;  // A Key without a value!!

      *curr = ' '; // Pretend '=' was just white space.
      
      rc = xmlSkipWS (curr);

      if ((*curr == '"') || (*curr == '\''))
	xmlReadQuote (curr, value);
      else
	{
	  // Read an unquoted value.  Not too Kosher?
	  i = 0;
	  value[i] = *curr;
	  while ((*curr != '>') && (*c != '/') && not_ws (curr) && (rc = fread (curr, 1, 1, f))) { i++; value[i] = *curr; }

	  rc = xmlSkipWS (curr);
	  if (rc)
	    return rc;
	}

      return 0;
    }
  
  /**
   * One can override this function to stick attributes wherever you like.
   */
  virtual void xmlPushAttribute (char *key, char *value)
    {
      fDomAttribute attribute;

      attribute.key = key;
      attribute.value = value;
      Attributes.push_back (attribute);
    }
    
  // Attribute functions
  void xmlReadAttributes (char *curr) 
    {
      char key[128];
      char value[128];
      int rc = 0;
      
      while (!(rc = xmlReadAttribute (curr, key, value))) 
	{
	  xmlPushAttribute (key, value);
	}
      return rc;
    }

  int xmlReadTag (char *curr)
    {
      int rc = 0;
      rc = xmlSkipWS (curr);
      if (*curr != '<')
	return PARSE_ERROR;
      
      curr = ' ';
      rc = xmlSkipWS (curr);
      
      if (curr == '/') 
	{
	  curr = ' ';
	  rc = xmlSkipWS (curr);
	  if (rc)
	    return PARSE_ERROR;
	  rc = ENDING_TAG;
	}
      else if (rc)
	return PARSE_ERROR;
      else rc = BEGINING_TAG;
      
	{
	  char tag[128];
	  int i = 0;
	  while ((*curr != '>') && (*c != '/') && not_ws (curr) && (rc = fread (curr, 1, 1, f))) { i++; tag[i] = *curr; }
	  tag[i+1] = 0;
	  xmlPushTag (curr, tag);
	}
      
      return rc;
    }

  
  char * xmlReadText (char *curr, char *text)
    {
      int i = 0;
      while ((*curr != '<') && (*c != '>') && (rc = fread (curr, 1, 1, f))) 
	{ i++; text[i] = *curr; }
    }

  /** 
   * Override this function to deal with the text in between tags
   * in a non-default manner.
   */
  int xmlPushText (char *curr)
    {
      char text[1024];
      fDomTextNode t;

      xmlReadText (curr, text);

      t.text (text);
      Children.push_back (t);
    }
  
  int xmlRead (char *curr)
    {
      int rc = 0;
      int endtag = 0;
      
      while (!end_tag)
	{
	  rc = xmlSkipWS (curr);

	  if (*curr == '<')
	    {
	      rc = xmlReadTag (curr);
	      if (rc == ENDING_TAG)
		return;
	      xmlPushTag (curr, tag);
	    }
	  else
	    {
	      // If it's not tagged it gets shoved into a text node
	      xmlPushText (curr);
	    }
	}
    }
  
  int xmlPushTag (char *curr, char *tag)
    {
      int rc;
      fDomNode t;
      // Use a node with a static tag if available, otherwise use a dynamic tag.
      t.name (tag);
      Children.push_back (t);
      rc = ((fDomNode *)(Children.back ()))->xmlReadAttributes (curr);
      if (rc == END_OF_UNPAIRED_TAG)
	return;
      ((fDomNode *)(Children.back ()))->xmlRead (curr);
    }
  
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


