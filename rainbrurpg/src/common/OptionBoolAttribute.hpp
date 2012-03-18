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

/** \file OptionBoolAttribute.hpp
  * Declares an option attribute storing a boolean value
  *
  * Modifications :
  * - 30 apr 2009 : Added caption parameter to constructor
  * - 04 apr 2009 : Now using gettext
  * - 08 aug 2008 : Single file documentation
  *
  */

#ifndef OPTION_BOOLEAN_ATTRIBUTE_H
#define OPTION_BOOLEAN_ATTRIBUTE_H

#include <string>

#include "Logger.hpp"
#include "OptionAttribute.hpp"
#include "StringConv.hpp"

#include "RainbruDef.hpp"

using namespace std;


namespace RainbruRPG {
  namespace Options{

    /** An option attribute storing a boolean value
      *
      * A boolean attribute is shown as a checkbox in the FOX LauncherOption
      * dialog
      *
      * \sa OptionManager, OptionAttribute
      *
      */
    class OptionBoolAttribute : public OptionAttribute{

    public:
      OptionBoolAttribute(const char*, const char*);
      /** An empty default constructor 
        *
        */
      ~OptionBoolAttribute(){};

      virtual bool setValueStr(const char*);
      virtual const char* getValueStr() const;

      virtual void update();

    private:
      /** The boolean value of the attribute
        *
	* \sa setValueStr(), getValueStr()
	*
	*/
      bool value;

    };
  }
}

#endif // OPTION_BOOLEAN_ATTRIBUTE_H

