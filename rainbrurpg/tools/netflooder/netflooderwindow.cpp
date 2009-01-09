/*
 *  Copyright 2006-2009 Jerome PASQUIER
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

/** \file tools/netflooder/netflooderwindow.cpp
  * Implements the NetFlooder's main window
  *
  */

#include "netflooderwindow.h"

#include "config.h"
#include "connectionpanel.h"

#include <logger.h>
#include <fox-1.6/FXMessageBox.h>

/** The Fox-toolkit event mapping 
  *
  * This map is needed by the Fox-Toolkit event model. It defines
  * the event used by the 
  * \ref RainbruRPG::Gui::NetFlooderWindow "NetFlooderWindow" class.
  *
  */
FXDEFMAP(RainbruRPG::Gui::NetFlooderWindow) NetFlooderWindowMap[]={
  //____Message_Type_____________ID_______________Message_Handler_______
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::NetFlooderWindow::ID_NYI, RainbruRPG::Gui::NetFlooderWindow::onNotYetImplemented),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::NetFlooderWindow::ID_HELP_ABOUT, RainbruRPG::Gui::NetFlooderWindow::onHelpAbout),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::NetFlooderWindow::ID_TOOL_SERVER, RainbruRPG::Gui::NetFlooderWindow::onManageServer),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::NetFlooderWindow::ID_TOOL_WAITING, RainbruRPG::Gui::NetFlooderWindow::onManageWaiting),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::NetFlooderWindow::ID_SHOW_WAITING_PANEL, RainbruRPG::Gui::NetFlooderWindow::onShowWaitingPanel),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::NetFlooderWindow::ID_TOOL_FLOOD, RainbruRPG::Gui::NetFlooderWindow::onManageFlood),


};

/** Declares the implementation of the class 
  *
  * This statement tells to Fox-Toolkit that the 
  * \ref RainbruRPG::Gui::NetFlooderWindow "NetFlooderWindow" class
  * uses the NetFlooderWindowMap event map.
  *
  */
FXIMPLEMENT(RainbruRPG::Gui::NetFlooderWindow,FXMainWindow,NetFlooderWindowMap,ARRAYNUMBER(NetFlooderWindowMap));


/** The constructor
  *
  * \param a The fox application instance the launcher will be used with
  *
  */
RainbruRPG::Gui::NetFlooderWindow::NetFlooderWindow(FXApp * a)
   :FXMainWindow(a,"RainbruRPG netflooder",NULL,NULL,DECOR_ALL,0,0,800,600){

  // We start with an incremental panel identifier at 0
  switcherChildId=0;

  FXint opt= BUTTON_NORMAL|LAYOUT_FIX_WIDTH;

  // frame containing admin info and button
  FXVerticalFrame *frame = new FXVerticalFrame(this, LAYOUT_FILL_X|LAYOUT_FILL_Y);


  // Menubar
  FXMenuBar * menubar = new FXMenuBar(frame,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|FRAME_RAISED);

  filemenu = new FXMenuPane(this);
  new FXMenuCommand(filemenu,"&Quit\tCtl-Q\tQuit the application.",
		    NULL,getApp(),FXApp::ID_QUIT);

  toolmenu = new FXMenuPane(this);
  new FXMenuCommand(toolmenu,"&Servers\tCtl-S\t"
		    "Choose a server to be flooded.",
		    NULL,this,ID_TOOL_SERVER);
  new FXMenuCommand(toolmenu,"&Waiting\tCtl-A\t"
		    "Waiting connection to a server.",
		    NULL,this,ID_TOOL_WAITING);

  new FXMenuCommand(toolmenu,"&Flooding\tCtl-F\t"
		    "Flooding a selected server.",
		    NULL,this,ID_TOOL_FLOOD);

  helpmenu = new FXMenuPane(this);
  new FXMenuCommand(helpmenu,"About x&Ident\tCtl-I\t"
		    "Primary informations about xident.",NULL,this,
		    ID_HELP_ABOUT);

  new FXMenuTitle(menubar,"&File",NULL,filemenu);
  new FXMenuTitle(menubar,"&Manage",NULL,toolmenu);
  new FXMenuTitle(menubar,"&Help",NULL,helpmenu,  
		  FX::LAYOUT_RIGHT| FX::LAYOUT_TOP);


  // Matrix containing Admin info
  FXHorizontalFrame* frMatrix=new FXHorizontalFrame(frame, LAYOUT_FILL_X);

  // Admin info
  FXLabel* labAdminName=new FXLabel(frMatrix, "Admin :");
  FXTextField* tfAdminName=new FXTextField (frMatrix, 20 );
  FXLabel* labAdminPwd=new FXLabel(frMatrix, "Password :");
  FXTextField* tfAdminPwd=new FXTextField (frMatrix, 20 );

  // The FXSwitcher
  FXuint fillAll=LAYOUT_FILL_X|LAYOUT_FILL_Y;

  switcher=new FXSwitcher(frame,fillAll);

  ConnectionPanel* cp=new ConnectionPanel(switcher,fillAll, this, 
					  ID_SHOW_WAITING_PANEL);

  panelConnectionId=switcherChildId++;

  wp=new WaitingPanel(switcher,fillAll, this->client);
  panelWaitingId=switcherChildId++;

  fp=new FloodPanel(switcher,fillAll, this->client);
  panelFloodId=switcherChildId++;

  // The status bar
  FXStatusBar* sb=new FXStatusBar (frame, LAYOUT_FILL_X|
				   STATUSBAR_WITH_DRAGCORNER);


  wp->sigConnectionRefused.connect(sigc::mem_fun(this, 
     &RainbruRPG::Gui::NetFlooderWindow::slotConnectionRefused));
  wp->sigConnectionAccepted.connect(sigc::mem_fun(this, 
     &RainbruRPG::Gui::NetFlooderWindow::slotConnectionAccepted));


}

/** The default destructor
  *
  *
  */
RainbruRPG::Gui::NetFlooderWindow::~NetFlooderWindow(){
  delete filemenu;
  delete helpmenu;
  delete toolmenu;

  delete wp;
  delete fp;

  delete switcher;
}


/** The FOX-Toolkit create method
  *
  * It creates and execute a LanguageSelector instance.
  *
  */
void RainbruRPG::Gui::NetFlooderWindow::create(){
   FXMainWindow::create();
   show(PLACEMENT_SCREEN);

 }

/** The callback of the help/about menu item
  *
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::NetFlooderWindow::
onHelpAbout(FXObject * o,FXSelector s,void* v){
  LOGI("Help::About called");

  FXMessageBox::information(this, FX::MBOX_OK, "About xIdent", 
	    "A tools used to managed the RainbruRPG administration website"
			    "files");

  return 1;
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
long RainbruRPG::Gui::NetFlooderWindow::
onNotYetImplemented(FXObject * o,FXSelector s,void* v){
  LOGW("Not yet implemented");
  return 1;
}

/** The Manage/Server menu callback
  *
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::NetFlooderWindow::
onManageServer(FXObject * o,FXSelector s,void* v){
  LOGI("onManageServer called");
  switcher->setCurrent(panelConnectionId, true);
  return 1;

}

/** The Manage/Waiting menu callback
  *
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::NetFlooderWindow::
onManageWaiting(FXObject *o,FXSelector s,void* v){
  LOGI("onManageWaiting called");
  switcher->setCurrent(panelWaitingId, true);
  return 1;
}

/** The Manage/Waiting menu callback
  *
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v The tServerListItem* received from the message
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::NetFlooderWindow::
onShowWaitingPanel(FXObject *o,FXSelector s,void* v){
  LOGI("onShowWaitingPanel called");
  switcher->setCurrent(panelWaitingId, false);
  wp->setServer((ServerListItem*)v);
  return 1;
}

/** A slot called when the connection is refused by the selected server
  *
  */
void RainbruRPG::Gui::NetFlooderWindow::slotConnectionRefused(){
  LOGI("NetFlooderWindow::slotConnectionRefused");
  switcher->setCurrent(panelConnectionId, false);
  wp->reset();
}

/** The Manage/Waiting menu callback
  *
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v The tServerListItem* received from the message
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::NetFlooderWindow::
onManageFlood(FXObject* o,FXSelector s,void* v){
  LOGI("onManageFlood called");
  switcher->setCurrent(panelFloodId, false);

}

/** A slot called when the connection is accepted by the selected server
  *
  */
void RainbruRPG::Gui::NetFlooderWindow::slotConnectionAccepted(){
  LOGI("NetFlooderWindow::slotConnectionAccepted");
  switcher->setCurrent(panelFloodId, false);
  fp->setClient(wp->getClient());
  wp->reset();
}
