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

#include "curlgetfile.h"

#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/fstream.hpp"
#include "loadbmp.h"
#include "httpresponse.h"

/** The destructor
  *
  * Here is deleted the \c curlget.xml file.
  *
  */
RainbruRPG::Network::Ident::CurlGetFile::~CurlGetFile(){
  // Remove curlget.xml
  boost::filesystem::path path("curlget.xml");
  boost::filesystem::remove(path);
}

/** Perform the given operation
  *
  * It simply call writeToFile()
  *
  * \return \c true if the operation was successfull
  *
  */
bool RainbruRPG::Network::Ident::CurlGetFile::perform(){
  curl_easy_setopt(handle, CURLOPT_WRITEDATA, this);
  return writeToFile();
}

/** Does nothing
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Network::Ident::CurlGetFile::controlBefore (){
  // Nothing to do here
  return true;
}

/** Does nothing
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Network::Ident::CurlGetFile::controlAfter (){
  // Nothing to do here
  return true;
}

/** Performs the write to file action
  *
  * \return \c true if success, \c false if an error occured
  *
  */
bool RainbruRPG::Network::Ident::CurlGetFile::writeToFile(){
  bool ret=false;

  // Remove curlget.xml
  boost::filesystem::path path("curlget.xml");
  boost::filesystem::remove(path);

  LOGI("Performing CurlGetFile writeToFile action, filename :");
  LOGCATS( this->filename.c_str() );
  LOGCAT();

  handle=curl_easy_init();
  if (handle==NULL){
    LOGE("The curl handle was not properly initialized");
    ret= false;
  }

  // Set the password
  LoadBMP *l=new LoadBMP();
  l->decode();
  char* a=const_cast<char*>(l->get1());
  curl_easy_setopt(handle, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
  curl_easy_setopt(handle, CURLOPT_USERPWD, a);

  // Curl URL setting
  LOGI("==> Setting the licurl URL");
  std::string s=filename;

  // Think about the \0 terminating string	       
  int len = s.length() + 1;
  std::vector<char> raw(len);
  const char* str = s.c_str();
 
  std::copy(str, str + len, raw.begin());

  curl_easy_setopt(handle, CURLOPT_URL, &(raw[0]));


  // Writing in a FILE structure using the built-in
  // cUrl write function
  FILE* f;
  if ((f = fopen("curlget.xml", "w")) == NULL){
    LOGE("Error opening the FILE pointer");
  }
  else{
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, f);
  }
  CURLcode success = curl_easy_perform(handle);
  fclose(f);

  // Error handling
  if (success!=0){
    LOGE("An error occured during CurlGetFile::writeToFile().");
    ret= false;
  }
  else{
    LOGI("Getting the last HTTP server status code");

    // Get the last response code
    CURLcode a=curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, 
				 &serverResponse);
    
    if (a==0){
       LOGI("The CurlGetInfo was successfull");
 
      /** A 2xx response is a success */
       if (serverResponse>199 & serverResponse<300){
	 LOGI("HTTP server returns SUCCESS.");
	 ret= true;
       }
       else{
	 LOGW("HTTP server returns an error status code :");
	 HttpResponse h;
	 LOGW(h.getMessage(serverResponse));

	 ret= false;
       }
    }
    else{
      LOGW("An error occured during CurlGetInfo operation");
      ret= false;
    }
  }
  curl_easy_cleanup( handle );

  return ret;
}
