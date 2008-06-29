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

/* Modifications :
 * - 13 may 2008 : draw* functions are not pure virtual anymore
 * - 17 apr 2008 : drawPopupMenu implementation
 * - 25 mar 2008 : drawMultiColumnList implementation
 * - 04 feb 2008 : Class renamed from SkinOverlay to Skin
 * - 15 nov 2007 : createBorderWindow implementation
 * - 15 oct 2007 : Skin class removed
 * - 27 sep 2007 : starting implementation
 *         
 */

#ifndef _OGRE_GUI_SKIN_H_
#define _OGRE_GUI_SKIN_H_

#include <string>
#include <OgreOverlayContainer.h>
#include <OgreRectangle.h>

//#include "bgbutton.h"

// Forward declarations
namespace BetaGUI{
  class GUI;
  class Window;
}
namespace RainbruRPG{
  namespace OgreGui{
    class QuadRenderer;
    class VScrollBar;
    class HScrollBar;
    class MultiColumnList;
    class PopupMenu;
    class ToolTip;
    class Dialog;
  }
}
// End of forward declarations

using namespace Ogre;
using namespace BetaGUI;

namespace RainbruRPG{
  namespace OgreGui{

    /** A skin base-class
      *
      * \note For historical reasons, this class was formerly called
      *       SkinOverlay. Its child derived classes are called so* (i.e.
      *       soBetaGui, soNavigation).
      *
      */
    class Skin{
    public:
      Skin(const std::string& n="unamedSkinOverlay");
      virtual ~Skin();

      virtual void drawWindow(QuadRenderer*, Rectangle, String );
      virtual void drawResizeGrip(QuadRenderer*, Vector4, bool );
      virtual void drawTitleBar(QuadRenderer*, Vector4, String, bool);
      virtual void drawPushButton(QuadRenderer*,Vector4,String,Window*,bool,bool);
      virtual void drawTextInput(QuadRenderer*, Rectangle, String, Window*, 
				 bool, int selStart = -1, int selEnd = -1);
      virtual void drawLabel(QuadRenderer*, Rectangle, String, Window* );
      virtual void drawToolTip(QuadRenderer*, ToolTip*);
      virtual void drawVerticalScrollbar(QuadRenderer*, VScrollBar* );
      virtual void drawHorizontalScrollbar(QuadRenderer*, HScrollBar* );
      virtual void drawMultiColumnList(QuadRenderer*, MultiColumnList*, bool );
      virtual void drawPopupMenu(QuadRenderer*, PopupMenu* );
      virtual void drawDialog(QuadRenderer*, Dialog* );

      virtual unsigned int getDialogBorderSize(void);

     int getTitleBarHeight(void);

    protected:
     void logUnimplementedFunction(const std::string&);

      /** The resizeGrip material name*/
      Ogre::String mnResizeGrip;
      /** The TitleBar material name*/
      Ogre::String mnTitleBar;
      /** The PushButton material name*/
      Ogre::String mnPushButton;

      /** Defines the border size of a dilaog
        *
	* Some widget are automatically placed from this value.
	*
	*/
      unsigned int dialogBorderSize;
      /** The TitleBar heigh in pixels */
      int mTitleBarHeight;

      /** The skin name */
      std::string mName;
    };

  }
}

#endif // _OGRE_GUI_SKIN_H_
