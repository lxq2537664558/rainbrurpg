/*
 *  Copyright 2006-2013 Jerome PASQUIER
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

#include "DummyRenderSystem.hpp"

#include <OgreRoot.h>

// Global variable
DummyRenderSystem* myPlugin;

// Ogre resitration
extern "C" void _Dummy_RS_Export_ dllStartPlugin(void)
{
  myPlugin = new DummyRenderSystem();
  //  Ogre::Root::getSingleton().installPlugin(myPlugin);
}
extern "C" void _Dummy_RS_Export_ dllStopPlugin(void)
{
  //  Ogre::Root::getSingleton().uninstallPlugin(myPlugin);
  delete myPlugin;
}
// End of ogre resitration

// The Plugin Interface
DummyRenderSystem::DummyRenderSystem():
  mName("Dummy Render System")
{

}

DummyRenderSystem::~DummyRenderSystem()
{

}

void DummyRenderSystem::install(void)
{
  Root::getSingleton().addRenderSystem(this);
}

void DummyRenderSystem::uninstall(void)
{

}


// The RenderSystem Interface
const String& DummyRenderSystem::getName(void) const
{
  return mName;
}

ConfigOptionMap& DummyRenderSystem::getConfigOptions(void)
{
  return mConfigOptionMap;
}

HardwareOcclusionQuery* DummyRenderSystem::
createHardwareOcclusionQuery(void)
{
  assert(false && "called createHarwareOcclusionQuery");
  return NULL;
}

RenderWindow* DummyRenderSystem::
createRenderWindow(const String&, unsigned int, 
		   unsigned int, bool, 
		   const NameValuePairList*)
{
  assert(false && "called createRenderWindow");
  return NULL;
};

MultiRenderTarget* DummyRenderSystem::
createMultiRenderTarget(const String&)
{
  assert(false && "called createMultiRenderTarget");
  return NULL;
}

RenderSystemCapabilities* DummyRenderSystem::
createRenderSystemCapabilities() const
{

}

RenderWindow* DummyRenderSystem::
_createRenderWindow(const String&, unsigned int, unsigned int, 
		    bool, const NameValuePairList*)
{

}

void DummyRenderSystem::
_setSeparateSceneBlending(SceneBlendFactor, SceneBlendFactor, 
			  SceneBlendFactor, SceneBlendFactor)
{

}

void DummyRenderSystem::
_setAlphaRejectSettings(CompareFunction, unsigned char, bool)
{

}

void DummyRenderSystem::
setClipPlanesImpl(const PlaneList&)
{

}

void DummyRenderSystem::
initialiseFromRenderSystemCapabilities(RenderSystemCapabilities*, RenderTarget*)
{

}
