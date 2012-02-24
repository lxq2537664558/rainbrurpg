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

/** \file xmloptions.cpp
  * Implements a class used to store client's options
  *
  */

#include "xmloptions.h"
#include "config.h"
#include "GlobalUri.hpp"

/** The default constructor
  *
  * It sets the filename field to \c ../config/options.xml and calls
  * the refresh method.
  *
  */
RainbruRPG::Options::xmlOptions::xmlOptions(){

  Network::GlobalURI gu;
  this->filename=gu.getUserDirFile("options.xml");
  doc=NULL;
  refresh();
}

/** The default destructor
  *
  * It deletes doc of necessary.
  */
RainbruRPG::Options::xmlOptions::~xmlOptions(){
  if (doc)
    delete doc;

  doc=NULL;
}

/** Loads the xml document 
  *
  * \return \c true if loadDocument is successfull
  *
  */
bool RainbruRPG::Options::xmlOptions::refresh(){
  bool ret=false;

  if (loadDocument()){
    ret=true;
  }
  else{
    GTS_MID(str);
    // TRANSLATORS: The parameter is a file name.
    sprintf(str, _("Cannot load the XML options from file %s"), 
	    this->filename.c_str());
    LOGE(str);
  }
  return ret;
}

/** Loads the xml document
  *
  * It asks TinyXml to loads the document pointed by filename
  *
  * \return \c true if successfull
  *
  */
bool RainbruRPG::Options::xmlOptions::loadDocument(){
  doc=new TiXmlDocument( this->filename.c_str() );
  bool ret=doc->LoadFile();
  root =doc->RootElement();

  return ret;
}

/** Saves the given snapshot with the current name 
  *
  * This function is called by the OptionManager when it may save
  * a snapshot.
  *
  * \param snapName The name of the snapshot
  * \param panels The list of panels to save
  *
  * \return \c true if the operation is succesfull, \c false if
  *         an error occured
  */
bool RainbruRPG::Options::xmlOptions::
saveSnapshot(const char* snapName, tOptionPanelList* panels){
  LOGI("Saving snapshot");

  TiXmlElement *snapNode;

  // Remove it if it already exists
  if (isSnapShotExists(snapName)){
    snapNode=getSnapshotNode(snapName);

    // Remove all childs
    snapNode->Clear();
  }
  else{
    // SnapShot element
    snapNode=new TiXmlElement( "Snapshot" );
    snapNode->SetAttribute("name", snapName );

    root->LinkEndChild( snapNode );
  }

  // Iterate though panels
  tOptionPanelList::const_iterator iter;
  for (iter=panels->begin(); iter != panels->end(); iter++){
    savePanel( snapNode, (*iter) );
  }

  doc->SaveFile();
  return true;
}

/** Save an option panel
  * 
  * Creates a new xml node for the given OptionPanel and add it as 
  * a child to the given TiXmlElement
  *
  * \param panel The OptionPanel to save
  * \param elem The xml node thet panel will be added to
  *
  */
void RainbruRPG::Options::xmlOptions::
savePanel(TiXmlElement* elem, OptionPanel* panel){
  TiXmlElement* panelNode=new TiXmlElement( "Panel" );
  panelNode->SetAttribute("name", panel->getName() );


  TiXmlNode* ret=elem->LinkEndChild( panelNode );

  // Iterate though panels
  tOptionButtonList::const_iterator iter;
  tOptionButtonList* lst =panel->getButtonList();

  for (iter=lst->begin(); iter != lst->end(); iter++){
    saveButton( panelNode, (*iter) );
  }

  if (!ret){
    LOGW(_("An error occured while saving panel to XML option file."));
  }
}

/** Save an option button
  * 
  * Creates a new xml node for the given OptionButton and add it as 
  * a child to the given TiXmlElement
  *
  * \param button The OptionButton to save
  * \param elem The xml node thet panel will be added to
  *
  */
void RainbruRPG::Options::xmlOptions::
saveButton(TiXmlElement* elem, OptionButton* button){

  TiXmlElement* btnNode=new TiXmlElement( "Button" );
  btnNode->SetAttribute("name", button->getName() );


  TiXmlNode* ret=elem->LinkEndChild( btnNode );

  // Iterate though panels
  tOptionAttributeList::const_iterator iter;
  tOptionAttributeList* lst=button->getAttributeList();

  for (iter=lst->begin(); iter != lst->end(); iter++){
    saveAttribute( btnNode, (*iter) );
  }

}

/** Save an option attribute
  * 
  * Creates a new xml node for the given OptionAttribute and add it as 
  * a child to the given TiXmlElement
  *
  * \param attrb The OptionAttribute to save
  * \param elem The xml node thet panel will be added to
  *
  */
void RainbruRPG::Options::xmlOptions::
saveAttribute(TiXmlElement* elem, OptionAttribute* attrb){
  TiXmlElement* btnNode=new TiXmlElement( "Attribute" );
  btnNode->SetAttribute("name", attrb->getName() );

  TiXmlText* textNode=new TiXmlText( attrb->getValueStr() );
  btnNode->LinkEndChild( textNode );
  elem->LinkEndChild( btnNode );
}

/** Get the list of existing snapshots
  *
  * \return NULL if the list is empty or if an error occured.
  *
  */
RainbruRPG::Options::tSnapshotList* 
RainbruRPG::Options::xmlOptions::getSnapshotList(){


  tSnapshotList* lst=new tSnapshotList();

  if (root){
    TiXmlNode* childNode = root->FirstChild( "Snapshot" );
    if (childNode){
      TiXmlElement* child= childNode->ToElement();

      for( child; child; child=child->NextSiblingElement() ){
	lst->push_back(child->Attribute("name"));
      }
    }
    else{
      LOGW(_("Empty snapshot list found in XML options file."));
      return NULL;
    }
  }
  else{
    LOGE(_("Cannot get a valid root element for XML options snapshot list."));
    return NULL;
  }

  return lst;
}

/** Tests if a snapshot name is already in use
  *
  * \param c The name to test
  *
  * \return \c true if a snapshot with the given name already exists,
  *         \c false otherwise
  *
  */
bool RainbruRPG::Options::xmlOptions::isSnapShotExists(const char* c){
  bool ret=false;

  tSnapshotList::const_iterator iter;
  tSnapshotList* snapList=getSnapshotList();

  // populate the combo box
  if (snapList){
    for (iter=snapList->begin(); iter != snapList->end(); iter++){
      if (strcmp(c, (*iter))==0)
	ret=true;
    }
  }

  return ret;
}

/** Get the xml node of the named snapshot
  *
  * \param n The name of the snapshot you want
  *
  * \return the snapshot xml node or \c NULL if not found
  *
  */
TiXmlElement* RainbruRPG::Options::xmlOptions::
getSnapshotNode(const char* n){

  TiXmlElement* ret=NULL;

  TiXmlNode* childNode = root->FirstChild( "Snapshot" );
  if (childNode){
    TiXmlElement* child= childNode->ToElement();

    for( child; child; child=child->NextSiblingElement() ){
      const char* snapName=child->Attribute("name");
      if (strcmp(n, snapName)==0){
	ret=child;
      }
    }
  }
  return ret;
}


/** Feeds the given panels with the named snapshot
  *
  * \param panels The panel list to feed
  * \param name The nalme of the snapshot to load
  * 
  */
void RainbruRPG::Options::xmlOptions::
loadSnapshot(const char* name, tOptionPanelList* panels){

  TiXmlElement* snapNode= getSnapshotNode(name);

  if (snapNode){

  
    // Iterate through list of panels
    tOptionPanelList::const_iterator iter;
    for (iter=panels->begin(); iter != panels->end(); iter++){

      loadPanel(snapNode, (*iter));
    }

  }
}

/** Loads a panel from the xml file
  *
  * For a panel, loads all buttons. First, we get the xml element
  * of the panel (by its name), then, we call loadButton(panelXmlNode,
  * button) for each button.
  *
  * \param panel The panel that will be feed
  * \param snapNode the parent snapshot xml node
  */
void RainbruRPG::Options::xmlOptions::
loadPanel(TiXmlElement* snapNode, OptionPanel* panel){

    
  // Get the xml node of the panel
  TiXmlNode* childNode = snapNode->FirstChild( "Panel" );
  if (childNode){
    TiXmlElement* child= childNode->ToElement();

    // search the good panel    
    for( child; child; child=child->NextSiblingElement() ){
      const char* panelName=child->Attribute("name");

      // We have the good panel (xml)
      if (strcmp(panelName, panel->getName())==0){
	
	tOptionButtonList* buttons=panel->getButtonList();
	tOptionButtonList::const_iterator iter2;

	// treat each button
	for (iter2=buttons->begin(); iter2 != buttons->end(); iter2++){
	  
	  loadButton(child, (*iter2));
	  
	}
      }
    }
  }
}

/** Loads a button from the xml file
  *
  *
  * \param button The button that will be feed
  * \param panelNode the parent panel xml node
  */
void RainbruRPG::Options::xmlOptions::
loadButton(TiXmlElement* panelNode, OptionButton* button){

  // Get the xml node of the panel
  TiXmlNode* childNode = panelNode->FirstChild( "Button" );
  if (childNode){
    TiXmlElement* child= childNode->ToElement();

    // search the good button
    for( child; child; child=child->NextSiblingElement() ){
      const char* buttonName=child->Attribute("name");

      // We have the good button (xml)
      if (strcmp(buttonName, button->getName())==0){


	tOptionAttributeList* attrbs=button->getAttributeList();
	tOptionAttributeList::const_iterator iter2;

	// treat each button
	for (iter2=attrbs->begin(); iter2 != attrbs->end(); iter2++){
	  
	  loadAttribute(child, (*iter2));
	  
	}
      }
    }
  }
}

/** Loads an attribute from the xml file
  *
  * \param attrb The attribute that will be feed
  * \param buttonNode the parent button xml node
  */
void RainbruRPG::Options::xmlOptions::
loadAttribute(TiXmlElement* buttonNode , OptionAttribute* attrb ){

  // Get the xml node of the panel
  TiXmlNode* childNode = buttonNode->FirstChild( "Attribute" );
  if (childNode){
    TiXmlElement* child= childNode->ToElement();

    // search the good attribute   
    for( child; child; child=child->NextSiblingElement() ){
      const char* attrbName=child->Attribute("name");

      // We have the good button (xml)
      if (strcmp(attrbName, attrb->getName())==0){

	TiXmlText* textNode=child->FirstChild()->ToText();
	if (textNode){
	  attrb->setValueStr(textNode->Value());
	}
      }
    }
  }
}

/** Deletes the named snapshot
  *
  * Removes the xml node of the named snapshot and saves the document.
  * 
  * \param c The name of the snapshot to delete
  *
  */
void RainbruRPG::Options::xmlOptions::deleteSnapshot(const char* c){
  TiXmlElement* snapNode=this->getSnapshotNode(c);
  if (snapNode){
    bool b=root->RemoveChild(snapNode);

    if (b){
      doc->SaveFile();
    }
    else{
      GTS_LIT(str);
      sprintf(str, "Cannot delete the snapshot '%s'.", c);
      LOGW(str);
    }
  }
  else{
    LOGW("Cannot get the snapshot xml node to delete");
  }
}

/** Set the LastUsed xml node to the given value
  *
  * \param c The new value of the LastUsed node
  *
  */
void RainbruRPG::Options::xmlOptions::setLastUse(const char* c){
  TiXmlNode* luNode = root->FirstChild( "LastUsed" );
  if (luNode){
    luNode->Clear();
    TiXmlText* textNode=new TiXmlText( c );
    luNode->LinkEndChild( textNode );
    doc->SaveFile();
  }
}

/** Get the LastUsed xml node content
  *
  * \return The LastUsed value
  *
  */
const char* RainbruRPG::Options::xmlOptions::getLastUse(){
  const char* ret="";

  TiXmlNode* luNode = root->FirstChild( "LastUsed" );
  if (luNode){
    TiXmlElement* child= luNode->ToElement();
    TiXmlText* textNode=child->FirstChild()->ToText();
    if (textNode){
      ret=textNode->Value();
    }
  }

  return ret;
}
