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

/* Modifications :
 * - 02 mar 2007 : To be unit testing, modify :
 *         - A default constructor
 *         - A connect(...) function
 */

#ifndef CLIENT_CONNECT_H
#define CLIENT_CONNECT_H

#include "xmlaccountlist.h"
#include "taccountlist.h"
#include "hashpassword.h"

using namespace std;
using namespace RainbruRPG::Gui;

namespace RainbruRPG{
  namespace Network {
    namespace Ident {

      /** Defines the result of the client connection
        *
	* This structure is returned by the ClientConnect class. It is
	* used to determine if the client can be connected or if an error
	* occured.
	*/
      enum tClientConnectReturn { 
	CCR_SUCCESS,             //!< The connnection is successfull
	CCR_INEXISTANT_USER,     //!< The account does not exist
	CCR_WRONG_PWD,           //!< The password is wrong
	CCR_EMAIL_NOT_VALIDATED, //!< The email is not validated
	CCR_BLACKLIST,           //!< The user is in blacklist
	CCR_UNKNOWN_ERROR        //!< An unknown error occured
      };

     /** Verifies the client connection ability
        *
	* It uses xmlPlayerList to check if this client can connect. To test
	* the connection ability of a client, you must call the constructor
	* of this class with the username and the password of the user.
	*
	* Do not pass the password hashsum here, the constructor need the 
	* user's password, not its password hashsum.
	*
	* To know the response of the connection, call the getResponse()
	* function and test the tClientConnectReturn returned with a switch.
	*
	* \sa tClientConnectReturn, xmlPlayerList
	*/
      class ClientConnect{
      public:
	ClientConnect();
	ClientConnect(const char*, const char*);
	tClientConnectReturn getResponse();

	tClientConnectReturn connect(const char*, const char*);

      private:
	/** The response of the last connection 
	  *
	  * This is the response that is given by the getResponse() function.
	  *
	  */
	tClientConnectReturn response;
      };

    }
  }
}
#endif // CLIENT_CONNECT_H
