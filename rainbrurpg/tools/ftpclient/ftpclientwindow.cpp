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

  FXMAPFUNC(SEL_TIMEOUT, RainbruRPG::Gui::FtpClientWindow::ID_UPDT, RainbruRPG::Gui::FtpClientWindow::onUpdateTransfer),


};

FXIMPLEMENT(RainbruRPG::Gui::FtpClientWindow,FXMainWindow,FtpClientWindowMap,ARRAYNUMBER(FtpClientWindowMap));


/** The constructor
  *
  * \param a The fox application instance the launcher will be used with
  *
  */
RainbruRPG::Gui::FtpClientWindow::FtpClientWindow(FXApp * a)
   :FXMainWindow(a,"RainbruRPG FTP client",NULL,NULL,DECOR_ALL,0,0,600,600){

  ftpClient=new FtpClient();

  ftpClient->sigBytesWritten.connect( sigc::mem_fun(this, 
	     &RainbruRPG::Gui::FtpClientWindow::slotBytesWritten));

  ftpClient->sigTransferTerminated.connect( sigc::mem_fun(this,
	     &RainbruRPG::Gui::FtpClientWindow::slotTransferTerminated));

  ftpClient->sigFileSizeReceived.connect( sigc::mem_fun(this,
	     &RainbruRPG::Gui::FtpClientWindow::slotFileSizeReceived));

  downloadedBytes=0;
  resetTransfer=false;

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

  // Command lines remember
  fxText=new FXText(frame, this, ID_NYI, LAYOUT_FILL_X|LAYOUT_FILL_Y|FX::TEXT_READONLY);
  fxText->disable();
  fxText->setStyled(true);

  fxTextField=new FXTextField(frame, 20, this, ID_NEW_CMD, LAYOUT_FILL_X);
  fxTextField->disable();

  // Showing transfer
  FXMatrix* transMatrix=new FXMatrix(frame,4, LAYOUT_FILL_X|MATRIX_BY_COLUMNS);
  FXLabel* labTrFn=new FXLabel(transMatrix, "Filename");
  FXLabel* labTrIo=new FXLabel(transMatrix, "In/Out");
  FXLabel* labTrFs=new FXLabel(transMatrix, "Filesize");
  FXLabel* labTrPr=new FXLabel(transMatrix, "Progression", 
			       NULL,LAYOUT_FILL_X );

  // Sample
  labTransName=new FXLabel(transMatrix, "none");
  labTransOrie=new FXLabel(transMatrix, "");
  labTransSize=new FXLabel(transMatrix, "");
  labTrPb=new FXProgressBar(transMatrix, NULL, 0, 
			    PROGRESSBAR_NORMAL|PROGRESSBAR_PERCENTAGE|
			    LAYOUT_FIX_WIDTH|LAYOUT_FILL_Y);
  labTrPb->setWidth(250);

  // The status bar
  FXStatusBar* sb=new FXStatusBar (frame, LAYOUT_FILL_X|
				   STATUSBAR_WITH_DRAGCORNER);

  getApp()->addTimeout(this, ID_UPDT, UPDATE_INTERVAL, NULL);
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
  delete labTrPb;

  delete labTransName;
  delete labTransOrie;
  delete labTransSize;
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

  FXString filename=(FX::FXchar*)v;

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
      else if (str.contains("PASS")!=0){
	showHelpPass();
      }
      else if (str.contains("PASV")!=0){
	showHelpPasv();
      }
      else if (str.contains("PWD")!=0){
	showHelpPwd();
      }
      else if (str.contains("LIST")!=0){
	showHelpList();
      }
      else if (str.contains("SYST")!=0){
	showHelpSyst();
      }
      else if (str.contains("BINARY")!=0){
	showHelpBinary();
      }
      else if (str.contains("ASCII")!=0){
	showHelpAscii();
      }
      else if (str.contains("STOR")!=0){
	showHelpStore();
      }
      else if (str.contains("RETR")!=0){
	showHelpRetrieve();
      }
      else{
	onHelp(NULL,0,NULL);

      }
    }
    else if (str.contains("LIST")!=0){
      string s=ftpClient->commandLIST();
      FXString str=s.c_str();
      str.substitute('\r', ' ', true );
      logMessage(str);
    }
    else if (str.contains("PASV")!=0){
      ftpClient->toggleTransferMode();
      string s=ftpClient->waitControlResponse();
      logMessage(s.c_str());
    }
    else if (str.contains("PWD")!=0){
      string s=ftpClient->commandPWD();
      logMessage(s.c_str());
    }
    else if (str.contains("SYST")!=0){
      string s=ftpClient->commandSYST();
      logMessage(s.c_str());
    }
    else if (str.contains("BINARY")!=0){
      string s=ftpClient->commandBINARY();
      logMessage(s.c_str());
    }
    else if (str.contains("ASCII")!=0){
      string s=ftpClient->commandASCII();
      logMessage(s.c_str());
    }
    else if (str.contains("STOR")!=0){
      // because str is in UPPER case
      // I get the no-upper string
      int pos = str.find("STOR", 0);
      filename.erase( pos, 5 );

      LOGCATS("Filename :");
      LOGCATS(filename.text());
      LOGCAT();

      std::string fn(filename.text());

      // Get filename
      int filesize=ftpClient->getFilesize(fn);
      labTrPb->setTotal(filesize);

      // Change transfer information
      labTransName->setText(filename);
      labTransOrie->setText("Out");
      labTransSize->setText(filesizeToString(filesize));

      string s=ftpClient->commandSTOR(fn);
      logMessage(s.c_str());
    }
    else if (str.contains("RETR")!=0){
      // because str is in UPPER case
      // I get the no-upper string
      int pos = str.find("RETR", 0);
      filename.erase( pos, 5 );

      LOGCATS("Filename :");
      LOGCATS(filename.text());
      LOGCAT();

      std::string fn(filename.text());

      // Change transfer information
      labTransName->setText(filename);
      labTransOrie->setText("In");

      string s=ftpClient->commandRETR(fn);
      logMessage(s.c_str());
    }
    else{
      logMessage("Unknown command");
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
    std::string s=ftpClient->waitControlResponse();
    logMessage(s.c_str());
    fxText->enable();
    fxTextField->enable();

  }
  else{
    LOGE("Connection to FTP Host failed");
    logMessage("Connection to FTP Host failed");
  }

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
  showHelpCommand("ASCII",
		  "The server send files in ASCII mode (TYPE A)");
  showHelpCommand("BINARY",
		  "The server send files in BINARY mode (TYPE I)");
  showHelpCommand("HELP <command>", 
		  "A more detailled description of a command");
  showHelpCommand("LIST",
		  "Prints the content of the server's working directory");
  showHelpCommand("PASS <password>", "Enter user password");
  showHelpCommand("PASV",
		  "Toggle the transfer mode (Active/Passive)");
  showHelpCommand("PWD",
		  "Prints the server's working directory");
  showHelpCommand("RETR",
		  "Get a file from the server");
  showHelpCommand("STOR",
		  "Send a file to the server");
  showHelpCommand("SYST",
		  "Prints the host type");
  showHelpCommand("USER <username>", "Use username to log to the server");

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
  scrollDown();
}

/** Show the help text on the PASS command
  *
  */
void RainbruRPG::Gui::FtpClientWindow::showHelpPass(){

  FXString help;
  help+=            "This command is used to send the user password.\n";
  help+= HELP_INDENT"It is often used just after a USER command and should\n";
  help+= HELP_INDENT"not be used by the end-user. The password is not\n";
  help+= HELP_INDENT"crypted.";

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

/** Show a help text on the PWD command
  *
  */
void RainbruRPG::Gui::FtpClientWindow::showHelpPwd(){
  FXString help;
  help+=            "Print the current server's working directory.\n";
  help+= HELP_INDENT"When you retrieve or store a file from/to a FTP\n";
  help+= HELP_INDENT"server the filename is always relative to the\n";
  help+= HELP_INDENT"working directory. This command let you know\n";
  help+= HELP_INDENT"the current working directory of the server.";

  showHelpCommand("PWD", help);

}

/** Show a help text on the LIST command
  *
  */
void RainbruRPG::Gui::FtpClientWindow::showHelpList(){
  FXString help;
  help+=            "Print the current server's working directory content.\n";
  help+= HELP_INDENT"It prints the file and directory list in a form\n";
  help+= HELP_INDENT"similary to the ls unix command.\n";

  showHelpCommand("LIST", help);

}

/** Show a help text on the SYST command
  *
  */
void RainbruRPG::Gui::FtpClientWindow::showHelpSyst(){
  FXString help;
  help+=            "Print the host type.\n";
  help+= HELP_INDENT"It is important in the game context because we.\n";
  help+= HELP_INDENT"can test if we are connected to a real game server.\n";

  showHelpCommand("SYST", help);

}

/** Show a help text on the Binary command
  *
  */
void RainbruRPG::Gui::FtpClientWindow::showHelpBinary(){
  FXString help;
  help+=            "Set the server in binary mode. The file send by the\n";
  help+= HELP_INDENT"will now be in binary.\n";

  showHelpCommand("BINARY", help);

}

/** Show a help text on the ascii command
  *
  */
void RainbruRPG::Gui::FtpClientWindow::showHelpAscii(){
  FXString help;
  help+=            "Set the server in ascii mode. The file send by the\n";
  help+= HELP_INDENT"will now be in ascii.\n";

  showHelpCommand("ASCII", help);

}

/** Show a help text on the STOR command
  *
  */
void RainbruRPG::Gui::FtpClientWindow::showHelpStore(){
  FXString help;
  help+=            "Send the file named filename to the server. The name\n";
  help+= HELP_INDENT"should contain absolute path.\n";

  showHelpCommand("STOR <filename>", help);

}

/** Show a help text on the RETR command
  *
  */
void RainbruRPG::Gui::FtpClientWindow::showHelpRetrieve(){
  FXString help;
  help+=            "Get the given file from the server. The filename\n";
  help+= HELP_INDENT"should not contain path. The file will be saved in\n";
  help+= HELP_INDENT"the user directory.\n";

  showHelpCommand("RETR <filename>", help);

}

/** The slot connected to the FtpClient::sigBytesWritten signal
  *
  * This slot cannot update GUI because the FtpClient is executed in a 
  * different thread. See onUpdateTransfer() for more details.
  *
  */
void RainbruRPG::Gui::FtpClientWindow::slotBytesWritten(int b){
  downloadedBytes+=b;
}

/** The update button callback
  *
  * The sigc++ signal comming from FtpClient is connected to the 
  * slotBytesWritten(). But as the FtpClient is executed in a separate
  * thread, we can update the GUI (a <code>Xlib: unexpected async 
  * reply</code> error occured).
  *
  * This callback is regularly called (the timeout is defined by the
  * UPDATE_INTERVAL macro) to update the GUI.
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::FtpClientWindow::
onUpdateTransfer(FXObject* o,FXSelector s,void* v){
  labTrPb->setProgress(downloadedBytes);
  getApp()->addTimeout(this, ID_UPDT, UPDATE_INTERVAL, NULL);

  if (resetTransfer){
    resetTransfer=false;
    labTransName->setText("none");
    labTransOrie->setText("");
    labTransSize->setText("");
  }
  return 1;
}

/** Get a filesize in string
  *
  * \param filesize The filesize in bytes
  *
  * \return The string
  *
  */
FXString RainbruRPG::Gui::FtpClientWindow::filesizeToString(int filesize){

  FXString s;
  float fs;
  int mo=1024*1024;

  if (filesize>mo){
    fs=filesize/mo;
    s+=FXStringVal(fs, 2, FALSE);
    s+=" Mb";
  }
  else if (filesize>1024){
    fs=filesize/1024;
    s+=FXStringVal(fs, 2, FALSE);
    s+=" kb";
  }
  else{
    s+=FXStringVal(filesize, 10);
    s+=" b";
  }

  return s;
}

/** A slot connected to the FtpClient::sigTransferTerminated signal
  *
  * This slot will be called when the current transfer will be
  * terminated. It should reset the transfer visual.
  *
  */
void RainbruRPG::Gui::FtpClientWindow::slotTransferTerminated(){
  downloadedBytes=0;
  resetTransfer=true;;
}

/** A slot connected to the FtpClient::sigFileSizeReceived signal
  *
  * \param i The filesize in bytes.
  *
  */
void RainbruRPG::Gui::FtpClientWindow::slotFileSizeReceived(int i){
  labTransSize->setText(filesizeToString(i));
  labTrPb->setTotal(i);
}
