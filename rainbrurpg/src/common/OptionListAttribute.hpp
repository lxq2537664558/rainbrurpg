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

/** \file OptionListAttribute.hpp
  * Declares a list of string for the launcher's options editor
  *
  * Modifications :
  * - 30 apr 2009 : Need caption in constructor
  * - 14 apr 2009 : Using gettext strings
  * - 09 aug 2008 : Single file documentation
  *
  */

#ifndef OPTION_LIST_ATTRIBUTE_H
#define OPTION_LIST_ATTRIBUTE_H

#include <string>
#include <list>

#include "Logger.hpp"
#include "OptionAttribute.hpp"
#include "StringConv.hpp"

#include "RainbruDef.hpp" // For the gettext stuff

using namespace std;


namespace RainbruRPG {
  namespace Options{

    /** The values of a OptionListAttribute */
    typedef std::list<const char*> tValueList;

    /** An option storing a list of string
      *
      * It is used with the OptionManager and may be added to an
      * OptionButton. 
      *
      */
    class OptionListAttribute : public OptionAttribute{

    public:
      OptionListAttribute(const char*, const char*);
      /** An empty default constructor */
      virtual ~OptionListAttribute(){};

      virtual bool setValueStr(const char*);
      virtual const char* getValueStr() const;
      virtual void update();


      bool exists(const char*);
      void add(const char*); 
      unsigned int valueCount();
      tValueList* getValueList();

    protected:
      /** The value of the OptionListAttribute */
      std::string value;

    private:
      /** The list of possible values */
      tValueList valueList;
      /** This attribute has set a default value
        *
	* The initial value of this boolean is \c false, when we
	* first use add(), it is set to true and the value added is
	* set using setValueStr()
	*
	*/
      bool hasDefaultValue;
    };
  }
}

#endif // OPTION_LIST_ATTRIBUTE_H

