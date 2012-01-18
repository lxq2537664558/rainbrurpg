/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file NullWindowHandleException.hpp
  * Declares an exception thrown if window handle cannot be found
  *
  * Modifications :
  * - 08 jan 2011 : First implementation
  *
  */

#ifndef _NULL_WINDOW_HANDLE_EXCEPTION_HPP_
#define _NULL_WINDOW_HANDLE_EXCEPTION_HPP_

#include <exception>
#include <string>

// Forward declaration
namespace Ogre
{
  class RenderWindow;
}
//end of forward declaration

using namespace std;

namespace RainbruRPG
{
  namespace Exception
  {
    /** An exception used to create a usefull message when
      * window handle cannot be found
      *
      */
    class NullWindowHandleException : public std::exception
    {
    public:
      NullWindowHandleException(Ogre::RenderWindow*) throw();
      virtual ~NullWindowHandleException() throw();

      virtual const char* what() const throw();

    private:
      string getPlatform() const;

      string mMessage; //!< The exception message

    };

  }
}

#endif // !_NULL_WINDOW_HANDLE_EXCEPTION_HPP_
