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

#include "gsserverlist.h"

#include <stringconv.h>
#include <logger.h>

#include <label.h>
#include <bgwindow.h>
#include <pushbutton.h>
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
  gsMenuBase(false),
  mWin(NULL),
  mMcl(NULL),
  mNumServer(NULL),
  btnRefresh(NULL),
  btnPlay(NULL),
  btnMoreInfos(NULL)
{

  LOGI("Constructing a gsServerList");
  velocity=new vcConstant();
  translateTo(0.0f);

  xml=new xmlServerList();

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

  delete xml;
  xml=NULL;

  delete mWin;
  mWin=NULL;

  delete mMcl;
  mMcl=NULL;

  delete mNumServer;
  mNumServer=NULL;

  // deleting buttons
  delete btnRefresh;
  delete btnPlay;
  delete btnMoreInfos;
  btnRefresh = NULL;
  btnPlay = NULL;
  btnMoreInfos = NULL;
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
  Ogre::RenderWindow* rw=GameEngine::getSingleton().getRenderWindow();

  setupTabOrder();
}

/** Setup the list content
  *
  * \sa serverList
  *
  */
void RainbruRPG::Core::gsServerList::setupServerList(){

  // Create the list
  unsigned int width = 600;
  unsigned int rwWidth=GameEngine::getSingleton().getRenderWindow()->getWidth();
  unsigned int posX=(rwWidth/2)-(width/2);
  BetaGUI::GUI* mGUI =GameEngine::getSingleton().getOgreGui();
  mWin =new Window(Vector4(posX, 10, width, 400), BetaGUI::OWT_RESIZE_AND_MOVE, 
		   "Server list", mGUI);
  mGUI->addWindow(mWin);

  Vector4 mclPosDim(10,30,width - 30,320);
  mMcl=new MultiColumnList(mclPosDim, mWin);
  mMcl->sigSelectionChanged.
    connect( sigc::mem_fun(this, &RainbruRPG::Core::gsServerList::slotSelectionChanged) );
  mMcl->setDebugName("MCL.ServerList");
  mWin->addWidget(mMcl);

  // Adding columns
  mMcl->addColumn( "#", 30 );
  mMcl->addColumn( "Name", 150 );
  mMcl->addColumn( "Occ", 50 );
  mMcl->addColumn( "Type", 100 );
  mMcl->addColumn( "Description", 200 );

  // Numbers of found servers
  Vector4 mNumServerDim(10, 362, 20, 20);
  mNumServer=new Label (mNumServerDim, "??? servers found", mWin);
  mWin->addWidget(mNumServer);

  // Boutons
  btnRefresh= new PushButton(Vector4(200,360,100,24),
				 "Refresh", 
				 BetaGUI::Callback::Callback(this), mWin);
  mWin->addWidget(btnRefresh);
  
  btnPlay = new PushButton(Vector4(320,360,100,24),
				 "Play", 
				 BetaGUI::Callback::Callback(this), mWin);
  btnPlay->disable();
  mWin->addWidget(btnPlay);

  btnMoreInfos= new PushButton(Vector4(440,360,140,24),
				 "More infos", 
				 BetaGUI::Callback::Callback(this), mWin);
  btnMoreInfos->disable();
  mWin->addWidget(btnMoreInfos);



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
  unsigned int itemId=1;
  tServerList* lst=xml->getServerList();
  tServerList::const_iterator iter;
  MultiColumnListItem* item;

  // Feed the list
  for (iter=lst->begin(); iter != lst->end(); iter++){
    item=new MultiColumnListItem();
    item->setText(0, StringConv::getSingleton().itos(itemId));
    item->setText(1, (*iter)->getName());
    item->setText(2, (*iter)->getOccupationStr());
    item->setText(3, (*iter)->getTypeStr());
    item->setText(4, (*iter)->getDescription());

    mMcl->addItem(item);
    itemId++;
  }

  LOGCATI(mMcl->getItemList().size());
  LOGCATS(" items in the MultiColumnList");
  LOGCAT();

  String numS=StringConv::getSingleton().itos(lst->size());
  numS += " servers found";
  mNumServer->setCaption(numS);
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
  // Registering TabNavigation
  /*  tabNav->clear();
  tabNav->setParent("RainbruRPG/ServerList/");
  //  tabNav->addMultiColumnList("RainbruRPG/ServerList/List", 
  //	   CEGUI::Event::Subscriber(&gsServerList::onConnectClicked,this));
  tabNav->addWidget("RainbruRPG/ServerList/Refresh");
  tabNav->addWidget("RainbruRPG/ServerList/Connect");
  tabNav->addWidget("RainbruRPG/ServerList/Back");
  */
}

/** A button was pressed in this game state
  *
  * \param vButton The button to be pressed
  *
  */
void RainbruRPG::Core::gsServerList::onButtonPress(BetaGUI::Button* vButton){
  std::string msg;
  bool log=true;

  if (vButton == btnRefresh){
    log = false;
    refreshList();
  }
  else if (vButton == btnPlay){
    msg = "Play";
  }
  else if (vButton == btnMoreInfos){
    msg = "MoreInfos";
  }

  if (log){
    msg += " button pressed";
    LOGI(msg.c_str());
  }
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

  bool sel = mMcl->isOneItemSelected();
  btnPlay->setEnable( sel );
  btnMoreInfos->setEnable( sel );
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

  // Disable all buttons
  btnRefresh->disable();
  btnPlay->disable();
  btnMoreInfos->disable();

  // Clear the list
  mMcl->clear();
  
  // Refresh xml
  xml->refresh();

  // Feed the list
  feedList();

  // Enable refresh button
  btnRefresh->enable();
  
}
