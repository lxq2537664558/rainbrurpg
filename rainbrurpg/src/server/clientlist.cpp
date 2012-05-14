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

/** \file clientlist.cpp
  * Implements a widget that shows connected/refused clients information
  *
  */

#include "clientlist.h"

#include <Logger.hpp>

/** The default constructor
  *
  * \param parent The parent widget
  *
  */
RainbruRPG::Gui::ClientList::ClientList(QWidget* parent)
  :QWidget(parent)
{

  setWindowTitle("Connected clients");

  // The main layout
  QVBoxLayout* vb1=new QVBoxLayout();
  this->setLayout(vb1);
  
  // The tree
  tree=new QTreeWidget();
  tree->setSortingEnabled(true);
  QStringList header;
  header << tr("Ip") << tr("Port") << tr("Type") << tr("Status") 
	 << tr("Try");
  tree->setColumnCount(5);
  tree->setHeaderLabels(header);
  vb1->addWidget(tree);

}

/** The default destructor
  *
  */
RainbruRPG::Gui::ClientList::~ClientList(){
  delete tree;
  tree=NULL;
}

/** Adds the givent client to the list
  *
  * \param ip The IP address of the client
  * \param port The port of the client
  * \param type The client's type
  * \param accepted Is this client accepted
  *
  */
void RainbruRPG::Gui::ClientList::
addClient(enet_uint32 ip, enet_uint16 port, tNetworkClientType type, 
	  bool accepted){

  npIdentification npi;
  QColor r=Qt::red;

  QString ipText;
  ipText.setNum(ip, 16);
  ipText=ipText.toUpper();

  QString portText;
  portText.setNum(ip);

  QString typeText;
  typeText=npi.clientTypeToString(type );

  QString statusText;
  if (accepted){
    statusText="Accepted";
  }
  else{
    statusText="Refused";
  }

  int exists=existingClient(ipText, portText, typeText, statusText);

  // Is this client already listed
  if (exists!=-1){
    LOGI("This client is already listed");
    increaseClientTry(exists);
  }
  else{
    // It is a new client, adding it to the list
    QTreeWidgetItem *it= new QTreeWidgetItem(tree);
    it->setText(0,ipText );
    it->setText(1, portText);
    it->setText(2, typeText);
    it->setText(3, statusText);
    if (!accepted){
      it->setTextColor(3, r);
    }
    it->setText(4, "1");

    tree->addTopLevelItem( it );
  }
}

/** Is this client already listed
  *
  * \param ip The IP adress
  * \param port The client's port
  * \param type The client's type
  * \param status Is the client connection accepted or refused
  *
  * \return The index of the existing client or -1 if not found
  *
  */
int RainbruRPG::Gui::ClientList::
existingClient(const QString& ip, const QString& port, const QString& type, 
	       const QString& status){
  int ret=-1;

  for (int i=0;i<tree->topLevelItemCount();i++){
    QTreeWidgetItem *it=tree->topLevelItem(i);
    if (ip.compare(it->text(0))==0){
      if (port.compare(it->text(1))==0){
	if (type.compare(it->text(2))==0){
	  if (status.compare(it->text(3))==0){
	    ret=i;
	  }
	}
      }
    }
  }
  return ret;
}

/** Increase the number of try of the client
  *
  * The row index is given by the existingClient() function.
  *
  * \param row The treeview's row index of the item to modify
  *
  */
void RainbruRPG::Gui::ClientList::increaseClientTry(int row){
  QTreeWidgetItem * it=tree->topLevelItem(row);
  int i=it->text(4).toInt();
  i++;
  it->setText(4, QString::number(i)); 
}
