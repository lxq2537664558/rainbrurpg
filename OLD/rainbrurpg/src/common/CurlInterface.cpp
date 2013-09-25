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

/** \file curlinterface.cpp
  * Implements a common base for all libcUrl based classes
  *
  */

#include "CurlInterface.hpp"
#include <cstring> // For strlen()

/** The default constructor
  *
  * It sets customErrorMessage to an empty string an serverResponse
  * to -1.
  */
RainbruRPG::Network::Ident::CurlInterface::CurlInterface(){
  customErrorMessage="";
  serverResponse=-1;
}

/** The default destructor
  *
  */
RainbruRPG::Network::Ident::CurlInterface::~CurlInterface(){
}


/** The initialisation of libcurl
  *
  * Typically calls curl_easy_init()to initialise the handle.
  *
  * \return true if successfull otherwise false.
  */
bool RainbruRPG::Network::Ident::CurlInterface::init(){
  LOGI(_("Initializing the libcurl interface"));
  handle=curl_easy_init();

  if (handle){
    return true;
  }
  else{

    LOGE(_("An error occured during the libcurl iitialization"));

    return false;
  }
}

/** Calls curl_easy_cleanup to ends curl operation
  *
  * \return Currently always returns true
  */
bool RainbruRPG::Network::Ident::CurlInterface::cleanup(){
  LOGI(_("Cleaning up the libcurl interface"));

  if (handle){
    curl_easy_cleanup( handle );
    handle=NULL;
  }
  else{
    LOGW(_("Calling cleanup on a non-existing handle"));
  }
  return true;
}

/** Set the write function to the curl CURLOPT_WRITEFUNCTION option
  *
  *
  * \param f The function parameter
  */
void RainbruRPG::Network::Ident::CurlInterface::setWriteFunction(void* f){
  LOGI(_("Setting up a custom WriteFunction"));

  if (handle)
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, f);
  else
    LOGW(_("Cannot set a WriteFunction, the handle is undefined"));
}

/** Returns the last server response
  *
  * The long returned by this function can be used with a HttpResponse
  * instance to get an human-readable message. If none server response
  * was set, return -1.
  *
  * \sa HttpResponse
  *
  * \return a long representing the last server response
  */
long RainbruRPG::Network::Ident::CurlInterface::getServerResponse(){
  return this->serverResponse;
}

/** Get the custom error message
  *
  * \return The custom error message
  *
  * \sa setCustomErrorMessage(const char* msg)
  */
const char* RainbruRPG::Network::Ident::CurlInterface::getCustomErrorMessage(){

  return customErrorMessage;
}

/** Set a new custom error message
  *
  * Only one custom error message can be set, so the second time 
  * you call this, a warning log is sent but the message is not
  * modified.
  *
  * \param msg The new custom error message
  *
  * \sa getCustomErrorMessage()
  */
void RainbruRPG::Network::Ident::CurlInterface::setCustomErrorMessage(
						      const char* msg){

  if (strlen(customErrorMessage)!=0){
   LOGW(_("A customErrorMessage already exists. Keeping only the first one."));
  }
  else{
    customErrorMessage=msg;
  }
}

 