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

/** \file AttributeModifierList.hpp
  * Defines a list of attribute modifier
  *
  * Modifications :
  * - 30 nov 2010 : CamelCased files
  * - 18 mar 2009 : string ready to be translated
  * - 31 jul 2008 : Documentation improved
  * - 02 mar 2007 : Avoid std::cout during unit testing
  *                 Inprove documentation
  *
  */
#ifndef _ATTRIBUTE_MODIFIER_LIST_HPP_
#define _ATTRIBUTE_MODIFIER_LIST_HPP_

#include <iostream>
#include <string>
#include <list>
#include <sstream>

#include "logger.h"
#include "stringconv.h"
#include "rainbrudef.h" // For the gettext stuff

using namespace std;

namespace RainbruRPG{
  namespace Network {
    namespace Ident {


      /** The type of a modifier
        *
	* It can be its sign.
	*/
      enum tAttributeModifierType{
	AMT_PLUS,  //!< A +? modifier
	AMT_MINUS  //!< A -? modifier
      };

      /** A struct used to store an attribute's modifier
        *
	* A attribute's modifier can modify a numeric attribute. It is
	* found in the website-side xml file in the form +? or -? where
	* ? is an integer.
	*/
      struct tAttributeModifierListItem{
	tAttributeModifierType type;  //!< the type (sign) of the modifier
	int value;    //!< The value of the modifier (the ?)
      };

      /** A std::list of tAttributeModifierType
        *
	* Used to store all the modifiers.
	*/
      typedef std::list<tAttributeModifierListItem> tAttributeModifierList;

      /** A list of attribute's modifier
        *
	* It keep in a stl list all the modifiers of an attribute and
	* give the total of them. A modifier is in form +x or -x. x is 
	* an unsigned integer.
	*
	* First, create an instance of AttributeModifierList. Then call
	* addModifier with the modifier string. The refrsh methode is call
	* automatically. You can get the total with getTotal(). You can also 
	* add the inverse of a modifier with addModifierInverse(std::string), 
	* when you want to remove it.
	*
	* An unsigned modifier string is not added as we can know its sign.
	* Unsigned modifiers are not considered to be positive modifiers.
	*
	*/
      class AttributeModifierList{
      public:
	AttributeModifierList();
	~AttributeModifierList();

	void addModifier(std::string);
	void addModifierInverse(std::string);
	int getTotal();
	std::string getTotalString();

      private:
	void refresh();
	void addToTotal(const tAttributeModifierListItem*);

	/** The global list of attribute's modifier */
	tAttributeModifierList modList;

	/** An integer value representing the total value of modifiers
	  *
	  */
	int total;
      };

    }
  }
}


#endif // _ATTRIBUTE_MODIFIER_LIST_HPP_
