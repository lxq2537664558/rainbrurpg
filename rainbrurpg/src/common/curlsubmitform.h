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

/** \file curlsubmitform.h
  * Defines a class used to fill a form and submit it
  *
  * Modification :
  * - 23 mar 2009 : Now uses gettext
  * - 05 aug 2008 : Single file documentation added
  * - 02 mar 2007 : Some functions become protected: 
  *            \ref RainbruRPG::Network::Ident::CurlSubmitForm::setPostedData() 
  *            "setPostedData()", 
  *            \ref RainbruRPG::Network::Ident::CurlSubmitForm::setPostedPwd() 
  *            "setPostedPwd()", 
  *            \ref RainbruRPG::Network::Ident::CurlSubmitForm::setCustomPost() 
  *            "setCustomPost()". 
  *         
  */

#ifndef CURL_SUBMIT_FORM
#define CURL_SUBMIT_FORM

#include <string>
#include <vector>
#include <curl/curl.h>

#include "rainbrudef.h"
#include "curlinterface.h"
#include "curlposteddata.h"
#include "hashpassword.h"

namespace RainbruRPG {
  namespace Network {
    namespace Ident {


      /** A class used to fill a form and submit it
        *
	* In this class, the controlBefore() and controlAfter() are very
	* important. If you add a player, you use setPlayerName() and others
	* to correctly fill the POST datas and call the perform() function.
	*
	* The controlBefore function will be called, the postedData variable 
	* will be initialized by the call of computePostedData(), the post is
	* done and we call controlAfter to see if all the changes are done.
	*
	* If you override controlBefore(), controlAfter() and 
	* computePostedData(), you don't have to override perform().
	*
	* In a subclass, You can use 
	* setPostedData(const char* , const char* ) to post
	* a value for a regular key. Instead use 
	* setPostedPwd(const char* , const char*) to post the password
	* of the user. Use setCustomPost(const char* , const char* ) if the
	* key does not yet exist.
	*
	* After setting all the data to post, call perform() to submit 
	* the form.
	*
	* The end-user of a subclass should not use setPostedData and cie, 
	* he may use accessor in the subclass (setName, setPwd...)
	*
	* \sa CurlPostedData
	*/
      class CurlSubmitForm : public CurlInterface{
      public:
	CurlSubmitForm();
	virtual bool perform();

      protected:
	const char* getComputedData();

	void setCustomPost(const char* , const char* );
	void setPostedData(const char* , const char* );
	void setPostedPwd(const char* , const char* );

	virtual bool controlBefore()=0;
	virtual bool controlAfter()=0;

	virtual bool computePostedData();
	virtual bool submitForm();

	/** The data that will be posted to the url */
	CurlPostedData postedData;

	/** If an error occurs during controlBefore() or controlAfter(), 
	  * this variable may contains a error message
	  *
	  */
	const char* controlError();
      };
    }
  }
}

#endif //CURL_SUBMIT_FORM
