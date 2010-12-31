/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

/** \file xmltimestamp.cpp
  * Implements a class that manage XML timestamps
  *
  */

#include "xmltimestamp.h"
#include "logger.h"

/** The default constructor
  *
  */
RainbruRPG::Network::Ident::xmlTimestamp::xmlTimestamp(){

}

/** The default destructor
  *
  */
RainbruRPG::Network::Ident::xmlTimestamp::~xmlTimestamp(){

}

/** Add the current date/time with the given tag to the given xml node
  *	
  * \param tag The xml attribute used as tag for the timestamp
  * \param child The xml node to add the timestamp
  */
void RainbruRPG::Network::Ident::xmlTimestamp::
addTimestamp( const char * tag, TiXmlNode* child){

  TiXmlElement ts("Timestamp");
  ts.SetAttribute("tag", tag);

  time_t now=time (NULL);

  ostringstream o;
  o<<now;

  TiXmlText nText( o.str().c_str());
  ts.InsertEndChild( nText );

  child->InsertEndChild( ts );

  child->Print( stdout, 0 );
}

/** Get a string representing the timestamp tagged \c tag
  *
  * Return a string like this :
  * <code>Www Mmm dd hh:mm:ss yyyy</code>
  *
  * where \c Www is the weekday, \c Mmm the month in letters, \c dd the day of
  * the month, \c hh:mm:ss the time, and \c yyyy the year. The string is
  * followed by a new-line character (\n) and a terminating
  * null-character, conforming a total of 26 characters.
  *
  * \param tag The xml attribute used as tag for the timestamp
  * \param child The xml node to add the timestamp
  *
  * \return A string at the ctime function format
  */
const char* RainbruRPG::Network::Ident::xmlTimestamp::
getCTime( const char *tag, TiXmlElement* child){

  return getCTimeS(tag, child).c_str();

}

/** Get the Ctime format
  *
  * It returns a human readable string corresponding to a xmlTimeStamp.
  * It remove the 2 last char. (line feed...)
  *
  * \param child The TiXmlElement to parse
  * \param tag The tag name to find in the TiXmlElement
  *
  * \return A string representation of the founded timestamp
  */
std::string RainbruRPG::Network::Ident::xmlTimestamp::
getCTimeS( const char *tag, TiXmlElement* child ){

  bool foundedTimestamp=false;

  TiXmlHandle docHandle( child );
  TiXmlElement* times = docHandle.FirstChild( "Timestamp" ).Element();
    
  for( times; times; times=times->NextSiblingElement() ){

    const char* childTag=times->Attribute("tag");

    // If child is NULL, no attribute was found
    if (childTag){
      if (strcmp(childTag, tag)==0){
	foundedTimestamp=true;
	

	TiXmlNode* timesNode=times->FirstChild();
	if (timesNode){
	  TiXmlText* textNode=times->FirstChild()->ToText();
	  if (textNode){
	    time_t val;
	    string strTimeStamp=textNode->Value();
	    istringstream iss;
	    iss.str( strTimeStamp );
	    iss >> val;
	  
	    ostringstream o;
	    o<<ctime(&val);
	    // I must remove the newline and line feed characters
	    string ret=o.str().substr( 0, 24 );;
	    
	    return ret;
	  }
	}
      }
    } // !childtag
  }


  if (!foundedTimestamp)
    return "";
}

/** Definitively remove a timestamp
  *
  * It removes the child's timestamp named tag.
  *
  *
  * \param child The TiXmlElement to parse
  * \param tag The tag name of the timestamp to remove
  *
  */
void RainbruRPG::Network::Ident::xmlTimestamp::
delTimestamp( const char* tag, TiXmlNode* child){

  TiXmlHandle docHandle( child );
  TiXmlElement* times = docHandle.FirstChild( "Timestamp" ).Element();
    
  for( times; times; times=times->NextSiblingElement() ){

    const char* childTag=times->Attribute("tag");

    // If child is NULL, no attribute was found
    if (childTag){
      if (strcmp(childTag, tag)==0){
	child->RemoveChild(times );
	
      }
    }
  } // !childtag
}
