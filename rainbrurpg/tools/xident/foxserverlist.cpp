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

#include "foxserverlist.h"
#include "addserver.h"
#include "deleteserver.h"
#include "modifyserver.h"
#include "serverdesc.h"
#include "servertechnote.h"
#include <logger.h>

FXDEFMAP(RainbruRPG::Gui::FoxServerList) FoxServerListMap[]={
  //____Message_Type_____________ID_______________Message_Handler_______
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::FoxServerList::ID_NYI, RainbruRPG::Gui::FoxServerList::onNotYetImplemented),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::FoxServerList::ID_ADD, RainbruRPG::Gui::FoxServerList::onShowAddServerDialog),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::FoxServerList::ID_TABLE, RainbruRPG::Gui::FoxServerList::onTableSelectionChange),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::FoxServerList::ID_DEL, RainbruRPG::Gui::FoxServerList::onShowDeleteServerDialog),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::FoxServerList::ID_EDIT, RainbruRPG::Gui::FoxServerList::onShowEditServerDialog),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::FoxServerList::ID_DESC, RainbruRPG::Gui::FoxServerList::onShowDescriptionDialog),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::FoxServerList::ID_TECH, RainbruRPG::Gui::FoxServerList::onShowTechNoteDialog),

};

FXIMPLEMENT(RainbruRPG::Gui::FoxServerList,FXPacker,FoxServerListMap,ARRAYNUMBER(FoxServerListMap));

/** The constructor
  *
  * The parent must not be NULL
  *
  * \param parent The parent composite
  * \param opts The FOX construction parameter
  *
  */
RainbruRPG::Gui::FoxServerList::
FoxServerList(FXComposite *parent,FXuint opts)
  :FXPacker(parent, opts)
{
  selServer="";

  FXVerticalFrame *root = new FXVerticalFrame(this,
             LAYOUT_FILL_X|LAYOUT_FILL_Y);

  FXString lab="This screen provides the server management. From the list "
    "of servers below, you can chose one and edit it.";
  FXLabel* labAdminName=new FXLabel(root, lab);

 // frame containing admin info and button
  FXHorizontalFrame *hframe = new FXHorizontalFrame(root,
             LAYOUT_FILL_X|LAYOUT_FILL_Y);


  FXVerticalFrame *frame = new FXVerticalFrame(hframe,
             LAYOUT_FILL_X|LAYOUT_FILL_Y);

  FXint tableOpt=LAYOUT_FILL_X|LAYOUT_FILL_Y|TABLE_COL_SIZABLE;
  tableOpt+=TABLE_NO_COLSELECT|TABLE_ROW_RENUMBER|TABLE_READONLY;

  table=new FXTable(frame, this, ID_TABLE, tableOpt);

  // Serverlist count label
  labPlCount=new FXLabel(frame, "Total servers : <not set>");

  // Buttons in the right
  FXVerticalFrame *btnFrame = new FXVerticalFrame(hframe);
  FXuint btnOpts= LAYOUT_FILL_X|BUTTON_NORMAL;
  FXButton* btn1=new FXButton( btnFrame, "Add", NULL, this, ID_ADD, btnOpts);
  btnDelete=new FXButton( btnFrame, "Delete", NULL, this, ID_DEL, btnOpts);
  btnDesc=new FXButton( btnFrame, "Description", NULL, this, ID_DESC, btnOpts);
  btnTech=new FXButton( btnFrame, "TechNote", NULL, this, ID_TECH, btnOpts);
  btnEdit=new FXButton( btnFrame, "Edit", NULL, this, ID_EDIT, btnOpts);
  btnDelete->disable();
  btnDesc->disable();
  btnTech->disable();
  btnEdit->disable();

  // Initialize the panel
  refresh();
}

/** The destructor
 *
 */
RainbruRPG::Gui::FoxServerList::~FoxServerList(){
  delete serverList;
  delete btnDelete;
  delete btnEdit;

}

/** The FOX-Toolkit create method
  *
  * It creates and execute a FoxServerList instance.
  *
  */
void RainbruRPG::Gui::FoxServerList::create(){
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
long RainbruRPG::Gui::FoxServerList::
onNotYetImplemented(FXObject * o,FXSelector s,void* v){
  LOGW("Not yet implemented");
}

/** The method feeding the account table
  *
  * It uses the tServerList retrived from xmlServerList serverList. It
  * also calls setServerNumber(unsigned int) to change the total server
  * number label.
  *
  */
void RainbruRPG::Gui::FoxServerList::feedTable(){
  LOGI("Starting feedTable");
  tServerList* pl=serverList->getServerList();
  if (pl){
    setServerNumber(pl->size());

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

/** Change the number of account printed
  *
  * i.e. change the labPlCount content. It is called by the feedTable()
  * method.
  *
  * \param i The new value
  *
  */
void RainbruRPG::Gui::FoxServerList::setServerNumber(unsigned int i){
  std::ostringstream temp ;
  temp << "Total servers : ";
  temp << i;

  labPlCount->setText(temp.str().c_str());
}

/** Adds the informations of the given server into the table
  *
  * \param p The player to add
  *
  */
void RainbruRPG::Gui::FoxServerList::
addServer(RainbruRPG::Network::Ident::tServerListItem* p){
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
  FXTableItem* item=new FXTableItem(p->name);
  table->setItem(num, 0, item);

  // Sets the mail
  FXTableItem* item2=new FXTableItem(p->ipAdress);
  table->setItem(num, 1, item2);

  // Sets the UDP port
  FXTableItem* item3=new FXTableItem(p->port);
  table->setItem(num, 2, item3);

  // Sets the FTP port
  FXTableItem* item4=new FXTableItem(p->ftp);
  table->setItem(num, 3, item4);

  // Sets the creation date
  FXTableItem* item5=new FXTableItem(p->creation.c_str());
  table->setItem(num, 4, item5);

  // Sets the clients informations
  std::string cli="";
  cli= StringConv::getSingleton().itos(p->actClients);
  cli+="/" ;
  cli+= StringConv::getSingleton().itos(p->maxClients);

  FXTableItem* item6=new FXTableItem(cli.c_str());
  table->setItem(num, 5, item6);
}

/** The add server callback
  *
  * This functions shows the AddServer dialog. It is linked with the
  * 'Add' button.
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::FoxServerList::
onShowAddServerDialog(FXObject * o,FXSelector s,void* v){
  LOGI("Add server button clicked");

  AddServer as(getApp());
  // Setting PLACEMENT_SCREEN as placement behavior in the next call
  // seems to get the dialog unreachable with the mouse (the prg freezes)
  FXuint res=as.execute();

  if (res==TRUE){
    refresh();
  }

  return 1;
}

/** Refresh the list of server
  *
  * It delete the actual serverList, re-creates it and reload the 
  * server information by a call to feedTable(). We must call 
  * createTableHeader() each time we call table->clearItems() because
  * it removes the columns headers.
  *
  */
void RainbruRPG::Gui::FoxServerList::refresh(){
  // Destructs the current serverList
  if (serverList)
    delete serverList;

  serverList=new xmlServerList();

  table->clearItems();
  createTableHeader();
  feedTable();
}

/** Creates the table's column headers
  *
  * This method must be called in refresh() because the table->clearItems()
  * call also delete column headers.
  *
  */
void RainbruRPG::Gui::FoxServerList::createTableHeader(){
  table->insertColumns(0, 6);
  table->getColumnHeader()->setItemText(0, "Name");
  table->getColumnHeader()->setItemText(1, "Ip");
  table->getColumnHeader()->setItemText(2, "Port");
  table->getColumnHeader()->setItemText(3, "Ftp");
  table->getColumnHeader()->setItemText(4, "Creation");
  table->getColumnHeader()->setItemText(5, "Clients");
  table->getRowHeader()->setWidth(40);
}

/** Returns the name of the currently selected server
  *
  * It takes from the FXTable of server the selected row, and
  * from this row number get the server's name.
  *
  * \sa selServer, onTableSelectionChange
  *
  * \return The selected server's name
  *
  */
FXString RainbruRPG::Gui::FoxServerList::getSelectedServerName(){
  FXint selRow=table->getSelStartRow();

  FXString s=table->getItem(selRow, 0)->getText();
  return s;
}

/** The table selection callback
  *
  * It is called each time the table selection changed. It change the
  * selection behavior by selectionning the whole row and set selServer
  * to the current name with the getSelectedServerName() function.
  *
  * \sa selServer, getSelectedServerName
  *
  * \param o A parameter used for FOX callbacks
  * \param sel A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::FoxServerList::
onTableSelectionChange(FXObject *o,FXSelector sel,void* v){
  FXint selRow=table->getSelStartRow();
  table->selectRow(selRow);

  selServer=getSelectedServerName();
  std::string name(selServer.text());
  LOGCATS("Selected server name : '");
  LOGCATS(name.c_str());
  LOGCATS("'");
  LOGCAT();

  if (selServer.empty()){
    btnDelete->disable();
    btnEdit->disable();
  }
  else{
    btnDelete->enable();
    btnEdit->enable();
    btnDesc->enable();
    btnTech->enable();
  }
}
								 
/** The delete button callback
  *
  * It opens the DeleteServer dialog with the current selected server name.
  *
  * \sa selServer
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::FoxServerList::
onShowDeleteServerDialog(FXObject * o,FXSelector s,void* v){
  DeleteServer ds(getApp(), selServer);
  FXuint res=ds.execute();

  if (res==TRUE){
    refresh();
  }
}

/** The delete button callback
  *
  * It opens the EditServer dialog with the current selected server name.
  *
  * \sa selServer
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::FoxServerList::
onShowEditServerDialog(FXObject *o,FXSelector s,void* v){
  LOGI("Edit server called");

  ModifyServer ms(getApp(), selServer);
  FXuint res=ms.execute();

  if (res==TRUE){
    refresh();
  }
}

/** The description button callback
  *
  * It opens the ServerDesc dialog with the current selected server name.
  *
  * \sa selServer
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::FoxServerList::
onShowDescriptionDialog(FXObject * o,FXSelector s,void* v){
  LOGI("Openening Description dialog");
  ServerDesc sd(getApp(), selServer);
  sd.execute();
  return 1;
}

/** The technical note's button callback
  *
  * It opens the ServerDesc dialog with the current selected server name.
  *
  * \sa selServer
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::FoxServerList::
onShowTechNoteDialog(FXObject * o,FXSelector s,void* v){
  LOGI("Openening tech note dialog");

  ServerTechNote stn(getApp(), selServer);
  stn.execute();

  return 1;
}
