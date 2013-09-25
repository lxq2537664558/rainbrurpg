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

/** \file configdialog.h
  * Declares the server configuration dialog
  *
  * Modifications :
  * - 30 aug 2008 : Single file documentation
  * - 27 jun 2007 : Adding UniqueName
  * - 29 may 2007 : Creation TabControl
  *
  */
#ifndef CONFIG_DIALOG_H
#define CONFIG_DIALOG_H

#include <QtGui>
#include "serverconfiguration.h"

/** The default server port  */
#define DEFAULT_SERVER_PORT 1234
/** The default maximum number of clients allowed */
#define DEFAULT_MAX_CLIENTS 20

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
    class ConfigDialog : public QDialog{
      Q_OBJECT
	
	public:
      ConfigDialog( ServerConfiguration*, QWidget *parent = 0);
      ~ConfigDialog();

    private:
      void initValues(void);

      /** The server configuration */
      ServerConfiguration* serverConfig;
      /** The line edit containing the server's name */
      QLineEdit* leName;
      /** The text edit widget containing the server's description */
      QTextEdit* teDesc;
      /** The playMode check box */
      QCheckBox* cbPlay;
      /** The editMode check box */
      QCheckBox* cbEdit;
      /** The floodMode check box */
      QCheckBox* cbFlood;
      /** The server's port spin box*/
      QSpinBox* sbPort;
      /** The server's FTP control channel port spin box*/
      QSpinBox* sbFtpPort;
      /** The maximum client spin box*/
      QSpinBox* sbCli;
      /** Is there a text in technote */
      QLabel* showTechNote;
      /** The IP adress LineEdit */
      QLineEdit* leIp;

      /** The database hostname lineedit */
      QLineEdit* leDbHost;
      /** The database name lineedit */
      QLineEdit* leDbName;
      /** The database role lineedit */
      QLineEdit* leDbRole;
      /** The database password lineedit */
      QLineEdit* leDbPwd;
      /** The label used to show the server's type description */
      QLabel* labTypeDescription; 
      /** The buttonGroup that contains the type radio buttons */
      QButtonGroup* typeButtonsGroup;
      /** The QLabel that contains the unique name */
      QLabel* uName;

    private slots:
      void descriptionChanged();
      void nameChanged();
      void playModeChanged(int);
      void editModeChanged(int);
      void floodModeChanged(int);
      void portChanged(int);
      void ftpPortChanged(int);
      void maxClientChanged(int);
      void ipAddressChanged(const QString&);

      void hostNameChanged(const QString&);
      void dbNameChanged(const QString&);
      void UserNameChanged(const QString&);
      void passwordChanged(const QString&);

      void controls();
      void serverTypeChanged(int);
    };
  }
}
#endif // CONFIG_DIALOG_H
