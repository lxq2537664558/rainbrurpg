/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file WidgetList.cpp
  *
  * Implements a list of widget
  *
  * Modifications :
  * - 30 may 2009 : Starting implementation
  * - 13 jun 2010 : Focus functions implemented
  *
  */

#include "WidgetList.hpp"

#include <rainbrudef.h> // For the gettext stuff
#include <logger.h>


/** The named constructor
  *
  * \param vName The name used for serialization
  *
  */
RainbruRPG::OgreGui::WidgetList::WidgetList(const string& vName):
  Serializable(vName),
  mCurrentFocused(mList.begin()),
  mValidIterator(false)
{

}

/** The destructor
  *
  */
RainbruRPG::OgreGui::WidgetList::~WidgetList(){

}

/** Set the unique name of the list and all its widgets
  *
  * \param vParentUniqueName The parent name
  *
  */
void RainbruRPG::OgreGui::WidgetList::
setUniqueName(const string& vParentUniqueName){
  if (vParentUniqueName.empty()) LOGW(_("Parent name is empty"));

  mUniqueName = vParentUniqueName + "/" + mName;
  tWidgetList::iterator iter;
  
  for (iter = mList.begin(); iter != mList.end(); iter++){
    (*iter)->setUniqueName(mUniqueName);
  }

}

/** Returns the size of the list 
  *
  * \return The number of widget contained in the list
  *
  */
unsigned int RainbruRPG::OgreGui::WidgetList::size(){
  return mList.size();
}

/** Adds a widget to the end of the list
  *
  * \param vWidget The widget to be added
  *
  */
void RainbruRPG::OgreGui::WidgetList::push_back(Widget* vWidget){
  mList.push_back(vWidget);
}

/** Is this list empty ?
  *
  * \return \c true if empty
  *
  */
bool RainbruRPG::OgreGui::WidgetList::empty(){
  return mList.empty();
}

/** Return the internal STL list
  *
  * \return The internal list of widget as a constant
  *
  */
const RainbruRPG::OgreGui::tWidgetList& 
RainbruRPG::OgreGui::WidgetList::getList()const{
  return mList;
}

/** Return the next focusable widget
  *
  * Calling this function returns the next focusable widget from
  * the list, starting from mCurrentFocused. If no focusable is
  * found, it return NULL.
  *
  * This function updates mCurrentFocused to the next focusable
  * widget or to the end of the list if not found.
  *
  * \return The next focusable widget in the list
  *
  */
RainbruRPG::OgreGui::Widget* 
RainbruRPG::OgreGui::WidgetList::focusNext(void){

  tWidgetList::iterator iter;

  if (mValidIterator){
    iter = mCurrentFocused;
    iter++;
  }
  else{
    iter = mList.begin();
  }

  for (iter; iter != mList.end(); iter++){
    if ( (*iter)->canTakeFocus() ){
      mCurrentFocused = iter;
      mValidIterator=true;
      return (*iter);
    }
  }

  // No more focusable was found, devalidate the iterator and return NULL
  mValidIterator=false;
  return NULL;
}

/** Return the previous focusable widget
  *
  * Calling this function returns the previous focusable widget from
  * the list, starting from mCurrentFocused. If no focusable is
  * found, it return NULL.
  *
  * This function updates mCurrentFocused to the previous focusable
  * widget or to the end of the list if not found.
  *
  * \return The previous focusable widget in the list
  *
  */
RainbruRPG::OgreGui::Widget* 
RainbruRPG::OgreGui::WidgetList::focusPrevious(void){

  tWidgetList::reverse_iterator iter;

  if (mValidIterator){
    iter = tWidgetList::reverse_iterator(mCurrentFocused);
    iter++;
  }
  else{
    iter = mList.rbegin();
  }

  for (iter; iter != mList.rend(); iter++){
    if ( (*iter)->canTakeFocus() ){
      mCurrentFocused = tWidgetList::iterator(iter.base());
      mValidIterator=true;
      return (*iter);
    }
  }

  // No more focusable was found, devalidate the iterator and return NULL
  mValidIterator=false;
  return NULL;
}
