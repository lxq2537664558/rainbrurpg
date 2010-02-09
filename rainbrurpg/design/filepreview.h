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

/** \file filepreview.h
  * Declares a class that creates a dialog used to preview a file.
  *
  * Modifications :
  * - 13 aug 2008 : Single file documentation
  * - 18 jul 2007 : Starting implementation
  *
  */


#ifndef _FILE_PREVIEW_H_
#define _FILE_PREVIEW_H_

#include <QtGui>

#include <string>

#include "filetypeguesser.h"

namespace RainbruRPG{
  namespace Gui{

    /** A Qt previewer widget
      *
      * This class creates a dialog used to preview a file.
      *
      * \section filetype_sec File type
      *
      * Before we preview the file, we determine the file type. There is
      * two solution :
      * - try to get a mime-type;
      * - use the file extension.
      *
      * We use two dispatcher : mimeDispatcher() and extDispatcher(). If one
      * discover a usable file type, it returns true and launch the 
      * appropriate viewer widget.
      *
      */
    class FilePreview : public QDialog{
      Q_OBJECT
    public:
      FilePreview(const QString&, QWidget* parent=0);
      ~FilePreview();

      bool mimeDispatcher();
      bool extDispatcher();

    private:
      void imagePreview();
      void textPreview();
      void htmlPreview();
      void showMessage(const QString&);

      /** The filename in Qt format */
      QString filename;
      /** The filename in STL format */
      std::string strFilename;
      /** A help label, shown if the file cannot be previewed */
      QLabel* help;
    };

  }
}

#endif // _FILE_PREVIEW_H_
