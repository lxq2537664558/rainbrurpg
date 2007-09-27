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
 * - 27 sep 2007 : starting implementation
 *         
 */

#ifndef _OGRE_GUI_SKIN_MANAGER_H_
#define _OGRE_GUI_SKIN_MANAGER_H_

#include "singleton.h"
#include "skin.h"

#include <vector>

using namespace std;
using namespace RainbruRPG::Core;

namespace RainbruRPG{
  namespace OgreGui{

    /** The skin identifier
      *
      * This must be a skin in the SkinManager::skins member.
      * The default skin is defined in the SkinManager class.
      *
      */
    enum OgreGuiSkinID{
      OSI_BETAGUI=0,
      OSI_DEFAULT=0xff,   //!< The default skin
    };

    using namespace Core;

    /** The OgreGUI skins manager
      *
      * This Singleton handles the skins of OgreGUI.
      *
      */
    class SkinManager : public Singleton<SkinManager>{
    public:

      void init();
      RainbruRPG::OgreGui::Skin* getSkin(RainbruRPG::OgreGui::OgreGuiSkinID);

    private:
      /** A vector of skins */
      vector<RainbruRPG::OgreGui::Skin*> skins;
      /** The default skin */
      unsigned int defaultSkin;
    };
  }
}

#endif // _OGRE_GUI_SKIN_MANAGER_H_
