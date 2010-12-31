/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

/** \file tools/xident/addserver.cpp
  * Implements a dialog used to add a server
  *
  */

#include "addserver.h"

#include <logger.h>
#include <fox-1.6/FXMessageBox.h>

/** The Fox-toolkit event mapping 
  *
  * This map is needed by the Fox-Toolkit event model. It defines
  * the event used by the 
  * \ref RainbruRPG::Gui::AddServer "AddServer" class.
  *
  */
FXDEFMAP(RainbruRPG::Gui::AddServer) AddServerMap[]={
  //____Message_Type_____________ID_______________Message_Handler_______
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::AddServer::ID_NYI, RainbruRPG::Gui::AddServer::onNotYetImplemented),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::AddServer::ID_BTN_OK, RainbruRPG::Gui::AddServer::onOkClicked),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::AddServer::ID_BTN_CANCEL, RainbruRPG::Gui::AddServer::onCancelClicked),

};

/** Declares the implementation of the class 
  *
  * This statement tells to Fox-Toolkit that the 
  * \ref RainbruRPG::Gui::AddServer "AddServer" class
  * uses the AddServerMap event map.
  *
  */
FXIMPLEMENT(RainbruRPG::Gui::AddServer,FXDialogBox,AddServerMap,ARRAYNUMBER(AddServerMap));

/** The addserver dialog constructor
  *
  * \param a The FXApp needed to create the FXDialogBox instance
  *
  */
RainbruRPG::Gui::AddServer::AddServer(FXApp *a)
  :FXDialogBox(a, "Add a new server", DECOR_TITLE|DECOR_BORDER|DECOR_RESIZE)
{
  // The root frame
  FXVerticalFrame *root =new FXVerticalFrame(this,LAYOUT_FILL_X|LAYOUT_FILL_Y);

  FXString lab1="Enter the server's information and click the button \n"
    "to add it. Click the cancel button to abort.";
  FXLabel* labHelp=new FXLabel(root, lab1, 0, LABEL_NORMAL|LAYOUT_FILL_X);

  // The info matrix
  FXMatrix *frInfo = new FXMatrix(root, 2, MATRIX_BY_COLUMNS,LAYOUT_FILL_X);
  FXLabel* labServerName   =new FXLabel(frInfo, "Name");
  tfServerName=new FXTextField(frInfo, 20 );

  FXLabel* labServerUniqueName   =new FXLabel(frInfo, "Unique Name");
  tfServerUniqueName=new FXTextField(frInfo, 20 );

  FXLabel* labServerType   =new FXLabel(frInfo, "Type");
  cbServerType=new FXComboBox(frInfo, 20 );
  cbServerType->setNumVisible(4);
  cbServerType->appendItem( "1 - Fantasy");
  cbServerType->appendItem( "2 - Contemporary");
  cbServerType->appendItem( "3 - Futuristic");
  cbServerType->appendItem( "4 - Post-apocalyptic");


  FXLabel* labServerIp     =new FXLabel(frInfo, "IP adress");
  tfServerIp  =new FXTextField(frInfo, 20 );

  FXLabel* labServerPort   =new FXLabel(frInfo, "UDP port");
  tfServerPort=new FXTextField(frInfo, 20 );

  FXLabel* labServerFtpPort   =new FXLabel(frInfo, "FTP port");
  tfServerFtp=new FXTextField(frInfo, 20 );

  FXLabel* labServerCli    =new FXLabel(frInfo, "Maximum allowed clients");
  tfServerCli =new FXTextField(frInfo, 20 );

  // The description
  FXLabel* labDesc=new FXLabel(root, "Description :", 0, 
			       LABEL_NORMAL|LAYOUT_FILL_X);
  txtDesc=new FXText(root, NULL, 0,LAYOUT_FILL_X|LAYOUT_FILL_Y);

  // The technote
  FXLabel* labTech=new FXLabel(root, "Technical note :", 0, 
			       LABEL_NORMAL|LAYOUT_FILL_X);
  txtTech=new FXText(root, NULL, 0,LAYOUT_FILL_X|LAYOUT_FILL_Y);

  // The buttons
  FXHorizontalFrame *btnFrame = new FXHorizontalFrame(root,LAYOUT_FILL_X);
  FXuint btnOpts= LAYOUT_RIGHT|BUTTON_NORMAL|LAYOUT_FIX_WIDTH ;
  FXint btnWidth=120;
  FXButton* btn1=new FXButton( btnFrame, "Cancel", NULL, this, 
			       ID_BTN_CANCEL, btnOpts, 0, 0, btnWidth);
  btn1->setDefault(true);
  FXButton* btn2=new FXButton( btnFrame, "OK", NULL, this, ID_BTN_OK, 
			       BUTTON_NORMAL|LAYOUT_FIX_WIDTH, 0, 0, btnWidth);

  errorMsg="";
}

/** The destructor
  *
  */
RainbruRPG::Gui::AddServer::~AddServer(){
  delete tfServerName;
  delete tfServerIp;
  delete tfServerPort;
  delete tfServerCli;
  delete txtDesc;
  delete txtTech;
  delete tfServerUniqueName;
  delete cbServerType;
}

/** The FOX-Toolkit create method
  *
  * It creates the instance of FXDialogBox and set the placement behavior to
  * PLACEMENT_SCREEN.
  *
  */
void RainbruRPG::Gui::AddServer::create(){
  FXDialogBox::create();
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
long RainbruRPG::Gui::AddServer::
onNotYetImplemented(FXObject *o,FXSelector s,void* v){
  LOGW("Not yet implemented");
  return 1;
}

/** The OK button callback
  *
  * It makes some tests in the server information and add it using
  * CurlServerAdd.
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::AddServer::
onOkClicked(FXObject *o,FXSelector s,void* v){
  LOGI("OK button clicked");

  // Makes some controls
  if (controls()){   // We can add the server
    addServer();
    handle(this, FXSEL(SEL_COMMAND, FXDialogBox::ID_ACCEPT), NULL);
  }
  else{              // An error occured
    FXMessageBox::information(this, MBOX_OK, "Validation error", errorMsg);
  }
  return 1;
}

/** The Cancel button callback
  *
  * It simply closes the dialog.
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::AddServer::
onCancelClicked(FXObject *o,FXSelector s,void* v){
  LOGI("Cancel button clicked");
  handle(this, FXSEL(SEL_COMMAND, FXDialogBox::ID_CANCEL), NULL);
  return 1;
}

/** Control the entered values before adding the server
  *
  * The most important error must be tested last because the error message
  * stored in the errorMsg variable will be overriden.
  *
  * \return \c true if the server can be added
  *
  */
bool RainbruRPG::Gui::AddServer::controls(){
  bool ret=true;
  FXString serverName = tfServerName->getText();
  FXString serverIp   = tfServerIp->getText();

  // Tests the server IP adress
  if(serverIp.empty()){
    errorMsg="The server's IP address cannot be empty";
    ret=false;
  }

  // Tests the server name
  if(serverName.empty()){
    errorMsg="The server's name cannot be empty";
    ret=false;
  }

  return ret;
}

/** Adds the server
  * 
  * This method uses the dialog's informations with CurlServerAdd to
  * submit an administration form to add the server. It is called by
  * the onOkClicked callback is the controls found no error.
  *
  */
void RainbruRPG::Gui::AddServer::addServer(){
  std::string name(tfServerName->getText().text());
  std::string uniqueName(tfServerUniqueName->getText().text());
  std::string type=StringConv::getSingleton()
    .itos(cbServerType->getCurrentItem()+1);
  std::string ip  (tfServerIp->getText().text());
  std::string port(tfServerPort->getText().text());
  std::string ftp (tfServerFtp->getText().text());
  std::string cli (tfServerCli->getText().text());
  std::string desc(txtDesc->getText().text());
  std::string tech(txtTech->getText().text());
  LOGI("Setting posted data :");

  LOGCATS("Server name : '");
  LOGCATS(name.c_str());
  LOGCATS("'");
  LOGCAT();

  LOGCATS("Server IP : '");
  LOGCATS(ip.c_str());
  LOGCATS("'");
  LOGCAT();

  LOGCATS("Server port : '");
  LOGCATS(port.c_str());
  LOGCATS("'");
  LOGCAT();

  LOGCATS("Server maxClients : '");
  LOGCATS(cli.c_str());
  LOGCATS("'");
  LOGCAT();

  CurlServerAdd csa;
  csa.setName(name);
  csa.setUniqueName(uniqueName);
  csa.setType(type);
  csa.setIpAddress(ip);
  csa.setPort(port);
  csa.setFtpPort(ftp);
  csa.setMaxClients(cli);
  csa.setDescription( desc);
  csa.setTechNote( tech);
  //  csa.setPostedData("technote", tech);
  bool per=csa.perform();

  if (per){
    LOGI("The form was correctly posted");
  }
  else{
    HttpResponse hr;
    long resp=csa.getServerResponse();
    const char* mes=hr.getMessage(resp);
    LOGCATS("HTTP rsponse :");
    LOGCATS(mes);
  }
}
