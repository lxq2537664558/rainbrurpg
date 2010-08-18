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

#include "OgreMinimalSetup.hpp"

#include "ogreimport.h"

#include <string>

using namespace std;

OgreMinimalSetup::OgreMinimalSetup()
{

}

OgreMinimalSetup::~OgreMinimalSetup()
{

}

/** Setup a minimal ogre renderer
  *
  */
void OgreMinimalSetup::setupOgre()
{
  mListener = new SilentLogListener();

  Ogre::LogManager* logger = new Ogre::LogManager();
  logger->createLog("log.log", true, false, true);
  Ogre::LogManager::getSingleton().getDefaultLog()->addListener(mListener);

    string dir="../../../config/";
    new Ogre::Root(dir + "plugins.cfg", dir + "ogre.cfg", dir + "ogre-unittests.log");
    

    // Select rendersystem
    Ogre::RenderSystemList* list=Ogre::Root::getSingleton().getAvailableRenderers();
    Ogre::Root::getSingleton().setRenderSystem((*list->begin()));
    Ogre::Root::getSingleton().initialise(false, "RainbruRPG blah");
    Ogre::Root::getSingleton().addResourceLocation("../../../data/", "FileSystem");
    Ogre::Root::getSingleton().getRenderSystem()->createRenderWindow("a", 20, 20, false);
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
}

/** Tear down the ogre renderer
  *
  */
void OgreMinimalSetup::teardownOgre()
{
  Ogre::Root::getSingleton().getRenderSystem()->shutdown();
  Ogre::Root::getSingleton().shutdown();
  Ogre::Root* mRoot = Ogre::Root::getSingletonPtr();
  delete mRoot;

  Ogre::LogManager* mLog = Ogre::LogManager::getSingletonPtr();
  delete mLog;

  delete mListener;
}
