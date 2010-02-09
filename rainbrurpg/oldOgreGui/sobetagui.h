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

/** \file sobetagui.h
  * Declares a skin based on SkinOverlay, drawing like BetaGUI does
  *
  * \note We must scope the Rectangle class with its namespace in this 
  *       file to avoid complications when cross-compiling to Win32
  *       platform.
  *
  * Modifications :
  * - 16 feb 2009 : Fix a bug in drawToolTip().
  * - 23 sep 2008 : \ref RainbruRPG::OgreGui::soBetaGui::getVScrollBarMinHeight
  *                 "getVScrollBarMinHeight()" and 
  *                 \ref RainbruRPG::OgreGui::soBetaGui::getHScrollBarMinWidth 
  *                 "getHScrollBarMinWidth()" added.
  * - 30 aug 2008 : Single file documentation
  * - 25 mar 2008 : drawMultiColumnList implementation
  * - 22 jan 2008 : drawTextInput implementation using QuadRenderer
  * - 27 sep 2007 : starting implementation
  *         
  */

#ifndef _OGRE_GUI_SKIN_BETA_GUI_H_
#define _OGRE_GUI_SKIN_BETA_GUI_H_

#include "skin.h"

#include <OgreVector4.h>
#include <OgreTexture.h>


// Forward declarations
namespace RainbruRPG{
  namespace OgreGui{
    class QuadRenderer;
    class Font;
    class TextSettings;
    class VScrollBar;
    class HScrollBar;
    class MultiColumnList;
    class wdMultiColumnList;
    class PopupMenu;
    class ToolTip;
  }
}
// End of forward declarations


using namespace Ogre;

namespace RainbruRPG{
  namespace OgreGui{

    /** A skin based on SkinOverlay, drawing like BetaGUI does
      *
      */
    class soBetaGui : public Skin{
    public:
      soBetaGui();
      virtual ~soBetaGui();

      virtual void drawWindow(QuadRenderer*, Ogre::Rectangle, String);
      virtual void drawPushButton(QuadRenderer*,Vector4, String, Window*, bool, bool);
      virtual void drawResizeGrip(QuadRenderer*, Vector4, bool);
      virtual void drawTitleBar(QuadRenderer*, Vector4, String, bool);
      virtual void drawLabel(QuadRenderer* qr, Ogre::Rectangle dim, 
			     String caption, Window* parent);
      virtual void drawTextInput(QuadRenderer*, Ogre::Rectangle , String , 
				 Window*, bool active, int selStart = -1,
				 int selEnd = -1);

      virtual void drawVerticalScrollbar(QuadRenderer*qr, VScrollBar* );
      virtual void drawHorizontalScrollbar(QuadRenderer*qr, HScrollBar* );
      virtual void drawMultiColumnList(QuadRenderer*, MultiColumnList*, bool );
      virtual void drawToolTip(QuadRenderer*, ToolTip* );
      virtual void drawPopupMenu(QuadRenderer*, PopupMenu*);
      virtual void drawDialog(QuadRenderer*, Dialog* );

      virtual int getVScrollBarMinHeight(void);
      virtual int getHScrollBarMinWidth(void);

    private:
      // ============= MATERIALS VALUES =================
      /** The text input's material name */
      Ogre::String mnTextInput;
      /** The dialog border material name */
      Ogre::String mnDialogBorder;


      // ============= FONTS VALUES =================
      /** The text setting for drawing title bar caption */
      TextSettings* tsTitleBar;

      /** The text setting for drawing push button caption when enable */
      TextSettings* tsPushButton;

      /** The text setting for drawing push button caption when disable */
      TextSettings* tsDisabledPushButton;

      /** The text setting for drawing label caption */
      TextSettings* tsLabel;

      /** The text setting for drawing rext input content */
      TextSettings* tsTextInput;

      /** The texture of the window background */
      TexturePtr mWindowTexture;

      /** The texture of the titlebar background */
      TexturePtr mTitleBarTexture;
      /** The texture of the active titlebar background */
      TexturePtr mTitleBarActiveTexture;

      /** The texture of the resizegrip background */
      TexturePtr mResizeGripTexture;
      /** The texture of the active resizegrip background */
      TexturePtr mResizeGripActiveTexture;

      /** The texture of the push button background */
      TexturePtr mPushButtonTexture;
      /** The texture of the active push button background */
      TexturePtr mPushButtonActiveTexture;

      /** The texture used to draw TextInput */
      TexturePtr mTextInputTexture;
      /** The texture used to draw active TextInput */
      TexturePtr mTextInputActiveTexture;

      /** The texture used to draw the top arrow of the vertical scrollbar 
        * in normal mode.
	*
	*/
      TexturePtr mVerticalScrollBarTopArrow;

      /** The texture used to draw the bottom arrow of the vertical scrollbar 
        * in normal mode.
	*
	*/
      TexturePtr mVerticalScrollBarBottomArrow;

      /** The texture used to draw the top of the body of the vertical 
        * scrollbar 
	*
	*/
      TexturePtr mVerticalScrollBarBodyTop;

      /** The texture used to draw the middle of the body of the vertical 
        * scrollbar 
	*
	*/
      TexturePtr mVerticalScrollBarBodyMid;

      /** The texture used to draw the bottom of the body of the vertical 
        * scrollbar 
	*
	*/
      TexturePtr mVerticalScrollBarBodyBot;

      /** The texture used to draw the cursor of the vertical 
        * scrollbar in normal mode.
	*
	*/
      TexturePtr mVerticalScrollBarCursor;

      /** The texture used to draw the top arrow of the vertical scrollbar 
        * in active mode.
	*
	*/
      TexturePtr mVerticalScrollBarTopArrowActive;

      /** The texture used to draw the bottom arrow of the vertical scrollbar 
        * in active mode.
	*
	*/
      TexturePtr mVerticalScrollBarBotArrowActive;

      /** The texture used to draw the cursor of the vertical 
        * scrollbar in active mode.
	*
	*/
      TexturePtr mVerticalScrollBarCursorActive;

      // ====== Horizontal scroll bar =========
      /** The texture used to draw the left arrow of the horizontal 
        * scrollbar in normal mode.
	*
	*/
      TexturePtr mHorizontalScrollBarLeftArrow;

      /** The texture used to draw the right arrow of the horizontal 
        * scrollbar in normal mode.
	*
	*/
      TexturePtr mHorizontalScrollBarRightArrow;

      /** The texture used to draw the left side of the body of the horizontal 
        * scrollbar in normal mode.
	*
	*/
      TexturePtr mHorizontalScrollBarBodyLeft;

      /** The texture used to draw the middle side of the body of the 
        * horizontal scrollbar in normal mode.
	*
	*/
      TexturePtr mHorizontalScrollBarBodyMid;

      /** The texture used to draw the right side of the body of the 
        * horizontal scrollbar in normal mode.
	*
	*/
      TexturePtr mHorizontalScrollBarBodyRight;

      /** The texture used to draw the cursor of the 
        * horizontal scrollbar in normal mode.
	*
	*/
      TexturePtr mHorizontalScrollBarCursor;

      /** The texture used to draw the left arrow of the horizontal 
        * scrollbar in active mode.
	*
	*/
      TexturePtr mHorizontalScrollBarLeftArrowActive;

      /** The texture used to draw the right arrow of the horizontal 
        * scrollbar in active mode.
	*
	*/
      TexturePtr mHorizontalScrollBarRightArrowActive;

      /** The texture used to draw the cursor of the 
        * horizontal scrollbar in active mode.
	*
	*/
      TexturePtr mHorizontalScrollBarCursorActive;

      /** The drawer used for MultiColumnList */
      wdMultiColumnList* mMultiColumnListDrawer;
    };

  }
}
#endif //_OGRE_GUI_SKIN_OVERLAY_BETA_GUI_H_
