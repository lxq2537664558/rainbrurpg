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

#ifndef BOOL_ATTRIBUTE_H
#define BOOL_ATTRIBUTE_H

#include "objectattribute.h"

namespace RainbruRPG{
  namespace Exception{


    /** The boolean attribute 
      *
      * A boolean can take the value \c on or \c off
      *
      */
    class BoolAttribute: public ObjectAttribute{
    public:
      virtual const char* getTypeText();
      virtual const char* getValueText();
      virtual bool setValueText(const char *);

    private:

      /** The value of the attribute
        *
	*
	*
	*/
      bool value;

    protected:
      BoolAttribute(const char* name);

      /** Set the value according to the type
        *
	* This method must be override. It is called when
	* the value change, called by setValueText(char *);
	*
	*/
      virtual void setValue(bool)=0;
    };
  }
}

#endif // BOOL_ATTRIBUTE_H
