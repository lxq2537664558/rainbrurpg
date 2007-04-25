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

#include <logger.h>
#include <fox-1.6/FXMessageBox.h>

FXDEFMAP(RainbruRPG::Gui::FtpClientWindow) FtpClientWindowMap[]={
  //____Message_Type_____________ID_______________Message_Handler_______
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::FtpClientWindow::ID_NYI, RainbruRPG::Gui::FtpClientWindow::onNotYetImplemented),


};

FXIMPLEMENT(RainbruRPG::Gui::FtpClientWindow,FXMainWindow,FtpClientWindowMap,ARRAYNUMBER(FtpClientWindowMap));


/** The constructor
  *
  * \param a The fox application instance the launcher will be used with
  *
  */
RainbruRPG::Gui::FtpClientWindow::FtpClientWindow(FXApp * a)
   :FXMainWindow(a,"RainbruRPG netflooder",NULL,NULL,DECOR_ALL,0,0,800,600){


}

/** The default destructor
  *
  *
  */
RainbruRPG::Gui::FtpClientWindow::~FtpClientWindow(){

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
