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

/** \file tools/xident/deleteserver.cpp
  * Implements a dialog used to delete a server
  *
  */

#include "deleteserver.h"

#include <logger.h>

/** The Fox-toolkit event mapping 
  *
  * This map is needed by the Fox-Toolkit event model. It defines
  * the event used by the 
  * \ref RainbruRPG::Gui::DeleteServer "DeleteServer" class.
  *
  */
FXDEFMAP(RainbruRPG::Gui::DeleteServer) DeleteServerMap[]={
  //____Message_Type_____________ID_______________Message_Handler_______
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::DeleteServer::ID_NYI, RainbruRPG::Gui::DeleteServer::onNotYetImplemented),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::DeleteServer::ID_BTN_CANCEL, RainbruRPG::Gui::DeleteServer::onCancelClicked),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::DeleteServer::ID_BTN_OK, RainbruRPG::Gui::DeleteServer::onOkClicked),

};

/** Declares the implementation of the class 
  *
  * This statement tells to Fox-Toolkit that the 
  * \ref RainbruRPG::Gui::DeleteServer "DeleteServer" class
  * uses the DeleteServerMap event map.
  *
  */
FXIMPLEMENT(RainbruRPG::Gui::DeleteServer,FXDialogBox,DeleteServerMap,ARRAYNUMBER(DeleteServerMap));

/** The deleteserver dialog constructor
  *
  * The second parameter is used to initialize the serverName variable.
  *
  * \sa serverName.
  *
  * \param a The FXApp needed to create the FXDialogBox instance
  * \param serverName The name of the server to delete
  *
  */
RainbruRPG::Gui::DeleteServer::DeleteServer(FXApp *a, FXString serverName)
  :FXDialogBox(a, "Delete selected server", 
	       DECOR_TITLE|DECOR_BORDER|DECOR_RESIZE)
{
  this->serverName=serverName;

  // The root frame
  FXVerticalFrame *root =new FXVerticalFrame(this,LAYOUT_FILL_X|LAYOUT_FILL_Y);

  FXString lab1="You are about to delete this server.\n"
    "Click OK to delete it ot Cancel.";
  FXLabel* labHelp=new FXLabel(root, lab1, 0, LABEL_NORMAL|LAYOUT_FILL_X);

  // The buttons
  FXHorizontalFrame *btnFrame = new FXHorizontalFrame(root,LAYOUT_FILL_X);
  FXuint btnOpts= LAYOUT_RIGHT|BUTTON_NORMAL|LAYOUT_FIX_WIDTH ;
  FXint btnWidth=120;
  FXButton* btn1=new FXButton( btnFrame, "Cancel", NULL, this, 
			       ID_BTN_CANCEL, btnOpts, 0, 0, btnWidth);
  btn1->setDefault(true);
  FXButton* btn2=new FXButton( btnFrame, "OK", NULL, this, ID_BTN_OK, 
			       BUTTON_NORMAL|LAYOUT_FIX_WIDTH, 0, 0, btnWidth);

}

/** The destructor
  *
  */
RainbruRPG::Gui::DeleteServer::~DeleteServer(){

}

/** The FOX-Toolkit create method
  *
  * It creates the instance of FXDialogBox and set the placement behavior to
  * PLACEMENT_SCREEN.
  *
  */
void RainbruRPG::Gui::DeleteServer::create(){
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
long RainbruRPG::Gui::DeleteServer::
onNotYetImplemented(FXObject *o,FXSelector s,void* v){
  LOGW("Not yet implemented");
  return 1;
}

/** The Cancel button callback
  *
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::DeleteServer::
onCancelClicked(FXObject * o,FXSelector s,void* v){
  handle(this, FXSEL(SEL_COMMAND, FXDialogBox::ID_CANCEL), NULL);
  return 1;
}

/** The OK button callback
  *
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::DeleteServer::
onOkClicked(FXObject * o,FXSelector s,void* v){
  LOGI("OK button clicked");

  std::string name(serverName.text());

  CurlServerDelete csd;
  csd.setName(name);
  bool per=csd.perform();

  if (per){
    LOGI("The form was correctly posted");
  }
  else{
    HttpResponse hr;
    long resp=csd.getServerResponse();
    const char* mes=hr.getMessage(resp);
    LOGCATS("HTTP rsponse :");
    LOGCATS(mes);
  }

  handle(this, FXSEL(SEL_COMMAND, FXDialogBox::ID_ACCEPT), NULL);
  return 1;
}
