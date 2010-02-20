/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file curlaccounttoggleblacklist.h
  * Defines how submit a toggle blacklist request of an account
  *
  * Modifications :
  * - 26 mar 2009 : Added gettext stuff
  * - 04 aug 2008 : Documentation of the file 
  *        
  */

#ifndef CURL_ACCOUNT_TOGGLE_BLACKLIST_H
#define CURL_ACCOUNT_TOGGLE_BLACKLIST_H

#include "globaluri.h"
#include "curlsubmitform.h"
#include "xmlaccountlist.h"
#include "rainbrudef.h" // For the gettext stuff

using namespace RainbruRPG::Network;

namespace RainbruRPG {
  namespace Network {
    namespace Ident {

      /** Submits a add account to the administration site
        * 
	* The admin adress is toggleblacklist.php. The only key used
	* is the account's name.
	*
	*/
      class CurlAccountToggleBlacklist : public CurlSubmitForm{
      public:
	CurlAccountToggleBlacklist();
	~CurlAccountToggleBlacklist();

	void setName(const char*);

      protected:
	virtual bool controlBefore();
	virtual bool controlAfter();

      private:
	/** The xmlAccountList used to deal with the xml file */
	xmlAccountList* xml;
      };

    }
  }
}

#endif // CURL_ACCOUNT_TOGGLE_BLACKLIST_H
