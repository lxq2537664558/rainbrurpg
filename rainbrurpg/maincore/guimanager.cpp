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
 *  along with Foobar; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

#include "guimanager.h"

#include "config.h"

#include <logger.h>
#include <iostream>
#include <exception>
#include <CEGUI/CEGUIExceptions.h>

/** The constructor of the singleton
  *
  * This method must be called before using GuiManager
  *
  */
void RainbruRPG::Gui::GuiManager::init(){
  LOGI("Initializing GuiManager...");
  this->transitionTime=600;
  guiFadeInTime=1000;
  guiOpacity=0.7f;
  inGuiFadeIn=false;
  inGuiFadeOut=false;
  velocity=new vcConstant();
  dialogSystemLayout=NULL;
  mTitleOverlay=NULL;
}

/** The destructor of the singleton
  *
  * This method must be called after using GuiManager
  *
  */
void RainbruRPG::Gui::GuiManager::cleanup(){
  LOGI("Cleaning up GuiManager...");

  if (velocity)
    delete velocity;

  velocity=NULL;

  if (mTitleOverlay){
    detroyTitleOverlay();
  }

}

/** Create a GUI overlay wich shows fps and primitives count
  *
  * The window shows the minimum, maximum ans actual number of fps
  * (frame per second) and drawn primitives
  *
  *
  * \param win The Ogre window that receive the debug window
  */
void RainbruRPG::Gui::GuiManager::
createNumDebugWindow(Ogre::RenderWindow* win){
  this->win=win;
  LOGI("Creating Numeric Debug Window...");

  Ogre::Overlay* mPanelOverlay=NULL;

  mPanelOverlay =OverlayManager::getSingleton().
    getByName("RainbruRPG/NumericDebug");

  if (mPanelOverlay)
    mPanelOverlay->show();
  else
    LOGE("Cannot load RainbruRPG/NumericDebug");

}

/** Create a GUI overlay wich shows the name and the version of the game
  *
  * The \c win parameter cannot be \c NULL. You can get this with the
  * \ref  RainbruRPG::Core::GameEngine::getRenderWindow "getRenderWindow"
  * function.
  *
  * \param win The Ogre window that receive the overlay
  *
  */
void RainbruRPG::Gui::GuiManager::createTitleOverlay(Ogre::RenderWindow* win){
  this->win=win;
  LOGI("Creating Title overlay...");

  mTitleOverlay=NULL;

  mTitleOverlay =OverlayManager::getSingleton().getByName("RainbruRPG/Title");

  if (mTitleOverlay){
    mTitleOverlay->show();

    Ogre::String s;
    s="v";
    s+=VERSION;
    s+="-";
    s+=BUILD_RELEASE;

    OverlayElement* ver=mTitleOverlay->getChild("RainbruRPG/Title/Panel")
      ->getChild("RainbruRPG/Title/Version");
    ver->setParameter( "caption", s );
  }
  else{
    LOGE("Cannot load RainbruRPG/Title");
  }
}


/** Actualize the window created with createNumDebugWindow()
  *
  * The values are taken from the Irrlicht Driver getFPS() and
  * getPrimitiveCountDrawn() functions. We also manage the minimum and
  * maximum values of fps and primitives.
  *
  */
void RainbruRPG::Gui::GuiManager::showFPS(){
  static String currFps = "Current FPS: ";
  static String avgFps = "Average FPS: ";
  static String bestFps = "Best FPS: ";
  static String worstFps = "Worst FPS: ";
  static String tris = "Triangle Count: ";
  
  // update stats when necessary
    try {
    OverlayElement* guiAvg = OverlayManager::getSingleton().
      getOverlayElement("RainbruRPG/NumericDebug/AverageFps");

    OverlayElement* guiCurr = OverlayManager::getSingleton().
      getOverlayElement("RainbruRPG/NumericDebug/CurrFps");

    OverlayElement* guiBest = OverlayManager::getSingleton().
      getOverlayElement("RainbruRPG/NumericDebug/BestFps");

    OverlayElement* guiWorst = OverlayManager::getSingleton().
      getOverlayElement("RainbruRPG/NumericDebug/WorstFps");
    
    const RenderTarget::FrameStats& stats = win->getStatistics();
    
    guiAvg->setCaption(avgFps + StringConverter::toString((int)stats.avgFPS));
    guiCurr->setCaption(currFps + StringConverter::toString((int)stats.lastFPS));
    guiBest->setCaption(bestFps + StringConverter::toString((int)stats.bestFPS)
			+" "+StringConverter::toString(stats.bestFrameTime)
			+" ms");

    guiWorst->setCaption(worstFps + StringConverter::toString((int)stats.worstFPS)
			 +" "+StringConverter::toString(stats.worstFrameTime)
			 +" ms");
    
    OverlayElement* guiTris = OverlayManager::getSingleton().
      getOverlayElement("RainbruRPG/NumericDebug/NumTris");

    guiTris->setCaption(tris + StringConverter::toString(stats.triangleCount));
    
    OverlayElement* guiDbg = OverlayManager::getSingleton().
      getOverlayElement("RainbruRPG/NumericDebug/DebugText");

    //  guiDbg->setCaption(win->getDebugText());
    guiDbg->setCaption("DebugText");

  }
  catch(...)
    {
      LOGE("Cannot update numeriocDebugWindow");
    }

}

/** Loads a CEGUI layout and shows it
  *
  * Typically, the file may be in the \c /rpg/data/gui/layout directory.
  * The extension of the file is layout.
  *
  * \param layoutName The name of the layout file to load
  *
  */
void RainbruRPG::Gui::GuiManager::loadCEGUILayout(const char* layoutName){
  LOGI("Loading a CEGUI layout");
  LOGCATS("Layout name :'");
  LOGCATS(layoutName);
  LOGCATS("'");
  LOGCAT();

  CEGUI::Window* mEditorGuiSheet = CEGUI::WindowManager::getSingleton().
    loadWindowLayout((CEGUI::utf8*)layoutName);

  if (!mEditorGuiSheet){
    LOGW("Failed to load the CEGUI layout");
  }

  GameEngine::getSingleton().getCEGUISystem()->setGUISheet(mEditorGuiSheet);
  setGuiTransparency(0.0f);

  LOGI("Debugging CEGUI GUISheet");
  CEGUI::Window* deb=GameEngine::getSingleton().getCEGUISystem()
    ->getGUISheet();

  debugWindow(deb);

  if (deb->getChildCount()>0){
    LOGI("Debugging active child");
    debugWindow(deb->getActiveChild());
  }
}

/** Returns the Ogre render window
  *
  * \return The Ogre render window
  *
  */
Ogre::RenderWindow* RainbruRPG::Gui::GuiManager::getRenderWindow(){
  if (!win){
    LOGE("Returning a NULL Ogre render window");
    return NULL;
  }
  else{
    return this->win;
  }
}

/** Change the transition time value
  *
  * \param ui The new transition time in milliseconds
  *
  */
void RainbruRPG::Gui::GuiManager::setTransitionTime(unsigned int ui){
  this->transitionTime=ui;
}

/** Get the transition time value
  *
  * \return The current transition time in milliseconds
  *
  */
unsigned int RainbruRPG::Gui::GuiManager::getTransitionTime(){
  return this->transitionTime;
}

/** Set the transparency of the CEGUI system
  *
  * \param f A new value (0.0f is fully transparent, 1.0f is opaque)
  *
  */
void RainbruRPG::Gui::GuiManager::setGuiTransparency(float f){
  CEGUI::Window* guiSheet=GameEngine::getSingleton().getCEGUISystem()
    ->getGUISheet();

  if (guiSheet!=NULL){
    guiSheet->setAlpha(f);
  }
}

/** Called when the gui fadeIn must begin
  *
  */
void RainbruRPG::Gui::GuiManager::beginGuiFadeIn(){
  LOGI("Gui fadeIn is beginning");
  inGuiFadeIn=true;
  velocity->setTranslationLenght(guiOpacity);
  velocity->setTransitionTime(guiFadeInTime);
  velocity->start();
}

/** Set for each frame the gui transparency
  *
  * It is typically called during a frameStarted function
  *
  */
void RainbruRPG::Gui::GuiManager::guiFade(){
  if (inGuiFadeIn){
    increaseGuiTransparency(velocity->getNextFrame(inGuiFadeIn));
    if (!inGuiFadeIn){
      LOGI("FadeIn ended");
      LOGCATS("gui opacity set to :");
      LOGCATF(guiOpacity);
      LOGCAT();
      setGuiTransparency(guiOpacity);
    }
  }

  else if (inGuiFadeOut){
    increaseGuiTransparency(velocity->getNextFrame(inGuiFadeOut));
    if (!inGuiFadeOut){
      LOGI("FadeOut ended");
      LOGCATS("gui opacity set to :");
      LOGCATF(guiOpacity);
      LOGCAT();
      setGuiTransparency(0.0f);
    }
  }
}

/** Increase the GUI transparency value
  *
  * \param f The value to add to the current transparency value
  *
  */
void RainbruRPG::Gui::GuiManager::increaseGuiTransparency(float f){
  float t;

  CEGUI::Window* guiSheet=GameEngine::getSingleton().getCEGUISystem()
    ->getGUISheet();

  if (guiSheet!=NULL){
    t=guiSheet->getAlpha();
    setGuiTransparency(t+f);
  }
}

/** Called when the GUI fade out may begin
  *
  */
void RainbruRPG::Gui::GuiManager::beginGuiFadeOut(){
  LOGI("Gui fadeOut is beginning");
  inGuiFadeOut=true;

  velocity->setTranslationLenght(0.0f-guiOpacity);
  velocity->setTransitionTime(guiFadeInTime);
  velocity->start();
}

/** Destroys all the current CEGUI windows
  *
  * This function calls hideMessageBox() to set the GuiManager::
  * dialogSystemLayout pointer to \c NULL.
  *
  * \sa hideMessageBox(), dialogSystemLayout
  *
  */
void RainbruRPG::Gui::GuiManager::removeCurrentCEGUILayout(){
  LOGI("Removing current CEGUI layout");

  CEGUI::WindowManager::getSingleton().destroyAllWindows();
  GuiManager::getSingleton().hideMessageBox(true);

}

/** Are we in GUI fade out?
  *
  * \return \c true if we are currently in GUI fade out transition
  *
  */
bool RainbruRPG::Gui::GuiManager::isInGuiFadeOut(){
  return inGuiFadeOut;
}

/** Destroys the title overlay
  *
  */
void RainbruRPG::Gui::GuiManager::detroyTitleOverlay(){
  LOGI("Destroying title overlay");

  if (mTitleOverlay){
    try{
      Ogre::OverlayManager::getSingleton().destroy(mTitleOverlay);
      mTitleOverlay==NULL;
    }
    catch(Ogre::Exception e){
      LOGW("Cannot destroy title overlay");
    }
    LOGI("Title overlay not found, already destroyed?");
  }
}

/** Debug some values for the given CEGUI window
  *
  * It uses the RainbruRPG logger to log the values of this
  * window.
  *
  * \param win The window to debug
  *
  */
void RainbruRPG::Gui::GuiManager::debugWindow(CEGUI::Window* win){
  if (!win){
    LOGW("Cannot debug NULL window");
  }
  else{
    LOGCATS("GUISheet name :'");
    LOGCATS(win->getName().c_str());
    LOGCATS("'");
    LOGCAT();
    
    LOGCATS("GUISheet type :'");
    LOGCATS(win->getType().c_str());
    LOGCATS("'");
    LOGCAT();
    
    LOGCATS("GUISheet text :'");
    LOGCATS(win->getText().c_str());
    LOGCATS("'");
    LOGCAT();
    
    LOGCATS("Is visible ? :'");
    LOGCATB(win->isVisible());
    LOGCATS("'");
    LOGCAT();
    
    LOGCATS("Is disabled ? :'");
    LOGCATB(win->isDisabled());
    LOGCATS("'");
    LOGCAT();

    LOGCATS("Is active ? :'");
    LOGCATB(win->isActive());
    LOGCATS("'");
    LOGCAT();
    
    LOGCATS("Contains ");
    LOGCATI(win->getChildCount());
    LOGCATS(" child(s)");
    LOGCAT();
  }
}

/** Debug the named child
  *
  */
void RainbruRPG::Gui::GuiManager::debugChild(const char* name){
  CEGUI::Window* win=GameEngine::getSingleton().getCEGUISystem()
    ->getGUISheet()->getChild(name);

  debugWindow(win);
}

/** Shows a CEGUI message box with a single OK button
  *
  * Uses SimpleDialog to show a message with a title. 
  *
  * If you want a widget to get the focus after the message box is closed, 
  * you should activate this widget then show the message box. Please try
  * the following code :
  * <pre>
  * widget->activate();
  * GuiManager::getSingleton().showMessageBox("Title", "Message","parent");
  * </pre>
  * 
  * The message box will remain the focused widget when it is opened and
  * give the focus to \c widget when it is closed.
  *
  * \param title   The messageBox title
  * \param message The messageBox message text. This text will be word wrapped
  *                and justify.
  * \param parent  The parent name. If this string is empty (""), the message
  *                box will be non-modal, if a CEGUI Window's name is given,
  *                the dialog will be modal.
  *
  */
void RainbruRPG::Gui::GuiManager::
showMessageBox(const CEGUI::String& title, const CEGUI::String& message, 
	       const CEGUI::String& parent)

{

  // Init dialog
  if (dialogSystemLayout==NULL){
    this->dialogSystemLayout = CEGUI::WindowManager::getSingleton()
      .loadWindowLayout("dialogsystem.layout");

    LOGW("dialogSystemLayout pointer is NULL");
  }

  CEGUI::Window* root=CEGUI::System::getSingleton().getGUISheet();
  if (root && dialogSystemLayout){
    root->addChildWindow("DialogSystemRoot");

    MessageBox* simpleDialog=new MessageBox();
    simpleDialog->initWindow(parent);
    simpleDialog->setTitle(title);
    simpleDialog->setMessage(message);
    simpleDialog->doOpen();
  }
  else{
    LOGE("Cannot show message box (CEGUI guiSheet==NULL)");
  }

}

/** Set the dialogSystemLayout to NULL
  * 
  * As the DialogSystem::doClose() does not destroy the dialog and the
  * showMessageBox try to reload the CEGUI layout only if 
  * GuiManager::dialogSystemLayout
  * is \c NULL, the removeCurrentCEGUILayout() call this function. As the 
  * removeCurrentCEGUILayout() is called when we change gamestate, the
  * \c dialogsystem.layout file is reloaded for each gamestate change.
  *
  * \param destroy An unused parameter
  *
  * \sa dialogSystemLayout, showMessageBox(), removeCurrentCEGUILayout.
  *
  */
void RainbruRPG::Gui::GuiManager::hideMessageBox(bool destroy){
  dialogSystemLayout=NULL;
}
