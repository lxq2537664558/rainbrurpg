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

/** \file ogreimport.h
  * The file used to include all needed Ogre headers
  *
  * This file includes all Ogre headers with a little hack. If you
  * use the \c --enable-Wno-stddep-ogre option of the \c ./configure
  * script, all deprecated header warning from the Ogre3D inclusion
  * of standard headers will be ignored.
  *
  * \todo Removing when deprecated header warning fixed by Ogre team
  *
  * Modifications :
  * - 08 jul 2008 : Starting implementation
  *
  */

#ifndef _RAINBRURPG_OGRE_IMPORT_H_
#define _RAINBRURPG_OGRE_IMPORT_H_

#include "config.h"

#ifdef __GNUC__
#  ifdef RB_DISABLE_OGRE_DEPREC_WARN
  
// The following #undef will disable warnings due to inclusion
// of deprecated std headers.
#    undef __DEPRECATED
#  endif //RB_DISABLE_OGRE_DEPREC_WARN
#endif // __GNUC__





// Including Ogre headers files
#include <Ogre.h>
#include <OgreColourValue.h>
#include <OgreException.h>
#include <OgreFrameListener.h>
#include <OgreMaterialManager.h>
#include <OgreMovableObject.h>
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include <OgrePrerequisites.h>
#include <OgreRectangle.h>
#include <OgreRenderQueueListener.h>
#include <OgreRenderWindow.h>
#include <OgreRoot.h>
#include <OgreSceneQuery.h>
#include <OgreSceneManagerEnumerator.h>
#include <OgreStringConverter.h>
#include <OgreTexture.h>
#include <OgreTimer.h>
#include <OgreVector2.h>
#include <OgreVector4.h>





#ifdef __GNUC__
#  ifdef RB_DISABLE_OGRE_DEPREC_WARN
// Enable the __DEPRECATED warnings if needed
#    define __DEPRECATED
// With the following line, deprecated headers used after the include of this 
// file will again make a warning.
#    undef _BACKWARD_BACKWARD_WARNING_H
#  endif //RB_DISABLE_OGRE_DEPREC_WARN
#endif // __GNUC__




#endif //_RAINBRURPG_OGRE_IMPORT_H_

