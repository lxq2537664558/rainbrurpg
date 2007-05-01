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

  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::FtpClientWindow::ID_HELP, RainbruRPG::Gui::FtpClientWindow::onHelp),
};

FXIMPLEMENT(RainbruRPG::Gui::FtpClientWindow,FXMainWindow,FtpClientWindowMap,ARRAYNUMBER(FtpClientWindowMap));


/** The constructor
  *
  * \param a The fox application instance the launcher will be used with
  *
  */
RainbruRPG::Gui::FtpClientWindow::FtpClientWindow(FXApp * a)
   :FXMainWindow(a,"RainbruRPG FTP client",NULL,NULL,DECOR_ALL,0,0,550,600){

  ftpClient=new FtpClient();

  FXint opt= BUTTON_NORMAL|LAYOUT_FIX_WIDTH;

  // frame containing admin info and button
  FXVerticalFrame *frame = new FXVerticalFrame(this, LAYOUT_FILL_X|LAYOUT_FILL_Y);


  // Menubar
  FXMenuBar * menubar = new FXMenuBar(frame,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|FRAME_RAISED);

  filemenu = new FXMenuPane(this);
  new FXMenuTitle(menubar,"&File",NULL,filemenu);
  new FXMenuCommand(filemenu,"&Help\tCtl-H\tPrint a help text.",
		    NULL,this,ID_HELP);

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
  fxText->setStyled(true);

  fxTextField=new FXTextField(frame, 20, this, ID_NEW_CMD, LAYOUT_FILL_X);
  fxTextField->disable();

  // The status bar
  FXStatusBar* sb=new FXStatusBar (frame, LAYOUT_FILL_X|
				   STATUSBAR_WITH_DRAGCORNER);
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

  delete ftpClient;
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


    str=str.upper();
    if (str.contains("HELP")!=0){
      if (str.contains("USER")!=0){
	showHelpUser();
      }
      else if (str.contains("PORT")!=0){
	showHelpPort();
      }
      else if (str.contains("PASS")!=0){
	showHelpPass();
      }
      else if (str.contains("PASV")!=0){
	showHelpPasv();
      }
      else{
	onHelp(NULL,0,NULL);

      }
    }
    else if (str.contains("LIST")!=0){
      string s=ftpClient->commandLIST();
      logMessage(s.c_str());
    }
    else if (str.contains("PASV")!=0){
      ftpClient->toggleTransferMode();
      string s=ftpClient->waitControlResponse();
      logMessage(s.c_str());
    }
  }

  scrollDown();
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

  bool ret=ftpClient->connectToHost(sIp.text(), FXIntVal(sPort));

  if (ret){
    LOGI("Connection to FTP host successfull");
    logMessage("Connection to FTP host successfull");

  }
  else{
    LOGE("Connection to FTP Host failed");
    logMessage("Connection to FTP Host failed");
  }

  fxText->enable();
  fxTextField->enable();

}

/** Log a message in the history text view
  *
  * \param s The text to print
  *
  */
void RainbruRPG::Gui::FtpClientWindow::logMessage(FXString s){
  fxText->appendText( s );
  fxText->appendText( "\n" );
  fxTextField->setFocus();
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
onHelp(FXObject* o,FXSelector s,void* v){
  LOGI("Help text requested");

  fxText->appendText( "RainbruRPG FTPClient help :\n" );
  showHelpCommand("USER <username>", "Use username to log to the server");
  showHelpCommand("PASS <password>", "Enter user password");
  showHelpCommand("PORT <IP adress> <port>", 
		  "Change host and port used for data channel");
  showHelpCommand("HELP <command>", 
		  "A more detailled description of a command");
  showHelpCommand("PASV",
		  "Toggle the transfer mode (Active/Passive)");

  return 1;
}

/** Show the help text on the USER command
  *
  */
void RainbruRPG::Gui::FtpClientWindow::showHelpUser(){
  FXString help;
  help+= "Use username to log to the server. A password may be\n";
  help+= HELP_INDENT"prompted just after the host answer. The user and password\n";
  help+= HELP_INDENT"are taken from the administration website. It is the\n";
  help+= HELP_INDENT"account information you use to login to the game.\n";

  showHelpCommand("USER <username>", help);
}

/** Print a help text
  *
  * \param title The command name
  * \param text The command help text
  *
  */
void RainbruRPG::Gui::FtpClientWindow::
showHelpCommand(FXString title, FXString text){

  title+="\n";
  FXString text2=HELP_INDENT;
  text2+=text;
  text2+="\n";

  fxText->appendStyledText( title, FXText::STYLE_BOLD );
  fxText->appendText( text2 );

}

/** Show the help text on the PORT command
  *
  */
void RainbruRPG::Gui::FtpClientWindow::showHelpPort(){
  FXString help;
  help+=            "Change the port of the FTP data channel. This port will\n";
  help+= HELP_INDENT"be used by the server to connect the data channel to\n";
  help+= HELP_INDENT"when needed. This is a convenient command, not in native\n";
  help+= HELP_INDENT"FTP format.\n";

  help+= HELP_INDENT"The native format of the PORT command is: .\n";
  help+= HELP_INDENT"PORT h1,h2,h3,h4,p1,p2. See FTC 0959 for further .\n";
  help+= HELP_INDENT"informations.\n";

  showHelpCommand("PORT <IP adress> <port>", help);

}

/** Show the help text on the PASS command
  *
  */
void RainbruRPG::Gui::FtpClientWindow::showHelpPass(){

  FXString help;
  help+=            "This command is used to send the user password.\n";
  help+= HELP_INDENT"It is often used just after a USER command and should\n";
  help+= HELP_INDENT"not be used by the end-user. The password is not crypted.";

  showHelpCommand("PASS <password>", help);


}

/** Always scroll the text ecit down
  * 
  * Shows the last line of the text edit
  *
  */
void RainbruRPG::Gui::FtpClientWindow::scrollDown(){
  FXString t=fxText->getText();
  FXint i=t.length();
  fxText->makePositionVisible(i);
}

/** Show a help text on the PASV command
  *
  */
void RainbruRPG::Gui::FtpClientWindow::showHelpPasv(){
  FXString help;
  help+=            "Switch beetween active and passive transfer mode.\n";
  help+= HELP_INDENT"In active mode, the client will try to connect to the\n";
  help+= HELP_INDENT"server's data channel. It passive mode, The server\n";
  help+= HELP_INDENT"take the initiative of the connection.\n\n";
  help+= HELP_INDENT"The default client configuration is active. The\n";
  help+= HELP_INDENT"RainbruRPG FTP server is by default in passive mode.";

  showHelpCommand("PASV", help);

}

