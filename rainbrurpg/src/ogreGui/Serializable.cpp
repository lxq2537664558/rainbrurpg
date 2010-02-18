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

/** \file Serializable.cpp
  *
  * Implement a serializable object
  *
  * Modifications :
  * - 16 nov 2009 : Starting implementation
  *
  */

#include "Serializable.hpp"

#include <rainbrudef.h> // For the gettext stuff
#include <logger.h>

#include <DeserializationErrorList.hpp>

/** A named constructor
  *
  * The name should not be empty as it is used for creating unique name;
  *
  * \param vName The widget's name
  *
  */
RainbruRPG::OgreGui::Serializable::Serializable(const string& vName):
  mName(vName)
{
  if (mName.empty()) LOGW(_("Widget name is empty"));
  
}

/** Destructor */
RainbruRPG::OgreGui::Serializable::~Serializable(void){
  
}

/** Set the unique nam of the object
  *
  * Create a unique name based on parent name and object name (passed
  * to the constructor).
  *
  * \param vParentUniqueName The parent name
  *
  */
void RainbruRPG::OgreGui::Serializable::
setUniqueName(const string& vParentUniqueName){
  if (vParentUniqueName.empty()) LOGW(_("Parent name is empty"));
  mUniqueName = vParentUniqueName + "/" + mName;
}

/** Serialize this object
  *
  * \param os The stream used to serialize
  *
  * \return \c true if the operation was successfull
  *
  */
bool RainbruRPG::OgreGui::Serializable::serialize(ostream& os)const{
  serializeString(os, mUniqueName);
  return os.good();
}

/** Deserialize and test the unique name from the given stream
  *
  * If the unique name is not the same as the object's one,
  * the stream seek to the position just before the failed unique name,
  * to allow other Serializable object to extract (and check) it.
  *
  * This function must be called before the widget's deserialization,
  * to know if the widget and the stream position is the same.
  *
  * \param is The stream used to extract unique name
  *
  * \return \c true if the unique name check is succefull
  *
  */
bool RainbruRPG::OgreGui::Serializable::checkUniqueName(istream& is)const{
  const streampos beforeName=is.tellg();
  if (beforeName == ios::beg){
    LOGI("beforeName is at the stream's begining position");
  }
  else if (beforeName == -1){
    LOGE(_("beforeName stream position is -1 (failure)"));
  } 

  string un = deserializeString(is);
  if (un != mUniqueName){
    GTS_MID(str);
    // TRANSLATORS: The two parameters are Serializable object's
    // unique name.
    sprintf(str, _("Cannot deserialize '%s' (extracted unique name '%s')"),
	    mUniqueName.c_str(), un.c_str());
    
    LOGW("UniqueName is not the same");
    LOGW(str);
    is.seekg(beforeName);
    return false;
  }
  return true;
}

/** Deserialize this object
  *
  * The object is deserialized only if the unique name check
  * is successfull (see \ref checkUniqueName).
  *
  * \param is The input stream
  * \param el The error list
  *
  * \return \c true if deserialization was a success, \c false otherwise
  *         (checkUniqueName failed).
  *
  */
bool RainbruRPG::OgreGui::Serializable::
deserialize(istream& is, DeserializationErrorList* el)const{
  if (checkUniqueName(is)){
    // deserialize here
  }
  else{ 
    el->add(mUniqueName, BAD_UNIQUE_NAME, "checkUniqueName failed");
    return false;
  }
  return true;
}

/** Return the unique name of this object
  *
  * \return The unique name string
  *
  */
const string& RainbruRPG::OgreGui::Serializable::getUniqueName(void) const{
  return mUniqueName;
}

/** Equality comparison operator overriden
  *
  * \param other The object to test \c this with
  *
  * \return \c true if objects are equal
  *
  */
bool RainbruRPG::OgreGui::Serializable::
operator==(const Serializable& other)const{
  return (mUniqueName==other.getUniqueName());
}

/** Non-equal comparison operator overriden
  *
  * \param other The object to test \c this with
  *
  * \return \c true if objects are non-equal
  *
  */
bool RainbruRPG::OgreGui::Serializable::
operator!=(const Serializable& other)const{
  return !(*this==other);
}

/** Equality test with a pointer
  *
  * It is only a wrapper to the operator== function.
  *
  * \param other A pointer to the object to test \c this with
  *
  * \return \c true if objects are equal
  *
  */
bool RainbruRPG::OgreGui::Serializable::
equal(const Serializable* other)const{
  return (*this==(*other));
}

/** Serialize a string to a stream
  *
  * Serialize a string and handles the string separator.
  *
  * \param os  The output stream to put the string in
  * \param str The string to be serialized
  *
  */
void RainbruRPG::OgreGui::Serializable::
serializeString(ostream& os, const string& str)const{
  os << str << STRING_SEPARATOR;
}

/** Deserialize a string from a stream
  *
  * Deserialize a string previously serialized with \ref serializeString.
  * It handles the string separator and returns the extracted string.
  *
  * \param is The input stream where the string is extracted
  *
  * \return The extracted string
  *
  */
string RainbruRPG::OgreGui::Serializable::
deserializeString(istream& is)const{
  string str;
  is >> str;
  return str;
}
