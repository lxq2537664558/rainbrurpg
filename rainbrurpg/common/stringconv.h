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

/** \file stringconv.h
  * Declares a singleton to convert string format
  *
  * Modifications :
  * - 23 oct 2008 : BITSET_STR added bacause of an error on win32 platform
  * - 11 jun 2008 : \ref RainbruRPG::Core::StringConv::itobin "itobin()" 
  *                 implementation
  * - 31 may 2007 : 
  *      - \ref RainbruRPG::Core::StringConv::stoi "stoi()" replace ctoi()
  *      - Fix a bug in ctoi() when receiving \c NULL string
  * - 09 mar 2007 : Add the \ref RainbruRPG::Core::StringConv::xmlStripNewLine 
  *                 "xmlStripNewLine()" and 
  *                 \ref RainbruRPG::Core::StringConv::xmlToNewLine 
  *                 "xmlToNewLine" functions.
  * - 01 nov 2006 : Starting implementation
  */
#ifndef STRING_CONVERTER_H
#define STRING_CONVERTER_H

#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>

#include "singleton.h"

using namespace std;
using namespace RainbruRPG::Core;

/** \def BITSET_STR
  * Call the to_string() method on a STL bitset object
  * 
  * This macro is needed when cross-compiling because the behaviour
  * of the bitset.to_string() function is different in GNU/Linux and 
  * Win32 platforms.
  *
  * \note Please do not modify the synthax of the Win32 version of this macro.
  *       In the following part :
  *       <pre>
  *       x.to_string<char, char_traits<char>, allocator<char> >()
  *                                                           ^
  *                                                           |
  *                                                       this space
  *       </pre>
  *       must not be removed to avoid the following error : <code>error: 
  *       '>>' should be '> >' within a nested template argument list</code>.
  *       
  */
#ifdef __linux__
#  define BITSET_STR(x) (x.to_string())
#elif defined __WIN32__
#  define BITSET_STR(x) (x.to_string<char, char_traits<char>, \
                         allocator<char> >())
#else
#  error "Bitset to string conversion is not implemented for this platform"
#endif

namespace RainbruRPG {
  namespace Core{

    /** A singleton to convert string format
      *
      * Be carefull, some functions of this class must be freed by a
      * call to \ref StringConv::freeTte() "freeTte()". Please see the 
      * detail of a function before using it.
      *
      * On Win32, the mbsrtowcs function needs to be linked with the
      * msvcr60, msvcr library.
      *
      * StringConv can also manage xml strings. It can strip newlines from
      * them or make the newline available in c++ format. See
      * the xmlStripNewLine() and xmlToNewLine() function documentation
      * for more information.
      *
      */
    class StringConv : public Singleton<StringConv>{
    public:
      /** An empty default consdtructor */
      StringConv(){};

      // integer to...
      std::string itos(int);
      const char* itoc(int);

      std::string itobin(int,const int);

      std::string ftos(float);
      const char* ftoc(float);

      std::string btos(bool);
      const char* btoc(bool);

      int stoi(const std::string&);
      bool ctob(const char*);
      float ctof(const char*);

      void freeTte();

      std::string xmlStripNewLine(std::string);
      std::string xmlToNewLine(std::string);

    private:
      /** Forbidden copy constructors
        *
	* In a singleton the use of this method must be forbidden.
	*
	* \param obj A StringConv
	*/
      StringConv(const StringConv& obj);

      /** Forbidden assignment
        *
	* In a singleton the use of this method must be forbidden.
	* \param obj A StringConv
	*/
      StringConv& operator=(const StringConv& obj);

      /** The global char* variable used by some function */
      char *tte;
      /** A guardian to the freeTte function */
      bool mustFree;


    };
  }
}
#endif // STRING_CONVERTER_H
