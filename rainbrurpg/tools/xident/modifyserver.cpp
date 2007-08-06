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

#include "modifyserver.h"

#include <logger.h>
#include <fox-1.6/FXMessageBox.h>

FXDEFMAP(RainbruRPG::Gui::ModifyServer) ModifyServerMap[]={
  //____Message_Type_____________ID_______________Message_Handler_______
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::ModifyServer::ID_NYI, RainbruRPG::Gui::ModifyServer::onNotYetImplemented),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::ModifyServer::ID_BTN_OK, RainbruRPG::Gui::ModifyServer::onOkClicked),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::ModifyServer::ID_BTN_CANCEL, RainbruRPG::Gui::ModifyServer::onCancelClicked),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::ModifyServer::ID_SPI_CLI, RainbruRPG::Gui::ModifyServer::onSpinnerClicked),


};

FXIMPLEMENT(RainbruRPG::Gui::ModifyServer,FXDialogBox,ModifyServerMap,ARRAYNUMBER(ModifyServerMap));

/** The modifyserver dialog constructor
  *
  * \param a The FXApp needed to create the FXDialogBox instance
  * \param serverName The name of the server to modify
  *
  */
RainbruRPG::Gui::ModifyServer::ModifyServer(FXApp *a, FXString serverName)
  :FXDialogBox(a, "Add a new server", DECOR_TITLE|DECOR_BORDER|DECOR_RESIZE)
{

  this->serverName=serverName;
  std::string name(serverName.text());

  // Get the server's client informations
  xmlServerList xsl;
  ServerListItem* sli=xsl.getServerByName(name.c_str());
  unsigned int maxCli=sli->getMaxClients();
  unsigned int actCli=sli->getActClients();

  // The root frame
  FXVerticalFrame *root =new FXVerticalFrame(this,LAYOUT_FILL_X|LAYOUT_FILL_Y);

  std::string lab1="Here you can change the number of connected\n"
    "clients of the selected server.\n"
    "The server has actually ";
  lab1+=sli->getOccupationStr();


  FXLabel* labHelp=new FXLabel(root, lab1.c_str(), 0, 
			       LABEL_NORMAL|LAYOUT_FILL_X);

  // The Spinner
  FXSpinner* spiCli=new FXSpinner(root, 2, this, ID_SPI_CLI, 
				  LAYOUT_FILL_X|SPIN_NORMAL);
  spiCli->setRange(0, maxCli);
  spiCli->setValue(actCli);

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
RainbruRPG::Gui::ModifyServer::~ModifyServer(){

}

/** The FOX-Toolkit create method
  *
  * It creates the instance of FXDialogBox and set the placement behavior to
  * PLACEMENT_SCREEN.
  *
  */
void RainbruRPG::Gui::ModifyServer::create(){
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
long RainbruRPG::Gui::ModifyServer::
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
long RainbruRPG::Gui::ModifyServer::
onOkClicked(FXObject *o,FXSelector s,void* v){
  LOGI("OK button clicked");

  std::string name(serverName.text());

  CurlServerModifClients csmc;
  csmc.setName(name);
  csmc.setActClients(actClients);

  bool per=csmc.perform();

  if (per){
    LOGI("The form was correctly posted");
  }
  else{
    HttpResponse hr;
    long resp=csmc.getServerResponse();
    const char* mes=hr.getMessage(resp);
    LOGCATS("HTTP rsponse :");
    LOGCATS(mes);
  }

  handle(this, FXSEL(SEL_COMMAND, FXDialogBox::ID_ACCEPT), NULL);


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
long RainbruRPG::Gui::ModifyServer::
onCancelClicked(FXObject *o,FXSelector s,void* v){
  LOGI("Cancel button clicked");
  handle(this, FXSEL(SEL_COMMAND, FXDialogBox::ID_CANCEL), NULL);
  return 1;
}

/** The client number spinner callback
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v The new value of the spinner (need a cast to int)
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::ModifyServer::
onSpinnerClicked(FXObject *o,FXSelector s,void* v){

  int i=(int)v;
  LOGCATS("New value ");
  LOGCATI(i);
  LOGCAT();
  actClients=i;
}
