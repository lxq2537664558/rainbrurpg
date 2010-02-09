/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file tools/xident/serverdesc.cpp
  * Implements a dialog used to show the server description
  *
  */

#include "serverdesc.h"

#include <logger.h>
#include <fox-1.6/FXMessageBox.h>

/** The Fox-toolkit event mapping 
  *
  * This map is needed by the Fox-Toolkit event model. It defines
  * the event used by the 
  * \ref RainbruRPG::Gui::ServerDesc "ServerDesc" class.
  *
  */
FXDEFMAP(RainbruRPG::Gui::ServerDesc) ServerDescMap[]={
  //____Message_Type_____________ID_______________Message_Handler_______
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::ServerDesc::ID_NYI, RainbruRPG::Gui::ServerDesc::onNotYetImplemented),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::ServerDesc::ID_BTN_OK, RainbruRPG::Gui::ServerDesc::onOkClicked),

};

/** Declares the implementation of the class 
  *
  * This statement tells to Fox-Toolkit that the 
  * \ref RainbruRPG::Gui::ServerDesc "ServerDesc" class
  * uses the ServerDescMap event map.
  *
  */
FXIMPLEMENT(RainbruRPG::Gui::ServerDesc,FXDialogBox,ServerDescMap,ARRAYNUMBER(ServerDescMap));

/** The server description dialog constructor
  *
  * Creates the dialog itself. The server description is retrieved by
  * the getServerDesc() function.
  *
  * \param a The FXApplication the dialog will be used with
  * \param serverName The name of server, you want the description from
  *
  */
RainbruRPG::Gui::ServerDesc::ServerDesc(FXApp *a, FXString serverName)
  : FXDialogBox(a, "Server description", DECOR_TITLE|DECOR_BORDER|DECOR_RESIZE)
{
  this->resize(400, 400);

  // The root frame
  FXVerticalFrame *root =new FXVerticalFrame(this,LAYOUT_FILL_X|LAYOUT_FILL_Y);
  FXString lab1="Here is the description of the selected server.\n"
    "This description is read-only.";
  FXLabel* labHelp=new FXLabel(root, lab1, 0, LABEL_NORMAL|LAYOUT_FILL_X);

  // The description field
  FXint txtOpts=LAYOUT_FILL_X|LAYOUT_FILL_Y|TEXT_READONLY;
  FXText* txtDesc=new FXText(root, NULL, 0,txtOpts);
  //  txtDesc->setEditable(FALSE);
  txtDesc->setText(getServerDesc(serverName));

  // The buttons
  FXHorizontalFrame *btnFrame = new FXHorizontalFrame(root,LAYOUT_FILL_X);
  FXuint btnOpts= LAYOUT_RIGHT|BUTTON_NORMAL|LAYOUT_FIX_WIDTH ;
  FXint btnWidth=120;
  FXButton* btn2=new FXButton( btnFrame, "OK", NULL, this, ID_BTN_OK, 
			       BUTTON_NORMAL|LAYOUT_FIX_WIDTH, 0, 0, btnWidth);

}

/** The dialog destructor
  *
  */
RainbruRPG::Gui::ServerDesc::~ServerDesc(){

}

/** The FOXToolkit create method
  *
  * Call the FOX create() method on the dialog base class (FXDialogBox)
  * then call show with the \c PLACEMENT_SCREEN parameter.
  *
  */
void RainbruRPG::Gui::ServerDesc::create(){
  FXDialogBox::create();
  show(PLACEMENT_SCREEN);
}

/** A generic callback for unimplemented signals
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::ServerDesc::
onNotYetImplemented(FXObject * o,FXSelector s,void* v){
  LOGW("Not yet implemented");
  return 1;

}

/** The OK button callback
  *
  * Simply closes the dialog.
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::ServerDesc::
onOkClicked(FXObject * o,FXSelector s,void* v){
  handle(this, FXSEL(SEL_COMMAND, FXDialogBox::ID_ACCEPT), NULL);
  return 1;
}

/** Get the description of the named server
  *
  * This function is used in the ServerDesc constructor to get
  * the description.
  *
  * \param name The server's name
  *
  * \return The description
  *
  */
FXString RainbruRPG::Gui::ServerDesc::getServerDesc(FXString name){
  std::string n;
  n=StringConv::getSingleton().xmlToNewLine(name.text());

  xmlServerList xsl;
  ServerListItem* sli=xsl.getServerByName(n.c_str());
  FXString ret(sli->getDescription().c_str());

  return ret;
}
