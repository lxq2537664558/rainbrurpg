/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file curlaccountconfirmmail.h 
  * Defines confirmation of a account's mail address
  *
  * Modifications :
  * - 21 mar 2009 : Now using gettext compliant strings
  * - 06 aug 2007 : ConfirmId added
  * - 15 mar 2007 : Added a getName function for unittest         
  *
  */

#ifndef CURL_ACCOUNT_CONFIRM_MAIL_H
#define CURL_ACCOUNT_CONFIRM_MAIL_H

#include "curlsubmitform.h"
#include "rainbrudef.h" // For the gettext stuff

// Forward declarations
namespace RainbruRPG {
  namespace Network {

    class GlobalURI;

    namespace Ident {
      class xmlAccountList;
    }
  }
}
// End of forward declarations

using namespace RainbruRPG::Network;

namespace RainbruRPG {
  namespace Network {
    namespace Ident {

      /** Confirm the mail address of an account
        *
	* Since the mail confirmation was changed, we need a
	* confirmId to be able to validate a mail address. You
	* don't have to deal with it. It is automatically taken
	* from xmlAccountList within the setName() function.
	*
	*/
      class CurlAccountConfirmMail : public CurlSubmitForm{
      public:
	CurlAccountConfirmMail();
	~CurlAccountConfirmMail();

	void setName(const std::string&);
	const char* getName();

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

#endif // CURL_ACCOUNT_CONFIRM_MAIL_H
