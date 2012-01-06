/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file skinmanager.h
  * Declares the OgreGui skins manager
  *
  * Modifications :
  * - 09 jun 2008 : cleanup implementation
  * - 08 nov 2007 : OSI_PARENT added
  * - 27 sep 2007 : starting implementation
  *         
  */

#ifndef _OGRE_GUI_SKIN_MANAGER_H_
#define _OGRE_GUI_SKIN_MANAGER_H_

#include "singleton.h"
#include "skin.h"

#include <vector>

#include "config.h" // For RAINBRU_RPG_DEBUG macro

using namespace std;
using namespace RainbruRPG::Core;

// Forward declarations
namespace RainbruRPG{
  namespace OgreGui{
    class Widget;
  }
}
// End of forward declarations

namespace RainbruRPG{
  namespace OgreGui{

    /** The skin identifier
      *
      * This must be a skin in the SkinManager::skins member.
      * The default skin is defined in the SkinManager class.
      *
      * If a bad mapping warning occurs, please see the 
      * \ref RainbruRPG::OgreGui::SkinManager::init() "SkinManager::init()"
      * function. The mapping controls are here.
      *
      * OSI_DEFAULT is a special value, mapped with SkinManager::defaultSkin
      * value in the SkinManager::getSkin() function.
      *
      * \sa SkinManager::init(), SkinManager::defaultSkin
      *
      */
    enum OgreGuiSkinID{
      OSI_BETAGUI     =0,      //!< The BeraGUI based skin
      OSI_NAVIGATION,          //!< The navigation skin
      OSI_PARENT      =0xfe,   //!< An inherited from parent value
      OSI_DEFAULT     =0xff,   //!< A virtual default skin
    };

    /** The OgreGUI skins manager
      *
      * This Singleton handles the skins of OgreGUI. It manages a
      * STL vector of Skin objects (called \ref SkinManager::skins "skins") 
      * and a default skin reference (\ref SkinManager::defaultSkin
      * "defaultSkin").
      *
      * The skin vector can be accessed with a correct skin identifier
      * (\ref RainbruRPG::OgreGui::OgreGuiSkinID "OgreGuiSkinID"
      * enumeration).
      *
      * This singleton \b must be initialized or it may cause SEGFAULT.
      *
      */
    class SkinManager : public RainbruRPG::Core::Singleton<SkinManager>{
      // Keep Singleton fully scoped to avoid conflict declaration
    public:

      void init();
      void cleanup();

      RainbruRPG::OgreGui::Skin* getSkin(Widget*);

    private:
      /** A vector of skins 
        * 
	* The OgreGuiSkinID enumeration values must goes with the index
	* placement defined in the init function().
	*
	* \sa init()
	*
	*/
      vector<RainbruRPG::OgreGui::Skin*> skins;

      /** The default skin 
        *
        * This integer is used as index of the skins vector to get the default
	* Skin instance.
	* 
	* \sa init()
	*
        */
      OgreGuiSkinID defaultSkin;
    };
  }
}

#endif // _OGRE_GUI_SKIN_MANAGER_H_
