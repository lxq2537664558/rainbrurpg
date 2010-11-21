/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file Serializable.hpp
  *
  * Declare a serializable object
  *
  * Modifications :
  * - 16 nov 2009 : Starting implementation
  *
  */

#ifndef _SERIALIZABLE_HPP_
#define _SERIALIZABLE_HPP_

#include <string>

/// The separator character for serialized strings 
#define STRING_SEPARATOR '\t'


using namespace std;

namespace RainbruRPG{
  namespace OgreGui{

    /** This is the base class of all serailizable objects
      *
      *
      *
      */
    class Serializable{
    public:
      Serializable(const string&);
      virtual ~Serializable(void);

      void setUniqueName(const string&);
      const string& getUniqueName(void) const;

      template<class Archive> bool serialize(Archive&)const;
      template<class Archive> bool deserialize(Archive&)const;

      virtual bool operator==(const Serializable&)const;
      virtual bool operator!=(const Serializable&)const;
      virtual bool equal(const Serializable*)const;

    protected:
      /** The unique name of the object
        *
	* This name will be used when deserializing, to be sure
	* we are taking values of the same object. It is declared
	* as protected to be used by WidgetList.
	*
	*/
      string mUniqueName;

      /** The name passed to the constructor */
      string mName;

    };
  }
}
#endif // !_SERIALIZABLE_HPP_
