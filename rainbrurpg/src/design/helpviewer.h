/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

/** \file helpviewer.h
  * Declares a basic HTML viewer
  *
  * Modifications :
  * - 13 aug 2008 : Single file documentation
  * - 19 jul 2007 : Creating the map to acess html anchors
  * - 18 jul 2007 : Moves to design/
  *
  */
#ifndef SERVER_HELP_VIEWER_H
#define SERVER_HELP_VIEWER_H

#include <string>
#include <QtGui>
#include <list>

namespace RainbruRPG{
  namespace Gui{

    /** A structure that define a link to a documentation
      *
      * We search for a key. The file is the html file to link the key
      * to and the anchor is a section.
      *
      */
    typedef struct{
      std::string key;    //!< The key we will search
      std::string page;   //!< The html file
      std::string anchor; //!< The html name anchor
    }tHelpViewerMapItem;

    /** A list of map item
      *
      */
    typedef std::list<tHelpViewerMapItem*> tHelpViewerMap;

    /** A basic HTML viewer used to show the html format of the texinfo
      * manual
      *
      * This class is implemented in the design/ library. It can be used 
      * in the server and the editor.
      *
      */
    class HelpViewer : public QDialog{
      Q_OBJECT
    public:
      HelpViewer(const std::string& key="", QWidget* parent=0);
      ~HelpViewer();

    private:
      void feedMap();
      void addMapItem(const std::string&, const std::string&, 
		      const std::string& );

      std::string getUrlfromKey(const std::string&);
      tHelpViewerMapItem* getItemfromKey(const std::string&);

      /** The home url
        *
	* It is the html file location, where the help start. It is defined 
	* when the constructor is called. If the \c key string is empty, this
	* is the index.html page, if a key is given, we search in the map
	* for the page and anchor values.
	*
	* \sa HelpViewer::HelpViewer(), map
	*
	*/
      QUrl home;

      /** The key driven map
        *
	* It defines a map of key/page/anchor to access html page easilier.
	*
	*/
      tHelpViewerMap* map;
    };
  }
}

#endif // SERVER_HELP_VIEWER_H
