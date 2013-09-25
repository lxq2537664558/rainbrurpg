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

/** \file Serializable.cpp
  *
  * Implement a serializable object
  *
  * Modifications :
  * - 16 nov 2009 : Starting implementation
  *
  */

#include "Serializable.hpp"

#include <RainbruDef.hpp> // For the gettext stuff
#include <Logger.hpp>

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
  * \param ar The archive used to serialize
  *
  * \return \c true if the operation was successfull
  *
  */
template<class Archive> bool RainbruRPG::OgreGui::Serializable::serialize(Archive& ar)const{
  //  serializeString(os, mUniqueName);
  //  return os.good();
  return true;
}


/** Deserialize this object
  *
  * The object is deserialized only if the unique name check
  * is successfull.
  *
  * \param ar The archive used for deserialization
  *
  * \return \c true if deserialization was a success, \c false otherwise
  *         (checkUniqueName failed).
  *
  */
template<class Archive> bool RainbruRPG::OgreGui::Serializable::
deserialize(Archive& ar)const{
  if (checkUniqueName(ar)){
    // deserialize here
  }
  else{ 
    //    el->add(mUniqueName, BAD_UNIQUE_NAME, "checkUniqueName failed");
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

