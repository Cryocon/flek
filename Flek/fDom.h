
class fString : public fBase {

 protected:
  char *data;
};

// Listener is a function that fNode can register.
typedef fDomListener int (f*)(int);

// Listener enumerations:

enum {
  fDOM_DAMAGE,       // Data in node has changed.
  fDOM_CONNECT,      // Connect listener to data.
  fDOM_DISCONNECT    // Disconnect listener to data.
};

enum {
  fDOM_NODE,
  fDOM_GROUP,
};

class fDomNode : public fBase {
 public:

  int type () { return fDOM_NODE; }

  // Listener functions:
  void addListener (fDomListener);
  void removeListener (fDomListener);
  void clearListeners ();

  virtual handleListeners ();

 protected:

  fDomNode* Children[];
  char* Attributes[];

  /*
  fNodeList Child;
  fStringList Attribute;

  ((fString *)Child[3])->data ();
  */
};

// You wouldn't want to attach listeners to every node in a large
// database so you can have class listeners by overriding handleListeners ().


// Reading options from a raytracing file:

<viza::sphere R="33.322">
  <viza::name>First Sphere<viza::name/>
</viza::sphere>

class uSphere : public fDomNode 
{
 public:

  /*
   * These two procedures provide access to the data:
   */
  double radius () const { return Radius; }
  void radius (double R) 
    {
      Radius = R;
      damage ();  // Notify listeners!
    }

  /*
   * This method reads attributes for this object.
   */
  void readAttributes (FDOMF *f, char *attribute)
    {
      if (!strcmp (attribute, "R"))
	readDouble (f, Radius);
      else
	fDomNode::readAttributes (f, attribute)
    }

  /* 
   * This method writes attributes for this object.
   */
  void writeAttributes (FDOMF *f)
    {
      writeDouble (f, "R", Radius);
      fDomNode::writeAttributes (f);
    }

  /*
   * This method writes any children to the file.
   */
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
