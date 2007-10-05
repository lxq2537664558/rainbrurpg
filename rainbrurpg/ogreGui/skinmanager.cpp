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

#include "skinmanager.h"

#include "sobetagui.h"

#include <logger.h>

/** Initialize the manager
  *
  * It set the defaultSkin value and create Skin instances.
  *
  */
void RainbruRPG::OgreGui::SkinManager::init(){
  LOGI("Initialising SkinManager");
  defaultSkin=OSI_BETAGUI;

  Skin* sbg=new soBetaGui();
  skins.push_back(sbg);
  // Contol sbg correct index
  if (skins.size()!=OSI_BETAGUI+1){
    LOGW("OSI_BETAGUI index is incorrect : bad skin mapping");
  }
}

/** Get a skin by its Identifier
  *
  * \param s The identifier of the skin you want
  *
  */
RainbruRPG::OgreGui::Skin* RainbruRPG::OgreGui::SkinManager::
getSkin(RainbruRPG::OgreGui::OgreGuiSkinID s){

  LOGI("Getting skin :");
  LOGCATS("  skin number : ");
  LOGCATI(s);
  LOGCAT();

  if (s==OSI_DEFAULT){
    s=defaultSkin;
  }

#ifdef DEBUG
  if (skins[s]==NULL){
    LOGW("The requested skin is NULL")
  }
#endif // DEBUG

  return skins[s];
}