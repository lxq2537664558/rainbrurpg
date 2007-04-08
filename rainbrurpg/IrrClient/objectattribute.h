/*
 *  Copyright 2006 Jerome PASQUIER
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
 *  along with Foobar; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

#ifndef OBJECT_ATTRIBUTE_H

#define OBJECT_ATTRIBUTE_H


namespace RainbruRPG {
  namespace Exception{


    /** The super-class of all object attribute
      *
      * An Attribute is a pair Name/Value. It has a description
      * field for the console show object command and an access
      * control (the attribute can be read-only).
      *
      * There are several attribute type : IntAttribute,
      * CharAttribute, BoolAttribute.
      *
      */
    class ObjectAttribute{
    public:
      void setName( const char* name);
      const char* getName();
     
      void setDesc( const char* desc);
      const char* getDesc();
 
      const char* getAccessText();

      /** Return a char * defining the type of the attribute
        *
	* This function is used by the console to show the type of the
	* attribute. It must be \c [int] \c [char] \c [bool]...
	*
	*/
      virtual const char* getTypeText()=0;

      /** Return a char * of the value
        *
	* This function is used by the console to get the
	* value. According to the type of the child the implementation
	* will be different.
	*
	*/
      virtual const char* getValueText()=0;

      /** Set the value of the attribute
        *
	* This function is used by the console to set the
	* value. According to the type of the child the implementation
	* will be different. The function must return if the set is
	* correct.
	*
	* \return \c true if the affectation is correct otherwise \c
	* false.
	*/
      virtual bool setValueText(const char *)=0;

      virtual int count();

    private:
      /** The name of the attribute
        *
	* This name can't be null. It's the name we use in the console to
	* access its attributes.
	*/
      const char* name;
      /** The description of the attribute
        *
	* The description will be shown with the name with the show
	* command
	*
	*/
      const char* desc;

    protected:
      ObjectAttribute( const char* name );

      /** Is this attribute in read only mode
        *
	* Some attributes can't be modified.
	*/
      bool readOnly;
    };
  }
}
#endif// OBJECT_ATTRIBUTE_H
