/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

/** \file bgwindow.cpp
  * Implements a window widget used in OgreGUI
  *
  */

#include "bgwindow.h"

#include "bglistener.h"
#include "skinmanager.h"
#include "skin.h"
#include "quadrenderer.h"

#include <logger.h>
#include <gameengine.h>

#include <OgreStringConverter.h>
#include <OgreBorderPanelOverlayElement.h>
#include <OgreMaterial.h>
#include <OgreMaterialManager.h>

using namespace RainbruRPG::Core;

/** The constructor
  *
  * The minimal allowed size when window is resized is by default 50x50.
  * Please use setMinimalSize() to set this values
  * manually.
  *
  * \param D       The dimensions of the window to create as a Ogre vector
  * \param t       The window's type
  * \param caption The caption of the window
  * \param G       The GUI object used to create window
  * \param sid     The Skin used to draw this window
  *
  */
BetaGUI::Window::Window(Vector4 D,OgreGuiWindowType t,String caption, 
			GUI *G, RainbruRPG::OgreGui::OgreGuiSkinID sid):
  Widget(D, NULL, sid), // Warning, parent is now NULL
  mGUI(G),
  mTitleBar(NULL),
  mResizeGrip(NULL),
  minimalWidth(50),
  minimalHeight(100),
  alwaysTransparent(false),
  mCaption(caption)
{
  setName("Window");

  mSkin = SkinManager::getSingleton().getSkin(this);
  mScrollPane=new ScrollPane(D, this, sid);
  mScrollPane->setGUI(mGUI);

  // Create the window
  Vector4 resizeGripDim, titlebarDim;
  resizeGripDim=Vector4(D.z-16,D.w-16,16,16);
  titlebarDim=Vector4(0,0,D.z,22);
 
  if(t==OWT_RESIZE || t==OWT_RESIZE_AND_MOVE){
    // Create a resize grip
    Callback c;
    c.setType(OCT_WIN_RESIZE);
    this->mResizeGrip=new ResizeGrip(resizeGripDim, c, G, this);
  }
  
  if(t==OWT_MOVE || t==OWT_RESIZE_AND_MOVE){
    // Create a title bar
    Callback c;
    c.setType(OCT_WIN_MOVE);
    this->mTitleBar=new TitleBar(titlebarDim,caption,c, G, this);
  }

  makeCorners();
  mScrollPane->setScrollBarsVisbleStatus();
  computeMinimumSize();
}

/** The destructor
  *
  */
BetaGUI::Window::~Window(){

  LOGI("Window destructor called");
  mGUI->removeWindow(this);

  delete mScrollPane;
  mScrollPane=NULL;

}

/** Handle a key pressed event
  *
  * \param k The key pressed
  * \param px The mouse X position
  * \param py The mouse Y position
  *
  * \return \c true if the event is handled or \c false otherwise
  *
  */
bool BetaGUI::Window::checkKey(String k, unsigned int px, unsigned int py){
  return mScrollPane->handleKeyEvent( k, px, py);

}

/** Get the GUI object this window use
  *
  * \return Thze current GUI object
  *
  */
BetaGUI::GUI* BetaGUI::Window::getGUI(){
  return mGUI; 
}

/** Change the minimal allowed size of this window
  *
  * \param mw The minimal width in pixels
  * \param mh The minimal height in pixels
  *
  * \sa minimalWidth, minimalHeight.
  *
  */
void BetaGUI::Window::setMinimalSize(unsigned int mw, unsigned int mh){
  minimalWidth=mw;
  minimalHeight=mh;
}

/** Change the alwaysTransparent status of this window
  *
  * \param b The new alwaysTransparent status
  *
  * \sa \ref BetaGUI::Window::setAlwaysTransparent "alwaysTransparent" (member)
  *
  */
void BetaGUI::Window::setAlwaysTransparent(bool b){
  alwaysTransparent=b;
}

/** Change the title of this window
  *
  * \param title The new title
  *
  */
void BetaGUI::Window::setTitle(const String& title){
  if (mTitleBar){
    mTitleBar->setCaption(title);
  }

  mCaption=title;
}

/** Draws the window
  *
  * \param qr The QuadRenderer used to draw it
  *
  */
void BetaGUI::Window::draw(QuadRenderer* qr){
  if (visible){
    if (geometryDirty){
      makeCorners();
    }

    qr->setAlpha( this->alpha );
    mSkin->drawWindow(qr, corners, "Caption");

    // These widgets do not move with scrollpane
    if (mResizeGrip) mResizeGrip->draw(qr);
    if (mTitleBar)   mTitleBar->draw(qr);
    mScrollPane->draw( qr );
  }
}

/** Change the transparency of the window and all its childs
  *
  * \param f The new alpha value
  *
  */
void BetaGUI::Window::setTransparency(float f){
  this->alpha=f;
  if (mResizeGrip) mResizeGrip->setTransparency(f);
  if (mTitleBar)   mTitleBar->setTransparency(f);
  mScrollPane->setTransparency(f);
}

/** Return the title of this window
  *
  * \return The title as an Ogre string
  *
  */
const String& BetaGUI::Window::getTitle(void){
  return mCaption;
}

/** Set this window inactive
  *
  * The titlebar and the resizegrip are now inactive.
  *
  */
void BetaGUI::Window::deactivate(void){
  if (mTitleBar){
    mTitleBar->activate(false);
  }
  if (mResizeGrip){
    mResizeGrip->activate(false);
  }
}

/** Resize this widget
  *
  * This resizes the widget, moves its resizeGrip and resize its TitleBar.
  *
  * \param px The mouse pointer position in pixels
  * \param py The mouse pointer position in pixels
  *
  */
void BetaGUI::Window::resize(int px, int py){
  int new_height, new_width;
  int devX, devY;
  int old_width = getWidth();
  int old_height= getHeight();

  mScrollPane->getMovingDev(devX, devY);
  // Now devX and devY contains position of mouse cursor relative
  // to Window (or Container) top left corner.

  /* Compute new width
   *
   * v0.0.5-185 : The devX addition fix the attraction bug
   *
   */
  if (((px+devX) - getLeft()) < minimalWidth){
    new_width= minimalWidth;
  }
  else{
    new_width=  (px - getLeft()) + devX;
  }

  /* Compute new height
   *
   * v0.0.5-185 : The devY addition fix the attraction bug
   *
   */
  if (((py+devY) - getTop()) < minimalHeight){ 
    new_height= minimalHeight;
  }
  else{
    new_height=  (py - getTop()) + devY;
  }

  // Moves the ResizeGrip
  mResizeGrip->move( new_width - 16, new_height - 16 );


  // Resize the title bar
  mTitleBar->setWidth( new_width );

  setWidth( new_width );
  setHeight (new_height );

  mScrollPane->setWidth( new_width );
  mScrollPane->setHeight( new_height );

  mScrollPane->setScrollBarsVisbleStatus();
  mScrollPane->setGeometryDirty();

}

void BetaGUI::Window::move(int px, int py){
  int devX, devY;
  mScrollPane->getMovingDev(devX, devY);
  /*  LOGCATS("devX=");
  LOGCATI(devX);
  LOGCATS(" devY=");
  LOGCATI(devY);
  LOGCAT();
  */

  int width  = corners.right - corners.left;
  int height = corners.bottom - corners.top;

  corners.left =px-devX;
  corners.top  =py-devY;

  // Negative position is forbiden
  if (corners.left<0) corners.left=0;
  if (corners.top<0)  corners.top=0;

  corners.right=corners.left+width;
  corners.bottom=corners.top+height;

  mScrollPane->move( px, py );
  setGeometryDirty();
}

/** Is a point in this widget
  *
  * \param mx The X position of the mouse
  * \param my The Y position of the mouse
  * \param px Not used here
  * \param py Not used here
  *
  * \return \c true if the given values are inside the widget, \c false
  *         otherwise
  *
  */
bool BetaGUI::Window::
in(unsigned int mx, unsigned int my, unsigned int px, unsigned int py){
  return (mx>=corners.left&&mx<=corners.right) && 
    (my>=corners.top&&my<=corners.bottom);
}

/** Handle a mouse event
  *
  * The mouse event handling loop. For more information on mouse event 
  * handling from Widget, please see the \link 
  * RainbruRPG::OgreGui::Widget::injectMouse() Widget::injectMouse() \endlink
  * function.
  *
  * \param px    The X position of the mouse
  * \param py    The X position of the mouse
  * \param event The mouse event
  *
  * \return \c true if the event is handled or \c false otherwise
  *
  */
bool BetaGUI::Window::check(unsigned int px, unsigned int py, 
			    const OgreGui::MouseEvent& event){
  
  // The OgreGui scope for MouseEvent to avoid ambigous use in Win32
  
  bool inWindow=in(px, py, 0, 0);
  bool LMB=event.isLeftMouseButtonPressed();

  // If we are outside window
  if (!inWindow){
    mGUI->getMousePointer()->setState(MPS_ARROW);
    if (mTitleBar) mTitleBar->activate(false);
  }

  if (mResizeGrip) mResizeGrip->activate(false);

  bool inTitleBar=handleMouseMoveCursor(px,py,LMB);

  // If we are in titlebar but the mouse button is up, all is done
  if (inTitleBar&&!LMB) return true;
 
  if (mTitleBar){
    bool btnEvent = mScrollPane
      ->handleButtonEvent(px, py, corners.left, corners.top,
			  LMB, this, mTitleBar );
    
    if (btnEvent){
      return true;
    }
    else{
      mScrollPane->resetMovingDev();
    }
    
 }

  // Handle resizegrip
  bool resize=handleMouseResizeCursor(px, py, LMB, inTitleBar);

  if (mResizeGrip){
    bool btnEvent = mScrollPane
      ->handleButtonEvent(px, py, corners.left, corners.top,
			  LMB, this, mResizeGrip );

    if (btnEvent){
      return true;
    }

  }

  bool scEvent=mScrollPane->handleScrollBarsEvent(px, py, event, this);
  if (scEvent) return true;

  return mScrollPane->handleChildsEvent( px, py, 
					 event, this );
}

/** Add a widget to this window
  *
  * It is simply a call to 
  * \ref RainbruRPG::OgreGui::ScrollPane::addWidget(Widget*)
  * "ScrollPane::addWidget(Widget*)".
  *
  * \param w The widget to add
  *
  */
void BetaGUI::Window::addWidget(Widget* w){
  mScrollPane->addWidget(w);
  mScrollPane->setScrollBarsVisbleStatus();
}

/** Add a widget to this window
  *
  * It is simply a call to 
  * \ref RainbruRPG::OgreGui::ScrollPane::addWidget(Button*)
  * "ScrollPane::addWidget(Button*)".
  *
  * \param btn The widget to add
  *
  */
void BetaGUI::Window::addWidget(Button* btn){
  mScrollPane->addWidget(btn);
  mScrollPane->setScrollBarsVisbleStatus();
}

/** Add a widget to this window
  *
  * It is simply a call to 
  * \ref RainbruRPG::OgreGui::ScrollPane::addWidget(TextInput*)
  * "ScrollPane::addWidget(TextInput*)".
  *
  * \param ti The widget to add
  *
  */
void BetaGUI::Window::addWidget(BetaGUI::TextInput* ti){
  mScrollPane->addWidget(ti);
  mScrollPane->setScrollBarsVisbleStatus();
}

/** Change the scrollbar policy
  *
  * \param p The new scrollpane policy
  *
  * \sa \ref RainbruRPG::OgreGui::ScrollPane::setHorizontalScrollbarPolicy()
  *     "setHorizontalScrollbarPolicy()", 
  *     \ref RainbruRPG::OgreGui::tScrollBarPolicy 
  *     "tScrollBarPolicy"
  *
  */
void BetaGUI::Window::setHorizontalScrollbarPolicy(tScrollBarPolicy p){
  mScrollPane->setHorizontalScrollbarPolicy(p);
}

/** Change the scrollbar policy
  *
  * \param p The new scrollpane policy
  *
  * \sa \ref RainbruRPG::OgreGui::ScrollPane::setVerticalScrollbarPolicy()
  *     "setVerticalScrollbarPolicy()", 
  *     \ref RainbruRPG::OgreGui::tScrollBarPolicy 
  *     "tScrollBarPolicy"
  *
  */
void BetaGUI::Window::setVerticalScrollbarPolicy(tScrollBarPolicy p){
  mScrollPane->setVerticalScrollbarPolicy(p);
}

/** Get the scrollbar policy
  *
  * \return p The scrollpane policy
  *
  * \sa \ref RainbruRPG::OgreGui::ScrollPane::getHorizontalScrollbarPolicy()
  *     "getHorizontalScrollbarPolicy()", 
  *     \ref RainbruRPG::OgreGui::tScrollBarPolicy 
  *     "tScrollBarPolicy"
  *
  */
tScrollBarPolicy BetaGUI::Window::getHorizontalScrollbarPolicy(void){
  return mScrollPane->getHorizontalScrollbarPolicy();
}

/** Get the scrollbar policy
  *
  * \return p The scrollpane policy
  *
  * \sa \ref RainbruRPG::OgreGui::ScrollPane::getVerticalScrollbarPolicy()
  *     "getVerticalScrollbarPolicy()", 
  *     \ref RainbruRPG::OgreGui::tScrollBarPolicy 
  *     "tScrollBarPolicy"
  *
  */
tScrollBarPolicy BetaGUI::Window::getVerticalScrollbarPolicy(void){
  return mScrollPane->getVerticalScrollbarPolicy();
}


/** Debug the scrollpane using \ref RainbruRPG::Exception::Logger
  *
  */
void BetaGUI::Window::debugScrollPane(void){
  LOGCATS("maxChildRight=");
  LOGCATI(mScrollPane->getMaxChildRight());
  LOGCATS(" maxChildBottom=");
  LOGCATI(mScrollPane->getMaxChildBottom());
  LOGCAT();
}

/** Is the vertical scrollbar needed ?
  *
  * \return The scrollbar visibility status
  *
  */
bool BetaGUI::Window::isVerticalScrollbarVisible(void)const{
  return mScrollPane->isVerticalScrollbarNeeded();
}

/** Is the horizontal scrollbar needed ?
  *
  * \return The scrollbar visibility status
  *
  */
bool BetaGUI::Window::isHorizontalScrollbarVisible(void)const{
  return mScrollPane->isHorizontalScrollbarNeeded();
}

/** The corners computation function
  *
  * This function set the 
  * \ref RainbruRPG::OgreGui::ScrollPane::mContentRectangle
  * "ScrollPane::mContentRectangle" value, used to specify the rectangle
  * where ScrollPane's childs widgets are drawn.
  *
  */
void BetaGUI::Window::makeCorners(void){

  geometryDirty = false;

  if (mTitleBar && mTitleBar->isVisible()){
    Ogre::Rectangle contentRectangle(corners);
    contentRectangle.top += mTitleBar->getHeight();
    mScrollPane->setContentRectangle(contentRectangle);
  }
  else{
    mScrollPane->setContentRectangle(corners);
  }

}

/** Get the scrollbar
  *
  * It is just a wrapper to the
  * \ref RainbruRPG::OgreGui::ScrollPane::getHorizontalScrollbar 
  * "ScrollPane::getHorizontalScrollbar()" function called on
  * \ref BetaGUI::Window::mScrollPane "mScrollPane".
  *
  * \return The scrollbar
  *
  */
RainbruRPG::OgreGui::HScrollBar* 
BetaGUI::Window::getHorizontalScrollbar(void){
  return mScrollPane->getHorizontalScrollbar();
}

/** Get the scrollbar
  *
  * It is just a wrapper to the
  * \ref RainbruRPG::OgreGui::ScrollPane::getVerticalScrollbar 
  * "ScrollPane::getVerticalScrollbar()" function called on
  * \ref BetaGUI::Window::mScrollPane "mScrollPane".
  *
  * \return The scrollbar
  *
  */
RainbruRPG::OgreGui::VScrollBar* 
BetaGUI::Window::getVerticalScrollbar(void){
  return mScrollPane->getVerticalScrollbar();
}

/** Computation of the minimal size of the window
  *
  * The minimal size of the windows must depends only on Skin values. In case
  * some skins are used, the size will be computed with real used values.
  * In both width and height, the size of the ResizeGrip must be used.
  *
  * The minimal height depends on the TitleBar's height if the window is
  * movable and the vertical scrollbar's height. 
  *
  * The minimal width depends only on the horizontal scrollbar's width.
  *
  */
void BetaGUI::Window::computeMinimumSize(void){
  //minimalWidth(50),
  minimalHeight =  mSkin->getVScrollBarMinHeight();

  if (this->mTitleBar){
    minimalHeight += mSkin->getTitleBarHeight();
  }

  minimalWidth = mSkin->getHScrollBarMinWidth();
}
