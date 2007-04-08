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
 * - 22 mar 2007 : ServerLog is not a dock window anymore (A single MDI child)
 * - 16 mar 2007 : Client connection packets received and sent
 * - 21 jan 2007 : Starting implementation
 */
#ifndef __MainWindow_h__
#define __MainWindow_h__

#include <QtGui>
#include <QMetaType>

#include <curlserveradd.h>
#include <curlserverdelete.h>
#include <stringconv.h>
#include <enet/enet.h>

#include <npidentification.h>
#include <npconnectionresponse.h>

#include "configdialog.h"
#include "technotedialog.h"
#include "serverconfiguration.h"
#include "serverthread.h"
#include "clientlist.h"
#include "serverlog.h"

using namespace RainbruRPG::Gui;
using namespace RainbruRPG::Network;
using namespace RainbruRPG::Network::Ident;

namespace RainbruRPG{
  namespace Server{
    /** The RainbruRPG server main window
      *
      */
    class MainServerWindow : public QMainWindow{
      Q_OBJECT
	
    public:
      MainServerWindow(const QString &fileName, QWidget *parent = 0);
      ~MainServerWindow();

    private:
      void setupActions();  
      bool registerServer();
      bool unregisterServer();
      bool isClientAccepted(tNetworkClientType);

      /** The server status bar */
      QStatusBar* statusbar;
      /** A label used in the status bar 
        *
	* It shows if the server is started.
	*
	*/
      QLabel* stateLab;
      /** A label used in the status bar 
        *
	* It shows the number of connected clients.
	*
	*/
      QLabel* clientsLab;
      /** The server configuration datas */
      ServerConfiguration* serverConfig;
      /** The 'stop server' action */
      QAction* stopAct;
      /** The 'start server' action */
      QAction* runAct;
      /** Is the server running ? */
      bool running;
      /** The enet host used by the server */
      ServerThread* server;
      /** The workspace for MDI ability */
      QWorkspace* workspace;
      /** A unique client list widget */
      ClientList * clientList;
      /** The server log widget */
      ServerLog* serverLog;

    public slots:
      void exitRequested();

    private slots:
      void showConfigDialog();
      void showTechNoteDialog();
      void showHelpDialog();
      void showLog();
      void startServer();
      void stopServer();
      void manageClients();

      void clientConnected(const ENetAddress&);
      void packetReceived(const tReceivedPacket&);    
    };
  }
}
#endif // __MainWindow_h__
