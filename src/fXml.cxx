#include <Flek/fXml.h>

// fXmlNode

fXmlNode::fXmlNode (xmlNodePtr p)
{
  Node = p;
}

fXmlElementType fXmlNode::type () 
{ 
  return ((fXmlElementType) Node->type); 
}

fXmlDocument fXmlNode::document () 
{ 
  return fXmlDocument (Node->doc); 
}

fXmlNode fXmlNode::children () 
{ 
  return fXmlNode (Node->children); 
}

fXmlNode fXmlNode::next () 
{ 
  return fXmlNode (Node->next); 
}

fXmlNode fXmlNode::previous () 
{ 
  return fXmlNode (Node->prev); 
}

fXmlNode fXmlNode::last () 
{ 
  return fXmlNode (Node->last); 
}

fXmlNode fXmlNode::parent () 
{ 
  return fXmlNode (Node->parent); 
}

fXmlAttr fXmlNode::properties () 
{ 
  return fXmlAttr (Node->properties); 
}

/**
 * Caller must free the memory.
 */
char* fXmlNode::property (const char *name) 
{ 
  return (char *)xmlGetProp (Node, (const xmlChar *)name);
}

/*
fXmlNs fXmlNode::ns ()
{
  return fXmlNs (Node->ns);
}
*/

char* fXmlNode::content ()
{
  return (char *)Node->content;
}

const char* fXmlNode::name ()
{
  return (const char*)Node->name;
}

// fXmlDocument

fXmlDocument::fXmlDocument (xmlDocPtr p)
{
  Doc = p;
}

fXmlElementType fXmlDocument::type () 
{ 
  return ((fXmlElementType) Doc->type); 
}

fXmlDocument fXmlDocument::document () 
{ 
  return fXmlDocument (Doc->doc); 
}

fXmlNode fXmlDocument::children () 
{ 
  return fXmlNode (Doc->children); 
}

fXmlNode fXmlDocument::next () 
{ 
  return fXmlNode (Doc->next); 
}

fXmlNode fXmlDocument::previous () 
{ 
  return fXmlNode (Doc->prev); 
}

fXmlNode fXmlDocument::last () 
{ 
  return fXmlNode (Doc->last); 
}

fXmlNode fXmlDocument::parent () 
{ 
  return fXmlNode (Doc->parent); 
}

const char* fXmlDocument::name ()
{
  return (const char*)Doc->name;
}

fXmlDocument fXmlDocument::parseFile (const char* filename)
{
  return (fXmlDocument (xmlParseFile (filename)));
}

fXmlDocument fXmlDocument::parseBuffer (const char* buffer, int size)
{
  return (fXmlDocument (xmlParseMemory ((char *)buffer, size)));
}

// fXmlAttr

fXmlAttr::fXmlAttr (xmlAttrPtr p)
{
  Attr = p;
}

fXmlElementType fXmlAttr::type () 
{ 
  return ((fXmlElementType) Attr->type); 
}

fXmlAttributeType fXmlAttr::atype () 
{ 
  return ((fXmlAttributeType) Attr->atype); 
}

/*
fXmlAttrDefault fXmlAttr::def () 
{ 
  return ((fXmlAttrDefault) Attr->def); 
}
*/

fXmlDocument fXmlAttr::document () 
{ 
  return fXmlDocument (Attr->doc); 
}

fXmlNode fXmlAttr::children () 
{ 
  return fXmlNode (Attr->children); 
}

fXmlAttr fXmlAttr::next () 
{ 
  return fXmlAttr (Attr->next); 
}

fXmlAttr fXmlAttr::previous () 
{ 
  return fXmlAttr (Attr->prev); 
}

fXmlNode fXmlAttr::last () 
{ 
  return fXmlNode (Attr->last); 
}

fXmlNode fXmlAttr::parent () 
{ 
  return fXmlNode (Attr->parent); 
}

const char* fXmlAttr::name ()
{
  return (const char*)Attr->name;
}

fXmlNode fXmlAttr::value ()
{
  return fXmlNode (Attr->children);
}
