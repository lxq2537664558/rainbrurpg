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
 * - 18 jul 2007 : Moves to design/
 *
 */
#ifndef SERVER_HELP_VIEWER_H
#define SERVER_HELP_VIEWER_H

#include <QtGui>

namespace RainbruRPG{
  namespace Server{

    /** A basic HTML viewer used to show the html format of the texinfo
      * manual
      *
      */
    class ServerHelpViewer : public QDialog{
      Q_OBJECT
    public:
      ServerHelpViewer(QWidget* parent=0);
      ~ServerHelpViewer();
    private:
      /** The home url
        *
	* It is the index.html location, where the help start. If a home
	* button is created, this URL will be linked to.
	*
	*/
      QUrl home;
    };
  }
}

#endif // SERVER_HELP_VIEWER_H
