#include <Flek/FXml.H>
#include <string.h>

void main () {
  
  FXmlDocument doc = FXmlDocument::parse_file ("fxml.xml");
  FXmlNode node = doc.children ();

  if (doc.valid ())
    if (doc.name ())
      printf ("doc name=%s\n", doc.name ());

  node = node.children ();

  while (node.valid ())
    {
      if (!strcmp (node.name (), "transaction"))
	{
	  printf ("node name=%s\n", node.name ());
	  FXmlAttr attribute = node.properties ();
	  
	  while (attribute.valid ())
	    {
	      FXmlNode property = attribute.value ();
	      if (property.valid ())
		printf ("property=%s\n", property.content ());
	      attribute = attribute.next ();
	    }
	}
      node = node.next ();
    }
}
