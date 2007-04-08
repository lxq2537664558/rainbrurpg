/*
 *  Copyright 2006 Jerome PASQUIER
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

#ifndef LANGUAGE_LIST_ITEM_H
#define LANGUAGE_LIST_ITEM_H

#include "stringconv.h"

using namespace RainbruRPG::Core;

namespace RainbruRPG{
  namespace Options{

    /** A class defining a language
      *
      * It represents a Language/Country pair.
      * The language configuration file is config/languages.xml
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
	* It is a 2 character code in lower case.
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
	* It is set by xmlLanguage
	*
	*/
      bool defaultLanguage;
      /** Is it the current language ?
        *
	* It is set by xmlLanguage
	*
	*/
      bool currentLanguage;
    };

  }
}

#endif // LANGUAGE_LIST_ITEM_H
