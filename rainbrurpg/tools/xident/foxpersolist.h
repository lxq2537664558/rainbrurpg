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
 * - 19 jul 2007 : Starting implementation
 *
 */

#ifndef FOX_PERSOS_LIST_H
#define FOX_PERSOS_LIST_H

#include <fox-1.6/fx.h>

#include <xmlpersolist.h>
#include <stringconv.h>
#include <string>

using namespace RainbruRPG::Network;

namespace RainbruRPG{
  namespace Gui{

    /** The perso list compound for xIdent
      *
      */
    class FoxPersoList : public FX::FXPacker {
      FXDECLARE(FoxPersoList)
    public:
      FoxPersoList(FXComposite* parent=0, FXuint opts=0);

      virtual ~FoxPersoList(); 

      virtual void create();
      
      /** The enumeration defining the Fox selectors, used in event 
        * mechanism
	*/
      enum{
	/** Not Yet Implemented Identifier */
	ID_NYI=FXPacker::ID_LAST,
	/** The account list identifier */
	ID_ACCOUNT,
      };
 
      long onNotYetImplemented(FXObject *,FXSelector,void*);
      long onAccountSelected(FXObject *,FXSelector,void*);

    private:
      void feedAccountList(void);

      /** The account list FOX widget */
      FXList* accountList;
      /** The persos list FOX widget */
      FXList* persoList;

      /** The perso list XML reader */
      xmlPersoList* xmlPerso;
    };
  }
}

#endif // FOX_PERSOS_LIST_H
