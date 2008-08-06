/*
 *  Copyright 2006-2008 Jerome PASQUIER
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

/** \file curlpersoheaderadd.h
  * Defines how to submits a add perso header request
  *
  * Modifications :
  * - 04 aug 2008 : Documentation of the files
  *
  */

#ifndef CURL_PERSO_HEADER_ADD_H
#define CURL_PERSO_HEADER_ADD_H

#include "globaluri.h"
#include "curlsubmitform.h"
#include "xmlpersolist.h"

using namespace RainbruRPG::Network::Ident;

namespace RainbruRPG {
  namespace Network {

      /** Submits a add perso header to the administration site
        * 
	* It is used with CurlPersoModifAttrb by erCreatePerso to
	* create the data of a newly created character (perso)
	*/
      class CurlPersoHeaderAdd : public CurlSubmitForm{
      public:
	CurlPersoHeaderAdd();
	~CurlPersoHeaderAdd();

	void               setName(const std::string&);
	const std::string& getName(void);

      protected:
	virtual bool controlBefore();
	virtual bool controlAfter();

      private:
	/** The xml interface to the character list */
	xmlPersoList* xml;
	/** The perso name */
	std::string persoName;
      };

  }
}

#endif // CURL_PERSO_HEADER_ADD_H
