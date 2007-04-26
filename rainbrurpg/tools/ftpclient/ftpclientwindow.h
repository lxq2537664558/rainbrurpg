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

/* Modifications :
 *
 * - 25 apr 2007 : Starting implementation
 */ 
#ifndef NET_FLOODER_WINDOW_H
#define NET_FLOODER_WINDOW_H

#include <fox-1.6/fx.h>
#include <sigc++/sigc++.h>

#include <gnet.h>
#include <logger.h>

namespace RainbruRPG{
  namespace Gui{

    /** The ftpClient main window
      *
      * It is a simple FTP client used to test the FTP client-side functions
      * implementation.
      *
      */
    class FtpClientWindow : public FX::FXMainWindow {
      FXDECLARE(FtpClientWindow)
	
    public:
      FtpClientWindow(FXApp *); 
      virtual ~FtpClientWindow(); 

      virtual void create();
      
      /** The enumeration defining the Fox selectors, used in event 
        * mechanism
	*/
      enum{
	/** Not Yet Implemented Identifier */
	ID_NYI=FXMainWindow::ID_LAST,
	/** A new command was entered */
	ID_NEW_CMD,
	/** The connect button identifier */
	ID_CONN,
	/** Setting the new value to  FXMainWindow::ID_LAST*/
	ID_LAST
      };
 
      long onNotYetImplemented(FXObject *,FXSelector,void*);
      long treatNewCommand(FXObject *,FXSelector,void*);
      long onConnect(FXObject *,FXSelector,void*);

    private:
      void logMessage(FXString);

      /** Required or Undefined references */
      FtpClientWindow(){};
      /** Required or Undefined references */
      FtpClientWindow(const FtpClientWindow&);
      /** Required or Undefined references */
      FtpClientWindow &operator=(const FtpClientWindow&);

      /** The file menu item */
      FXMenuPane*filemenu;
      /** The widget where we treat commands */
      FXText* fxText;
      /** The command text field */
      FXTextField* fxTextField;

      FXTextField* tfHostIp;
      FXTextField* tfHostPort;
    }; 
  }
}

#endif// NET_FLOODER_WINDOW_H



