/*
 *  Copyright 2006 Jerome PASQUIER
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

#include "curlfiletoxml.h"

/** The default constructor
  *
  */
RainbruRPG::Network::Ident::CurlFileToXml::CurlFileToXml(){

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
  if (!doc)
    LOGW("Returning a NULL xml document");

  return doc;
}

/** Get the XML file and send it to a TinyXML document
  *
  * It uses writeToFile to store the server file in a curlget.xml local
  * file and open it with TinyXML
  *
  * \return \c true if the document was correctly loaded
  *
  */
bool RainbruRPG::Network::Ident::CurlFileToXml::fileToxml(){
  if (writeToFile()){
    doc=new TiXmlDocument( "curlget.xml" );
    if(doc->LoadFile()){
      return true;
    }
    else{
      LOGW("An error occured while loading curlget.xml");
      return false;
    }
  }
  else{
    LOGW("The writeToFile operation failed");
    return false;
  }
}
