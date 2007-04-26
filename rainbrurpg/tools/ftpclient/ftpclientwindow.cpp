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


#include "ftpclientwindow.h"

#include <fox-1.6/FXMessageBox.h>

FXDEFMAP(RainbruRPG::Gui::FtpClientWindow) FtpClientWindowMap[]={
  //____Message_Type_____________ID_______________Message_Handler_______
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::FtpClientWindow::ID_NYI, RainbruRPG::Gui::FtpClientWindow::onNotYetImplemented),

  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::FtpClientWindow::ID_NEW_CMD, RainbruRPG::Gui::FtpClientWindow::treatNewCommand),

  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::FtpClientWindow::ID_CONN, RainbruRPG::Gui::FtpClientWindow::onConnect),

};

FXIMPLEMENT(RainbruRPG::Gui::FtpClientWindow,FXMainWindow,FtpClientWindowMap,ARRAYNUMBER(FtpClientWindowMap));


/** The constructor
  *
  * \param a The fox application instance the launcher will be used with
  *
  */
RainbruRPG::Gui::FtpClientWindow::FtpClientWindow(FXApp * a)
   :FXMainWindow(a,"RainbruRPG FTP client",NULL,NULL,DECOR_ALL,0,0,800,600){

  FXint opt= BUTTON_NORMAL|LAYOUT_FIX_WIDTH;

  // frame containing admin info and button
  FXVerticalFrame *frame = new FXVerticalFrame(this, LAYOUT_FILL_X|LAYOUT_FILL_Y);


  // Menubar
  FXMenuBar * menubar = new FXMenuBar(frame,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|FRAME_RAISED);

  filemenu = new FXMenuPane(this);
  new FXMenuTitle(menubar,"&File",NULL,filemenu);


  new FXMenuCommand(filemenu,"&Quit\tCtl-Q\tQuit the application.",
		    NULL,getApp(),FXApp::ID_QUIT);

  // Matrix containing Admin info
  FXHorizontalFrame* frMatrix=new FXHorizontalFrame(frame, LAYOUT_FILL_X);

  // Admin info
  FXLabel* labIp=new FXLabel(frMatrix, "Server IP :");
  tfHostIp=new FXTextField (frMatrix, 20 );
  tfHostIp->setText("82.232.174.195");
  FXLabel* labHostPort=new FXLabel(frMatrix, "port :");
  tfHostPort=new FXTextField (frMatrix, 20 );
  tfHostPort->setText("50002");

  FXButton* btnConnect=new FXButton(frMatrix, "Connect" , NULL, this, ID_CONN);

  // Command lines remenber
  fxText=new FXText(frame, this, ID_NYI, LAYOUT_FILL_X|LAYOUT_FILL_Y|FX::TEXT_READONLY);
  fxText->disable();
  fxTextField=new FXTextField(frame, 20, this, ID_NEW_CMD, LAYOUT_FILL_X);
  fxTextField->disable();

}

/** The default destructor
  *
  *
  */
RainbruRPG::Gui::FtpClientWindow::~FtpClientWindow(){
  delete filemenu;
  delete fxText;
  delete fxTextField;

  delete tfHostIp;
  delete tfHostPort;

}


/** The FOX-Toolkit create method
  *
  * It creates and execute a LanguageSelector instance.
  *
  */
void RainbruRPG::Gui::FtpClientWindow::create(){
   FXMainWindow::create();
   show(PLACEMENT_SCREEN);

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
long RainbruRPG::Gui::FtpClientWindow::
onNotYetImplemented(FXObject * o,FXSelector s,void* v){
  LOGW("Not yet implemented");
  return 1;
}

/** The text entered in the command textfield is sent (enter key pressed)
  *
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v The text comming from the command textfield
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::FtpClientWindow::
treatNewCommand(FXObject* o,FXSelector s,void* v){
  FXString str;
  str=(FX::FXchar*)v;

  // If the entered text is not empty
  if (!str.empty()){

    fxText->appendText( "> " );
    fxText->appendText( str );
    fxText->appendText( "\n" );
    
    FXTextField* a=(FXTextField*)o;
    a->setText("");

  }

  return 1;
}

/** The connect button callback
  *
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::FtpClientWindow::
onConnect(FXObject* o,FXSelector s,void* v){
  FXString sIp=tfHostIp->getText();
  FXString sPort=tfHostPort->getText();

  GTcpSocket* socket=gnet_tcp_socket_connect(sIp.text(),
                                             FXIntVal(sPort));

  if (socket==NULL){
    LOGE("Connection to FTP Host failed");
    logMessage("Connection to FTP Host failed");
  }
  else{
    LOGI("Connection to FTP host successfull");
    logMessage("Connection to FTP host successfull");
  }

  fxText->enable();
  fxTextField->enable();

}

void RainbruRPG::Gui::FtpClientWindow::logMessage(FXString s){
  fxText->appendText( s );
  fxText->appendText( "\n" );
  fxTextField->setFocus();
}
