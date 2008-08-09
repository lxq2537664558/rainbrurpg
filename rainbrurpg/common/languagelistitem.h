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

/** \file languagelistitem.h
  * Declares a class defining a language
  *
  * Modifications :
  * - 14 oct 2007 : Documentation update
  *
  */

#ifndef LANGUAGE_LIST_ITEM_H
#define LANGUAGE_LIST_ITEM_H

#include "stringconv.h"

using namespace RainbruRPG::Core;

namespace RainbruRPG{
  namespace Options{

    /** A class defining a language.
      *
      * It represents a Language/Country pair, used in tLanguageList.
      * These values is shown in \ref RainbruRPG::Gui::LanguageSelector
      * "LanguageSelector" to provides a language selection for the user.
      *
      * \sa tLanguageList, \ref RainbruRPG::Gui::LanguageSelector
      * "LanguageSelector".
      *
      * \section LanguageListItem_design_sec Design
      *
      * Typically, a language (i.e. english) can be spoke in many countries
      * with some local particularities (U.S. vs England). Wich explains
      * why a language is defined by a Language/Country pair. This class
      * provides this pair. 
      * 
      * Each language is identified by a 2-letters code and a description 
      * text. Each country is also identified by a code and a description.
      * The difference is that language code is only lower case and country 
      * code is only upper case. So, you can identify a Language/Country pair
      * by a single text identifier where country code is separated from
      * the language code by a underscore : \c en_US.
      *
      * This class provide a completion percent to provide to the user
      * the ability to view if its prefered language translation is
      * ended or in-progress.
      *
      * \section LanguageListItem_files_sec Configuration files
      *
      * The language configuration file is <em>config/languages.xml</em> and
      * the xmlLanguage class is responsible of its loading.
      *
      */
    class LanguageListItem{
    public:
      LanguageListItem();
      LanguageListItem(const LanguageListItem&);
      ~LanguageListItem();

      /** The "less than" operator as needed by the stl sort algorythm */
      bool operator< (const LanguageListItem& right) const;

      void setLanguageCode(const char*);
      const char* getLanguageCode();
      void setCountryCode(const char*);
      const char* getCountryCode();
      void setLanguageText(const char*);
      const char* getLanguageText();
      void setCountryText(const char*);
      const char* getCountryText();

      void setCompletePerCent(const char*);
      void setCompletePerCent(float);
      float getCompletePerCent();

      void setDefault(bool);
      bool isDefault();
      void setCurrent(bool);
      bool isCurrent();

      const char* getComboText();
      const char* getLanguageCountry();

    private:
      /** The code of the language
        *
	* It is a 2 characters code in lower case.
	*
	*/
      const char* languageCode;
      /** The code of the country
        *
	* It is a 2 character code in upper case.
	*
	*/
      const char* countryCode;
      /** The human readable name of the language
        *
	*/
      const char* languageText;
      /** The human readable name of the country
        *
	*/
      const char* countryText;
      /** The complete percent of this translation
        *
	* if it is 100.00f, the translation for this language is up to date.
	*
	*/
      float completePerCent;
      /** Is it the default language ?
        *
	* It is set by xmlLanguage.
	*
	*/
      bool defaultLanguage;
      /** Is it the current language ?
        *
	* It is set by xmlLanguage.
	*
	*/
      bool currentLanguage;
    };

  }
}

#endif // LANGUAGE_LIST_ITEM_H
