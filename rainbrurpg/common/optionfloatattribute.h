/*
 *  Copyright 2006-2009 Jerome PASQUIER
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

/** \file optionfloatattribute.h
  * Declares a float attribute for the launcher's options editor
  *
  * Modifications :
  * - 29 apr 2009 : Added caption in constructor
  * - 04 apr 2009 : Now using gettext
  * - 09 aug 2008 : Single file documentation
  *
  */

#ifndef OPTION_FLOAT_ATTRIBUTE_H
#define OPTION_FLOAT_ATTRIBUTE_H

#include <string>
#include <cmath>

#include "logger.h"
#include "optionattribute.h"
#include "stringconv.h"
#include "rainbrudef.h" // For the gettext stuff

using namespace std;


namespace RainbruRPG {
  namespace Options{

    /** An option storing a signed float value
      *
      * It is used with the OptionManager and may be added to an
      * OptionButton. 
      *
      */
    class OptionFloatAttribute : public OptionAttribute{

    public:
      OptionFloatAttribute(const char*, const char*);
      /** An empty default constructor */
      ~OptionFloatAttribute(){};

      virtual bool setValueStr(const char*);
      virtual const char* getValueStr() const;

      void setStep(float);
      float getStep();

      virtual void update();
      virtual void increase();
      virtual void decrease();

    protected:
      void controlStep();

      /** The value of the OptionIntAttribute */
      float value;

      /** The value for incrementing or decrementing value 
        *
	* I cannot set a unsigned float so it is a float, but
	* i must use abs to get only positive number.
	*/
      float step;

    };
  }
}

#endif // OPTION_FLOAT_ATTRIBUTE_H

