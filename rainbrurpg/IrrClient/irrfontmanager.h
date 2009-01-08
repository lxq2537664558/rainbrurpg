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
 *  along with Foobar; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

#ifndef IRRLICHT_FONT_MANAGER_H
#define IRRLICHT_FONT_MANAGER_H

#include <irrlicht.h>
#include <string>
#include <stdlib.h>
#include <iostream>

#include "singleton.h"

using namespace std;
using namespace irr;
using namespace irr::core;
using namespace irr::gui;
using namespace RainbruRPG::Core;

namespace RainbruRPG {
  namespace Core{

    /** The name of font
      *
      *
      */
    enum tIrrFont{
      IFM_COURRIER,  //!< The console font
      IFM_SHA_BLACK, //!< The Shadowed black gothic font
      IFM_PLA_BLACK, //!< The Plain black gothic font
      IFM_INC_BLACK, //!< The Incised black gothic font
      IFM_CRUMBLE   //!< The Crumble gothic font
    };


    /** A singleton to help changing irrlicht font 
      *
      * Irrlicht uses \c irr::gui::IGUIFont instances to set fonts. But we
      * can only set the default font in \c irr::gui::IGUISkin and set
      * override font in \c irr::gui::IGUIStaticText,
      * \c irr::gui::IGUIEditBox, \c irr::gui::IGUIButton.
      *
      * The problem appears with the console. The Console's listBox
      * wich can have his own font. So we must have a global font in
      * courrier and then override the font in the other widgets.
      *
      * IrrFontManager can setGlobalFont(stringw fontName, stringw
      * size), setWidgetFont([widget], stringw fontName, stringw
      * size) where widget can be  \c irr::gui::IGUIStaticText,
      * \c irr::gui::IGUIEditBox and \c irr::gui::IGUIButton.
      *
      */
    class IrrFontManager : public Singleton<IrrFontManager>{
    public:
      IrrFontManager(){};

      void setGlobalFont(tIrrFont fontName, unsigned int size);

      void setWidgetFont(irr::gui::IGUIStaticText *w, tIrrFont fontName, unsigned int size);
      void setWidgetFont(irr::gui::IGUIEditBox *w, tIrrFont fontName, unsigned int size);
      void setWidgetFont(irr::gui::IGUIButton *w, tIrrFont fontName, unsigned int size);

    private:
      /** Unimplemented copy constructors 
        *
	* In a singleton the use of this method must be forbidden.
	* 
	* \param obj A IrrFontManager
	*/
      IrrFontManager(const IrrFontManager& obj);

      /** Unimplemented assignment
        *
	* In a singleton the use of this method must be forbidden.
	* \param obj A IrrFontManager
	*/
      IrrFontManager& operator=(const IrrFontManager& obj);

     char* createFontFileName(tIrrFont fontName, unsigned int size );
      irr::gui::IGUIFont* loadFont(tIrrFont fontName, unsigned int size );
    };
  }
}
#endif // IRRLICHT_FONT_MANAGER_H
