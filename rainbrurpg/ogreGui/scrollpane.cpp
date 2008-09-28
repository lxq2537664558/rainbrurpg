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

/** \file scrollpane.cpp
  * Implements a scroll pane widget used in OgreGUI's windows
  *
  */

#include "scrollpane.h"

#include "bgwindow.h"
#include "quadrenderer.h"
#include "widget.h"
#include "hscrollbar.h"
#include "vscrollbar.h"
#include "drawingdevsettings.h"

#include <OgreOverlayManager.h>
#include <OgreException.h>
#include <logger.h>

#include <algorithm>

/** The constructor
  *
  * Both horizontal and vertical scrollbar are drawn only if needed by default.
  *
  * \param dim    The dimensions of the scrollpane
  * \param parent The parent
  * \param sid    The skin identifier
  *
  */
RainbruRPG::OgreGui::ScrollPane::
ScrollPane(Vector4 dim, Window* parent,OgreGuiSkinID sid):  
  Container(dim, parent, sid),
  mVScrollBarPolicy(SBP_IF_NEEDED),
  mHScrollBarPolicy(SBP_IF_NEEDED),
  mDrawingDev(NULL)
{
  setName("ScrollPane");

  // Base cnte nt corner
  mContentRectangle=parent->getCorners();

  Vector4 sbDim( dim.z-16, VSB_YPOS, 14, dim.w-(VSB_YPOS + 18) );
  mVScrollBar=new VScrollBar(sbDim, parent);//, OSI_BETAGUI);
  //  this->addWidget(mVScrollBar);

  Vector4 sbDim2( 2, dim.w-16, dim.z-20, 14 );
  mHScrollBar=new HScrollBar(sbDim2, parent);
  //  this->addWidget(mHScrollBar);

  // Signals connection
  mHScrollBar->sigValueChanged.connect( sigc::mem_fun(this,
     &RainbruRPG::OgreGui::ScrollPane::horizontalScrollBarValueChange));

  mVScrollBar->sigValueChanged.connect( sigc::mem_fun(this,
     &RainbruRPG::OgreGui::ScrollPane::verticalScrollBarValueChange));

  std::string s = "ScrollPane of the '";
  s += parent->getTitle();
  s += "' window";
  mDrawingDev = new DrawingDevSettings(s);

}

/** The destructor
  *
  */
RainbruRPG::OgreGui::ScrollPane::~ScrollPane(){
  delete mVScrollBar;
  mVScrollBar=NULL;

  delete mHScrollBar;
  mHScrollBar=NULL;

  delete mDrawingDev;
  mDrawingDev=NULL;

}

/** Draws the Scrollpane content
  *
  * The Scrollpane ability to draw only visible widgets is done using
  * the scissor rectangle. Please see \ref 
  * RainbruRPG::OgreGui::QuadRenderer::useParentScissor "useParentScissor"
  * for more informations.
  *
  */
void RainbruRPG::OgreGui::ScrollPane::draw(QuadRenderer* qr){
  /* v0.0.5-172 : This line fix a bug : The label wasn't drawn until scrollbars
   * was shown. The scissor rectangle was in used when ScrollBar wasn't needed
   *
   */
  qr->disableScissor();

  // This widgets do not move (QuadRenderer::DrawingDev comes after them)
  mVScrollBar->draw(qr);
  mHScrollBar->draw(qr);

  qr->setScissorRectangle(mContentRectangle);
  qr->setUseParentScissor(true);


  qr->addDrawingDev( mDrawingDev );
  Container::draw(qr);
  qr->removeDrawingDev( mDrawingDev );
  qr->setUseParentScissor(false);
}

/** Changes the horizontal Scrollbar policy
  *
  * \param p The new policy
  *
  * \sa \ref RainbruRPG::OgreGui::ScrollPane::getHorizontalScrollbarPolicy()
  *     "getHorizontalScrollbarPolicy()", 
  *     \ref RainbruRPG::OgreGui::tScrollBarPolicy 
  *     "tScrollBarPolicy"
  *
  */
void RainbruRPG::OgreGui::ScrollPane::
setHorizontalScrollbarPolicy(tScrollBarPolicy p){
  mHScrollBarPolicy=p;
}

/** Changes the vertical Scrollbar policy
  *
  * \param p The new policy
  *
  * \sa \ref RainbruRPG::OgreGui::ScrollPane::getVerticalScrollbarPolicy()
  *     "getVerticalScrollbarPolicy()", 
  *     \ref RainbruRPG::OgreGui::tScrollBarPolicy 
  *     "tScrollBarPolicy"
  *
  */
void RainbruRPG::OgreGui::ScrollPane::
setVerticalScrollbarPolicy(tScrollBarPolicy p){
  mVScrollBarPolicy=p;
}

/** Get the horizontal Scrollbar policy
  *
  * \return The current policy
  *
  * \sa \ref RainbruRPG::OgreGui::ScrollPane::setHorizontalScrollbarPolicy()
  *     "setHorizontalScrollbarPolicy()", 
  *     \ref RainbruRPG::OgreGui::tScrollBarPolicy 
  *     "tScrollBarPolicy"
  *
  */
tScrollBarPolicy RainbruRPG::OgreGui::ScrollPane::
getHorizontalScrollbarPolicy(void){
  return mHScrollBarPolicy;
}

/** Get the vertical Scrollbar policy
  *
  * \return The current policy
  *
  * \sa \ref RainbruRPG::OgreGui::ScrollPane::setVerticalScrollbarPolicy()
  *     "setVerticalScrollbarPolicy()", 
  *     \ref RainbruRPG::OgreGui::tScrollBarPolicy 
  *     "tScrollBarPolicy"
  *
  */
tScrollBarPolicy RainbruRPG::OgreGui::ScrollPane::
getVerticalScrollbarPolicy(void){
  return mVScrollBarPolicy;
}

/** Get the max right position of childs widget
  *
  * \return The max right position
  *
  */
int RainbruRPG::OgreGui::ScrollPane::getMaxChildRight(void){
  int maxRight=0;
  unsigned int i;

  for ( i=0; i<widgetList.size(); i++){
    maxRight=max( maxRight, widgetList[i]->getRight() );
  }

  for ( i=0; i<textInputList.size(); i++){
    maxRight=max( maxRight, textInputList[i]->getRight() );
  }

  for ( i=0; i<buttonList.size(); i++){
    maxRight=max( maxRight, buttonList[i]->getRight() );
  }

  return maxRight;
}

/** Get the max bottom position of childs widget
  *
  * \return The max bottom position
  *
  */
int RainbruRPG::OgreGui::ScrollPane::getMaxChildBottom(void){
  int maxBottom=0;
  unsigned int i;

  for ( i=0; i<widgetList.size(); i++){
    maxBottom = max( maxBottom, widgetList[i]->getBottom() );
  }

  for ( i=0; i<textInputList.size(); i++){
    maxBottom = max( maxBottom, textInputList[i]->getBottom() );
  }

  for ( i=0; i<buttonList.size(); i++){
    maxBottom = max( maxBottom, buttonList[i]->getBottom() );
  }

  return maxBottom;
}

/** Tells if the horizontal scrollbar is needed according to its policy
  * 
  * \note This function uses \ref isVerticalScrollbarNeeded() to
  *       know if the horizontal one is needed.
  *
  * \return \c true if we need to draw horizontal scrollbar
  *
  */
bool RainbruRPG::OgreGui::ScrollPane::isHorizontalScrollbarNeeded(void){
  bool ret; // The scrollbar visibility status

  switch (mHScrollBarPolicy){
  case SBP_NEVER:
    return false;
    break;

  case SBP_ALWAYS:
    return true;
    break;

  case SBP_IF_NEEDED:
    int maxRight=getMaxChildRight()+parent->getLeft();

    // If the vertical scrollbar is needed, it must be outside computation
    if (isVerticalScrollbarNeeded()){
      ret = maxRight > (corners.right - mVScrollBar->getWidth());
    }
    else{
      ret = maxRight > corners.right;
    }

    return ret;
    break;
  }
}

/** Tells if the vertical scrollbar is needed according to its policy
  * 
  * \note We must know if the horizontal scrollbar is visible to know
  *       if the vertical one is needed but we cannot use the 
  *       \ref isHorizontalScrollbarNeeded() function : This uses 
  *       isVerticalScrollbarNeeded() and if both function uses
  *       the other one, we could have a circular reference.
  *       
  *
  * \return \c true if we need to draw vertical scrollbar
  *
  */
bool RainbruRPG::OgreGui::ScrollPane::isVerticalScrollbarNeeded(void){
  bool isHorisVisible; // Is the horizontal scrollbar visible ?
  bool ret;            // The vertical scrollbar visibility status

  switch (mVScrollBarPolicy){
  case SBP_NEVER:
    return false;
    break;

  case SBP_ALWAYS:
    return true;
    break;

  case SBP_IF_NEEDED:

    // We must know if horizontal scrollbar is needed but we can't
    // call isHorizontalScrollbarNeeded() to avoid circular refences
    int maxRight=getMaxChildRight()+parent->getLeft();
    isHorisVisible = maxRight > corners.right;

    // Is the vertical scroll bar visible
    int maxBottom=getMaxChildBottom()+parent->getTop();
    if (isHorisVisible){
      ret = maxBottom > (corners.bottom - mHScrollBar->getHeight());
    }
    else{
      ret = maxBottom > corners.bottom;
    }
    return ret;
    break;
  }
}

/** Set the scrollbars visible or hidden according to policies
  *
  * It sets the scrollbars (\ref RainbruRPG::OgreGui::ScrollPane::mHScrollBar
  * "mHScrollBar" and \ref RainbruRPG::OgreGui::ScrollPane::mVScrollBar
  * "mVScrollBar") visible or hidden according to their policies using 
  * \ref RainbruRPG::OgreGui::ScrollPane::isVerticalScrollbarNeeded 
  * "isVerticalScrollbarNeeded()" and 
  * \ref RainbruRPG::OgreGui::ScrollPane::isHorizontalScrollbarNeeded 
  * "isHorizontalScrollbarNeeded".
  *
  */
void RainbruRPG::OgreGui::ScrollPane::setScrollBarsVisbleStatus(){
  bool hsb_needed = isHorizontalScrollbarNeeded();
  bool vsb_needed = isVerticalScrollbarNeeded();

  if (hsb_needed){
    mHScrollBar->setVisible(true);

    int hsb_max = getMaxChildRight() - getWidth() + 5;

    // Handle the vertical scrollbar's width if needed
    if (vsb_needed) hsb_max += mVScrollBar->getWidth();

    mHScrollBar->setMax(hsb_max);
  }
  else{
    mHScrollBar->setVisible(false);
    mHScrollBar->setValue(0);
  }

  if (vsb_needed){
    mVScrollBar->setVisible(true);

    int vsb_max = getMaxChildBottom() - getHeight() + 5;

    // Handle the horizontal scrollbar's height if needed
    if (hsb_needed) vsb_max += mHScrollBar->getHeight();

    mVScrollBar->setMax(vsb_max);
  }
  else{
    mVScrollBar->setVisible(false);
    mVScrollBar->setValue(0);
  }
}

/** Change the width of this scrollpane
  *
  * This function is reimplemented because it must move 
  * \ref RainbruRPG::OgreGui::ScrollPane::mVScrollBar "mVScrollBar"
  * and resize \ref RainbruRPG::OgreGui::ScrollPane::mHScrollBar 
  * "mHScrollBar".
  *
  * \param i The new width in pixels
  *
  */
void RainbruRPG::OgreGui::ScrollPane::setWidth(int i){
  corners.right=corners.left+i;

  mVScrollBar->move(i-16, VSB_YPOS);
  mHScrollBar->setWidth(i-20);
}

/** Change the width of this scrollpane
  *
  * This function is reimplemented because it must resize 
  * \ref RainbruRPG::OgreGui::ScrollPane::mVScrollBar "mVScrollBar"
  * and move \ref RainbruRPG::OgreGui::ScrollPane::mHScrollBar 
  * "mHScrollBar".
  *
  * \param i The new height in pixels
  *
  */
void RainbruRPG::OgreGui::ScrollPane::setHeight(int i){
  corners.bottom=corners.top+i;

  mHScrollBar->move(2, i-16);
  mVScrollBar->setHeight( i-(VSB_YPOS + 18));
}

/** Change the width of this scrollpane
  *
  * This function is reimplemented because it must 
  * move \ref RainbruRPG::OgreGui::ScrollPane::mHScrollBar 
  * "mHScrollBar" and \ref RainbruRPG::OgreGui::ScrollPane::mVScrollBar 
  * "mVScrollBar".
  *
  * \param vX The new left position
  * \param vY The new top position
  *
  */
void RainbruRPG::OgreGui::ScrollPane::move(int vX, int vY){
  int temp_width = getWidth();
  int temp_height= getHeight();

  corners.top  = vY;
  corners.left = vX;

  setWidth(temp_width);
  setHeight(temp_height);
  setChildWidgetGeometryDirty();
}


/** The horizontal scrollbar slot
  * 
  * This sig-c++ slot is connected to the 
  * \ref RainbruRPG::OgreGui::ScrollBar::sigValueChanged "sigValueChanged"
  * signal of \ref RainbruRPG::OgreGui::ScrollPane::mHScrollBar 
  * "mHScrollBar".
  *
  * \param i The new scrollbar value
  *
  */
void RainbruRPG::OgreGui::ScrollPane::horizontalScrollBarValueChange(int i){
  mDrawingDev->setDevX( i );
}

/** The vertical scrollbar slot
  * 
  * This sig-c++ slot is connected to the 
  * \ref RainbruRPG::OgreGui::ScrollBar::sigValueChanged "sigValueChanged"
  * signal of \ref RainbruRPG::OgreGui::ScrollPane::mVScrollBar 
  * "mVScrollBar".
  *
  * \param i The new scrollbar value
  *
  */
void RainbruRPG::OgreGui::ScrollPane::verticalScrollBarValueChange(int i){
  mDrawingDev->setDevY( i );
}

/** Handles the scrollbars events
  *
  * \param px, py The mouse position in pixels
  * \param event  The mouse event 
  * \param P      The parent window
  *
  * \return \c true if the event is used
  *
  */
bool RainbruRPG::OgreGui::ScrollPane::
handleScrollBarsEvent(unsigned int px, unsigned int py,  
		      const MouseEvent& event, Window* P){
  unsigned int x=px-P->getLeft();
  unsigned int y=py-P->getTop();

  bool hEvent=mHScrollBar->injectMouse( x, y, event );
  if (hEvent) return true;

  return mVScrollBar->injectMouse( x, y, event );
}

/** Handle mouse events of childs
  *
  * \note This function is reimplemented to handle the xDrawingDev
  *       and yDrawingDev values.
  *
  * \param px, py The mouse pointer position
  * \param event  The mouse event
  * \param win    The window from where the event if fired
  *
  * \return \c true if the event is used.
  *
  */
bool RainbruRPG::OgreGui::ScrollPane::
handleChildsEvent(unsigned int px, unsigned int py, const MouseEvent& event, 
		  Window* win){

  bool inWindow=win->in(px, py, 0, 0);
  bool LMB=event.isLeftMouseButtonPressed();

  // Handles drawing dev
  px += mDrawingDev->getDevX();
  py += mDrawingDev->getDevY();

  // If we are outside window, we don't handle events
  if (!inWindow){
    if(activeButton) activeButton->activate(false);
    if(activeTextInput) activeTextInput->deactivate();
    mGUI->getMousePointer()->setState(MPS_ARROW);
    return false;
  }
  

  handleMouseTextCursor(px, py, LMB);
  handleWidgetMouseEvents(px, py, event);


  if(activeButton){
    activeButton->activate(false);
    activeButton=NULL;
  }
     
  /*  if(activeTextInput){
    activeTextInput->deactivate();
    activeTextInput=NULL;
  }
  */
  // handle button events
  for(unsigned int i=0;i<buttonList.size();i++){
    bool btn= handleButtonEvent( px, py, corners.left, corners.top, LMB, win, 
				 buttonList[i] );
    if (btn) return true;

  }

  if (event.isLeftButtonClick()){
    for(unsigned int i=0;i<textInputList.size();i++){
      if(textInputList[i]->in( px, py, corners.left, corners.top))
	continue;
      LOGI("Selecting TextInput");
    
      /* The current indexed textInputList element is under the mouse
       * activeTextInput is set as a pointer to it.
       * And we change its texture to graphically mark it as active.
       *
       * We also call the deactivateAllOtherTextInput to get only one
       * TextInput activated.
       *
       */
      activeTextInput=textInputList[i];
      activeTextInput->activate();
      deactivateAllOtherTextInput(activeTextInput);
      return true;
    }
  }

  // We click anywhere in the window but not on a widget
  if (event.isLeftButtonClick()){
    if(activeTextInput) activeTextInput->deactivate();
  }


  return true;
}

/** Change the content geometry
  *
  * This function is used by subclasses to change the content geometry, 
  * by example to handle the height of a TitleBar.
  *
  * \param vRect The new geometry
  *
  * \sa \ref ScrollPane::mContentRectangle "mContentRectangle" (member)
  *
  */
void RainbruRPG::OgreGui::ScrollPane::
setContentRectangle(const Ogre::Rectangle& vRect){
  mContentRectangle = vRect;

  // Computing content scissor rectangle
  if (mVScrollBar->isVisible()){
    mContentRectangle.right -= mVScrollBar->getWidth();
  }
  if (mHScrollBar->isVisible()){
    mContentRectangle.bottom -= mHScrollBar->getHeight();
  }

}

/** Get the content rectangle
  *
  * \return The rectangle containing the childs widgets
  *
  * \sa \ref ScrollPane::mContentRectangle "mContentRectangle" (member)
  *
  */
const Ogre::Rectangle& RainbruRPG::OgreGui::ScrollPane::
getContentRectangle(void){
  return mContentRectangle;
}

/** Get the horizontal scrollbar
  *
  * \sa \ref RainbruRPG::OgreGui::ScrollPane::mHScrollBar "mHScrollBar"
  *     (member).
  *
  * \return A pointer to the horizontal scrollbar
  *
  */
HScrollBar* RainbruRPG::OgreGui::ScrollPane::getHorizontalScrollbar(void){
  return mHScrollBar;
}

/** Get the vertical scrollbar
  *
  * \sa \ref RainbruRPG::OgreGui::ScrollPane::mVScrollBar "mVScrollBar"
  *     (member).
  *
  * \return A pointer to the vertical scrollbar
  *
  */
VScrollBar* RainbruRPG::OgreGui::ScrollPane::getVerticalScrollbar(void){
  return mVScrollBar;
}
