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

#ifndef _DESERIALIZATION_ERROR_LIST_HPP_
#define _DESERIALIZATION_ERROR_LIST_HPP_

#include <string>
#include <list>

using namespace std;

namespace RainbruRPG{
  namespace OgreGui{

    /** Define the type of an error
      *
      */
    typedef enum{
      BAD_UNIQUE_NAME          //!< The unique name is spurious
    }DeserializationErrorType;

    /** Define an error that occurs during deserialization
      *
      */
    class DeserializationError{
    public:
      DeserializationError(const string&, DeserializationErrorType, 
			   const string&);

      /// The widget's unique name
      string widgetUniqueName;
      /// The error type
      DeserializationErrorType errorType;
      /// The message
      string message;
    };

    /** A list of errors
      *
      */
    class DeserializationErrorList{
    public:
      DeserializationErrorList(void){}
      ~DeserializationErrorList(void){};
      
      void add(const string&, DeserializationErrorType, const string&);

      bool empty(void) const;
      size_t size(void) const;
      
    private:
      /// The internal error list 
      list<DeserializationError> mList;
    };
  }
}
#endif // !_DESERIALIZATION_ERROR_LIST_HPP_
