/*
 *  Copyright 2006-2007 Jerome PASQUIER
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
 * - 15 oct 2007 : Skin class removed
 * - 27 sep 2007 : starting implementation
 *         
 */

#ifndef _OGRE_GUI_SKIN_OVERLAY_H_
#define _OGRE_GUI_SKIN_OVERLAY_H_

#include <string>
#include <OGRE/OgreOverlayContainer.h>

// Forward declarations
namespace BetaGUI{
  class Button;
  class GUI;
  class Window;
}
// End of forward declarations

using namespace Ogre;
using namespace BetaGUI;

namespace RainbruRPG{
  namespace OgreGui{

    /** A skin base-class on Ogre::Overlay
      *
      * There is two createOverlay() functions depending wich is the
      * parent's type bacause Ogre::Overlay and Ogre::OverlayContainer 
      * cannot be casted. Internally, both use createOverlayImpl to 
      * graphically create the Overlay.
      *
      * For the buttons to get a mouse over effect, the materials names
      * must be \e basename and <em>basename.active</em>. The 
      * <em>.active</em> is mandatory and must be the last characters of
      * the material name.
      *
      */
    class SkinOverlay{
    public:
      SkinOverlay(std::string n="unamedSkinOverlay");

      Ogre::OverlayContainer* getOverlayByName(Ogre::String);

      void createOverlay(String, Vector4,String, Overlay*);
      void createOverlay(String, Vector4, String, OverlayContainer*);

      void createCaption(String, Vector4, String, String, 
			 unsigned int, OverlayContainer*);

      virtual void setTransparency(Ogre::OverlayElement*, float f);
      virtual void setCaptionTransparency(Ogre::OverlayElement*, float f);

     /** Create a window
        *
        * Please see the sub-class documentation for implementation
        * details.
        *
        * \param name    The internal name of the window
        * \param dim     The window's dimension in pixels in a 
        *                Ogre::Vector4 object
        * \param caption The title bar caption
        * \param bg      The BetaGUI::GUI object 
        *
        */
      virtual void createWindow(String name, Vector4 dim, String caption, 
                                GUI* bg)=0;
      /** Graphically create a ResizeGrip widget
        *
        * \param name    The internal name of the ResizeGrip (must be unique)
        * \param dim     The widget's dimension in pixels in a 
        *                Ogre::Vector4 object
        * \param parent  The parent window
        *
        */
     virtual void createResizeGrip(String name, Vector4 dim, Window* parent)=0;

      /** Graphically create a TitleBar widget
        *
        * \param name    The internal name of the ResizeGrip (must be unique)
        * \param dim     The widget's dimension in pixels in a 
        *                Ogre::Vector4 object
        * \param caption The rendered text
        * \param parent  The parent window
        *
        */
     virtual void createTitleBar(String name, Vector4 dim, String caption,Window* parent)=0;

      /** Graphically create a PushButton widget
        *
        * \param name    The internal name of the push button (must be unique)
        * \param dim     The widget's dimension in pixels in a 
        *                Ogre::Vector4 object
        * \param caption The rendered text
        * \param parent  The parent window
        *
        */
     virtual void createPushButton(String name, Vector4 dim, String caption, Window* parent)=0;

      /** Graphically create a TextInput widget
        *
        * \param name    The internal name of the widget (must be unique)
        * \param dim     The widget's dimension in pixels in a 
        *                Ogre::Vector4 object
        * \param caption The rendered text
        * \param parent  The parent window
        *
        */
     virtual void createTextInput(String name, Vector4 dim, String caption, Window* parent)=0;

     virtual void activateButton(Button* button, bool active);


    protected:
      /** The resizeGrip material name*/
      Ogre::String mnResizeGrip;
      /** The TitleBar material name*/
      Ogre::String mnTitleBar;
      /** The PushButton material name*/
      Ogre::String mnPushButton;

    private:
      OverlayContainer* createOverlayImpl(String, Vector4, String);

    };

  }
}

#endif // _OGRE_GUI_SKIN_OVERLAY_H_
