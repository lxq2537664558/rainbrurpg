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

#include "xmlaccountlist.h"

/** The default constructor
  *
  */
RainbruRPG::Network::Ident::xmlAccountList::xmlAccountList(){
  LOGI("Creation xmlAccountList");
  refresh();

}

/** Get the xml file and load it
  *
  * \return \c true if no error occured
  *
  */
bool RainbruRPG::Network::Ident::xmlAccountList::refresh(){
  LOGI("xmlAccountList refresh function called");
  bool ret;

  GlobalURI gu;
  filename=gu.getXmlAdress("players.xml");

  bool success= CurlFileToXml::perform();

  if (success){
    loadDocument(this);
    ret=true;
  }
  else{
    long resp=CurlFileToXml::getServerResponse();
    LOGE("An error occured while getting xmlAccountList");
    cout << "Last server response : " << resp << endl;
    correctlyLoaded=false;
    ret=false;
  }

  return ret;
}


/** The default destructor
  *
  *
  */
RainbruRPG::Network::Ident::xmlAccountList::~xmlAccountList(){
  delete doc;
  doc=NULL;
  root=NULL;
}

/** Loads the xml document or creates it if it does not exist
  *
  * \param cgf The curl object use to get the file
  *
  */
void RainbruRPG::Network::Ident::xmlAccountList::loadDocument(
                                         CurlFileToXml* cgf){

  doc=cgf->getXmlDocument();
  if (doc){
    root =doc->RootElement();
    correctlyLoaded=true;
    LOGI("xmlAccountList correctly loaded"); 
  }
  else{
    correctlyLoaded=false;
    LOGW("An error occured while getting xmlAccountList");
  }
}

/** Returns the player list from the xml file
  *
  * This function is used by the AccountList class to get the
  * playerlist. This list is then iterates and we can feed the list of
  * player names.
  *
  * \return A list of player
  */
RainbruRPG::Gui::tAccountList* RainbruRPG::Network::Ident::
                                  xmlAccountList::getAccountList(){

  tAccountList* pl= new tAccountList();

  if (doc){
    TiXmlHandle docHandle( doc );
    TiXmlElement* child = docHandle.FirstChild( "PlayerList" )
      .FirstChild( "Player" ).Element();
    
    for( child; child; child=child->NextSiblingElement() ){
      
      tAccountListItem *it=new tAccountListItem();
      
      it->name=         getXMLTextFromName(child, "Name");
      it->password=     getXMLTextFromName(child, "Pwd");
      it->mail=         getXMLTextFromName(child, "Mail");
      it->validationId= getXMLTextFromName(child, "ConfirmId");

      // Get the creation timestamp
      xmlTimestamp xts;
      it->creation= xts.getCTimeS("creation", child);

      // Get the confirmation timestamp
      it->confirm= xts.getCTimeS("confirm", child);
      
      LOGCATS("Account : name='");
      LOGCATS(it->name);
      LOGCATS("' confirm='");
      LOGCATS(it->confirm.c_str());
      LOGCATS("'");
      LOGCAT();

      const char* bl=getXMLTextFromName(child, "Black");
      if (strcmp( bl, "Yes")==0)
	it->blacklist=true;
      else
	it->blacklist=false;
      
      pl->push_back(it);
    }
    return pl;
  }
  else{
    LOGW("Cannot get a valid root element, account list will be NULL");
    return NULL;
  }
}

/** Test if a player's name is already in use
  *
  * This function is used to test the existence of a player before
  * adding a new one.
  *
  * \param n The player's name to test.
  *
  * \return true if the player's name is already existing, otherwise false
  */
bool RainbruRPG::Network::Ident::xmlAccountList::isAccountExisting(
                                                   const char* n){
  tAccountList::const_iterator iter;

  tAccountList* pl=this->getAccountList();
  
  if (pl){
    for (iter=pl->begin(); iter != pl->end(); iter++){
      if (strcmp(n, (*iter)->name )==0){
	return true;
      }
    }
  }

  return false;
}

/** Return the list of note of the given player
  *
  * \param playerName the player's name.
  * 
  * \return a pointer to a tNoteList STL list.
  */
tNoteList* RainbruRPG::Network::Ident::xmlAccountList::getAccountNoteList(
				      const char* playerName){

  tNoteList* list=new tNoteList();
  TiXmlText* textNode;
  const char* nodeName;
  tNoteListItem* i1;

  TiXmlHandle docHandle( doc );
  TiXmlElement* child = docHandle.FirstChild( "PlayerList" )
                                 .FirstChild( "Player" ).Element();

  for( child; child; child=child->NextSiblingElement() ){

    nodeName= getXMLTextFromName(child, "Name");
    if (strcmp( playerName, nodeName )==0){

      TiXmlHandle docHandle( child );
      TiXmlElement* noteChild = docHandle.FirstChild( "Note" ).Element();

      for( noteChild; noteChild; noteChild=noteChild->NextSiblingElement() ){
	i1=new tNoteListItem();
	i1->title=noteChild->Attribute("title");

	// Cause a segfault if omitted
	if (noteChild->FirstChild()){
	  textNode=noteChild->FirstChild()->ToText();
	  if (textNode)
	    i1->text=textNode->Value();
	  else
	    LOGI("A note has no text");
	}
	else
	  LOGI("A note element has no child");

	list->push_back(i1);

      }
    }
  }

  return list;
}

/** Test if player's note already exists
  *
  * \param playerName The player's name.
  * \param noteTitle The title of the note to test.
  *
  * \return \c true if the note already exists, false if we can safely
  *         create the given note.
  */
bool RainbruRPG::Network::Ident::xmlAccountList::isAccountNoteExisting(
			     const char* playerName, const char* noteTitle){

  bool ret=false;

  const char* nodeName;
  const char* titleAttrb;

  TiXmlHandle docHandle( doc );
  TiXmlElement* child = docHandle.FirstChild( "PlayerList" )
                                 .FirstChild( "Player" ).Element();

  for( child; child; child=child->NextSiblingElement() ){

    nodeName= getXMLTextFromName(child, "Name");
    // We have the good player
    if (strcmp( playerName, nodeName )==0){

      TiXmlHandle docHandle( child );
      TiXmlElement* noteChild = docHandle.FirstChild( "Note" ).Element();

      for( noteChild; noteChild; noteChild=noteChild->NextSiblingElement() ){
	titleAttrb=noteChild->Attribute("title");

	// A note with this title already exists
	if (strcmp( noteTitle, titleAttrb )==0){
	  ret=true;
	  break;
	}
      }
    }
  }
  return ret;
}

/** Test if the mail adress is valid
  *
  * The mail adress can not be empty and must contain \c '@' and \c '.' .
  *
  * \return \c true if the mail adress is valid
  *
  */
bool RainbruRPG::Network::Ident::xmlAccountList::isValidMail(const char* mail){

  bool ret=true;

  if (strlen(mail)==0)
    ret=false;

  if (strstr( mail, "@" )==NULL)
    ret=false;

  if (strstr( mail, "." )==NULL)
    ret=false;

  return ret;
}

/** Tests if a mail is already existing
  *
  * \c true if the given mail is already in use
  *
  */
bool RainbruRPG::Network::Ident::xmlAccountList::isMailExisting(const char* mail){

  tAccountList::const_iterator iter;

  tAccountList* pl=this->getAccountList();
  
  if (pl){
    for (iter=pl->begin(); iter != pl->end(); iter++){
      if (strcmp(mail, (*iter)->mail )==0){
	return true;
      }
    }
  }

  return false;
}

/** Test if a mail is confirmed 
  *
  * \return \c true if the mail adress of this player is confirmed
  *
  */
bool RainbruRPG::Network::Ident::xmlAccountList::isMailConfirmed(
					 const char* playerName){

  tAccountList::const_iterator iter;

  tAccountList* pl=this->getAccountList();
  
  if (pl){
    for (iter=pl->begin(); iter != pl->end(); iter++){

      // We have the good player
      if (strcmp(playerName, (*iter)->name )==0){

	// No confirmation date
	if ((*iter)->confirm.empty())
	  return false;
	else
	  return true;

      }
    }
  }
}

/** Return a player by his name
  *
  * \param playerName The name of the wanted player
  *
  * \return The player if found or \c NULL if the player does not exist
  *
  */
RainbruRPG::Gui::tAccountListItem* RainbruRPG::Network::Ident::
              xmlAccountList::getAccount(const char* playerName){

  bool found=false;

  tAccountList::const_iterator iter;

  tAccountList* pl=this->getAccountList();
  
  if (pl){
    for (iter=pl->begin(); iter != pl->end(); iter++){

      // We have the good player
      if (strcmp(playerName, (*iter)->name )==0){
	found=true;
	return (*iter);

      }
    }
  }

  if (!found)
    return NULL;
}
