/*
 * Copyright 2011-2015 Jerome Pasquier
 *
 * This file is part of rainbrurpg-client.
 *
 * rainbrurpg-client is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * rainbrurpg-client is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with rainbrurpg-client.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "LoadingBar.hpp"

#include <OgreOverlayElement.h>
#include <OgreOverlayManager.h>

  /** Show the loading bar and start listening.
      @param window The window to update 
      @param numGroupsInit The number of groups you're going to be initialising
      @param numGroupsLoad The number of groups you're going to be loading
      @param initProportion The proportion of the progress which will be taken
      up by initialisation (ie script parsing etc). Defaults to 0.7 since
      script parsing can often take the majority of the time.
  */
void LoadingBar::
start(RenderWindow* window,  unsigned short numGroupsInit , 
      unsigned short numGroupsLoad, Real initProportion)
{
    mWindow = window;
    mNumGroupsInit = numGroupsInit;
    mNumGroupsLoad = numGroupsLoad;
    mInitProportion = initProportion;
    // We need to pre-initialise the 'Bootstrap' group so we can use
    // the basic contents in the loading screen
    ResourceGroupManager::getSingleton().initialiseResourceGroup("Bootstrap");
    
    OverlayManager& omgr = OverlayManager::getSingleton();
    mLoadOverlay = (Overlay*)omgr.getByName("Core/LoadOverlay");
    if (!mLoadOverlay)
      {
	OGRE_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, 
		    "Cannot find loading overlay", "ExampleLoadingBar::start");
      }
    mLoadOverlay->show();
    
    // Save links to the bar and to the loading text, for updates as we go
    mLoadingBarElement = omgr.getOverlayElement("Core/LoadPanel/Bar/Progress");
    mLoadingCommentElement = omgr.getOverlayElement("Core/LoadPanel/Comment");
    mLoadingDescriptionElement = omgr.getOverlayElement("Core/LoadPanel/Description");
    
    OverlayElement* barContainer = omgr.getOverlayElement("Core/LoadPanel/Bar");
    mProgressBarMaxSize = barContainer->getWidth();
    mLoadingBarElement->setWidth(0);
    
    // self is listener
    ResourceGroupManager::getSingleton().addResourceGroupListener(this);
  }

  /** Hide the loading bar and stop listening. 
   */
void LoadingBar::finish(void)
{
  // hide loading screen
  mLoadOverlay->hide();

  // Unregister listener
  ResourceGroupManager::getSingleton().removeResourceGroupListener(this);
}

// ResourceGroupListener callbacks
void LoadingBar::resourceGroupScriptingStarted(const String& groupName, 
					       size_t scriptCount)
{
  assert(mNumGroupsInit > 0 && "You stated you were not going to init "
	 "any groups, but you did! Divide by zero would follow...");
  // Lets assume script loading is 70%
  mProgressBarInc = mProgressBarMaxSize * mInitProportion / (Real)scriptCount;
  mProgressBarInc /= mNumGroupsInit;
    mLoadingDescriptionElement->setCaption("Parsing scripts...");
    mWindow->update();
}
 
void LoadingBar::scriptParseStarted(const String& scriptName, 
				    bool &skipThisScript)
{
  mLoadingCommentElement->setCaption(scriptName);
  mWindow->update();
}

void LoadingBar::scriptParseEnded(const String& scriptName, bool skipped)
{
  mLoadingBarElement->setWidth(mLoadingBarElement->getWidth() + 
			       mProgressBarInc);
  mWindow->update();
}


void LoadingBar::resourceGroupLoadStarted(const String& groupName, 
					  size_t resourceCount)
{
  assert(mNumGroupsLoad > 0 && "You stated you were not going to load "
	 "any groups, but you did! Divide by zero would follow...");
  mProgressBarInc = mProgressBarMaxSize * (1-mInitProportion) / 
    (Real)resourceCount;
  mProgressBarInc /= mNumGroupsLoad;
  mLoadingDescriptionElement->setCaption("Loading resources...");
  mWindow->update();
}

void LoadingBar::resourceLoadStarted(const ResourcePtr& resource)
{
  mLoadingCommentElement->setCaption(resource->getName());
  mWindow->update();
}

void LoadingBar::worldGeometryStageStarted(const String& description)
{
  mLoadingCommentElement->setCaption(description);
  mWindow->update();
}

void LoadingBar::worldGeometryStageEnded(void)
{
  mLoadingBarElement->setWidth(mLoadingBarElement->getWidth() + 
			       mProgressBarInc);
  mWindow->update();
}

Ogre::DataStreamPtr 
LoadingBar::resourceLoading(const String &name, const String &group, 
			    Resource *resource)
{
  return Ogre::DataStreamPtr();
}

bool 
LoadingBar::resourceCollision(ResourcePtr &resource, 
			      ResourceManager *resourceManager)
{
  return false;
}
