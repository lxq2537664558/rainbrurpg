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

/** \file curlsubmitform.cpp
  * Implements a class to fill and submit a form via libcUrl
  *
  */
#include "CurlSubmitForm.hpp"

/** The default constructor
  *
  */
RainbruRPG::Network::Ident::CurlSubmitForm::CurlSubmitForm(){
}


/** The function to call to performed operation
  *
  * it successively calls controlBefore, computePostedData, submitForm and 
  * controlAfter.
  *
  * \return true if all operations are successful, otherwise returns false.
  */
bool RainbruRPG::Network::Ident::CurlSubmitForm::perform(){
  bool ret=false;
  LOGI(_("Performing CurlSubmitForm action..."));
  if (controlBefore()){
    // Control before success
    if (computePostedData()){
      // Compute data success
      if (submitForm()){
	// Form submitting success
	if (controlAfter()){
	  // The operation is successful
	  ret=true;
	}
	else{
	  LOGW(_("CurlSubmitForm controlAfter() failed..."));
	  ret=false;
	}
      }
      else{
	LOGW(_("CurlSubmitForm failed to submit form..."));
	ret=false;
      }
    }
    else{
      LOGW(_("CurlSubmitForm failed to compute posted data..."));
      ret=false;
    }
  }
  else{
    LOGW(_("CurlSubmitForm controlBefore() failed..."));
    ret=false;
  }
  return ret;
}

/** Makes the post data string
  *
  * The result string, stored in postedData must be in the form
  * var1=aze&var2=144
  *
  * \return always \c true
  */
bool RainbruRPG::Network::Ident::CurlSubmitForm::computePostedData(){
  return true;
}

/** Submit the form filled with postedData
  *
  * \return \c true is success, otherwise \c false
  */
bool RainbruRPG::Network::Ident::CurlSubmitForm::submitForm(){
  bool ret=false;
  string s=postedData.getComputedData();

  handle=curl_easy_init();

  // Writing in a FILE structure using the built-in
  // cUrl write function (Only for submitted form's
  // not write to stdout)
  FILE* f;
  if ((f = fopen("curlget.xml", "w")) == NULL){
    LOGE(_("Error opening the FILE pointer"));
  }
  else{
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, f);
  }

  // Curl URL setting
  LOGI(_("Setting the licurl URL"));
  std::string s2=filename;
  // Penser au 0 terminal	       
  int len2 = s2.length() + 1;
  std::vector<char> raw2(len2);
  const char* str2 = s2.c_str();
 
  std::copy(str2, str2 + len2, raw2.begin());

  curl_easy_setopt(handle, CURLOPT_URL, &(raw2[0]));

  // Using a vector to convert string to char*
  int len = s.length() + 1; // null terminators, rah rah rah
  std::vector<char> raw(len); // or is that "raw raw raw"?
  const char* str = s.c_str();

  // Do not use strcpy, memcpy etc.
  std::copy(str, str + len, raw.begin());
  //  brokenCFunction(&(raw[0])); 
  // Assuming the C function modifies the input string and we 
  // want to return the
  // modified version
  //  return std::string(&(raw[0]));
 


  // Ajoute le cookie de connexion
  curl_easy_setopt(handle, CURLOPT_COOKIE, "login=true;");



  //  curl_easy_setopt(handle, CURLOPT_URL, this->filename);
  //  char* data="name=essaiCurl4&pwd=curl&pwd2=curl&mail=essai@curl.org";
  curl_easy_setopt(handle, CURLOPT_POSTFIELDS,&(raw[0]) );
  curl_easy_setopt(handle, CURLOPT_POST, 1);
  CURLcode success=curl_easy_perform(handle); /* post away! */

  if (success==0){
    LOGI(_("The form was successfully submited"));
    ret=true;
  }
  else{
    LOGW(_("An error occured during submitForm"));
  }


  // Get the last response code
  CURLcode a=curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, 
			       &serverResponse);

  if (serverResponse>199 & serverResponse<300)
    ret=true;
  else 
    ret=false;

  if (a==0){
    LOGI(_("Setting server response successfull"));
  }
  else{
    LOGW(_("Cannot get the server response"));
  }

  curl_easy_cleanup( handle );
  fclose(f);

  return ret;
}


/** Used to add a key/value pair to post 
  *
  * It simply calls setValue to the CurlPostedData instance.
  *
  * \param key The key to fill
  * \param value The value to set to the given key
  */
void RainbruRPG::Network::Ident::CurlSubmitForm::setPostedData(
		           const char* key, const char* value){

  postedData.setValue(key, value);
}

/** Get the computed post data computed by CurlPostedData
  *
  * \return The CurlPostedData computed data
  */
const char* RainbruRPG::Network::Ident::CurlSubmitForm::getComputedData(){
  return postedData.getComputedData().c_str();
}

/** Set a password to a key
  *
  * The password is crypted using HashPassword and set to the key. 
  *
  * \param key The key to fill
  * \param value The password
  *
  * \sa HashPassword
  */
void RainbruRPG::Network::Ident::CurlSubmitForm::setPostedPwd(
	                  const char* key, const char* value){

  LOGI(_("Adding a Pwd Data to post"));

  HashPassword hp;
  std::string hash= hp.encryptString( value );
  postedData.setValue(key, hash );
}

/** Used to post some custom key and value
  *
  * This method is used to add a key and a value at the same time. If you
  * know the key does not exist, call this. It simply call 
  * CurlPostedData::addKey(const char*) and 
  * CurlPostedData::setValue(const char* key, const char* val) 
  * with the given parameters.
  *
  * This is intended to do not warn up the user for a not-needed key. If a
  * key is facultative, use it.
  *
  * \param key The key to add
  * \param value The password
  *
  * \sa CurlPostedData
  */
void RainbruRPG::Network::Ident::CurlSubmitForm::
setCustomPost(const char* key, const char* value){
  postedData.addKey( key );
  postedData.setValue(key, value);
}
