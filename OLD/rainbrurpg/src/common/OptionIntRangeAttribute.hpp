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

/** \file OptionIntRangeAttribute.hpp
  * Declares a range of integer for the launcher's options editor
  *
  * Modifications :
  * - 29 apr 2009 : Constructor need caption parameter
  * - 14 apr 2009 : Using gettext compliant strings
  * - 09 aug 2008 : Single file documentation
  *
  */

#ifndef OPTION_INT_RANGE_ATTRIBUTE_H
#define OPTION_INT_RANGE_ATTRIBUTE_H

#include <string>

#include "Logger.hpp"
#include "OptionIntAttribute.hpp"
#include "StringConv.hpp"

#include "RainbruDef.hpp" // For the gettext stuff

using namespace std;


namespace RainbruRPG {
  namespace Options{

    /** An option storing a signed int value beetween a range
      *
      * It is used with the OptionManager and may be added to an
      * OptionButton. 
      *
      */
    class OptionIntRangeAttribute : public OptionIntAttribute{

    public:
      OptionIntRangeAttribute(const char*,const char*, int, int);
      OptionIntRangeAttribute(const char*,const char*, int, int, unsigned int);

      /** An empty default destructor */
      ~OptionIntRangeAttribute(){};

      void setMinRange(int);
      void setMaxRange(int);

      int getMinRange();
      int getMaxRange();

      virtual bool setValueStr(const char*);
      virtual void update();
      virtual void increase();
      virtual void decrease();

    private:
      /** the minimum range of the value */
      int minRange;

      /** the maximum range of the value */
      int maxRange;

    };
  }
}

#endif // OPTION_INT_RANGE_ATTRIBUTE_H

