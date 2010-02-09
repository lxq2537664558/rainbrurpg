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

/** \file tools/netflooder/connectionpanel.cpp
  * Declares the netFlooder connection panel
  *
  */

#include "connectionpanel.h"

#include <logger.h>
#include <fox-1.6/FXMessageBox.h>

/** The Fox-toolkit event mapping 
  *
  * This map is needed by the Fox-Toolkit event model. It defines
  * the event used by the 
  * \ref RainbruRPG::Gui::ConnectionPanel "ConnectionPanel" class.
  *
  */
FXDEFMAP(RainbruRPG::Gui::ConnectionPanel) ConnectionPanelMap[]={
  //____Message_Type_____________ID_______________Message_Handler_______
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::ConnectionPanel::ID_NYI, RainbruRPG::Gui::ConnectionPanel::onNotYetImplemented),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::ConnectionPanel::ID_BTN_REFRESH, RainbruRPG::Gui::ConnectionPanel::onRefreshClicked),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::ConnectionPanel::ID_BTN_CONNECT, RainbruRPG::Gui::ConnectionPanel::onConnectClicked),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::ConnectionPanel::ID_TABLE, RainbruRPG::Gui::ConnectionPanel::onTableSelectionChange),

};

/** Declares the implementation of the class 
  *
  * This statement tells to Fox-Toolkit that the 
  * \ref RainbruRPG::Gui::ConnectionPanel "ConnectionPanel" class
  * uses the ConnectionPanelMap event map.
  *
  */
FXIMPLEMENT(RainbruRPG::Gui::ConnectionPanel,FXPacker,ConnectionPanelMap,ARRAYNUMBER(ConnectionPanelMap));

/** The constructor
  *
  * The parent must not be NULL. The sender and id are used to send
  * FOX signals.
  *
  * \param parent The parent composite
  * \param opts The FOX construction parameter
  * \param sender The FOX object receiving events
  * \param id The ID used for send events
  *
  */
RainbruRPG::Gui::ConnectionPanel::
ConnectionPanel(FXComposite *parent,FXuint opts, FXObject* sender, FXuint id)
  :FXPacker(parent, opts)
{
  this->sender=sender;
  this->messageId=id;

  selServer="";
  serverList=new xmlServerList();

  FXVerticalFrame *root = new FXVerticalFrame(this,
             LAYOUT_FILL_X|LAYOUT_FILL_Y);

  // The help label
  FXString lab="Select and flood a registered server. "
    "For security reason, the selected server must accept "
    "flooder connections.";
  FXLabel* labAdminName=new FXLabel(root, lab);

  // The buttons frame
  FXHorizontalFrame *frButtons = new FXHorizontalFrame(root,
             LAYOUT_FILL_X|PACK_UNIFORM_WIDTH);
  FXButton* btnRefresh=new FXButton(frButtons, "Refresh", NULL, this, 
				    ID_BTN_REFRESH);

  btnConnect=new FXButton(frButtons, "Connect", NULL, this, 
				    ID_BTN_CONNECT);
  btnConnect->disable();

  // frame containing the servers' table
  FXHorizontalFrame *hframe = new FXHorizontalFrame(root,
             LAYOUT_FILL_X|LAYOUT_FILL_Y);

  FXVerticalFrame *frame = new FXVerticalFrame(hframe,
             LAYOUT_FILL_X|LAYOUT_FILL_Y);

  FXint tableOpt=LAYOUT_FILL_X|LAYOUT_FILL_Y|TABLE_COL_SIZABLE;
  tableOpt+=TABLE_NO_COLSELECT|TABLE_ROW_RENUMBER|TABLE_READONLY;

  table=new FXTable(frame, this, ID_TABLE, tableOpt);

  // Initialize the panel
  createTableHeader();
  feedTable();
}

/** The destructor
 *
 */
RainbruRPG::Gui::ConnectionPanel::~ConnectionPanel(){
  delete btnConnect;
}

/** The FOX-Toolkit create method
  *
  * It creates and execute a ConnectionPanel instance.
  *
  */
void RainbruRPG::Gui::ConnectionPanel::create(){
  FXPacker::create();
  this->show();
}


/** The NotYetImplemented callback
  *
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::ConnectionPanel::
onNotYetImplemented(FXObject * o,FXSelector s,void* v){
  LOGW("Not yet implemented");
  return 1;
}

/** The method feeding the account table
  *
  * It uses the tServerList retrived from xmlServerList serverList. It
  * also calls setServerNumber(unsigned int) to change the total server
  * number label.
  *
  */
void RainbruRPG::Gui::ConnectionPanel::feedTable(){
  LOGI("Starting feedTable");
  tServerList* pl=serverList->getServerList();
  if (pl){
    // Feeding ^^
    tServerList::const_iterator iter;
    for (iter=pl->begin(); iter != pl->end(); iter++){
      this->addServer((*iter));
    }

    pl=NULL;
    LOGI("feedTable complete");
  }
  else{
    LOGE("Cannot get a valid account list");
  }
}

/** Adds the informations of the given server into the table
  *
  * \param p The player to add
  *
  */
void RainbruRPG::Gui::ConnectionPanel::
addServer(RainbruRPG::Network::Ident::ServerListItem* p){
  FXString s;

  FXint num=table->getNumRows();

  // Adds a new row at the end of the table
  table->insertRows(num, 1);

  std::ostringstream temp ;
  temp << num+1;

  // Set the row header
  table->getRowHeader()->setItemText(num, temp.str().c_str());
  table->getRowHeader()->setItemJustify(num, FXHeaderItem::RIGHT);

  // Sets the name
  FXTableItem* item=new FXTableItem(p->getName().c_str());
  table->setItem(num, 0, item);
  item->setJustify(FXTableItem::LEFT);

  // Sets the derscription
  std::string d=StringConv::getSingleton()
    .xmlStripNewLine(p->getDescription());

  FXTableItem* item2=new FXTableItem(d.c_str());
  table->setItem(num, 1, item2);
  item2->setJustify(FXTableItem::LEFT);
}

/** Creates the table's column headers
  *
  * This method must be called in refresh() because the table->clearItems()
  * call also delete column headers.
  *
  */
void RainbruRPG::Gui::ConnectionPanel::createTableHeader(){
  table->insertColumns(0, 2);
  table->getColumnHeader()->setItemText(0, "Name");
  table->getColumnHeader()->setItemText(1, "Description");
  table->getRowHeader()->setWidth(40);
  table->setColumnWidth(1, 500);
  table->setColumnJustify(0, FXHeaderItem::LEFT);
  table->setColumnJustify(1, FXHeaderItem::LEFT);
}

/** The Refresh button callback
  *
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::ConnectionPanel::
onRefreshClicked(FXObject *o,FXSelector s,void* v){
  LOGI("Refresh button clicked");
  serverList->refresh();
  table->clearItems();
  btnConnect->disable();
  createTableHeader();
  feedTable();
  return 1;
}

/** Returns the name of the currently selected server
  *
  * It takes from the FXTable of server the selected row, and
  * from this row number get the server's name.
  *
  * \sa selServer, onTableSelectionChange
  *
  * \return The selected server's name or "" if none selected
  *
  */
FXString RainbruRPG::Gui::ConnectionPanel::getSelectedServerName(){
  FXint selRow=table->getSelStartRow();

  // selRow is -1 if no row selected
  if (selRow==-1){
    return "";
  }
  else{
    FXString s=table->getItem(selRow, 0)->getText();
    return s;
  }
}

/** The Table selection changed callback
  *
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::ConnectionPanel::
onTableSelectionChange(FXObject *o,FXSelector s,void* v){
  FXint selRow=table->getSelStartRow();
  table->selectRow(selRow);

  selServer=getSelectedServerName();
  std::string name(selServer.text());
  LOGCATS("Selected server name : '");
  LOGCATS(name.c_str());
  LOGCATS("'");
  LOGCAT();

  if (selServer.empty()){
    
    btnConnect->disable();
  }
  else{
    btnConnect->enable();
  }
  return 1;
}

/** The Connect button callback
  *
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::ConnectionPanel::
onConnectClicked(FXObject *o,FXSelector s,void* v){
  LOGI("Connect button clicked");
  std::string name(selServer.text());
  ServerListItem *server=serverList->getServerByName (name.c_str());

  if (!server){
    LOGW("Cannot get server informations");
  }
  else{

    std::string techNote(server->getTechNote());
    bool empty=(techNote.size()==0);
    if (empty){
      LOGI("Server technote is empty");
      changeToWaitingPanel(server);
    }
    else{

      std::string s=StringConv::getSingleton().xmlToNewLine(techNote);


      LOGI("Server technote is not empty");
      s+="\n\nContinue connection?";
      FXuint resp=FX::FXMessageBox::question(this, FX::MBOX_OK_CANCEL ,
		"Server's technical note", s.c_str());

      // Ok to change to WaitingPanel
      if (resp==FX::MBOX_CLICKED_OK){
	changeToWaitingPanel(server);
      }

    }

  }
  return 1;
}

/** Makes the netflooder show the waiting panel
  *
  * Send the ID_SHOW_WAITING_PANEL event
  *
  * \param s The tServerListItem that will be send with the FOX message.
  *
  */
void RainbruRPG::Gui::ConnectionPanel::
changeToWaitingPanel(ServerListItem* s){

  LOGI("Sending ID_SHOW_WAITING_PANEL signal");

  if (sender){
    sender->handle(this,FXSEL(SEL_COMMAND,messageId), s);
  }
  else{
    LOGW("Sender is NULL, cannot send messages");
  }
}
