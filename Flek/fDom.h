#include <Flek/fBase.h>
#include <Flek/fList.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

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

  int open (const char *filename, const char *mode)
    {
      fh = fopen (filename, mode);
      if (fh)
	return 1;
      return 0;
    }

  int close ()
    {
      return fclose (fh);
    }

  int read ()
    {
      int rc;

      rc = fread (&ch, 1, 1, fh);

      if (rc==0)
	Eof = 1;

      if (feof (fh))
	Eof = 1;

      if (ch == '\n') 
	linecnt++;

      printf ("#: %c\n", ch);

      return rc;
    }

  int eof ()
    {
      return Eof;
    }

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

  int skipSpace ()
    {
      int rc = 1;
      
      // Skip whitespace
      while (isSpace () && (rc = read ())) { }
     
      // Return if there is nothing to be read.
      if (!rc)
	return 0;

      if (ch == '>')
	return END_OF_PAIRED_TAG;
      
      if (ch == '/')
	{
	  ch = ' ';
	  // Skip whitespace
	  while (isSpace () && (rc = read ())) { }
	  if (ch == '>')
	    return END_OF_UNPAIRED_TAG;
	  return PARSE_ERROR;
	}
      return 0;
    }

  int readKey (char *key)
    {
      int rc = 1, i = 0;
      key[i] = ch;
      while ((ch != '=') && (!isSpace ()) && (rc = read ())) { i++; key[i] = ch; }
      key[i] = 0;
      return (!rc);
    }

  int readQuote (char *value)
    {
      int rc = 0, i = 0;
      char quote = ch;
      ch = ' ';
      while ((ch != quote) && (rc = read ())) { value[i] = ch; i++; }
      if (!rc)
	return (!rc);
      if (i>0) 
	value[i-1] = 0;
      else
	value[0] = 0;
      rc = read ();
      return (!rc);
    }

  int readValue (char *value)
    {
      int rc, i = 0;
      value[i] = ch;
      while ((ch != '>') && (ch != '/') && (!isSpace ()) && (rc = read ())) { i++; value[i] = ch; }
      value[i] = 0;

      rc = skipSpace ();
      if (!rc)
	return (!rc);
      return 0;
    }

  int readText (char *text)
    {
      int rc, i = 0;
      text[i] = ch;
      while ((ch != '<') && (ch != '>') && (rc = read ())) 
	{ i++; text[i] = ch; }
      text[i] = 0;
    }

  int readAttribute (char *key, char *value)
    {
      int rc;
      key[0] = 0;
      value[0] = 0;
      
      rc = skipSpace ();
      if (rc)
	return rc;

      rc = readKey (key);

      if (rc)
	return rc;

      printf ("KEY=\"%s\"\n", key);

      rc = skipSpace ();
      if (rc)
	return rc;

      if (ch != '=')
	return 0; // A key without a value!!

      ch = ' '; // Pretend = was just white space.

      rc = skipSpace ();
      printf ("Skipped =..\n");

      if (rc)
	return rc;

      if (isQuote ())
	rc = readQuote (value);
      else
	rc = readValue (value);

      printf ("VALUE=\"%s\"\n", value);

      return 0;
    }

  int readTag (char *tag)
    {
      int rc = 0;
      printf ("BEGIN: readTag ();\n");
      rc = skipSpace ();
      if (ch != '<')
	return PARSE_ERROR;
      
      ch = ' ';
      rc = 0;
      read (); // ch = ' '; skipSpace ();
      if (ch == '/')
	{
	  ch = ' ';
	  rc = skipSpace ();
	  if (rc)
	    return PARSE_ERROR;
	  rc = END_TAG;
	}
      else if (rc)
	return PARSE_ERROR;
      else rc = BEGIN_TAG;

      int i = 0;
      tag[i] = ch;
      while ((ch != '>') && (ch != '/') && (!isSpace ()) && (read ())) 
	{ i++; tag[i] = ch; }
      tag[i] = 0;

      return rc;
    }

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

class fDomNode : public fBase 
{
 public:

  typedef fDomNode * Ptr;

  fDomNode ()
    {
    }

  fDomNode (const fDomNode & n) : fBase (n)
    {
      // Add children..
      Children = n.Children;
      // Add attributes..
      Attributes = n.Attributes;
      // Add listeners..
      Listeners = n.Listeners;
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
  
  
  /**
   * One can override this function to stick attributes wherever you like.
   */
  virtual void xmlPushAttribute (char *key, char *value)
    {
      fDomAttribute attribute;

      attribute.key = key;
      attribute.value = value;
      printf ("PUSHING ATTRIBUTES : (%s, %s)\n", key, value);
      Attributes.push_back (&attribute);
    }
    
  // Attribute functions
  int xmlReadAttributes (xmlFile &xml) 
    {
      char key[128];
      char value[128];
      int rc = 0;
      
      printf ("!! Beginning of Attributes\n");
      while (!(rc = xml.readAttribute (key, value))) 
	{
	  xmlPushAttribute (key, value);
	}
      printf ("!! End of Attributes\n");
      return rc;
    }

  /** 
   * Override this function to deal with the text in between tags
   * in a non-default manner.
   */
  virtual int xmlPushText (xmlFile &xml);
  
  int xmlRead (char *filename)
    {
      xmlFile xml;
      xml.open (filename, "r");
      return xmlRead (xml);
    }

  int xmlRead (xmlFile &xml)
    {
      int rc = 0;
      char tag[128];

      xml.ch = ' ';
      // Reset the current value.
      while (!(xml.eof ()))
	{
	  printf ("WHILE... %c\n", xml.ch);

	  // Clean up after last tag..
	  if (xml.ch == '>') 
	    xml.ch = ' ';

	  rc = xml.skipSpace ();

	  if (xml.ch == '<')
	    {
	      rc = xml.readTag (tag);
	      printf ("TAG=\"%s\"\n", tag);
	      if (rc == xmlFile::END_TAG)
		{
		  printf ("END OF TAG!\n");
		  return rc;
		}
	      xmlPushTag (xml, tag);
	    }
	  else
	    {
	      // If it's not tagged it gets shoved into a text node
	      xmlPushText (xml);
	    }
	}
      return 0;
    }

  int xmlPushTag (xmlFile &xml, char *tag);
  
  virtual void writeAttributes () 
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

  virtual void setAttribute (char *key, char *value)
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

  virtual char * getAttribute (char *key) 
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
      return (new fDomNode (*this));
    }

  // Child functions
  void add  (fDomNode *child) { Children.push_back (child); }

  virtual void writeChildren () 
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

  virtual void write ()
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

class fDomTextNode : public fDomNode
{
 public:
  fDomTextNode () { Text = 0; }
  fDomTextNode (const fDomTextNode & n) : fDomNode (n)
    {
      Text = strdup (n.Text);
    }

  char * name () { return "__text__"; }

  void write ()
    {
      printf (Text);
      printf ("\n");
    }

  void text (char *t) { if (Text) free (Text); Text = strdup (t); }
  char *text () { return Text; }

  fBase::Ptr copy (void) const
    {
      return (new fDomTextNode (*this));
    }

 protected:
  char *Text;
};

class fDomDynamicNode : public fDomNode
{
 public:
  fDomDynamicNode () { Name = 0; }
  fDomDynamicNode (const fDomDynamicNode & n) : fDomNode (n)
    {
      Name = strdup (n.Name);
    }
  char * name () { return Name; }
  void name (char *n) { if (Name) free (Name); Name = strdup (n); }

  fBase::Ptr copy (void) const
    {
      return (new fDomDynamicNode (*this));
    }

 protected:
  char *Name;
};

static void trim_left (char *text)
{
  int j = 0;
  int first = 1;
  for (unsigned int i=0; i<strlen(text); i++)
    {
      text[j] = text[i];
      if (!isspace (text[i]))
	first = 0;

      if (!first) j++;
    }
}

static void trim_right (char *text)
{
  for (int i=strlen(text)-1; i>=0; i--)
    {
      if (isspace (text[i])) text[i] = 0;
      else return;
    }
}

static void trim (char *text)
{
  trim_right (text);
  trim_left (text);
}

int fDomNode::xmlPushText (xmlFile &xml)
{
  char text[1024];
  
  xml.readText (text);
  
  trim (text);

  if (strlen (text) > 0)
    {
      fDomTextNode t;
      t.text (text);
      Children.push_back (&t);
    }
}

int fDomNode::xmlPushTag (xmlFile &xml, char *tag)
{
  int rc;
  fDomDynamicNode t;
  // Use a node with a static tag if available, otherwise use a dynamic tag.
  t.name (tag);
  Children.push_back (&t);

  rc = ((fDomDynamicNode *)(Children.back ()))->xmlReadAttributes (xml);
  if (rc == xmlFile::END_OF_UNPAIRED_TAG)
    return rc;

  ((fDomDynamicNode *)(Children.back ()))->xmlRead (xml);
}

