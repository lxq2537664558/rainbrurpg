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

/** \file languagelistitem.cpp
  * Implements a class defining a language
  *
  */

#include "languagelistitem.h"


/** The default constructor
  *
  * It initializes all local value at 0 or an empty string. \ref defaultLanguage
  * and \ref currentLanguage are set to \c false.
  *
  * \note A call to \ref getComboText() on a default language list item
  *       will not give an empty string.
  *
  */
RainbruRPG::Options::LanguageListItem::LanguageListItem(){
  languageCode="";
  countryCode="";
  languageText="";
  countryText="";
  completePerCent=0.0f;
  defaultLanguage=false;
  currentLanguage=false;

}

/** The copy constructor
  *
  * Set the local variables values as the LanguageListItem passed as 
  * parameter.
  *
  * \param l The item to get initial values from.
  *
  */
RainbruRPG::Options::LanguageListItem::
LanguageListItem(const LanguageListItem& l){
  languageCode=l.languageCode;
  countryCode=l.countryCode;
  languageText=l.languageText;
  countryText=l.countryText;
  completePerCent=l.completePerCent;
  defaultLanguage=l.defaultLanguage;
  currentLanguage=l.currentLanguage;

}

/** The default destructor
  *
  */
RainbruRPG::Options::LanguageListItem::~LanguageListItem(){

}

/** Set the language code of this language
  *
  * \param code The language code
  *
  */
void RainbruRPG::Options::LanguageListItem::
setLanguageCode(const char* code){
  languageCode=code;
}

/** Get the language code of this language
  *
  * \return the language code
  *
  */
const char* RainbruRPG::Options::LanguageListItem::getLanguageCode(){
  return languageCode;
}

/** Set the country code of this language
  *
  * \param code The country code
  *
  */
void RainbruRPG::Options::LanguageListItem::setCountryCode(const char* code){
  countryCode=code;
}

/** Get the country code of this language
  *
  * \return the country code
  *
  */
const char* RainbruRPG::Options::LanguageListItem::getCountryCode(){
  return countryCode;
}

/** Set the text of this language
  *
  * \param text The language text
  *
  */
void RainbruRPG::Options::LanguageListItem::setLanguageText(const char* text){
  languageText=text;
}

/** Get the text of this language
  *
  * \return the language text
  *
  */
const char* RainbruRPG::Options::LanguageListItem::getLanguageText(){
  return languageText;
}

/** Set the counttry text 
  *
  * \param text The country text
  *
  */
void RainbruRPG::Options::LanguageListItem::setCountryText(const char* text){
  countryText=text;
}

/** Get the country text
  *
  * \return the country text
  *
  */
const char* RainbruRPG::Options::LanguageListItem::getCountryText(){
  return countryText;
}

/** Set the completePercent value
  *
  * The conversion is assumed by \ref RainbruRPG::Core::StringConv::ctof().
  *
  * \param val The new completePercent value in string format
  *
  */
void RainbruRPG::Options::LanguageListItem::
setCompletePerCent(const char* val){
  completePerCent=StringConv::getSingleton().ctof(val);
}

/** Set the completePercent value
  *
  * \param val The new completePercent value in float format
  *
  */
void RainbruRPG::Options::LanguageListItem::setCompletePerCent(float val){
  completePerCent=val;
}

/** Get the completePercent value
  *
  * \return the completePercent value
  *
  */
float RainbruRPG::Options::LanguageListItem::getCompletePerCent(){
  return completePerCent;
}

/** Get the LanguageSelector's combobox text
  *
  * \return the value used to feed LanguageSelector combobox
  *
  */
const char* RainbruRPG::Options::LanguageListItem::getComboText(){
  std::string s=languageText;
  s+=" (";
  s+=countryText;
  s+=") ";

  if (!defaultLanguage){
    s+=StringConv::getSingleton().ftos(completePerCent);
    s+="% ";
  }

  if (defaultLanguage)
    s+="default ";

  if (currentLanguage)
    s+="current ";

  return s.c_str();
}

/** Set if this item is the default language
  *
  * \param b The new default value
  *
  */
void RainbruRPG::Options::LanguageListItem::setDefault(bool b){
  defaultLanguage=b;
}

/** Is this language set default
  *
  * \return \c true if it is the default language
  *
  */
bool RainbruRPG::Options::LanguageListItem::isDefault(){
  return defaultLanguage;
}

/** Set if this item is the current language
  *
  * \param b The new current value
  *
  */
void RainbruRPG::Options::LanguageListItem::setCurrent(bool b){
  currentLanguage=b;
}

/** Is this language the current one
  *
  * \return \c true if it is the current language
  *
  */
bool RainbruRPG::Options::LanguageListItem::isCurrent(){
  return currentLanguage;
}

/** Get the LanguageCountry string
  *
  * If \c LL is the language and \c CC is the country, the value returned
  * will be \c LL_CC.
  *
  * \return The LanguageCountry string
  *
  */
const char* RainbruRPG::Options::LanguageListItem::getLanguageCountry(){
  std::string s=languageCode;
  s+="_";
  s+=countryCode;

  return s.c_str();
}
