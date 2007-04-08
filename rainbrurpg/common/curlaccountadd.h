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
 *
 * - 06 mar 2007 : Adds tCurlAccountAddReturn enumeration
 * - 02 mar 2007 : Renamed CurlAccountAdd (was CurlPlayerAdd)
 * - 02 mar 2007 : Adds some accessors( setName, setPassword, setMail)
 *         
 */

#ifndef CURL_ACCOUNT_ADD_H
#define CURL_ACCOUNT_ADD_H

#include "globaluri.h"
#include "curlsubmitform.h"
#include "xmlaccountlist.h"
#include "hashpassword.h"

using namespace RainbruRPG::Network;

namespace RainbruRPG {
  namespace Network {
    namespace Ident {

      /** The return value of CurlAccountAdd
        *
	* To privide precise error message, we can know
	* why an account cannot be created
	*
	*/
      typedef enum tCurlAccountAddReturn{
	CAA_SUCCESS,        //!< Adding the Account was successfull
	CAA_EXISTS,         //!< The account already exists
	CAA_EMPTY_NAME,     //!< Empty name error
	CAA_EMPTY_PWD,      //!< Empty password error
	CAA_EMPTY_MAIL,     //!< Empty mail error
	CAA_MAIL_INUSE,     //!< Mail address already in use
	CAA_MAIL_SIGN_AT,   //!< Mail address at sign missing
	CAA_MAIL_SIGN_DOT,  //!< Mail address dot sign missing
	CAA_UNDEFINED,      //!< Response was undefined
	CAA_UNKNOWN         //!< Unknown error, often controlAfter
      };

      /** Submits a add account to the administration site
        * 
	*/
      class CurlAccountAdd : public CurlSubmitForm{
      public:
	CurlAccountAdd();
	~CurlAccountAdd();

	void setName(const char*);
	void setPassword(const char*);
	void setMail(const char*);
	tCurlAccountAddReturn getResponse();

      protected:
	virtual bool controlBefore();
	virtual bool controlAfter();

      private:
	/** The xmlAccountList used to deal with the xml file */
	xmlAccountList* xml;
	/** The perform response */
	tCurlAccountAddReturn response;
      };

    }
  }
}

#endif // CURL_ACCOUNT_ADD_H
