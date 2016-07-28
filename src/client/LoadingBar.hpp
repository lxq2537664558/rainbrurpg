/*
 * Copyright 2011-2016 Jerome Pasquier
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

#include <OgreResourceGroupManager.h>
#include <OgreException.h>
#include <OgreOverlay.h>

#include <OgreRenderWindow.h>

using namespace Ogre;

/** Defines an example loading progress bar which you can use during 
	startup, level changes etc to display loading progress. 
@remarks
	Basically you just need to create an instance of this class, call start()
	before loading and finish() afterwards. You may also need to stop areas of
	your scene rendering in between since this method will call 
	RenderWindow::update() to update the display of the bar - we advise using
	SceneManager's 'special case render queues' for this, see
	SceneManager::addSpecialCaseRenderQueue for details.
@note 
	This progress bar relies on you having the OgreCore.zip package already 
	added to a resource group called 'Bootstrap' - this provides the basic 
	resources required for the progress bar and will be loaded automatically.
*/
class LoadingBar : public ResourceGroupListener
{
protected:
  RenderWindow* mWindow;
  Overlay* mLoadOverlay;
  Real mInitProportion;
  unsigned short mNumGroupsInit;
  unsigned short mNumGroupsLoad;
  Real mProgressBarMaxSize;
  Real mProgressBarScriptSize;
  Real mProgressBarInc;
  OverlayElement* mLoadingBarElement;
  OverlayElement* mLoadingDescriptionElement;
  OverlayElement* mLoadingCommentElement;
  
public:
  LoadingBar() {}
  virtual ~LoadingBar(){}

  virtual void start(RenderWindow*,unsigned short numGroupsInit = 1, 
		     unsigned short numGroupsLoad = 1, 
		     Real initProportion = 0.70f);
  virtual void finish(void);

  // ResourceGroupListener callbacks
  void resourceGroupScriptingStarted(const String& groupName, 
				     size_t scriptCount);
  void scriptParseStarted(const String& scriptName, bool &skipThisScript);
  void scriptParseEnded(const String& scriptName, bool skipped);

  void resourceGroupLoadStarted(const String& groupName, size_t resourceCount);
  void resourceLoadStarted(const ResourcePtr& resource);


  void worldGeometryStageStarted(const String& description);
  void worldGeometryStageEnded(void);

  void resourceGroupScriptingEnded(const String& groupName){ }
  void resourceLoadEnded(void){	}
  void resourceGroupLoadEnded(const String& groupName){	}

  Ogre::DataStreamPtr resourceLoading(const String &name, const String &group, Resource *resource);

  bool resourceCollision(ResourcePtr &resource, ResourceManager *resourceManager);

};

