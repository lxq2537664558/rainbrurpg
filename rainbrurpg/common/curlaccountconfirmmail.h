/*
 *  Copyright 2006-2007 Jerome PASQUIER
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

/* Modifications :
 * - 15 mar 2007 : Added a getName function for unittest         
 *
 */

#ifndef CURL_ACCOUNT_CONFIRM_MAIL_H
#define CURL_ACCOUNT_CONFIRM_MAIL_H

#include "globaluri.h"
#include "curlsubmitform.h"
#include "xmlaccountlist.h"

using namespace RainbruRPG::Network;

namespace RainbruRPG {
  namespace Network {
    namespace Ident {

      /** Confirm the mail address of an account
        *
	*
	*
	*/
      class CurlAccountConfirmMail : public CurlSubmitForm{
      public:
	CurlAccountConfirmMail();
	~CurlAccountConfirmMail();

	void setName(const char*);
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
