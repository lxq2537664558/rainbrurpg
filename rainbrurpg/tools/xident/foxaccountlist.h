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

/* Modifications :
 * - 08 aug 2007 : AddAcount button managed
 *
 */

#ifndef FOX_ACCOUNT_LIST_H
#define FOX_ACCOUNT_LIST_H

#include <fox-1.6/fx.h>
#include <string>

// Forward declarations
namespace RainbruRPG{
  namespace Gui{
    struct tAccountListItem;
  }
  namespace Network{
    namespace Ident{
      class xmlAccountList;
    }
  }
}
// End forward declarations

using namespace RainbruRPG::Network::Ident;

namespace RainbruRPG{
  namespace Gui{
    /** The xIdent main window
      *
      *
      */
    class FoxAccountList : public FX::FXPacker {
      FXDECLARE(FoxAccountList)
	
    public:
      FoxAccountList(FXComposite* parent=0, FXuint opts=0); 
      virtual ~FoxAccountList(); 

      virtual void create();
      
      /** The enumeration defining the Fox selectors, used in event 
        * mechanism
	*/
      enum{
	/** Not Yet Implemented Identifier */
	ID_NYI=FXPacker::ID_LAST,
	/** The add account button FOX identifier */
	ID_BTN_ADD,
 	/** Setting the new value to  FXMainWindow::ID_LAST*/
	ID_LAST
      };
 
      long onNotYetImplemented(FXObject *,FXSelector,void*);
      long onAddAccountClicked(FXObject *,FXSelector,void*);

    private:
      /** The account list */
      xmlAccountList* accountList;
      /** The account's table */
      FXTable* table;
      /** The label where we print the total number of account */
      FXLabel* labPlCount;

      void feedTable();
      void setAccountNumber(unsigned int);
      void addAccount(RainbruRPG::Gui::tAccountListItem*);
    }; 

  }
}

#endif // FOX_ACCOUNT_LIST_H
