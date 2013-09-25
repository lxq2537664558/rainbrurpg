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

/** \file optionattribute.h
  * Declares an attribute that will be shown in the launcher's option editor
  *
  * Modifications :
  * - 29 apr 2009 : Added caption member for translation
  * - 04 apr 2009 : Using gettext strings
  * - 08 aug 2008 : Single file documentation
  *
  */


#ifndef OPTION_ATTRIBUTE_H
#define OPTION_ATTRIBUTE_H

#include <string>
#include <fox-1.6/fx.h>

#include "Logger.hpp"

using namespace std;


namespace RainbruRPG {
  namespace Options{


    /** Defines the type of an OptionAttribute
      *
      * Each attribute is typed. The OptionAttribute::type field of OptionAttribute is
      * by default sets to OAT_UNKNOWN, but this should never happen.
      *
      */
    enum tOptionAttributeType{
      OAT_UNKNOWN,     /** This should never be used */
      OAT_INTEGER,     /** An integer attribute */
      OAT_STRING,      /** A user defined string attribute */
      OAT_BOOLEAN,     /** A boolean attribute */
      OAT_FLOAT,       /** A float attribute */
      OAT_FLOAT_RANGE, /** A range of floats */
      OAT_INT_RANGE,   /** A range of integers */
      OAT_LIST         /** A list of string values */
    };

    /** An attribute that will be shown in the launcher's option dialog
      *
      * The option's attribute classes are used by the OptionManager
      * to create the LauncherOptions gui.
      *
      * It is a pure virtual class that can not be instancied. Please
      * use a subclass.
      *
      * \note Attributes ar identified by their name, always in english.
      *       The caption is the shown text, that can be translated.
      *
      * \sa OptionManager, OptionIntAttribute, OptionStringAttribute, 
      *     OptionFloatAttribute, OptionListAttribute, 
      *     OptionIntRangeAttribute, OptionFloatRangeAttribute. 
      */
    class OptionAttribute{
    public:
      OptionAttribute(tOptionAttributeType);
      /** Unimplemented default destructor needed by C++ specifications*/
      virtual ~OptionAttribute(){};

      void setType(tOptionAttributeType);
      void setName(const char*);
      void setToolTip(const char*);

      tOptionAttributeType getType();
      const char* getName();
      const char* getToolTip();

      void setCaption(const char*);
      const char* getCaption(void) const;

      void setWidget(FXObject*);
      FXObject* getWidget();

      /** A virtual function used to graphically update the value
        * of the attribute
	*
	*
	*/
      virtual void update()=0;

      /** A virtual function used in serialization of the attribute
        *
	* This function must be overloaded by subclasses. It is used
	* by the OptionManager to store the attribute value in a
	* xml file.
	*/
      virtual bool setValueStr(const char*)=0;

      /** A virtual function used in serialization of the attribute
        *
	* This function must be overloaded by subclasses. It is used
	* by the OptionManager to store the attribute value in a
	* xml file.
	*/
      virtual const char* getValueStr() const=0;

    private:
      /** The type of the OptionAttribute 
        *
	* \sa tOptionAttributeType, setType(), getType()
	*
	*/
      tOptionAttributeType type;

      /** The name of the attribute 
        *
	* \sa setName(), getName()
	*
	*/
      const char* name;

      /** The caption of the attribute
        *
	* \sa setCaption(), getCaption();
	*
	*/
      const char* mCaption;

      /** The tooltip associated with this attribute
        *
	* A tooltip is an help string shown if the LauncherOptions dialog,
	* when you let the mouse over a widget.
	*
	* \sa setToolTip(), getToolTip()
	*/
      const char* tooltip;

    protected:
      /** The widget linked to this attribute
        *
	* For the update of the graphic representation of the attribute,
	* we keep a pointer to the widget.
	*/
      FXObject* widget;
    };
  }
}


#endif // OPTION_ATTRIBUTE_H
