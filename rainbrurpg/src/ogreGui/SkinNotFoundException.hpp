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

#ifndef _SKIN_NOT_FOUND_EXCEPTION_HPP_
#define _SKIN_NOT_FOUND_EXCEPTION_HPP_

#include <exception>

#include <string>

using namespace std;

namespace RainbruRPG
{
  namespace Exception{

    /** An exception thrown when Drawable cannot load a texture
      *
      *
      */
    class SkinNotFoundException : public std::exception
    {
    public:
      SkinNotFoundException(const string&, const string&) throw();
      virtual ~SkinNotFoundException() throw();

      virtual const char* what() const throw();

    private:
      string mMessage; //!< The Exception's message
    };
  }
}

#endif // !_SKIN_NOT_FOUND_EXCEPTION_HPP_
