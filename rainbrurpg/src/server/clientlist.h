/*
 *  Copyright 2006-2013 Jerome PASQUIER
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

/** \file clientlist.h
  * Declares a widget that shows connected/refused clients information
  *
  * Modifications :
  * - 30 aug 2008 : Single file documentation
  * - 21 mar 2007 : A addClient function
  * - 16 mar 2007 : Starting implementation
  *
  */

#ifndef CLIENTS_LIST_H
#define CLIENTS_LIST_H

#include <QtGui>
#include <enet/enet.h>

#include <StringConv.hpp>
#include <NpIdentification.hpp>

using namespace RainbruRPG::Core;
using namespace RainbruRPG::Network;


namespace RainbruRPG{
  namespace Gui{

    /** Show a table with connected/refused clients information
      *
      * The table is feed with unique clients information : IP adress, port
      * and client type. The result of the connection (accepted or refused)
      * is shown. The last column indicates the number of connection the
      * client ask.
      *
      * This list is feed by MainServerWindow when a client is request
      * a connection.
      *
      * It uses a npIdentification instance to convert tNetworkClientType
      * to an human-readable string.
      *
      */
    class ClientList : public QWidget {
      Q_OBJECT

    public:
      ClientList(QWidget* parent=0);
      ~ClientList();
      void addClient(enet_uint32, enet_uint16 ,tNetworkClientType, bool);

    private:
      int existingClient(const QString&, const QString&, 
			 const QString&, const QString&);

      void increaseClientTry(int);

      /** The tree widget */
      QTreeWidget* tree;
    };
  }
}

#endif // CLIENTS_LIST_H
