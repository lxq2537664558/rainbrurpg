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

#include "curlposteddata.h"
#include <cstring> // For strlen() and strcmp()


/** The default constructor
  *
  * It actually set customTimestamp to false and create the PostedDataKeyList.
  */
RainbruRPG::Network::Ident::CurlPostedData::CurlPostedData(){
  LOGI("Creating a posted data structure");
  customTimestamp=false;
  list=new PostedDataKeyList();
}

/** The default destructor
  *
  * Deletes the PostedDataKeyList.
  */
RainbruRPG::Network::Ident::CurlPostedData::~CurlPostedData(){
  if (list)
    delete list;

  list=NULL;
}

/** Adds a key to the PostedDataKeyList
  *
  * \param key The key to add.
  */
void RainbruRPG::Network::Ident::CurlPostedData::addKey(const char* key){
  LOGI("Adding a key to the CurlPostedData list");
  if (strlen(key)==0){
    LOGW("Trying to add a empty key to the CurlPostedData list. Aborded");
  }
  else{
    list->push_back(key);
  }
}

/** A simple debug method 
  *
  * It prints in the standard output (cout) the kay list.
  */
void RainbruRPG::Network::Ident::CurlPostedData::debugKeyList(){
  LOGI("Debugging CurlPostedData key list");
  for(PostedDataKeyList::iterator iter = list->begin();
      iter != list->end(); iter++){
    LOGCATS((*iter));
    LOGCAT();
  }
}

/** Set an auto timestamp for the given key
  *
  * If no custom timestamp was set, it will set the posted data for the key
  * to now. If a custom timestamp was set, it does nothing but prints a 
  * warning log.
  *
  * \param key The key that will receive the timestamp.
  */
void RainbruRPG::Network::Ident::CurlPostedData::setTimestamp(const char* key){
  LOGI("Adding an auto timestamp");
  if (!customTimestamp){
    time_t now=time(NULL);
    
    ostringstream o;
    o<<now;
    this->setValue( key, o.str().c_str());
  }
  else{
    LOGW("Setting an auto timestamp while a custom timestamp already exists");
  }

}

/** Get the value of a posted data
  *
  * \param key The key of the data you want.
  *
  * \return The data of the given key or "" if not found.
  */
const char* RainbruRPG::Network::Ident::CurlPostedData::getValue(
                                                 const char* key){
  const char* ret;
  bool found=false;
  PostedDataMapIterator iter;

  // We iterates through the list
  for(iter = map.begin(); iter != map.end(); iter++){
    // We search the key
    if (strcmp(key, iter->first)==0){
      // We have the good key
      found=true;
      ret= iter->second.c_str();
      break;

    }
  }
  if (!found){
    string err="In CurlPostedData::getValue() : this key cannot be found : '";
    err.append(key);
    err.append("'");
    LOGW(err.c_str());
    ret= "";
  }

  return ret;
}

/** Sets a value for the given key
  *
  *
  *
  * \param key The key to fill
  * \param val The value to set to the given key.
  */
void RainbruRPG::Network::Ident::CurlPostedData::setValue(const char* key, 
						  const std::string& val){

  string snew(val);
  LOGI("Setting the value of a key (std::string form)");
  setValue(key, snew.c_str());
}

/** Get the computed dta to post
  *
  * The computed data is in the form \c key1=value1&key2=value2...
  *
  * \return The computed data string.
  */
std::string RainbruRPG::Network::Ident::CurlPostedData::getComputedData(){
  LOGI( "Computing posted data..." );
  PostedDataMapIterator iter;
  //  const char* key, val;
  ostringstream oss;
  bool first=true;

  // We iterates through the list
  for(iter = map.begin(); iter != map.end(); iter++){

    if (iter->second.length()==0){
      LOGW("A key has no value : ");
      LOGCATS("key name : ");
      LOGCATS(iter->first);
      LOGCAT();
    }
    else{
      if (first){
	first=false;
      }
      else{
	oss <<"&";
      }
      oss <<iter->first<<"="<<iter->second;
    }
  }
  return oss.str();
}

/** Sets a value to the given key
  *
  *
  *
  * \param key The key to fill
  * \param val The value to set to the given key.
  *
  */
void RainbruRPG::Network::Ident::CurlPostedData::setValue(const char* key, 
							  const char* val){

  LOGI("Setting the value of a key (const char* form)");
  bool found=false;
  //if the key exists in the list
  for(PostedDataKeyList::iterator iter = list->begin();
      iter != list->end(); iter++){

    if (strcmp((*iter), key)==0){
      LOGI("The key was found");
      if (strcmp("timestamp", key)==0){
	LOGI("Setting a custom timestamp");
	customTimestamp=true;

      }
      map.insert(PostedDataPair(key, val));
      list->erase(iter);
      found=true;
      break;
    }
  }
  
  if (!found){
    string warn="The key you want was not found : '";
    warn.append(key);
    warn.append("'");
    LOGW(warn.c_str());
  }
  //  debugKeyList();
}

/** Get the number of keys
  *
  * This function is mainly used by Unit Test. 
  *
  * \return The number of item in PostedDataKeyList
  *
  */
int RainbruRPG::Network::Ident::CurlPostedData::keyCount(){
  return list->size();
}
