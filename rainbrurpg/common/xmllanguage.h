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

#ifndef XML_LANGUAGE_H
#define XML_LANGUAGE_H

#include <list>
#include <string>

#include "languagelistitem.h"
#include "tinyxml.h"

namespace RainbruRPG{
  namespace Options{

    /** A STL list of language
      *
      */
    typedef std::list<LanguageListItem*> tLanguageList;

    /** A class used to read and write languages.xml configuration file
      *
      * The codes use in this file are from KDE (http://l10n.kde.org/).
      *
      * First, there is a LastUsed element. If it is empty, the 
      * LanguageSelector is shown at startup. The Default element
      * id used to tell the language the original game text are in. So,
      * for the Default language, we don't have to deal with any translation
      * tool.
      *
      * Then, there is language definitions (french, english...) and
      * for each language there \b must be at least a country. User can
      * select any Language/Country pair and for each pair a human readable
      * text is done.
      *
      * For any non-default pair, a CompletePerCent element gives the 
      * translation completion state. It is provided for unfinished 
      * translation. The default language/country pair does not need a 
      * CompletePerCent element as it always translate :)
      *
      * The LastUsed element of the xml files cannot be empty. If no language
      * was used before (first use), it should be set to None. An empty
      * LastUsed element may cause segfault.
      *
      */
    class xmlLanguage{
    public:
      xmlLanguage();
      ~xmlLanguage();

      RainbruRPG::Options::tLanguageList* getLanguageList();

      bool refresh();

      bool isLastUsedEmpty();

    private:

      bool loadDocument();
      void loadLastUsed();
      void loadDefault();
      void treatAllLanguages();
      void treatOneLanguage(TiXmlElement*);
      void treatLanguageCountries(TiXmlElement*, const LanguageListItem&);
      void treatCountry(TiXmlElement*, const LanguageListItem&);
      const char* getCommonCode(TiXmlElement*);          
      const char* getCommonText(TiXmlElement*);                       
      float getCountryPerCent(TiXmlElement*);

      /** The created list of language */
      tLanguageList* languageList;
      /** The filename of languages.xml */
      std::string filename;
      /** The global xml document pointer */
      TiXmlDocument *doc;
      /** A global pointer to the \c PlayerList xml node */
      TiXmlElement *root;
      /** The last used language */
      const char* lastUsed;
      /** The default language */
      const char* defaultLang;
    };
  }
}
#endif //XML_LANGUAGE_H
