#include <Flek/fXml.h>
#include <string.h>

void main ()
{
  fXmlDocument doc = fXmlDocument::parseFile ("fxml.xml");
  fXmlNode node = doc.children ();

  if (doc.valid ())
    if (doc.name ())
      printf ("doc name=%s\n", doc.name ());

  node = node.children ();

  while (node.valid ())
    {
      if (!strcmp (node.name (), "transaction"))
	{
	  printf ("node name=%s\n", node.name ());
	  fXmlAttr attribute = node.properties ();
	  
	  while (attribute.valid ())
	    {
	      fXmlNode property = attribute.value ();
	      if (property.valid ())
		printf ("property=%s\n", property.content ());
	      attribute = attribute.next ();
	    }
	}
      node = node.next ();
    }

}
