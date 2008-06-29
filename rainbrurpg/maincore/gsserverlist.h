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
 * - 27 jun 2008 : PushButtons added
 * - 27 jul 2007 : Starting implementation
 *
 */

#ifndef GS_SERVER_LIST_H
#define GS_SERVER_LIST_H

#include <xmlserverlist.h>

#include "gsmenubase.h"
#include "vcconstant.h"
#include "guimanager.h"
#include "bglistener.h"

// Forward declarations
namespace BetaGUI{
    class Window;
}
namespace RainbruRPG{
  namespace OgreGui{
    class MultiColumnList;
    class PushButton;
    class Label;
  }
}
// End of forward declarations

using namespace BetaGUI;
using namespace RainbruRPG::Network::Ident;

namespace RainbruRPG {
  namespace Core{


    /** The server list menu
      *
      * If the account connection is accepted, this list appears. Here you
      * can select a server and connect your client to it.
      *
      */
    class gsServerList : public gsMenuBase, public BetaGUI::BetaGUIListener{
    public:
      gsServerList();
      virtual ~gsServerList();

      virtual void init();
      virtual void resume();

      virtual void setupTabOrder();
      virtual void onButtonPress(BetaGUI::Button*);
      void slotSelectionChanged(void);

    protected:
      void refreshList(void);

    private:
      void setupServerList();
      void feedList();

       /** Load and manage the server list 
        *
	* It is used to feed the serverList widget in the feedList()
	* function. It is initialized 
	* in gsServerList() and destroyed in ~gsServerList()
	*
	* \sa serverList, feedList(), gsServerList(), ~gsServerList().
	*
        */
      xmlServerList* xml;

      /** The Wndow containing the server list */
      Window* mWin;

      /** The widget used to draw server list */
      MultiColumnList* mMcl;
      /** The label used to show the number of server found */
      Label* mNumServer;

      /** The refresh button */
      PushButton* btnRefresh;
      /** The play button */
      PushButton* btnPlay;
      /** The 'more infos' button */
      PushButton* btnMoreInfos;
      
    };
  }
}


#endif // GS_SERVER_LIST_H
