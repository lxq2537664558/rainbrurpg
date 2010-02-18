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

/** \file DeserializationErrorList.hpp
  *
  * Declare a list of deserialization error
  *
  * Modifications :
  * - 18 nov 2009 : Starting implementation
  *
  */

#include "DeserializationErrorList.hpp"

/** The error constructor
  *
  * \param vWidgetUniqueName The unique name of the Serializable
  * \param vErrorType        The error type
  * \param vMessage          The error message
  *
  */
RainbruRPG::OgreGui::DeserializationError::
DeserializationError(const string& vWidgetUniqueName, 
		     DeserializationErrorType vErrorType, 
		     const string& vMessage):
  widgetUniqueName(vWidgetUniqueName),
  errorType(vErrorType),
  message(vMessage)
{

}

//========== Starting DeserializationErrorList ====================

/** Add an error to the list
  *
  * \param vWidgetUniqueName The unique name of the Serializable
  * \param vErrorType        The error type
  * \param vMessage          The error message
  *
  */
void RainbruRPG::OgreGui::DeserializationErrorList::
add(const string& vWidgetUniqueName, 
    DeserializationErrorType vErrorType, 
    const string& vMessage)
{
  mList.push_back(DeserializationError(vWidgetUniqueName,vErrorType,vMessage));
}

/** Is this list empty ?
  *
  * \return \c true if this error list is empty
  *
  */
bool RainbruRPG::OgreGui::DeserializationErrorList::empty(void) const{ 
  return mList.empty(); 
}

/** Return the size of this list
  *
  * \return The number of errors
  *
  */
size_t RainbruRPG::OgreGui::DeserializationErrorList::size(void) const{ 
  return mList.size(); 
}
