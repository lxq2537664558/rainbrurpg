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
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

#ifndef OPTION_BUTTON_H
#define OPTION_BUTTON_H

#include <string>
#include <list>

#include "logger.h"
#include "optionattribute.h"

using namespace std;


namespace RainbruRPG {
  namespace Options{


    /** A stl list of  OptionAttribute*/
    typedef list<OptionAttribute*> tOptionAttributeList;


    /** A button for the launcher's options dialog
      *
      * It is used by the OptiionManager and is inserted into OptionPanel
      */
    class OptionButton{
    public:
      OptionButton(const char*);
      OptionButton(const char*, const char*);

      void setCaption(const char*);
      void setIconFilename(const char*);

      const char* getCaption();
      const char* getIconFilename();

      void setFoxPanelId(int);
      int getFoxPanelId();

      void update();

      void add(OptionAttribute*);
      tOptionAttributeList* getAttributeList();

    private:
      /** The caption of the panel */
      const char* m_caption;

      /** The filename of the icon of the panel */
      const char* m_iconFilename;

      /** The FOX panel Id
        *
	* To be able to show the panel (FXComposite) corresponding with 
	* the button, we must keep its identifier.
	*
	* When we click on the button, we can call 
	* FXSwitcher::setCurrent(FXint index).
	*
	* The default value is -1.
	*
	* \sa getFoxPanelId(), setFoxPanelId()
	*
	*/
      int foxPanelId;

      /** The list of OptionAttribute */
      tOptionAttributeList attrbList;
    };
  }
}


#endif // OPTION_BUTTON_H