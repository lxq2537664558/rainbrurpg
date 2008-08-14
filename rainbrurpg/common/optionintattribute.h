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

/** \file optionintattribute.h
  * Declares an integer option for the launcher's options editor
  *
  * Modifications :
  * - 09 aug 2008 : Single file documentation
  *
  */

#ifndef OPTION_INTEGER_ATTRIBUTE_H
#define OPTION_INTEGER_ATTRIBUTE_H

#include <string>

#include "logger.h"
#include "optionattribute.h"
#include "stringconv.h"

using namespace std;


namespace RainbruRPG {
  namespace Options{

    /** An option storing a signed int value
      *
      * It is used with the OptionManager and may be added to an
      * OptionButton. 
      *
      */
    class OptionIntAttribute : public OptionAttribute{

    public:
      OptionIntAttribute(const char*);
      /** An empty default destructor */
      ~OptionIntAttribute(){};

      virtual void update();
      virtual bool setValueStr(const char*);
      virtual const char* getValueStr() const;

      void setStep(unsigned int);
      unsigned int getStep();

      virtual void increase();
      virtual void decrease();

    protected:
      void controlStep();


      /** The value of the OptionIntAttribute */
      int value;

      /** The value for incrementing or decrementing value */
      unsigned int step;


    };
  }
}

#endif // OPTION_INTEGER_ATTRIBUTE_H

