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

/** \file logexportdialog.h
  * Declares a class to help user to export log content
  *
  * Modifications :
  * - 05 sep 2008 : Single file documentation
  *
  */

#ifndef LOG_EXPORT_DIALOG_H
#define LOG_EXPORT_DIALOG_H

#include <QDialog>
#include <QWidget>
#include <QLineEdit>

namespace RainbruRPG{
  namespace Server{

    /** A class to help user to export log content
      *
      * It primary use is to define the filename of the log.
      *
      */
    class LogExportDialog : public QDialog{
      Q_OBJECT
    public:
      LogExportDialog(QWidget* parent=0);
      ~LogExportDialog();

      const QString& getFilename();

    private slots:
      void changeFilename();

    private:
      void initFilename();

      /** The line edit receiving the log filename */
      QLineEdit* leFilename;
      /** The chosen filename */
      QString filename;
    };
  }
}

#endif // LOG_EXPORT_DIALOG_H
