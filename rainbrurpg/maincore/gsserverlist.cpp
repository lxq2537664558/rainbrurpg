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
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

#include "gsserverlist.h"

#include <stringconv.h>

/** The default constructor
  *
  * Creates a vcConstant velocity calculator and initialize
  * the \ref RainbruRPG::Network::Ident::xmlServerList "xmlServerList"
  * class member called xml.
  *
  * \sa velocity, xml.
  * 
  */
RainbruRPG::Core::gsServerList::gsServerList()
  :gsMenuBase(false){

  serverList=NULL;
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
  serverList=NULL;

  delete xml;
  xml=NULL;
}

/** Initialize this game state
  *
  * Loads the \c serverList.layout CEGUI layout then call setupServerList()
  * and setupTabOrder().
  *
  */
void RainbruRPG::Core::gsServerList::init(){
  LOGI("Initialising gsServerList");
  gsMenuBase::init();
  GuiManager::getSingleton().loadCEGUILayout("serverList.layout");

  // Initialise the dialog parent
  this->rootWindowName="RainbruRPG/ServerList";

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
  // GuiManager::getSingleton().createTitleOverlay(rw);
  GuiManager::getSingleton().loadCEGUILayout("serverList.layout");
  setupServerList();

  // Initialise the dialog parent
  this->rootWindowName="RainbruRPG/Connection";

  setupTabOrder();
}

/** Setup the event callback for the CEGUI layout
  *
  * It initialize the pointer of the class member serverList. All the 
  * CEGUI button callbacks are also defined here.
  *
  * \sa serverList
  *
  */
void RainbruRPG::Core::gsServerList::setupServerList(){

  // Subscribe event
  CEGUI::Window* root=CEGUI::System::getSingleton().getGUISheet();

  // Root window
  CEGUI::Window* mainWindow=root->getChild("RainbruRPG/ServerList/");

  // Get the server ListBox
  CEGUI::Window* slWindow=mainWindow->getChild("RainbruRPG/ServerList/List");

  serverList=static_cast<CEGUI::MultiColumnList*>(slWindow);
  serverList->setSelectionMode(CEGUI::MultiColumnList::RowSingle);
  //  serverList->setSelectionBrushImage("TaharezLook", 
  //			       "MultiListSelectionBrush");

  serverList->setUserSortControlEnabled(true);

  // Creates column for serverList
  serverList->addColumn("Name", 0, CEGUI::UDim(0.40F, 0.0F));
  serverList->addColumn("Type", 1, CEGUI::UDim(0.25F, 0.0F));
  serverList->addColumn("Occupation", 2, CEGUI::UDim(0.25F, 0.0F));

  // Feed the list
  feedList();

  // Getting buttons
  CEGUI::Window* btnBack=root->getChild("RainbruRPG/ServerList/Back");

  CEGUI::Window* btnRefresh=mainWindow
    ->getChild("RainbruRPG/ServerList/Refresh");
  btnConnect=mainWindow->getChild("RainbruRPG/ServerList/Connect");
  btnConnect->setVisible(false);

  // Registering callbacks
  btnBack->subscribeEvent(CEGUI::Window::EventMouseClick, 
    CEGUI::Event::Subscriber(&gsServerList::onBackClicked,this));

  btnRefresh->subscribeEvent(CEGUI::Window::EventMouseClick, 
    CEGUI::Event::Subscriber(&gsServerList::onRefreshClicked,this));

  btnConnect->subscribeEvent(CEGUI::Window::EventMouseClick, 
    CEGUI::Event::Subscriber(&gsServerList::onConnectClicked,this));

  serverList->subscribeEvent(CEGUI::MultiColumnList::EventSelectionChanged, 
    CEGUI::Event::Subscriber(&gsServerList::onListSelectionChange,this));

  serverList->subscribeEvent(CEGUI::Window::EventMouseDoubleClick, 
    CEGUI::Event::Subscriber(&gsServerList::onListDoubleClick,this));

  serverList->subscribeEvent(CEGUI::Window::EventKeyDown, 
    CEGUI::Event::Subscriber(&gsServerList::onListKeyDown,this));

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

  tServerList* lst=xml->getServerList();
  tServerList::const_iterator iter;

  for (iter=lst->begin(); iter != lst->end(); iter++){
    CEGUI::uint newRow=serverList->addRow();

    // name
    const char* name=(*iter)->name;
    serverList->setItem(new CEGUI::ListboxTextItem(name), 0, newRow);

    // type
    unsigned int type=(*iter)->type;
    CEGUI::String itemTypeText;

    switch (type){
    case 1:
      itemTypeText="1 (Fantasy)";
      break;
    case 2:
      itemTypeText="2 (Contemporary)";
      break;
    case 3:
      itemTypeText="3 (Futuristic)";
      break;
    case 4:
      itemTypeText="4 (Post-apocalyptic)";
      break;
    default:
      itemTypeText="ERROR";
      break;
    }
    serverList->setItem(new CEGUI::ListboxTextItem(itemTypeText), 1, newRow);

    // Occupation
    const char* actC=StringConv::getSingleton().itoc((*iter)->actClients);
    const char* maxC=StringConv::getSingleton().itoc((*iter)->maxClients);

    CEGUI::String occ;
    occ+=actC;
    occ+="/";
    occ+=maxC;
    serverList->setItem(new CEGUI::ListboxTextItem(occ), 2, newRow);

  }
 
}

/** The Back button callback
  *
  * Exit from this menu to the connection menu (gsConnection).
  *
  * \param evt The CEGUI event 
  *
  */
bool RainbruRPG::Core::gsServerList::
onBackClicked(const CEGUI::EventArgs& evt){
  LOGI("onBackClicked");

  GuiManager::getSingleton().beginGuiFadeOut();

  // We must wait for the CEGUI fade end to prevent
  // SEGFAULT in access to CEGUI windows (getAlpha())
  while (GuiManager::getSingleton().isInGuiFadeOut()){
    Ogre::Root::getSingleton().renderOneFrame();
  }

  GuiManager::getSingleton().removeCurrentCEGUILayout();

  GameEngine::getSingleton().changeState(ST_MENU_CONNECT);
  GuiManager::getSingleton().beginGuiFadeIn();

  return true;
}

/** The Refresh button callback
  *
  * Refresh the server list by reloading it.
  *
  * \param evt The CEGUI event 
  *
  */
bool RainbruRPG::Core::gsServerList::
onRefreshClicked(const CEGUI::EventArgs& evt){
  LOGI("onRefreshClicked");

  xml->refresh();
  btnConnect->setVisible(false);
  serverList->resetList();
  feedList();

  return true;
}

/** The Connect button callback
  *
  * Connect the client to the currently selected server
  *
  * \param evt The CEGUI event 
  *
  */
bool RainbruRPG::Core::gsServerList::
onConnectClicked(const CEGUI::EventArgs& evt){
  LOGI("onConnectClicked");
  return true;
}

/** The ServerList selection button callback
  *
  * This function is called when the selection has changed.
  *
  * \param evt The CEGUI event 
  *
  */
bool RainbruRPG::Core::gsServerList::
onListSelectionChange(const CEGUI::EventArgs& evt){
  LOGI("onListSelectionChange");
  CEGUI::ListboxItem * it=serverList->getFirstSelectedItem();

  if (it){
    btnConnect->setVisible(true);
  }
  else{
    btnConnect->setVisible(false);
  }

  // Visually mark as selected all selected item (ie. the whole row)
  while (it){
    it->setSelected(true);
    it->setSelectionBrushImage( "TaharezLook", "MultiListSelectionBrush");
    it=serverList->getNextSelected(it);
  }

  return true;
}

/** The ServerList was double-clicked
  *
  * This function is called when the list was double-clicked.
  *
  * \param evt The CEGUI event 
  *
  */
bool RainbruRPG::Core::gsServerList::
onListDoubleClick(const CEGUI::EventArgs& evt){
  LOGI("onListDoubleClick");

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
  tabNav.clear();
  tabNav.setParent("RainbruRPG/ServerList/");
  tabNav.addWidget("RainbruRPG/ServerList/List");
  tabNav.addWidget("RainbruRPG/ServerList/Refresh");
  tabNav.addWidget("RainbruRPG/ServerList/Connect");
  tabNav.addWidget("RainbruRPG/ServerList/Back");
}

/** The ServerList key listener
  *
  * This function is called when a key is pressed in the 
  * serverlist. It provide the keyboard-based selection of a server.
  *
  * The down and up key moves the selection by one item. The Return or 
  * Enter key will call onConnectClicked().
  *
  * This function is possible cause of gsMenuBase::keyPressed() which is
  * the keyboard mapping beetwen OIS and CEGUI for all gsMenuBase based
  * subclasses.
  *
  * \param evt The CEGUI event 
  *
  */
bool RainbruRPG::Core::gsServerList::
onListKeyDown(const CEGUI::EventArgs& e){
  CEGUI::KeyEventArgs evt=static_cast<const CEGUI::KeyEventArgs&>(e);
  CEGUI::Key::Scan sc=evt.scancode;
  
  if (sc==CEGUI::Key::ArrowDown){
    LOGI("ArrowDown pressed in serverlist");
    selectNext();

  }
  else if(sc==CEGUI::Key::ArrowUp){
    LOGI("ArrowDown pressed in serverlist");
    selectPrevious();
  }
  else if (sc==CEGUI::Key::Return){
    // If a row is selected
    if (getSelectedRow()!=-1){
      CEGUI::EventArgs ea;
      onConnectClicked(ea);
    }
  }
}

int RainbruRPG::Core::gsServerList::getSelectedRow(){
  CEGUI::ListboxItem * it=serverList->getFirstSelectedItem();
  if (it){
    // There is already a selected item
    for (int i=0; i<serverList->getRowCount(); i++){
      if (serverList->isItemSelected(CEGUI::MCLGridRef(i, 0))){
	return i;
      }
    }
  }
  else{
    // No item was selected
    return -1;
  }

}

void RainbruRPG::Core::gsServerList::
setRowSelectState(int row, bool state, tRowSelectionDirection dir){
  LOGCATS("ROW=");
  LOGCATI(row);
  LOGCATS(" getRowCount()=");
  LOGCATI(serverList->getRowCount());
  LOGCAT();
  if (row<serverList->getRowCount()){
    serverList->setItemSelectState(CEGUI::MCLGridRef(row, 0), state);
    serverList->setItemSelectState(CEGUI::MCLGridRef(row, 1), state);
    serverList->setItemSelectState(CEGUI::MCLGridRef(row, 2), state);

    // Set the vertial scrollbar scrolling
    CEGUI::ListboxItem * item=serverList->getFirstSelectedItem();
    // Get an item height
    float itemHeight=item->getPixelSize().d_height;
    // Get the list heiht
    float listHeight=serverList->getPixelSize().d_height;
    float listMiddle=(listHeight/2)-itemHeight;

    LOGCATS("itemHeight=");
    LOGCATF(itemHeight);
    LOGCATS(" listHeight=");
    LOGCATF(listHeight);
    LOGCATS(" row*itemHeith=");
    LOGCATF(row*itemHeight);
    LOGCATS(" listMiddle=");
    LOGCATF(listMiddle);
    LOGCAT();

    CEGUI::Scrollbar* vsb=serverList->getVertScrollbar();
    float sp=vsb->getScrollPosition();

    float relItemTop=(row*itemHeight)-sp;

    if (dir==RSD_UP){
      if (relItemTop<listMiddle-itemHeight){
	vsb->setScrollPosition(sp-itemHeight);
      }
    }
    else{
      if (relItemTop>listMiddle){
	vsb->setScrollPosition(sp+itemHeight);
      }
    }
  }
}

void RainbruRPG::Core::gsServerList::selectNext(){
  int row=getSelectedRow();
  LOGCATS("getSelectedRow()=");
  LOGCATI(row);
  LOGCAT();
  row+=1;
  setRowSelectState(row, true, RSD_DOWN);
}

void RainbruRPG::Core::gsServerList::selectPrevious(){
  int row=getSelectedRow();
  setRowSelectState(--row, true, RSD_UP);

}

