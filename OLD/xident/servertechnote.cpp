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

/** \file tools/xident/servertechnote.cpp
  * Implements a dialog used to show a server's technical note
  *
  */

#include "servertechnote.h"

#include <logger.h>
#include <fox-1.6/FXMessageBox.h>

/** The Fox-toolkit event mapping 
  *
  * This map is needed by the Fox-Toolkit event model. It defines
  * the event used by the 
  * \ref RainbruRPG::Gui::ServerTechNote "ServerTechNote" class.
  *
  */
FXDEFMAP(RainbruRPG::Gui::ServerTechNote) ServerTechNoteMap[]={
  //____Message_Type_____________ID_______________Message_Handler_______
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::ServerTechNote::ID_NYI, RainbruRPG::Gui::ServerTechNote::onNotYetImplemented),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::ServerTechNote::ID_BTN_OK, RainbruRPG::Gui::ServerTechNote::onOkClicked),

};

/** Declares the implementation of the class 
  *
  * This statement tells to Fox-Toolkit that the 
  * \ref RainbruRPG::Gui::ServerTechNote "ServerTechNote" class
  * uses the ServerTechNoteMap event map.
  *
  */
FXIMPLEMENT(RainbruRPG::Gui::ServerTechNote,FXDialogBox,ServerTechNoteMap,ARRAYNUMBER(ServerTechNoteMap));

/** The server technical note dialog constructor
  *
  * It creates the GUI dialog based on FOX toolkit and show the 
  * server's technical note retrieved by the getServerTechNote() function.
  * The server is identified by its name.
  *
  * \param a          The FXApplication the dialog will be used with
  * \param serverName The name of server, you want the technote from
  *
  */
RainbruRPG::Gui::ServerTechNote::ServerTechNote(FXApp *a, FXString serverName)
  : FXDialogBox(a, "Server description", DECOR_TITLE|DECOR_BORDER|DECOR_RESIZE)
{
  this->resize(400, 400);

  // The root frame
  FXVerticalFrame *root =new FXVerticalFrame(this,LAYOUT_FILL_X|LAYOUT_FILL_Y);
  FXString lab1="Here is the technical note of the selected server.\n"
    "This technote is read-only and can be empty.";
  FXLabel* labHelp=new FXLabel(root, lab1, 0, LABEL_NORMAL|LAYOUT_FILL_X);

  // The tech note field
  FXText* txtDesc=new FXText(root, NULL, 0,LAYOUT_FILL_X|LAYOUT_FILL_Y);
  txtDesc->setEditable(FALSE);
  txtDesc->setText(getServerTechNote(serverName));

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
RainbruRPG::Gui::ServerTechNote::~ServerTechNote(){

}

/** The FOXToolkit create method
  *
  * Call the FOX create() method on the dialog base class (FXDialogBox)
  * then call show with the \c PLACEMENT_SCREEN parameter.
  *
  */
void RainbruRPG::Gui::ServerTechNote::create(){
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
long RainbruRPG::Gui::ServerTechNote::
onNotYetImplemented(FXObject * o,FXSelector s,void* v){
  LOGW("Not yet implemented");
  return 1;

}

/** The OK button callback
  *
  * Simply closes the dialog by sending the FXDialogBox::ID_ACCEPT to
  * the base FXDialogBox.
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::ServerTechNote::
onOkClicked(FXObject * o,FXSelector s,void* v){
  handle(this, FXSEL(SEL_COMMAND, FXDialogBox::ID_ACCEPT), NULL);
  return 1;

}

/** Get the technical note of the named server
  *
  * This function is used in the ServerTechNote constructor to get
  * the technote.
  *
  * \param name The server's name
  *
  * \return The description
  *
  */
FXString RainbruRPG::Gui::ServerTechNote::getServerTechNote(FXString name){
  std::string n(name.text());
  xmlServerList xsl;
  ServerListItem* sli=xsl.getServerByName(n.c_str());
  FXString ret(sli->getTechNote().c_str());

  return ret;
}