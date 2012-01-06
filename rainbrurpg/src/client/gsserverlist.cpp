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

/** \file gsserverlist.cpp
  * Implements the state showing the server list
  *
  */

#include "gsserverlist.h"

#include <stringconv.h>
#include <logger.h>

#include <Widget.hpp>

#include <label.h>
#include <multicolumnlist.h>
#include <multicolumnlistitem.h>
#include <sigc++/sigc++.h>

#include "keyboardnavigation.h"

/** The default constructor
  *
  * Creates a vcConstant velocity calculator and initialize
  * the \ref RainbruRPG::Network::Ident::xmlServerList "xmlServerList"
  * class member called xml.
  *
  * \sa velocity, xml.
  * 
  */
RainbruRPG::Core::gsServerList::gsServerList():
  gsMenuBase("gsServerList", false)
{

  LOGI("Constructing a gsServerList");
  velocity=new vcConstant();
  translateTo(0.0f);

  xml = xmlServerList();

}

/** Destructor
  *
  * Free all memory used by this instance of this class.
  *
  * \sa velocity, serverList, xml.
  *
  */
RainbruRPG::Core::gsServerList::~gsServerList(){
  if (velocity){
    delete velocity;
    velocity=NULL;
  }
}

/** Initialize this game state
  *
  */
void RainbruRPG::Core::gsServerList::init(){
  LOGI("Initialising gsServerList");
  gsMenuBase::init();

  setupServerList();
  setupTabOrder();
  LOGI("gsServerList initialization complete");
}

/** Resume the game state after a pause() call or a state change
  *
  * This function is automatically called by GameEngine when switching
  * from another state.
  *
  */
void RainbruRPG::Core::gsServerList::resume(){
  setupTabOrder();
}

/** Setup the list content
  *
  * \sa serverList
  *
  */
void RainbruRPG::Core::gsServerList::setupServerList(){

  // Should now use OgerGui

  feedList();

}

/** Feed the server list widget
  *
  * The server list widget (serverList) is fed with the xml content. It
  * does not create the columns, there are added in the setupServerList()
  * function.
  *
  * \sa serverList, xml.
  *
  */
void RainbruRPG::Core::gsServerList::feedList(){

}

/** Setup the tabulation order 
  *
  * To be able to navigate with the \c Alt and \c Whift+Alt keys, this
  * function must correctly setup a TabNavigation instance.
  * Clears the current tabNav instance, set its parent and
  * adds the widgets that will have focus.
  *
  * \sa tabNav, TabNavigation, gsMainMenu::setupTabOrder().
  *
  */
void RainbruRPG::Core::gsServerList::setupTabOrder(){

}

/** A button was pressed in this game state
  *
  * \param vButton The button to be pressed
  *
  */
void RainbruRPG::Core::gsServerList::onButtonPress(BetaGUI::Button* vButton){


}

/** The server list's selection changed
  *
  * This slot is used to enable and disable \ref btnPlay and 
  * \ref btnMoreInfos buttons according to the selection content. This slot
  * must be connected to the 
  * \ref OgreGui::MultiColumnList::sigSelectionChanged 
  * "MultiColumnList::sigSelectionChanged" signal.
  *
  */
void RainbruRPG::Core::gsServerList::slotSelectionChanged(void){
  LOGI("slotSelectionChanged called");

}

/** Refresh the server list
  *
  * Reresh the content of the server list by caling 
  * \ref RainbruRPG::Network::Ident::xmlServerList::refresh()
  * "xmlServerList::refresh()".
  *
  */
void RainbruRPG::Core::gsServerList::refreshList(void){
  LOGI("gsServerList::refreshList called");

}
