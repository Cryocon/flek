#include <Flek/fDom.h>

//#define DEBUGJ


typedef vector<fBase *>::iterator fBaseIterator;

int xmlFile::open (const char *filename, const char *mode)
{
  fh = fopen (filename, mode);
  if (fh)
    return 1;
  return 0;
}

int xmlFile::close ()
{
  return fclose (fh);
}

int xmlFile::read ()
{
  int rc;
  
  rc = fread (&ch, 1, 1, fh);
  
  if (rc==0)
    Eof = 1;
  
  if (feof (fh))
    Eof = 1;
  
  if (ch == '\n') 
    linecnt++;
  
#ifdef DEBUGJ
  printf ("#: %c\n", ch);
#endif
  
  return rc;
}

int xmlFile::skipSpace ()
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

int xmlFile::readKey (char *key)
{
  int rc = 1, i = 0;
  key[i] = ch;
  while ((ch != '=') && (!isSpace ()) && (rc = read ())) { i++; key[i] = ch; }
  key[i] = 0;
  return (!rc);
}

int xmlFile::readQuote (char *value)
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

int xmlFile::readValue (char *value)
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

int xmlFile::readText (char *text)
{
  int rc = 1, i = 0;
  text[i] = ch;
  while ((ch != '<') && (ch != '>') && (rc = read ())) 
    { i++; text[i] = ch; }
  text[i] = 0;
  return rc;
}

int xmlFile::readAttribute (char *key, char *value)
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
  
#ifdef DEBUGJ
  printf ("read KEY=\"%s\"\n", key);
#endif

  rc = skipSpace ();
  if (rc)
    return rc;
  
  if (ch != '=')
    return 0; // A key without a value!!
  
  ch = ' '; // Pretend = was just white space.
  
  rc = skipSpace ();

#ifdef DEBUGJ
  printf ("read '='\n");
#endif  

  if (rc)
    return rc;
  
  if (isQuote ())
    rc = readQuote (value);
  else
    rc = readValue (value);
  
#ifdef DEBUGJ
  printf ("read VALUE=\"%s\"\n", value);
#endif

  return 0;
}

int xmlFile::readTag (char *tag)
{
  int rc = 0;

#ifdef DEBUGJ
  printf ("BEGIN: readTag ();\n");
#endif

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

void fDomNode::handleListeners (int event, long argument)
{
  fDomListener::Collection::iterator p;

  for (p = Listeners.begin (); p != Listeners.end (); p++)
    (*p)->listen (this, event, argument);
}  

/*void fDomNode::xmlPushAttribute (char *key, char *value)
{
  fDomAttribute *attribute = new fDomAttribute ();
  
  attribute->key = strdup (key);
  attribute->value = strdup (value);
  Attributes.push_back (attribute);
  }*/

int fDomNode::xmlReadAttributes (xmlFile &xml) 
{
  char key[128];
  char value[128];
  int rc = 0;
  
  while (!(rc = xml.readAttribute (key, value))) 
    setAttribute (key, value);
    //    xmlPushAttribute (key, value);

  return rc;
}

int fDomNode::xmlRead (xmlFile &xml)
{
  int rc = 0;
  char tag[128];
  
  xml.ch = ' ';
  // Reset the current value.
  while (!(xml.eof ()))
    {
#ifdef DEBUGJ
      printf ("<while loop> char= %c\n", xml.ch);
#endif
      
      // Clean up after last tag..
      if (xml.ch == '>') 
	xml.ch = ' ';
      
      rc = xml.skipSpace ();
      
      if (xml.ch == '<')
	{
	  rc = xml.readTag (tag);
#ifdef DEBUGJ
	  printf ("read TAG=\"%s\"\n", tag)
#endif
	  if (rc == xmlFile::END_TAG)
	    return rc;
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

void fDomNode::writeAttributes () 
{
  fDomAttr::Collection::iterator p;
  
  for (p = Attributes.begin (); p != Attributes.end (); p++)
    {
      // Need code to escape special characters and quotes..
      printf ("%s=\"%s\" ", (*p)->name (), (*p)->value ());
    }
}

fDomAttr * fDomNode::newAttribute (char *)
{
  return new fDomAttr ();
}

void fDomNode::setAttribute (char *key, char *value)
{
  fDomAttr::Collection::iterator p;
  int set = 0;

  for (p = Attributes.begin (); p != Attributes.end (); p++)
    {
      if (!strcmp ((*p)->name (), key ))
	{
	  (*p)->value (value);
	  set = 1;
	}
    }
  if (!set)
    {
      fDomAttr *new_attr = newAttribute (key);
      new_attr->name (key);
      new_attr->value (value);
      Attributes.push_back (new_attr);
    }
  damage (0);
}

fDomAttr * fDomNode::getAttribute (char *key) 
{
  fDomAttr::Collection::iterator p;

  for (p = Attributes.begin (); p != Attributes.end (); p++)
    {
      if (!strcmp ((*p)->name (), key))
	return *p;
    }
  return 0;
}

void fDomNode::writeChildren () 
{
  Collection::iterator p;

  for (p = Children.begin (); p != Children.end (); p++)
    (*p)->write ();
}

void fDomNode::write ()
{
  printf ("<%s ", tagName ());
  
  writeAttributes ();
  
  if (Children.size () == 0)
    printf ("/>\n");
  else
    {
      printf (">\n");
      writeChildren ();
      printf ("</%s>\n", tagName ());
    }
}

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
      fDomTextNode * t = new fDomTextNode();
      t->text (text);
      Children.push_back (t);
    }
  return 0;
}

fDomNode * fDomNode::nodeFromTag (char * tag)
{
  fDomDynamicNode *t = new fDomDynamicNode ();
  t->tagName (tag);
  return t;
}

int fDomNode::xmlPushTag (xmlFile &xml, char *tag)
{
  int rc;

  fDomNode *t = nodeFromTag (tag);

  // Use a node with a static tag if available, otherwise use a dynamic tag.
  Children.push_back (t);

  rc = ((fDomDynamicNode *)(Children.back ()))->xmlReadAttributes (xml);
  if (rc == xmlFile::END_OF_UNPAIRED_TAG)
    return rc;

  ((fDomDynamicNode *)(Children.back ()))->xmlRead (xml);
  return 0;
}

