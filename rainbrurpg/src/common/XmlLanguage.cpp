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

/** \file XmlLanguage.cpp
  * Implements a class used to read and write languages configuration file
  *
  */

#include "XmlLanguage.hpp"

#include "Logger.hpp"
#include "GlobalUri.hpp"
#include "StringConv.hpp"

/** The default constructor
  *
  */
RainbruRPG::Options::xmlLanguage::xmlLanguage()
  :doc(NULL), 
   root(NULL), 
   lastUsed(""),
   defaultLang(""),
   mNbMessages(0)
{

  LOGI("xmlLanguage creation");

  Network::GlobalURI gu;
  this->filename=gu.getUserDirFile("languages.xml");
  refresh();

  languageList=new tLanguageList();

  if (loadDocument()){
    loadLastUsed();
    loadDefault();
    loadNbMessages();
    
    GTS_LIT(str1);
    // TRANSLATORS: The parameter is a language name.
    sprintf(str1, _("Last used language found : '%s'"), lastUsed);
    LOGI(str1);

    GTS_LIT(str2);
    // TRANSLATORS: The parameter is a language name.
    sprintf(str2, _("Default language found : '%s'"), defaultLang);
    LOGI(str2);

    treatAllLanguages();

    GTS_TIN(str3);
    // TRANSLATORS: The parameter is an integer (the list size).
    sprintf(str3, _("Language list size is '%d'"), languageList->size());
    LOGI(str3);

  }
  else{
    LOGE(_("Cannot load languages.xml"));

    GTS_LIT(str4);
    // TRANSLATORS: The parameter is an absolute file name (i.e. with paths).
    sprintf(str4,_("languages.xml absolute filename : '%s'"),filename.c_str());
    LOGE(str4)

    GTS_BIG(str5);
    // TRANSLATORS: The parameter is an error string
    sprintf(str5,_("TinyXml error description '%s'"),doc->ErrorDesc());
    LOGE(str5)
  }

}

/** The default destructor
  *
  */
RainbruRPG::Options::xmlLanguage::~xmlLanguage(){
  tLanguageList::const_iterator iter;
  // Iterate through list and output each element.
  for (iter=languageList->begin(); iter != languageList->end(); iter++){
    delete (*iter);
  }

  languageList->clear();
  delete languageList;
  languageList=NULL;

  //  delete doc;
  doc->~TiXmlDocument();
  doc=NULL;

  root=NULL;
}

/** Get a pointer to the loaded language list
  *
  * Do not keep this pointer. The list it pointed to will be deleted
  * in ~xmlLanguage.
  *
  * \return The pointer
  *
  */
RainbruRPG::Options::tLanguageList* 
RainbruRPG::Options::xmlLanguage::getLanguageList(){
  return languageList;
}


/** Refresh the xml document
  *
  * It calls loadDocument() to reload the xml file.
  *
  * \return \c false if the operation failed, otherwise \c true.
  */
bool RainbruRPG::Options::xmlLanguage::refresh(){

}

/** Loads the xml document
  *
  */
bool RainbruRPG::Options::xmlLanguage::loadDocument(){
  doc=new TiXmlDocument( this->filename.c_str() );
  bool ret=doc->LoadFile();
  root =doc->RootElement();

  return ret;
}

/** Loads the LastUsed node
  *
  */
void RainbruRPG::Options::xmlLanguage::loadLastUsed(){

  TiXmlNode* childNode = root->FirstChild( "LastUsed" );
  if (childNode){
    TiXmlElement* lu= childNode->ToElement();
    if (lu){
      lastUsed=lu->GetText();
    }
    else{
      lastUsed="";
    }

  }
  else{
    lastUsed="";
  }

}

/** Loads the default node
  *
  */
void RainbruRPG::Options::xmlLanguage::loadDefault(){
  TiXmlNode* childNode = root->FirstChild( "Default" );
  if (childNode){
    TiXmlElement* lu= childNode->ToElement();
    if (lu){
      defaultLang=lu->GetText();
    }
  }
}

/** Load the number of po message translated
  *
  */
void RainbruRPG::Options::xmlLanguage::loadNbMessages(){
  TiXmlNode* childNode = root->FirstChild( "PoMessagesNumber");
  if (childNode){
    TiXmlElement* lu= childNode->ToElement();
    if (lu){
      const char* txt=lu->GetText();
      mNbMessages = StringConv::getSingleton().stoi(txt);
    }
  }
}


/** Get all the language nodes and call TreatOneLanguage for each one
  *
  */
void RainbruRPG::Options::xmlLanguage::treatAllLanguages(){
  TiXmlNode* childNode = root->FirstChild( "Language" );
  if (childNode){
    TiXmlElement* child= childNode->ToElement();
    for( child; child; child=child->NextSiblingElement() ){
      treatOneLanguage(child);
    }

  }
  else{
    LOGW(_("Empty language list found"));
  }

}

/** Creates and feeds a LanguageListItem for a single language node
  *
  * The created LanguageListItem sin't push_back here. It is passed
  * to treatLanguageCountries to be pushed back later as each 
  * Language/Country pair is a new entry in the language list
  *
  */
void RainbruRPG::Options::xmlLanguage::treatOneLanguage(TiXmlElement* e){
  LanguageListItem lli;
  lli.setLanguageCode(getCommonCode(e));
  lli.setLanguageText(getCommonText(e));

  treatLanguageCountries(e, lli);
}

/** Treat all countries of a single language
  *
  */
void RainbruRPG::Options::xmlLanguage::
treatLanguageCountries(TiXmlElement* e, const LanguageListItem& it){
  TiXmlNode* childNode = e->FirstChild( "Country" );
  if (childNode){
    TiXmlElement* child= childNode->ToElement();
    for( child; child; child=child->NextSiblingElement() ){
      treatCountry(child, it);
    }

  }
  else{
    LOGW(_("Empty country list found"));
  }
}

/** Treat a single country
  *
  */
void RainbruRPG::Options::xmlLanguage::
treatCountry(TiXmlElement* e, const LanguageListItem& it){
  LanguageListItem* item=new LanguageListItem(it);

  item->setCountryCode(getCommonCode(e));
  item->setCountryText(getCommonText(e));
  item->setCompletePerCent(getCountryPerCent(e));

  // Test if this item is default
  if (strcmp(item->getLanguageCountry(), defaultLang)==0){
    item->setDefault(true);
  }

  // Test if this item is current
  if (strcmp(item->getLanguageCountry(), lastUsed)==0){
    item->setCurrent(true);
  }

  languageList->push_back(item);
}

/** Get the Code of a language or a country node
  *
  */
const char* RainbruRPG::Options::xmlLanguage::getCommonCode(TiXmlElement* e){
  TiXmlNode* code=e->FirstChild( "Code" );
  if (code){
    TiXmlElement* elem=code->ToElement();
    if (elem){
      return elem->GetText();
    }
    else{
      return "Unset";
    }
  }
  else{
    return "Unset";
  }
}

/** Get the Text of a language or a country node
  *
  */
const char* RainbruRPG::Options::xmlLanguage::getCommonText(TiXmlElement* e){
  TiXmlNode* code=e->FirstChild( "Text" );
  if (code){
    TiXmlElement* elem=code->ToElement();
    if (elem){
      return elem->GetText();
    }
    else{
      return "Unset";
    }
  }
  else{
    return "Unset";
  }
}

/** Get the CompletePerCent value of a country                       
  *
  */
float RainbruRPG::Options::xmlLanguage::getCountryPerCent(TiXmlElement* e){
  float tr_msg_nb;
  TiXmlNode* code=e->FirstChild( "TranslatedMessages" );
  if (code){
    TiXmlElement* elem=code->ToElement();
    if (elem){
       tr_msg_nb = StringConv::getSingleton().ctof(elem->GetText());
       return (double)(tr_msg_nb * 100.0f) / (double)mNbMessages;
    }
    else{
      return 0.0f;
    }
  }
  else{
    return 0.0f;
  }
}

/** Is LastUsed already set ?                     
  *
  * \return \c true if the LanguageSelector must be execute
  *
  */
bool RainbruRPG::Options::xmlLanguage::isLastUsedEmpty(){
  if (strcmp(lastUsed, "None")==0){
    return true;
  }
  else{
    return false;
  }
}
