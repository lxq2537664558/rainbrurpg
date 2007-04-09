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


#include "xidentwindow.h"
#include "config.h"
#include "logger.h"

#include <fox-1.6/FXMessageBox.h>

FXDEFMAP(RainbruRPG::Gui::XIdentWindow) XIdentWindowMap[]={
  //____Message_Type_____________ID_______________Message_Handler_______
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::XIdentWindow::ID_NYI, RainbruRPG::Gui::XIdentWindow::onNotYetImplemented),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::XIdentWindow::ID_HELP_ABOUT, RainbruRPG::Gui::XIdentWindow::onHelpAbout),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::XIdentWindow::ID_TOOL_ACCOUNT, RainbruRPG::Gui::XIdentWindow::onManageAccount),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::XIdentWindow::ID_TOOL_SERVER, RainbruRPG::Gui::XIdentWindow::onManageServer),


};

FXIMPLEMENT(RainbruRPG::Gui::XIdentWindow,FXMainWindow,XIdentWindowMap,ARRAYNUMBER(XIdentWindowMap));


/** The constructor
  *
  * \param a The fox application instance
  *
  */
RainbruRPG::Gui::XIdentWindow::XIdentWindow(FXApp * a)
   :FXMainWindow(a,"RainbruRPG Xident",NULL,NULL,DECOR_ALL,0,0,800,600){

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
  new FXMenuCommand(toolmenu,"&Accounts\tCtl-A\t"
		    "Creates, deletes and manages accounts.",
		    NULL,this,ID_TOOL_ACCOUNT);
  new FXMenuCommand(toolmenu,"&Servers\tCtl-A\t"
		    "Creates, deletes and manages servers.",
		    NULL,this,ID_TOOL_SERVER);

  helpmenu = new FXMenuPane(this);
  new FXMenuCommand(helpmenu,"About x&Ident\tCtl-I\t"
		    "Primary informations about xident.",NULL,this,
		    ID_HELP_ABOUT);

  new FXMenuTitle(menubar,"&File",NULL,filemenu);
  new FXMenuTitle(menubar,"&Manage",NULL,toolmenu);
  new FXMenuTitle(menubar,"&Help",NULL,helpmenu,  
		  FX::LAYOUT_RIGHT| FX::LAYOUT_TOP);


  // Matric containing Admin info
  FXHorizontalFrame* frMatrix=new FXHorizontalFrame(frame, LAYOUT_FILL_X);

  // Admin info
  FXLabel* labAdminName=new FXLabel(frMatrix, "Admin :");
  FXTextField* tfAdminName=new FXTextField (frMatrix, 20 );
  FXLabel* labAdminPwd=new FXLabel(frMatrix, "Password :");
  FXTextField* tfAdminPwd=new FXTextField (frMatrix, 20 );

  // The FXSwitcher
  switcher=new FXSwitcher(frame,LAYOUT_FILL_X|LAYOUT_FILL_Y);
  // The Label panel
  FXLabel* labHelp=new  FXLabel(switcher, 
    "Welcome to RainbruRPG xident tool.\n\n" 
    "It is used to manage admin-website datas of the game.\n"
    "You can start working with a menu bar option.");
  panelHelpId=switcherChildId++;

  // The panels
  FoxAccountList* fal=new FoxAccountList(switcher);
  panelAccountId=switcherChildId++;
  FoxServerList* fsl=new FoxServerList(switcher);
  panelServerId=switcherChildId++;

  // The status bar
  FXStatusBar* sb=new FXStatusBar (frame, LAYOUT_FILL_X|
				   STATUSBAR_WITH_DRAGCORNER);


}

/** The default destructor
  *
  *
  */
RainbruRPG::Gui::XIdentWindow::~XIdentWindow(){
  delete filemenu;
  delete helpmenu;
  delete toolmenu;
  delete switcher;
}


/** The FOX-Toolkit create method
  *
  * It creates and execute the XIdentWindow.
  *
  */
void RainbruRPG::Gui::XIdentWindow::create(){
   FXMainWindow::create();
   show();

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
long RainbruRPG::Gui::XIdentWindow::
onHelpAbout(FXObject * o,FXSelector s,void* v){
  LOGI("Help::About called");

  FXMessageBox::information(this, FX::MBOX_OK, "About xIdent", 
	    "A tools used to managed the RainbruRPG administration website "
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
long RainbruRPG::Gui::XIdentWindow::
onNotYetImplemented(FXObject * o,FXSelector s,void* v){
  LOGW("Not yet implemented");
  return 1;
}

/** The Manage/Accounts menu callback
  *
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::XIdentWindow::
onManageAccount(FXObject * o,FXSelector s,void* v){
  LOGI("onManageAccount called");
  switcher->setCurrent(panelAccountId, true);
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
long RainbruRPG::Gui::XIdentWindow::
onManageServer(FXObject * o,FXSelector s,void* v){
  LOGI("onManageServer called");
  switcher->setCurrent(panelServerId, true);
  return 1;

}
