/*
 *  Copyright 2006-2013 Jerome PASQUIER
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

/** \file helpviewer.cpp
  * Implements a basic HTML viewer
  *
  */

#include "HelpViewer.hpp"

#include <config.h>
#include <Logger.hpp>

/** The server's help viewer constructor
  *
  * If \c key is an empty string, index.html is used.
  * 
  * \param key    The key that define the starting URL
  * \param parent The parent widget
  *
  * \sa home, map
  *
  */
RainbruRPG::Gui::HelpViewer::
HelpViewer(const std::string& key, QWidget* parent) 
  :QDialog(parent){

  map=new tHelpViewerMap;
  feedMap();

  std::string strHome=getUrlfromKey(key);
  QString qstrHome(strHome.c_str());
  home.setUrl(qstrHome);

  this->setMinimumWidth(600);
  this->setMinimumHeight(400);
  this->setWindowTitle(tr("Help viewer"));

  QVBoxLayout* vb1=new QVBoxLayout(this);
  QTextBrowser* tb=new QTextBrowser(this);
  vb1->addWidget(tb);

  tb->setSource(home);

  // The dialog's button
  QHBoxLayout *buttonLayout=new QHBoxLayout();
  vb1->addLayout(buttonLayout);
  buttonLayout->addStretch(100);
  QPushButton *btnOk=new QPushButton(tr("OK"), this );
  buttonLayout->addWidget(btnOk);

  connect(btnOk, SIGNAL(clicked()), this, SLOT(accept()) );
}

/** The destructor
  *
  */
RainbruRPG::Gui::HelpViewer::~HelpViewer(){
  delete map;
}

/** Makes the initialisation of the map
  *
  */
void RainbruRPG::Gui::HelpViewer::feedMap(){
  addMapItem("Server", "Server.html", "Server");
  addMapItem("Server-ident", "Server.html", "index-Identification-7");
  addMapItem("Server-ftp", "Server.html", "index-File-transfer-8");
  addMapItem("Server-quarant", "Server.html", "index-Quarantine-9");

}

/** Add an item to the map
  *
  * \param key The key
  * \param page The html page
  * \param anchor The anchor in the page
  *
  */
void RainbruRPG::Gui::HelpViewer::addMapItem(const std::string& key, 
					     const std::string& page, 
					     const std::string& anchor){

  tHelpViewerMapItem* it=new tHelpViewerMapItem();
  it->key    =key;
  it->page   =page;
  it->anchor =anchor;

  map->push_back(it);

  LOGCATS("Map size :");
  LOGCATI(map->size());
  LOGCAT();
}

/** Get the url from a key
  *
  * The given URL is ready to use, containing USER_INSTALL_PREFIX, the
  * web page address and eventually the anchor. If the key is not found, 
  * the index.html page is returned.
  *
  * \param key The map key
  *
  * \return The URL
  *
  */
std::string RainbruRPG::Gui::HelpViewer::
getUrlfromKey(const std::string& key){
  std::string ret=USER_INSTALL_PREFIX;
  ret+="/share/doc/RainbruRPG/";

  if (key==""){
    ret+="index.html";
  }
  else{
    tHelpViewerMapItem* it=getItemfromKey(key);
    if (it!=NULL){
      ret+=it->page;

      // Adds the anchor if not empty
      if (it->anchor!=""){
	ret+="#";
	ret+=it->anchor;
      }
    }
    else{
      ret+="index.html";
    }
  }

  return ret;
}

/** Get a map item from a key
  *
  * \param key The map key
  *
  * \return The item or \c NULL if not found
  *
  */
RainbruRPG::Gui::tHelpViewerMapItem* 
RainbruRPG::Gui::HelpViewer::getItemfromKey(const std::string& key){

  LOGCATS("getItemfromKey called. received key is '");
  LOGCATS(key.c_str());
  LOGCATS("'");
  LOGCAT();

  tHelpViewerMap::const_iterator iter;

  bool found=false;

  // Iterate through list
  for (iter=map->begin(); iter != map->end(); iter++)  {
    LOGCATS("map current key is '");
    LOGCATS((*iter)->key.c_str());
    LOGCATS("'");
    LOGCAT();

    if (key==(*iter)->key){
      LOGI("Key is found");
      found=true;
      return (*iter);
    }
  }

  if (!found){
    LOGW("HelpViewer map key not found");
    return NULL;
  }
}
