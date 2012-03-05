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

/** \file optionstringattribute.h
  * Declares a string for the launcher's options editor
  *
  * Modifications :
  * - 30 apr 2009 : Added caption parameter to constructor
  * - 14 apr 2009 : Using gettext strings
  * - 09 aug 2008 : Single file documentation
  *
  */

#ifndef OPTION_STRING_ATTRIBUTE_H
#define OPTION_STRING_ATTRIBUTE_H

#include <string>

#include "Logger.hpp"
#include "optionattribute.h"

#include "rainbrudef.h" // For the gettext stuff

using namespace std;


namespace RainbruRPG {
  namespace Options{


    /** Describes a string option
      *
      * \sa OptionAttribute
      */
    class OptionStringAttribute : public OptionAttribute{

    public:
      OptionStringAttribute(const char*, const char*);
      /** An empty default destructor */
      ~OptionStringAttribute(){};

      virtual void update();
      virtual bool setValueStr(const char*);
      virtual const char* getValueStr() const;

    private:
      /** The value of the attribute */
      std::string value;

    };
  }
}

#endif // OPTION_STRING_ATTRIBUTE_H

