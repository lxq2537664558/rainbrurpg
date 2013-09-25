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

/** \file CurlPostedData.hpp
  * Defines a class used to compute data for a form submit action
  *
  * Modification :
  * - 27 mar 2009 : Now using gettext
  * - 04 aug 2008 : File documentation
  * - 02 mar 2007 : An include to xmlplayerlist deleted
  *         
  */

#ifndef CURL_POSTED_DATA_H
#define CURL_POSTED_DATA_H

#include <iostream>
#include <sstream>
#include <map>
#include <list>
#include <time.h>
#include <string>

#include "RainbruDef.hpp" // For the gettext stuff
#include "Logger.hpp"

using namespace std;

namespace RainbruRPG {
  namespace Network {
    namespace Ident {


      /** A map where the key is a const char* and the data is a stl string
        *
        * \sa CurlPostedData
	*/
      typedef std::map<const char*, string>        PostedDataMap;

      /** A shortcut for the PostedDataMapiterator */
      typedef PostedDataMap::iterator         PostedDataMapIterator;

      /** The pairs added to the PostedDataMap 
        *
        * \sa CurlPostedData
	*/
      typedef std::pair<const char*, const char*>  PostedDataPair;

      /** The list of keys 
        *
	* \sa CurlPostedData
        */
      typedef std::list<const char*>               PostedDataKeyList;

      /** A class used to compute data to be submitted in a form 
        * submit action
	*
	* The keys are add to a list. When we call setValue (a pair of key
	* and value), we check if the key exists on the list and if it
	* exists, we add it to the map and remove the key from the list.
	* The key become now unusable so we can use a key once time.
	*
	* You can add a needed key with addKey(const char *), set its value
	* with setValue(const char *, const char *) or 
	* setValue(const char *, const std::string &) and to add a 'now' 
	* timestamp, use setTimestamp(const char *).
	*/
      class CurlPostedData{
      public:
	CurlPostedData();
	~CurlPostedData();

	void addKey(const char*);
	void setValue(const char*, const char*);
	void setValue(const char*, const std::string&);
	void setTimestamp(const char*);
	std::string getComputedData();

	const char* getValue(const char*);
	void debugKeyList();
	int keyCount();

      private:
	/** The map used to store the data to post
	  *
	  */
	PostedDataMap map;
	/** The list of key for the data to post
	  *
	  */
	PostedDataKeyList* list;
	/** Was a custom timestamp added
	  *
	  */
	bool customTimestamp;
      };
    }
  }
}

#endif // CURL_POSTED_DATA_H
