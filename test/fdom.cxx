#include <Flek/fDom.h>
#include <stdio.h>

int listen (fDomNode *node, long event, long)
{
  if (event == fDomNode::DAMAGE)
    {
      fDomAttr *n = node->getAttribute ("name");
      printf ("Ahhk.  Data was changed: %s\n", n->value ());
    }
  return 1;
}

fDomNode root, a, b, c, n;

void main ()
{
  vector<fDomNode*> documents;

  printf ("sizeof (fDomAttr) = %d\n", sizeof(fDomAttr));
  printf ("sizeof (fDomAttrNumber) = %d\n", sizeof(fDomAttrNumber));
  printf ("sizeof (fDomAttrInteger) = %d\n", sizeof(fDomAttrInteger));
  printf ("sizeof (fDomNode) = %d\n", sizeof(fDomNode));
  printf ("sizeof (fDomDynamicNode) = %d\n", sizeof(fDomDynamicNode));
  printf ("sizeof (list) = %d\n", sizeof(vector<fDomNode*>));
  
  root.setAttribute ("name", "Document");

  a.setAttribute ("name", "First field");
  b.setAttribute ("name", "Second field");
  c.setAttribute ("name", "Third field");

  printf ("1: %s\n", (a.getAttribute ("name"))->value ());
  printf ("2: %s\n", (b.getAttribute ("name"))->value ());
  printf ("3: %s\n", (c.getAttribute ("name"))->value ());

  fDomListener L (listen);
  a.addListener (&L);
  b.addListener (&L);
  c.addListener (&L);
  b.setAttribute ("name", "Another field");
  b.setAttribute ("name", "Yet Another field");

  root.add (&a);
  root.add (&b);
  root.add (&c);
  
  documents.push_back (&root);
  ((fDomNode *)(documents.back ()))->write ();
  n.xmlRead ("fdom.xml");
  n.write ();
}


/*
// You wouldn't want to attach listeners to every node in a large
// database so you can have class listeners by overriding handleListeners ().


// Reading options from a raytracing file:

<viza::sphere R="33.322">
  <viza::name>First Sphere<viza::name/>
</viza::sphere>

class uSphere : public fDomNode 
{
 public:

  *
   * These two procedures provide access to the data:
   *
  double radius () const { return Radius; }
  void radius (double R) 
    {
      Radius = R;
      damage ();  // Notify listeners!
    }

  *
   * This method reads attributes for this object.
   *
  void readAttributes (FDOMF *f, char *attribute)
    {
      if (!strcmp (attribute, "R"))
	readDouble (f, Radius);
      else
	fDomNode::readAttributes (f, attribute)
    }

  * 
   * This method writes attributes for this object.
   *
  void writeAttributes (FDOMF *f)
    {
      writeDouble (f, "R", Radius);
      fDomNode::writeAttributes (f);
    }

  *
   * This method writes any children to the file.
   *
  void writeChildren (FDOMF *f)
    {
      writeStringNode (f, "name", name);
      fDomNode::writeChildren (f);
    }

  void readChild (FDOMF *f, char *tag)
    {
      if (!strcmp(tag, "name"))
	{
	  name = readStringNode (f, "name");
	  damage ();
	}
      else
	fDomNode::readChild (f, tag);
    }

 protected:

  double Radius;
  char *name;
};

void main ()
{
  fDomDocument *document = new fDomDocument ("config.xml");

  for (fNode *i = document->children (); i != 0; i = i->next ())
    {
      if (strcmp (i->namespace (), "viza"))
	{
	  printf (STDERR, "unrecognized namespace: %s\n", i->namespace ());
	  continue;
	}
      if (strcmp (i->name (), "sphere"))
	{
	  printf (STDERR, "unrecognized primitive: %s\n", i->name ());
	  continue;
	}
      
      // It really is a sphere!!
      uSphere *j = (uSphere *)i;
      printf ("The radius of your sphere is %d.\n", i->radius ());
    }
}
*/
