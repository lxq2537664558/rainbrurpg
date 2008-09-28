/*
 *  Copyright 2006-2008 Jerome PASQUIER
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

/** \file netflooder/floodpanel.h
  * Declaration file of the options panel of the flooding tool
  *
  * Modifications : 
  * - 17 jul 2008 : PI redeclaration warning fixed 
  * - 27 mar 2007 : starting implementation
  *
  */

#ifndef FLOOD_PANEL_H
#define FLOOD_PANEL_H

#include <fox-1.6/fx.h>
#include <list>
#include <sigc++/sigc++.h>

#include "enetflooderclient.h"
#include "floodertestbase.h"

using namespace std;
using namespace RainbruRPG::Network;

namespace RainbruRPG{
  namespace Gui{

    /** A list of netflooder test
      *
      * It is used by the FloodPanel instance to keep a list of test.
      *
      * \sa FloodPanel, FlooderTestBase
      *
      */
    typedef std::list<FlooderTestBase*> tFlooderTestList;

    /** The netFlooder flood panel
      *
      * This panel allow the user to choose the flooding options.
      *
      */
    class FloodPanel : public FX::FXPacker{
      FXDECLARE(FloodPanel)
	
    public:
      FloodPanel(FXComposite* parent=0, FXuint opts=0, 
		   EnetFlooderClient* c=NULL); 

      virtual ~FloodPanel(); 

      virtual void create();
      

      void setClient(EnetFlooderClient* );

      /** The enumeration defining the Fox selectors, used in event 
        * mechanism
	*/
      enum{
	/** Not Yet Implemented Identifier */
	ID_NYI=FXPacker::ID_LAST,
        /** The test combo box identifier */
	ID_TEST_COMBO,
	/** The flood button */
	ID_RUN,
	/** Setting the new value to  FXMainWindow::ID_LAST*/
	ID_LAST
      };
 
      long onNotYetImplemented(FXObject *,FXSelector,void*);
      long onTestComboChanged(FXObject *,FXSelector,void*);
      long onRunClicked(FXObject *,FXSelector,void*);


    private:
      void feedTestCombo(FXComboBox*);
      void performTest(int);
      void performAllTests();

      void slotProgressOneStep();

      /** The global progress bar */
      FXProgressBar* pgGlobal;
      /** The current step progress bar */
      FXProgressBar* pgStep;
      /** The test list */
      tFlooderTestList* testList;

      /** The index of the selected test in the combobox
        *
	* If 0 (zero) all test must be perform.
	*
	*/
      int selectedTest;

      /** The flooder enet client kept to send packet */
      EnetFlooderClient* client;
    }; 
  }
}

#endif // FLOOD_PANEL_H
