/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file XmlOptions.hpp
  * Declares a class used to store client's options
  *
  * Modifications :
  * - 01 may 2009 : Strings are getetxt compliant
  * - 11 aug 2008 : Single file documentation
  *
  */

#ifndef XML_OPTIONS_H
#define XML_OPTIONS_H

#include <list>
#include <string>
#include "Logger.hpp"
#include "tinyxml.h"
#include "OptionManager.hpp"

#include "RainbruDef.hpp" // For the gettext stuff

namespace RainbruRPG {
  namespace Options{

    /** A std list of snapshot name */
    typedef std::list<const char*> tSnapshotList;

    /** Used to store client options
      *
      */
    class xmlOptions{
    public:
      xmlOptions();
      ~xmlOptions();
      bool refresh();

      bool saveSnapshot(const char*, tOptionPanelList* );
      void loadSnapshot(const char*, tOptionPanelList*);
      void deleteSnapshot(const char*);

      tSnapshotList* getSnapshotList();

      bool isSnapShotExists(const char*);

      void setLastUse(const char*);
      const char* getLastUse();


    private:
      bool loadDocument();

      void savePanel(TiXmlElement*, OptionPanel*);
      void saveButton(TiXmlElement*, OptionButton*);
      void saveAttribute(TiXmlElement*, OptionAttribute*);

      void loadPanel(TiXmlElement*, OptionPanel*);
      void loadButton(TiXmlElement*, OptionButton*);
      void loadAttribute(TiXmlElement*, OptionAttribute* );

      TiXmlElement* getSnapshotNode(const char* );

      /** The global xml document pointer */
      TiXmlDocument *doc;
      /** A global pointer to the \c PlayerList xml node */
      TiXmlElement *root;

      /** The filename of the xml file use to store options */
      std::string filename;
      /** Says if the document was correctly or not */
      bool correctlyLoaded;
 
    };
  }
}

#endif // XML_OPTIONS_H

