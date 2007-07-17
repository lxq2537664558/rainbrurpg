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
 * - 13 jul 2007 : Starting implementation
 *
 */

#ifndef QUARANTINE_LIST_H
#define QUARANTINE_LIST_H

#include <QtGui>

#include <filetypeguesser.h>
#include <globaluri.h>
#include <string>

using namespace RainbruRPG::Network;

namespace RainbruRPG{
  namespace Gui{

    /** Provide a list of files in quarantine
      *
      * Files in quarantine are waiting for approval. When an editor send 
      * a file to the server, it is place in a quarantine directory, where 
      * the game client <b>will not</b> search for download. The server
      * administrator need to approve each files before it can be downloaded
      * by game client.
      *
      */
    class QuarantineList : public QWidget {
      Q_OBJECT

    public:
      QuarantineList(QWidget* parent=0);
      virtual ~QuarantineList();

      void refresh();

    signals:
      /** A signal emitted when one or more files are removed from the list
        *
	* It is connected to the \ref
	* RainbruRPG::Server::MainServerWindow::filesRemoved(int) 
	* "MainServerWindow::filesRemoved(int)" slot. 
	* The MainServerWindow notification will not make an alert if this
	* signal is correctly emitted.
	*
	* \param i The number of removed files
	*
	*/
      void filesRemoved(int i);

    private slots:
      void treeSelectionChanged();
      void filePreview();
      void fileAccept();
      void fileRefused();

    protected:

      void contextMenuEvent(QContextMenuEvent*);

    private:
      QString fileSizeToString(qint64 filesize);     
      void addFile(QFileInfo);

      /** The main tree widget */
      QTreeWidget* tree;

      /** The action for file preview */
      QAction *previewAct;
      /** The action for approve file */
      QAction *approveAct;
      /** The action for deleting file */
      QAction *deleteAct;
    };
  }
}

#endif // QUARANTINE_LIST_H
