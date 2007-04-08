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
 * - 09 mar 2007 : starting implementation
 *
 */

#ifndef WAITING_PANEL_H
#define WAITING_PANEL_H

#include <fox-1.6/fx.h>

#include <xmlserverlist.h>
#include <string>
#include <stringconv.h>
#include <npidentification.h>
#include <sigc++/sigc++.h>

#include "enetflooderclient.h"

using namespace std;
using namespace RainbruRPG::Core;
using namespace RainbruRPG::Network;
using namespace RainbruRPG::Network::Ident;

namespace RainbruRPG{
  namespace Gui{

    /** The netFlooder waiting panel
      *
      * It shows a help text, a progress bar and a list of labels. Only one of
      * these  labels is enable at the same time. It is to show the
      * connection progression.
      *
      */
    class WaitingPanel : public FX::FXPacker, public sigc::trackable{
      FXDECLARE(WaitingPanel)
	
    public:
      /** Defines a signal returning void with none parameters */
      typedef sigc::signal<void> tVoidSignal;

      WaitingPanel(FXComposite* parent=0, FXuint opts=0, 
		   EnetFlooderClient* c=NULL); 

      virtual ~WaitingPanel(); 

      virtual void create();
      
      /** The enumeration defining the Fox selectors, used in event 
        * mechanism
	*/
      enum{
	/** Not Yet Implemented Identifier */
	ID_NYI=FXPacker::ID_LAST,
	/** Starts the client */
	ID_RUN_CLIENT,
	/** Setting the new value to  FXMainWindow::ID_LAST*/
	ID_LAST
      };
 
      long onNotYetImplemented(FXObject *,FXSelector,void*);
      long onRunClient(FXObject *,FXSelector,void*);
      void runClient();
      void setServer(tServerListItem*);

      /** A signal sent if the connection is refused by the selected server*/
      tVoidSignal sigConnectionRefused;
      /** A signal sent if the connection is accepted by the selected server*/
      tVoidSignal sigConnectionAccepted;

      void reset();

    private:
      void setAllStepsDisable();
      void setStepEnable(unsigned int);

      void slotConnectionAccepted();
      void slotConnectionRefused();
      void slotConnectionUndefined();

      /** The first step's label
        *
	*/
      FXLabel* labStep1;

      /** The second step's label
        *
	*/
      FXLabel* labStep2;

      /** The third step's label
        *
	*/
      FXLabel* labStep3;

      /** Another step's label
        *
	*/
      FXLabel* labStep4;
      /** The enet client taken in the constructor
        *
	*/
      EnetFlooderClient* client;
      /** The server to connect to
        *
	*/
      tServerListItem* server;
      /** The progress bar */
      FXProgressBar* prog;
    }; 
  }
}

#endif // WAITING_PANEL_H
