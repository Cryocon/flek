#include <Flek/FXml.H>

// FXmlNode

FXmlNode::FXmlNode (xmlNodePtr p)
{
  Node = p;
}

FXmlElementType FXmlNode::type () 
{ 
  return ((FXmlElementType) Node->type); 
}

FXmlDocument FXmlNode::document () 
{ 
  return FXmlDocument (Node->doc); 
}

FXmlNode FXmlNode::children () 
{ 
  return FXmlNode (Node->children); 
}

FXmlNode FXmlNode::next () 
{ 
  return FXmlNode (Node->next); 
}

FXmlNode FXmlNode::previous () 
{ 
  return FXmlNode (Node->prev); 
}

FXmlNode FXmlNode::last () 
{ 
  return FXmlNode (Node->last); 
}

FXmlNode FXmlNode::parent () 
{ 
  return FXmlNode (Node->parent); 
}

FXmlAttr FXmlNode::properties () 
{ 
  return FXmlAttr (Node->properties); 
}

/**
 * Caller must free the memory.
 */
char* FXmlNode::property (const char *name) 
{ 
  return (char *)xmlGetProp (Node, (const xmlChar *)name);
}

/*
FXmlNs FXmlNode::ns ()
{
  return FXmlNs (Node->ns);
}
*/

char* FXmlNode::content ()
{
  return (char *)Node->content;
}

const char* FXmlNode::name ()
{
  return (const char*)Node->name;
}

// FXmlDocument

FXmlDocument::FXmlDocument (xmlDocPtr p)
{
  Doc = p;
}

FXmlElementType FXmlDocument::type () 
{ 
  return ((FXmlElementType) Doc->type); 
}

FXmlDocument FXmlDocument::document () 
{ 
  return FXmlDocument (Doc->doc); 
}

FXmlNode FXmlDocument::children () 
{ 
  return FXmlNode (Doc->children); 
}

FXmlNode FXmlDocument::next () 
{ 
  return FXmlNode (Doc->next); 
}

FXmlNode FXmlDocument::previous () 
{ 
  return FXmlNode (Doc->prev); 
}

FXmlNode FXmlDocument::last () 
{ 
  return FXmlNode (Doc->last); 
}

FXmlNode FXmlDocument::parent () 
{ 
  return FXmlNode (Doc->parent); 
}

const char* FXmlDocument::name ()
{
  return (const char*)Doc->name;
}

FXmlDocument FXmlDocument::parse_file (const char* filename)
{
  return (FXmlDocument (xmlParseFile (filename)));
}

FXmlDocument FXmlDocument::parse_buffer (const char* buffer, int size)
{
  return (FXmlDocument (xmlParseMemory ((char *)buffer, size)));
}

// FXmlAttr

FXmlAttr::FXmlAttr (xmlAttrPtr p)
{
  Attr = p;
}

FXmlElementType FXmlAttr::type () 
{ 
  return ((FXmlElementType) Attr->type); 
}

FXmlAttributeType FXmlAttr::atype () 
{ 
  return ((FXmlAttributeType) Attr->atype); 
}

/*
FXmlAttrDefault FXmlAttr::def () 
{ 
  return ((FXmlAttrDefault) Attr->def); 
}
*/

FXmlDocument FXmlAttr::document () 
{ 
  return FXmlDocument (Attr->doc); 
}

FXmlNode FXmlAttr::children () 
{ 
  return FXmlNode (Attr->children); 
}

FXmlAttr FXmlAttr::next () 
{ 
  return FXmlAttr (Attr->next); 
}

FXmlAttr FXmlAttr::previous () 
{ 
  return FXmlAttr (Attr->prev); 
}

FXmlNode FXmlAttr::last () 
{ 
  return FXmlNode (Attr->last); 
}

FXmlNode FXmlAttr::parent () 
{ 
  return FXmlNode (Attr->parent); 
}

const char* FXmlAttr::name ()
{
  return (const char*)Attr->name;
}

FXmlNode FXmlAttr::value ()
{
  return FXmlNode (Attr->children);
}
