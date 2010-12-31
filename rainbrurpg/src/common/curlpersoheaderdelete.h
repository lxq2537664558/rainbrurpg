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

/** \file curlpersoheaderdelete.h
  * Defines how to delete the header of a perso
  *
  * Modifications : 
  * - 27 mar 2009 : Added the gettext stuff include
  * - 04 aug 2008 : Doxygen single file documentation
  *
  */

#ifndef CURL_PERSO_HEADER_DELETE_H
#define CURL_PERSO_HEADER_DELETE_H

#include <string>

#include "rainbrudef.h" // For gettext stuff
#include "globaluri.h"
#include "curlsubmitform.h"
#include "xmlpersolist.h"

using namespace RainbruRPG::Network::Ident;

namespace RainbruRPG {
  namespace Network {

      /** Submits a delete perso header to the administration site
        * 
	* It is used to delee a perso header.
	*
	*/
      class CurlPersoHeaderDelete : public CurlSubmitForm{
      public:
	CurlPersoHeaderDelete();
	~CurlPersoHeaderDelete();

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

#endif // CURL_PERSO_HEADER_DELETE_H
