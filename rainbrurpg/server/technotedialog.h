/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file technotedialog.h
  * Declares the technical note modification dialog
  *
  * Modifications :
  * - 05 sep 2008 : Single file documentation
  *
  */

#ifndef TECH_NOTE_DIALOG_H
#define TECH_NOTE_DIALOG_H

#include <QtGui>
#include "serverconfiguration.h"

namespace RainbruRPG{
  namespace Server{
    /** The RainbruRPG server configuration dialog
      *
      * It is only the graphic part of the server configuration. The data
      * are stored in a ServerConfiguration instance.
      *
      * We must pass a ServerConfiguration pointer in the constructor to be
      * able to modify it. 
      *
      */
    class TechNoteDialog : public QDialog{
      Q_OBJECT
	
    public:
      TechNoteDialog( ServerConfiguration*, QWidget *parent = 0);
      ~TechNoteDialog();

    private:
      void initValues(void);

      /** The server configuration */
      ServerConfiguration* serverConfig;
      /** The technical note text edit widget */
      QTextEdit* teTechNote;

    private slots:
      void techNoteChanged();
    };
  }
}
#endif // TECH_NOTE_DIALOG_H
