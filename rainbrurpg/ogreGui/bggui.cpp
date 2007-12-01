/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */
#include "bggui.h"

#include "bgwindow.h"
#include "quadrenderer.h"

#include <logger.h>

#include <OGRE/OgreOverlayManager.h>
#include <OGRE/OgreStringConverter.h>



// Static members initialisation
bool BetaGUI::GUI::isMouseButtonPressed=false;
// End of static members initialisation


/** The GUI constructor
  *
  */
BetaGUI::GUI::GUI(RenderSystem* rs, SceneManager* sm, Viewport* vp):
  mouseCursorOverlay(NULL),
  resizedWindow(NULL),
  movedWindow(NULL),
  wc(NULL),
  bc(NULL),
  tc(NULL),
  mQuadRenderer(NULL)
{

  rootOverlay=OverlayManager::getSingleton().create("BetaGUI");
  rootOverlay->show();
  rootOverlay->setZOrder(500);

  dialogOverlay=OverlayManager::getSingleton().create("BetaGUI.Dialog");
  dialogOverlay->show();
  dialogOverlay->setZOrder(550);

  mQuadRenderer=new QuadRenderer(rs, sm, vp);

}

/** The destructor
  *
  */
BetaGUI::GUI::~GUI(){
  windowList.clear();

  delete mQuadRenderer;
  mQuadRenderer=NULL;
}

/** Inject the backspace key pressed event
  *
  * \param x The X position of the mouse when you press the key
  * \param y The Y position of the mouse when you press the key
  *
  */
void BetaGUI::GUI::injectBackspace(unsigned int x, unsigned int y){
  injectKey("!b",x,y);
}

/** Remove the given window from the windowList
  *
  * This is automatically called by the Window destructor.
  *
  * \param name The name of the window to be deleted
  *
  */
void BetaGUI::GUI::destroyWindow(const Ogre::String& name){
  // Do not use the WindowListIterator typedef as it is a const_iterator
  // and we need a non-const one to use windowList.erase(iter).
  list<Window*>::iterator iter;
  for(iter=windowList.begin();iter!=windowList.end();iter++){
    if((*iter)->getName()==name){
      windowList.erase(iter);
      // Going out of this function
      return;
    }
  }
}

/** Inject a mouse move event
  *
  * \param x   The X position of the mouse
  * \param y   The Y position of the mouse
  *
  * \return \c true if this event is used, otherwise \c false
  *
  */
bool BetaGUI::GUI::injectMouse(unsigned int x,unsigned int y){

  bool LMB=isMouseButtonPressed;

  // Moves the mouse cursor
  if(mouseCursorOverlay){
    mouseCursorOverlay->setPosition(x,y);
  }

  if ((resizedWindow!=NULL)&&(LMB==true)){
    resizedWindow->resize(x, y);
    return true;
  }
  else if((movedWindow!=NULL)&&(LMB==true)){
    movedWindow->move(x, y);
  }
  else{
    resizedWindow=NULL;
    movedWindow=NULL;
  
    for(WindowListIterator iter=windowList.begin();iter!=windowList.end();iter++){
      if((*iter)->check(x,y,LMB)){
	return true;
      }
    }
    return false;
  }
}

/** Inject the given key at the given position into the system
  *
  * The arguments are passed to all windows by calling Window::checkKey().
  *
  * \param key The injected key
  * \param x   The X position of the mouse
  * \param y   The Y position of the mouse
  *
  * \return \c true if the injected key is used, otherwise, returns \c false
  *
  */
bool BetaGUI::GUI::injectKey(String key, unsigned int x,unsigned int y){
  for(WindowListIterator iter=windowList.begin();iter!=windowList.end();iter++){
    if((*iter)->checkKey(key,x,y)){
      return true;
    }
  }
  return false;
}

/** Create an overlay and returns it
  *
  * It guesses the overlay type from the C content. If the string is empty,
  * it creates a Panel, otherwise, it creates a TextArea.
  *
  * If A is \c true, the newly created overlay will be automatically
  * added to the current GUI root overlay and will be shown. So, if A
  * is \c false, the overlay will not be visible.
  *
  * \param N The instance name of the new overlay
  * \param P The position of the new overlay
  * \param D The dimensions of the new overlay
  * \param M The material name of the new overlay
  * \param C the content string of the overlay.
  * \param A Should we add it to the GUI root overlay ?
  *
  * \return The newly created Ogre overlay
  *
  */
OverlayContainer* BetaGUI::GUI::
createOverlay(String N,Vector2 P,Vector2 D,String M,String C,bool A){

  // Choose the type of overlay
  String t="Panel";
  if (C!="")
    t="TextArea";
  
  OverlayContainer* e=static_cast<OverlayContainer*>
    (OverlayManager::getSingleton().createOverlayElement(t, N));
  
  e->setMetricsMode(GMM_PIXELS);
  e->setDimensions(D.x,D.y);
  e->setPosition(P.x,P.y);

  if (M!="")
    e->setMaterialName(M);

  if (C!=""){
    e->setCaption(C);
  }

  if(A){
    rootOverlay->add2D(e);
    e->show();
  }
  return e;
}

/** Create a mouse pointer
  *
  * \param d The size in pixels of the mouse pointer
  * \param m The name of the Ogre material used to draw it
  *
  * \return The overlay now containing the mouse pointer
  *
  */
OverlayContainer* BetaGUI::GUI::createMousePointer(Vector2 d, String m){
  Overlay* o=OverlayManager::getSingleton().create("BetaGUI.MousePointer");
  o->setZOrder(649);
  mouseCursorOverlay=createOverlay("bg.mp",Vector2(0,0),d,m,"", false);
  
  o->add2D(mouseCursorOverlay);
  o->show();
  mouseCursorOverlay->show();
  return mouseCursorOverlay;
}

/** Adds a window to the GUI system
  *
  * \param w The window to add
  *
  * \sa windowList (member)
  *
  */
void BetaGUI::GUI::addWindow(Window* w){
  windowList.push_back(w);

  LOGCATS("GUI::addWindow called (");
  LOGCATI(windowList.size());
  LOGCATS(" registered)");
  LOGCAT();
}

/** Get the next uniqueId used by button
  *
  * \return A auto-incremental identifier used when creating a button
  *
  */
unsigned int BetaGUI::GUI::getUniqueId(void){
  return bc++;
}

/** Get the next uniqueId used by window
  *
  * \return A auto-incremental identifier used when creating a window
  *
  */
unsigned int BetaGUI::GUI::getWindowUniqueId(void){
  return wc++;
}

/** Get the next uniqueId used by StaticText
  *
  * \return A auto-incremental identifier used when creating a staticText
  *
  */
unsigned int BetaGUI::GUI::getStaticTextUniqueId(void){
  return tc++;
}

/** Get the parent of all windows
  *
  * \return The root overlay
  *
  */
Ogre::Overlay* BetaGUI::GUI::getRootOverlay(void){ 
  return rootOverlay; 
}

/** Set the GUI transparensy for all windows
  *
  * \param f The alpha value (from 0.0f to 1.0f)
  *
  * \sa guiTransparency, getGuiTransparency()
  *
  */
void BetaGUI::GUI::setGuiTransparency(float f){

  this->guiTransparency=f;
  //  for(unsigned int i=0;i<windowList.size();i++){
  for(WindowListIterator iter=windowList.begin();iter!=windowList.end();iter++){
    (*iter)->setTransparency(f);
  }
}

/** Get the current GUI transparency
  *
  * \return The GUI transparency value (from 0.0f to 1.0f)
  *
  * \sa guiTransparency, setGuiTransparency()
  *
  */
float BetaGUI::GUI::getGuiTransparency(void){
  return this->guiTransparency;
}

/** Change the currently resized Window
  *
  * \param w The window to be resized
  *
  * \sa resizedWindow (member), injectMouse().
  *
  */
void BetaGUI::GUI::setResizedWindow(Window* w){
  this->resizedWindow=w;
}

/** Change the currently moved Window
  *
  * \param w The window to be moved
  *
  * \sa movedWindow (member), injectMouse().
  *
  */
void BetaGUI::GUI::setMovedWindow(Window* w){
  this->movedWindow=w;
}

/** Makes sure no window is resized or moved
  *
  * \param win The window to be deactivated
  *
  */
void BetaGUI::GUI::deactivateWindow(Window* win){
  LOGI("Deactivate window");
  this->resizedWindow=NULL;
  this->movedWindow=NULL;
}

/** Inject a mouse button pressed event
  *
  * \param from The name of the function that call this (for debug purpose)
  *
  * \sa isMouseButtonPressed (member)
  *
  */
void BetaGUI::GUI::injectMouseButtonPressed(const std::string& from){
  isMouseButtonPressed=true;
}

/** Inject a mouse button released event
  *
  * \sa isMouseButtonPressed (member)
  *
  */
void BetaGUI::GUI::injectMouseButtonReleased(){
  isMouseButtonPressed=false;
}

/** Get the dialog overlay
  *
  * Used only for Dialog because it is aboce the windows one.
  *
  * \return The Ogre overlay, parent of all dialogs
  *
  */
Ogre::Overlay* BetaGUI::GUI::getDialogOverlay(void){
  LOGA(this->dialogOverlay, "dialogOverlay is NULL");
  return this->dialogOverlay;
}

/** Add a dialog 
  *
  * It is different as addWindow() as this use push_front to get
  * the dialog mouse event prioritary.
  *
  * \param win The dialog to add
  *
  */
void BetaGUI::GUI::addDialog(Window* win){
  windowList.push_front(win);
}

/** Draw the GUI
  * 
  * This is called for each frame by 
  * \ref RainbruRPG::OgreGui::OgreGuiRenderQueueListener 
  * "OgreGuiRenderQueueListener".
  *
  */
void BetaGUI::GUI::draw(){
  mQuadRenderer->begin();

  list<Window*>::iterator iter;
  for(iter=windowList.begin();iter!=windowList.end();iter++){
     
    // Each Window should call reset() itself
    (*iter)->draw(mQuadRenderer);
  }
  mQuadRenderer->end();
}
