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

/** \file guimanager.cpp
  * Implements a singleton used to manage GUI
  *
  */

#include "guimanager.h"

#include "config.h"

#include <logger.h>
#include <stringconv.h>

#include <iostream>
#include <sstream>
#include <exception>
#include <cstdlib>

#include <bgwindow.h>
#include <label.h>
#include <statuslabel.h>

#include <dialog.h> // For bug26 tests only


/** The constructor of the singleton
  *
  * This method must be called before using GuiManager
  *
  */
void RainbruRPG::Gui::GuiManager::init(){
  LOGI("Initializing GuiManager...");
  transitionTime=1200;
  guiFadeInTime=1000;
  guiOpacity=0.7f;
  inGuiFadeIn=false;
  inGuiFadeOut=false;
  mTitleOverlay=NULL;
  velocity=new vcConstant();
  win=NULL;

  // Error message
  mErrorLabel = NULL;
  errorLabelWindow = NULL;
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
    destroyTitleOverlay();
  }

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
  /*
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
  */
}


/** Actualize the window created with createNumDebugWindow()
  *
  * The values are taken from the Ogre RenderWindow. 
  * We also manage the minimum and
  * maximum values of fps and primitives.
  *
  */
void RainbruRPG::Gui::GuiManager::showFPS(){
#ifdef RAINBRU_RPG_DEBUG
  assert(win && "Current Ogre Window pointer is NULL");

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
#endif
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

  if (f>guiOpacity){
    LOGW("GuiManager::setGuiTransparency > guiOpacity");
  }

  if (f>=0.7f){
    LOGW("GuiManager::setGuiTransparency : f>=0.7f");
  }

  //  GUI::getSingleton().setGuiTransparency(f);
}

/** Called when the gui fadeIn must begin
  *
  */
void RainbruRPG::Gui::GuiManager::beginGuiFadeIn(){
  inGuiFadeIn=true;
  inGuiFadeOut=false;

  velocity->reset();
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
      setGuiTransparency(guiOpacity);
    }
  }

  else if (inGuiFadeOut){
    increaseGuiTransparency(velocity->getNextFrame(inGuiFadeOut));
    if (!inGuiFadeOut){
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
  //  float t=GUI::getSingleton().getGuiTransparency();
  float t=0.0f;
  float newT=t+f;
  
  /* v 0.0.5-160 : Gui transparency bugfix
   *
   * It seems that the value of newT can be superior to 0.7f, resulting
   * a graphical bug : The window does completely opaque and goes to 0.7f of
   * alpha blanding. The following statement fix it.
   *
   */
  if (newT>0.7f){
    newT=0.7f;
  }

  //  GUI::getSingleton().setGuiTransparency(newT);

}

/** Called when the GUI fade out may begin
  *
  */
void RainbruRPG::Gui::GuiManager::beginGuiFadeOut(){
  LOGI("Gui fadeOut is beginning");
  inGuiFadeIn=false;
  inGuiFadeOut=true;

  LOGCATS("FadeOut lenght : ");
  LOGCATF(0.0f-guiOpacity);
  LOGCAT();

  velocity->reset();
  velocity->setTranslationLenght(0.0f-guiOpacity);
  velocity->setTransitionTime(guiFadeInTime);
  velocity->start();
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
void RainbruRPG::Gui::GuiManager::destroyTitleOverlay(){
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

/** Shows a message box with a single OK button
  *
  * Uses RbMessageBox to show a message with a title. 
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
  * \note A conditionnal warning is available through the 
  *       MGM_SHOW_MESSAGE_BOX_WARNING you can find in the \ref guimanager.h 
  *       file. If this macro is defined, a warning message is sent to the
  *       logger when this function is called. It has been used when
  *       switching to the \ref setErrorMessage() function.
  *
  * \param title   The messageBox title
  * \param message The messageBox message text. This text will be word wrapped
  *                and justify.
  *
  */
void RainbruRPG::Gui::GuiManager::
showMessageBox(const String& title, const String& message){

#ifdef MGM_SHOW_MESSAGE_BOX_WARNING
  LOGW("*************************************");
  LOGW("You are about to use a function that should be used only if you	\
   do not want to use the setErrorMessage() function instead. You can	\
   disable this warning from the file maincore/guimanager.h");
  LOGW("*************************************");

#endif // !MGM_SHOW_MESSAGE_BOX_WARNING
  LOGI("GuiManager::showMessageBox() called");
  LOGI("  Creating messageBox");

  /*  RbMessageBox* mb=new RbMessageBox(title, &GUI::getSingleton());
  mb->setMessage(message);
  mb->show();
  GUI::getSingleton().addDialog(mb);
  */
  LOGI("MessageBox created");
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
}

/** Is a GUI dade in in progress
  *
  * \return \c true if a GUI fade in is in progress, otherwise \c false
  *
  * \sa inGuiFadeIn (member)
  *
  */
bool RainbruRPG::Gui::GuiManager::isInGuiFadeIn(){
  return inGuiFadeIn;

}

/** Create a GUI overlay wich shows fps and primitives count
  *
  * The window shows the minimum, maximum and actual number of fps
  * (frame per second) and drawn primitives.
  *
  *
  * \param win The Ogre window that receive the debug window
  *
  */
void RainbruRPG::Gui::GuiManager::
createNumDebugWindow(Ogre::RenderWindow* win){
  this->win=win;
  LOGI("Creating Numeric Debug Window...");
  
  Ogre::Overlay* mPanelOverlay=NULL;
  
  mPanelOverlay =OverlayManager::getSingleton().
    getByName("RainbruRPG/NumericDebug");
  
  if (mPanelOverlay){
    mPanelOverlay->show();
  }
  else{
    LOGE("Cannot load RainbruRPG/NumericDebug");
  }
}

/** Set a temporary error message
  *
  * \param s The string to be drawn
  *
  */
void RainbruRPG::Gui::GuiManager::setErrorMessage(const String& s){
  if (mErrorLabel){
    mErrorLabel->setCaption(s);
  }
  else{
    LOGE("Cannot set error message, mErrorLabel is NULL");
  }
}

/** Creates the label used to print error messages
  *
  */
void RainbruRPG::Gui::GuiManager::createErrorLabel(void){
  /*  BetaGUI::GUI* mGUI = &GUI::getSingleton();
  Ogre::Vector4 v(5, 462, 800, 477);
  errorLabelWindow = new BetaGUI::Window(v, BetaGUI::OWT_NONE, 
				   "Error window", mGUI, OSI_NAVIGATION);

  mGUI->addWindow(errorLabelWindow);

  Ogre::Vector4 v2(0, 0, 800, 15);
  mErrorLabel = new StatusLabel( v2, "Error message...", errorLabelWindow);
  errorLabelWindow->addWidget(mErrorLabel);
  */
}
