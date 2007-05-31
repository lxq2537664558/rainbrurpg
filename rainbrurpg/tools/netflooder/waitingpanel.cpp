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

#include "waitingpanel.h"

#include <logger.h>
#include <fox-1.6/FXMessageBox.h>

FXDEFMAP(RainbruRPG::Gui::WaitingPanel) WaitingPanelMap[]={
  //____Message_Type_____________ID_______________Message_Handler_______
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::WaitingPanel::ID_NYI, RainbruRPG::Gui::WaitingPanel::onNotYetImplemented),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::WaitingPanel::ID_RUN_CLIENT, RainbruRPG::Gui::WaitingPanel::onRunClient),

};

FXIMPLEMENT(RainbruRPG::Gui::WaitingPanel,FXPacker,WaitingPanelMap,ARRAYNUMBER(WaitingPanelMap));

/** The constructor
  *
  * The parent must not be NULL
  *
  * \param parent The parent composite
  * \param opts The FOX construction parameter
  * \param c The enet client used for connection
  *
  */
RainbruRPG::Gui::WaitingPanel::
WaitingPanel(FXComposite *parent,FXuint opts, EnetFlooderClient* c)
  :FXPacker(parent, opts)
{

  this->client=c;
  FXVerticalFrame *root = new FXVerticalFrame(this,
             LAYOUT_FILL_X|LAYOUT_FILL_Y);

  // The help label
  FXString lab="This panel is shown for waiting connection to the "
    "selected server. Click the 'Run' button to starting connection.";
  FXLabel* labAdminName=new FXLabel(root, lab);

  // The progress bar frame
  FXVerticalFrame *frProg = new FXVerticalFrame(root,
             LAYOUT_FILL_X);
  prog=new  FXProgressBar(frProg, this, ID_NYI, 
	PROGRESSBAR_NORMAL|LAYOUT_FILL_X|PROGRESSBAR_PERCENTAGE );
  prog->setTotal(5);

  // The steps labels
  labStep1=new FXLabel(frProg, "Initializing client");
  labStep2=new FXLabel(frProg, "Connecting client to selected server");
  labStep3=new FXLabel(frProg, "Sending identification packet");
  labStep4=new FXLabel(frProg, "Waiting for server's response");

  // The buttons
  FXHorizontalFrame *frButtons = new FXHorizontalFrame(frProg,
             LAYOUT_FILL_X|PACK_UNIFORM_WIDTH);
  FXButton* btnRun=new FXButton(frButtons, "Run", NULL, this, 
				ID_RUN_CLIENT, BUTTON_NORMAL|LAYOUT_CENTER_X);

  FXButton* btnRefresh=new FXButton(frButtons, "Cancel", NULL, this, 
				    ID_NYI, BUTTON_NORMAL|LAYOUT_CENTER_X);


  // Disable all steps
  setAllStepsDisable();

}

/** The destructor
 *
 */
RainbruRPG::Gui::WaitingPanel::~WaitingPanel(){
  delete prog;
  delete labStep1;
  delete labStep2;
  delete labStep3;
  delete labStep4;

  prog=NULL;
  labStep1=NULL;
  labStep2=NULL;
  labStep3=NULL;
  labStep4=NULL;

  // Set to NULL but not deleted
  server=NULL;
  client=NULL;
}

/** The FOX-Toolkit create method
  *
  * It creates and execute a WaitingPanel instance.
  *
  */
void RainbruRPG::Gui::WaitingPanel::create(){
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
long RainbruRPG::Gui::WaitingPanel::
onNotYetImplemented(FXObject * o,FXSelector s,void* v){
  LOGW("Not yet implemented");
  return 1;
}

/** Setes all the steps label to be disable
  *
  */
void RainbruRPG::Gui::WaitingPanel::setAllStepsDisable(){
  labStep1->disable();
  labStep2->disable();
  labStep3->disable();
  labStep4->disable();
}

/** Set the given step to be enable
  *
  * It also set the other steps disable by calling
  * setAllStepsDisable().
  *
  * \param i The step index
  *
  */
void RainbruRPG::Gui::WaitingPanel::setStepEnable(unsigned int i){
  setAllStepsDisable();

  FXLabel* lab;

  switch(i){
  case 1:
    lab=labStep1;
    break;

  case 2:
    lab=labStep2;
    break;

  case 3:
    lab=labStep3;
    break;

  case 4:
    lab=labStep4;
    break;

  default:
    lab=NULL;
  }

  if (lab){
    lab->enable();
  }
}

/** Run the client with the given server
  *
  * The server must be known.
  *
  * \sa setServer, server
  *
  */
void RainbruRPG::Gui::WaitingPanel::runClient(){
  // Step 1 : call the EnetFlooderClient constructor
  setStepEnable(1);
  client=new EnetFlooderClient();
  prog->increment(1);

  client->sigConnectionAccepted.connect(sigc::mem_fun(this, 
     &RainbruRPG::Gui::WaitingPanel::slotConnectionAccepted));

  client->sigConnectionRefused.connect(sigc::mem_fun(this, 
     &RainbruRPG::Gui::WaitingPanel::slotConnectionRefused));

  client->sigConnectionUndefined.connect(sigc::mem_fun(this, 
     &RainbruRPG::Gui::WaitingPanel::slotConnectionUndefined));


  const char* ip=server->ipAdress;
  int port=StringConv::getSingleton().stoi(server->port);
  prog->increment(1);
  LOGCATS("Running on server ");
  LOGCATS(ip);
  LOGCATS(":");
  LOGCATI(port);
  LOGCAT();

  // Step 2
  int waitingTime=200;
  setStepEnable(2);
  prog->increment(1);

  client->connect(ip, port, waitingTime);
  prog->increment(1);
 
  // Creating packet
  setStepEnable(3);
  npIdentification * ident=new npIdentification();
  ident->setClientType(NCT_FLOODER);
  client->sendPacket(ident);
  prog->increment(1);

  // Waiting for server's response
  setStepEnable(4);
  client->eventLoop();

}

/** Run the client
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v The tServerListItem to run
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::WaitingPanel::
onRunClient(FXObject *o,FXSelector s,void* v){

  LOGI("onRunClient called");
  runClient();
  return 1;
}

/** Set the actual server to connect to
  *
  * The given server will be 
  *
  * \param it The server to the connect the netflooder to
  *
  */
void RainbruRPG::Gui::WaitingPanel::setServer(tServerListItem* it){
  server=it;
}

/** A slot called when the connection is accepted by the selected server
  *
  */
void RainbruRPG::Gui::WaitingPanel::slotConnectionAccepted(){
  LOGI("Received a connectionAccepted signal");
  prog->increment(1);
  sigConnectionAccepted.emit();
}

/** A slot called when the connection is refused by the selected server
  *
  */
void RainbruRPG::Gui::WaitingPanel::slotConnectionRefused(){
  LOGI("Received a connectionRefused signal");
  prog->increment(1);
  FXuint resp=FX::FXMessageBox::information(this, FX::MBOX_OK ,
		"Server's technical note", 
	    "The server refuses flooder connection.");

  sigConnectionRefused.emit();
}

/** The received npConnectionResponse is undefined
  *
  * This should never happenned.
  *
  */
void RainbruRPG::Gui::WaitingPanel::slotConnectionUndefined(){
  LOGE("The server connection response is undefined, assuming it is refused");
  prog->increment(1);
}

/** Set the panel as if it never ran
  *
  */
void RainbruRPG::Gui::WaitingPanel::reset(){
  setAllStepsDisable();
  prog->setProgress(0);
}

/** Return the current client
  *
  * \return The current Enet client used
  *
  */
EnetFlooderClient* RainbruRPG::Gui::WaitingPanel::getClient(){
  return this->client;
}
