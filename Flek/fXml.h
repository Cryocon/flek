/* -*-C++-*- 

   "$Id: fXml.h,v 1.1 2000/04/07 17:11:25 jamespalmer Exp $"
   
   Copyright 1999-2000 by the Flek development team.
   
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.
   
   You should have received a copy of the GNU Library General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA.
   
   Please report all bugs and problems to "flek-devel@sourceforge.net".

*/

#ifndef _FXML_H__
#define _FXML_H__

#include <gnome-xml/parser.h>

typedef enum {
  fXmlElementNode = XML_ELEMENT_NODE,
  fXmlAttributeNode = XML_ATTRIBUTE_NODE,
  fXmlTextNode = XML_TEXT_NODE,
  fXmlCDataSectionNode = XML_CDATA_SECTION_NODE,
  fXmlEntityRefNode = XML_ENTITY_REF_NODE,
  fXmlEntityNode = XML_ENTITY_NODE,
  fXmlPiNode = XML_PI_NODE,
  fXmlCommentNode = XML_COMMENT_NODE,
  fXmlDocumentNode = XML_DOCUMENT_NODE,
  fXmlDocumentTypeNode = XML_DOCUMENT_TYPE_NODE,
  fXmlDocumentFragNode = XML_DOCUMENT_FRAG_NODE,
  fXmlNotationNode = XML_NOTATION_NODE,
  fXmlHtmlDocumentNode = XML_HTML_DOCUMENT_NODE,
  fXmlDtdNode = XML_DTD_NODE,
  fXmlElementDecl = XML_ELEMENT_DECL,
  fXmlAttributeDecl = XML_ATTRIBUTE_DECL,
  fXmlEntityDecl = XML_ENTITY_DECL
} fXmlElementType;

typedef enum {
  fXmlAttributeCData = XML_ATTRIBUTE_CDATA,
  fXmlAttributeId = XML_ATTRIBUTE_ID,
  fXmlAttributeIdRef = XML_ATTRIBUTE_IDREF,
  fXmlAttributeIdRefs = XML_ATTRIBUTE_IDREFS,
  fXmlAttributeEntity = XML_ATTRIBUTE_ENTITY,
  fXmlAttributeEntities = XML_ATTRIBUTE_ENTITIES,
  fXmlAttributeNMToken = XML_ATTRIBUTE_NMTOKEN,
  fXmlAttributeNMTokens = XML_ATTRIBUTE_NMTOKENS,
  fXmlAttributeEnumeration = XML_ATTRIBUTE_ENUMERATION,
  fXmlAttributeNotation = XML_ATTRIBUTE_NOTATION
} fXmlAttributeType;

typedef enum {
  fXmlAttributeNone = XML_ATTRIBUTE_NONE,
  fXmlAttributeRequired = XML_ATTRIBUTE_REQUIRED,
  fXmlAttributeImplied = XML_ATTRIBUTE_IMPLIED,
  fXmlAttributeFixed = XML_ATTRIBUTE_FIXED
} fXmlAttributeDefault;

class fXmlDocument;
class fXmlNode;

class fXmlAttr {

 public:

  fXmlAttr () { Attr = 0; }
  fXmlAttr (xmlAttrPtr);
  bool valid () { if (Attr) return true; return false; }
  fXmlElementType type ();

  const char* name ();  
  fXmlNode children ();
  fXmlAttr next ();
  fXmlAttr previous ();
  fXmlNode parent ();
  fXmlNode last ();
  fXmlDocument document ();

  fXmlAttributeType atype ();
  //fXmlAttrDefault def ();
  //const char* defaultValue ();

  fXmlNode value ();

 protected:

  xmlAttrPtr Attr;

};

class fXmlNode {

 public:

  fXmlNode () { Node = 0; }
  fXmlNode (xmlNodePtr);
  bool valid () { if (Node) return true; return false; }
  fXmlElementType type ();

  const char* name ();  
  fXmlNode children ();
  fXmlNode next ();
  fXmlNode previous ();
  fXmlNode parent ();
  fXmlNode last ();
  fXmlDocument document ();
  // fXmlNs ns ();
  char* content ();  

  fXmlAttr properties ();
  char* property (const char* name);

  fXmlNode& operator = (const xmlNodePtr& p)
    {
      Node = p;
      return (*this);
    }

  fXmlNode& operator = (const fXmlNode& p)
    {
      Node = p.Node;
      return (*this);
    }
  
 protected:

  xmlNodePtr Node;

};

class fXmlDocument {

 public:

  fXmlDocument () { Doc = 0; }
  fXmlDocument (xmlDocPtr);
  bool valid () { if (Doc) return true; return false; }
  fXmlElementType type ();

  const char* name ();
  fXmlNode children ();
  fXmlNode next ();
  fXmlNode previous ();
  fXmlNode parent ();
  fXmlNode last ();
  fXmlDocument document ();

  // Basic parsing interface:
  static fXmlDocument parseFile (const char* filename);
  static fXmlDocument parseBuffer (const char* buffer, int size);

 protected:

  xmlDocPtr Doc;

};

#endif
