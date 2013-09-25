/*
 *  Copyright 2006-2013 Jerome PASQUIER
 *
 *  This file is part of RainbruRPG.
 *
 *  RainbruRPG is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  RainbruRPG is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

/** \file curlfiletoxml.cpp
  * Implements a class that get a file from curl and pass it to TinyXml
  *
  */
#include "CurlFileToXml.hpp"

#include "tinyxml.h"

/** The default constructor
  *
  */
RainbruRPG::Network::Ident::CurlFileToXml::CurlFileToXml():
  doc(NULL)
{

}

/** The default destructor 
  *
  * \todo memory leaks test
  *
  */
RainbruRPG::Network::Ident::CurlFileToXml::~CurlFileToXml(){
  /*  if (doc)
    delete doc;

  doc=NULL;
  */
}

/** Perform the operation
  *
  * Simply calls the fileToxml() function.
  *
  * \return \c true if the operation is successfull, \c false if an
  *         error occured
  *
  */
bool RainbruRPG::Network::Ident::CurlFileToXml::perform(){
  return fileToxml();
}

/** Does nothing
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Network::Ident::CurlFileToXml::controlBefore (){
  // Nothing to do here
  return true;
}

/** Does nothing
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Network::Ident::CurlFileToXml::controlAfter (){
  // Nothing to do here
  return true;
}

/** Gets the TinyXML document
  *
  * \return A pointer to the TiXmlDocument instance
  *
  */
TiXmlDocument* RainbruRPG::Network::Ident::CurlFileToXml::getXmlDocument(){
  if (doc == NULL)
    LOGW(_("Returning a NULL xml document"));

  return doc;
}

/** Get the XML file and send it to a TinyXML document
  *
  * It uses \ref RainbruRPG::Network::Ident::CurlGetFile::writeToFile() 
  * "writeToFile" to store the server file in a curlget.xml local
  * file and open it with TinyXML
  *
  * \return \c true if the document was correctly loaded
  *
  */
bool RainbruRPG::Network::Ident::CurlFileToXml::fileToxml(){
  if (CurlGetFile::writeToFile()){

    doc=new TiXmlDocument( "curlget.xml" );
    if(doc->LoadFile()){
      return true;
    }
    else{
      GTS_MID(err);
      /* TRANSLATORS: The first parameter is the file name, the second
	 if the error string returned by TinyXml
       */
	sprintf(err, _("An error occured while loading curlget.xml for \
file '%s'. Error desc from TinyXML is : '%s'"), this->filename.c_str(), 
		doc->ErrorDesc());
      LOGE(err);

      return false;
    }
  }
  else{
    LOGW(_("The writeToFile operation failed"));
    return false;
  }
}

/** Returns the text element from the \c child and the given node
  * name.
  *
  * \param child The xml element where we must search the node.
  * \param nodeName The node's name we must find in \c child.
  *
  * \return The text store in the \c child's node defined by \c
  * nodeName. Returns an empty string ("") if none child was found.
  */  
const char* RainbruRPG::Network::Ident::CurlFileToXml::
getXMLTextFromName(TiXmlElement*child, const char* nodeName){

  TiXmlText* textNode;

  TiXmlNode* node=child->FirstChild(nodeName);
  if (node && node->FirstChild()){
    textNode=node->FirstChild()->ToText();
    if (textNode)
      return  textNode->Value();
    
    else  // !textNode
      return  "";
  }
  else    // !node
    return  "";
}
