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

#include "skinmanager.h"

#include "widget.h"
#include "sobetagui.h"
#include "sonavigation.h"

#include <logger.h>

/** Initialize the manager
  *
  * It set the defaultSkin value and create Skin instances.
  *
  */
void RainbruRPG::OgreGui::SkinManager::init(){
  LOGI("Initialising SkinManager");
  defaultSkin=OSI_BETAGUI;

  SkinOverlay* sbg=new soBetaGui();
  skins.push_back(sbg);

  SkinOverlay* sn=new soNavigation();
  skins.push_back(sn);


  // Contol sbg correct index
  if (skins.size()!=OSI_BETAGUI+2){
    LOGW("OSI_BETAGUI index is incorrect : bad skin mapping");
  }

  // Contol sn correct index
  if (skins.size()!=OSI_NAVIGATION+1){
    LOGW("OSI_BETAGUI index is incorrect : bad skin mapping");
  }

}

/** Get the skin of a widget
  *
  * This function handles two advanced features :
  * - The default skin if w->getSkinId() is OSI_DEFAULT;
  * - The inherited skin identifier value if w->getSkinId() is
  *   OSI_PARENT;
  *
  * In the case of OSI_PARENT, this function will be called recursively.
  *
  * \param w The widget
  *
  */
RainbruRPG::OgreGui::SkinOverlay* RainbruRPG::OgreGui::SkinManager::
getSkin(Widget* w){

  OgreGuiSkinID s= w->getSkinId();

  if (s==OSI_DEFAULT){
    s=defaultSkin;
  }

  if (s==OSI_PARENT){
    Widget* parent=w->getParent();
    return getSkin(parent);
  }

#ifdef RAINBRU_RPG_DEBUG
  if (skins[s]==NULL){
    LOGW("The requested skin is NULL")
  }
#endif // DEBUG

  return skins[s];
}
