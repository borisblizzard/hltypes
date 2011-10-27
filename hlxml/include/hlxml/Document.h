/// @file
/// @author  Kresimir Spes
/// @author  Boris Mikic
/// @version 1.3
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://www.opensource.org/licenses/bsd-license.php
/// 
/// @section DESCRIPTION
/// 
/// Represents an XML document.

#ifndef HLXML_DOCUMENT_H
#define HLXML_DOCUMENT_H


#ifdef USE_TINYXML
#include <tinyxml.h>
#define _xmlAttr TiXmlAttribute
#else
#include <libxml/xmlmemory.h>
#endif

#include <hltypes/hstring.h>

#include "hlxmlExport.h"

namespace hlxml
{
	struct Node;


#ifdef USE_TINYXML
	struct hlxmlExport Document : public TiXmlDocument
#else
	struct hlxmlExport Document
#endif
	{
	public:
		Document(chstr filename);
		~Document();
		Node* root(chstr rootElementQuery = "");
	
	protected:
#ifdef USE_TINYXML
		TiXmlDocument* xmlDocument;
#else
		xmlDocPtr xmlDocument;
#endif
		Node* rootNode;
	
	};

}

#endif