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

/** \file quarantinelist.h
  * Declares a widget showing files in quarantine
  *
  * Modifications :
  * - 05 sep 2008 : Single file documentation
  * - 13 jul 2007 : Starting implementation
  *
  */

#ifndef QUARANTINE_LIST_H
#define QUARANTINE_LIST_H

#include <QtGui>

#include <FileTypeGuesser.hpp>
#include <FilePreview.hpp>
#include <HelpViewer.hpp>
#include <GlobalUri.hpp>
#include <string>

using namespace RainbruRPG::Gui;
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

    public slots:
      void storeFile(const QString&);
      void transferComplete(const QString&);
      void refresh(void);

    private slots:
      void treeSelectionChanged(void);
      void treeDoubleClicked(QTreeWidgetItem*,int);
      void filePreview(void);
      void fileAccept(void);
      void fileRefused(void);
      void showHelp(void);

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

      /** The files in this list are stored from a FTP client */
      QStringList storedFiles;
      /** A message to tell that at least one file is still in transfer */
      QLabel* labStillInTransfer;
    };
  }
}

#endif // QUARANTINE_LIST_H
