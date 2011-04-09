/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

#include "config.h"
#ifdef HAVE_DIRENT_H
#  include <dirent.h>
#endif

// The Ogre's render window name
#define RW_NAME "RenderWindowName"

using namespace std;

OgreMinimalSetup::OgreMinimalSetup():
  mRenderWindow(0)
{

}

OgreMinimalSetup::~OgreMinimalSetup()
{
  mRenderWindow=0;
}

/** Setup a minimal ogre renderer
  *
  * \param custom_log Should we create a custom log
  * \param base_dir   The path to the config and data files 
  *                   (plugins.cfg and ogre.cfg
  *
  * \warning Incorrect base_dir could lead to a 'memory access violation' when
  *          launched.
  *
  * \note The \c custom_log parameter is used to avoid an Ogre3D assertion
  *       that occurs when creating our custom log. 
  *
  */
void 
OgreMinimalSetup::setupOgre(const Ogre::String& base_dir, bool custom_log)
{
  mListener = new SilentLogListener();

  string dir= base_dir + "config/";
  if (!dirExists(dir)){
    throw "config directory '" + dir + "' does not exist.";
  }

  try{
    if (custom_log == true)
      {
	Ogre::LogManager* logger = new Ogre::LogManager();
	assert(logger && "Failed to create an Ogre Logger");
	logger->createLog("log.log", true, false, true);
	Ogre::LogManager::getSingleton().getDefaultLog()
	  ->addListener(mListener);
      }

  }
  catch(Ogre::Exception e){
    cout << "setupOgre failed to initialize LogManager: "<< e.what() << endl;
    exit(1);
  }


  Ogre::Root* root = new Ogre::Root(dir + "plugins-unittests.cfg", 
				    dir + "ogre.cfg", dir + "ogre.log");
  assert(root && "Cannot initialize Ogre::Root");
  assert(Ogre::Root::getSingletonPtr() && "Cannot initialize Ogre::Root");

  // Select rendersystem
  Ogre::RenderSystemList* list=Ogre::Root::getSingleton().getAvailableRenderers();
  this->debugRenderList( list );
  Ogre::Root::getSingleton().setRenderSystem((*list)[0]);
  Ogre::Root::getSingleton().initialise(false, "RainbruRPG blah");
  Ogre::Root::getSingleton().addResourceLocation(base_dir + "data/", "FileSystem");
  Ogre::Root::getSingleton().addResourceLocation(base_dir + "data/gui/fonts", "FileSystem");
  mRenderWindow = Ogre::Root::getSingleton().getRenderSystem()
    ->_createRenderWindow(RW_NAME, 20, 20, false);
  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
 
}

/** Tear down the ogre renderer
  *
  */
void OgreMinimalSetup::teardownOgre()
{
  /*  Ogre::Root::getSingleton().getRenderSystem()
    ->destroyRenderWindow(RW_NAME);
  Ogre::Root::getSingleton().getRenderSystem()->shutdown();
  */
  Ogre::Root::getSingleton().shutdown();
  Ogre::Root* mRoot = Ogre::Root::getSingletonPtr();
  delete mRoot;

  Ogre::LogManager* mLog = Ogre::LogManager::getSingletonPtr();
  delete mLog;

  delete mListener;
  
}

bool OgreMinimalSetup::dirExists(const std::string& vDir)
{
  DIR* dir;
  bool ret = false;

  dir = opendir( vDir.c_str() );
  if (dir != NULL){
    ret = true;
    closedir(dir);
  }
  
  return ret;
}

Ogre::RenderWindow* OgreMinimalSetup::getRenderWindow()
{
  return mRenderWindow;
}

void OgreMinimalSetup::debugRenderList(Ogre::RenderSystemList* rsl)
{
  assert(rsl && "RenderSystemList is NULL");
  assert(rsl->size() && "RenderSystemList size is 0");
  cout << "RenderSystemList size is " << rsl->size() << endl;
  Ogre::RenderSystem* rs = (*rsl)[0];
  assert(rs && "First RenderSystem is NULL");
  cout << "First RenderSystem name is '" << rs->getName() << "'" << endl;
}
