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

#include "attributemodifierlist.h"

/** Default constructor
  *
  * It initialize modList
  */
RainbruRPG::Network::Ident::AttributeModifierList::AttributeModifierList(){

  LOGI("AttributeModifierList construction");
  //  modList=new tAttributeModifierList();
  total=0;
}

/** Default destructor
  *
  * It delete modList
  */
RainbruRPG::Network::Ident::AttributeModifierList::~AttributeModifierList(){
  //  delete modList;
  //  modList=NULL;
}

/** Add a modifier and refresh the total
  *
  * The modifier string is \c -x or \c +y. x and y are both integer. If the
  * modifier is not signed (ex \c 25 ), it is not added.
  *
  * \param mod The modifier string of a BonusFile's choice modifier.
  */
void RainbruRPG::Network::Ident::AttributeModifierList::
addModifier(std::string mod){

  bool check=true;

  tAttributeModifierListItem it;
  it.value=-1;

  char sign=mod[0];
  if (sign=='+'){
    it.type=AMT_PLUS;
  }
  else if (sign=='-'){
    it.type=AMT_MINUS;
  }
  else{
    LOGW("Cannot find the modifier's sign");
    check=false;
  }

  mod.erase(0,1);
  istringstream iss(mod);

  iss >> it.value;

  if (it.value==-1){
    LOGW("Cannot find the modifier's value : modifier is not added");
    check=false;
  }

  if (check){
    modList.push_back(it);
    this->refresh();
  }
}

/** Calculate the total of all added modifiers
  *
  * All modifiers sign and values are added to the total integer.
  * Use getTotal() to get the value of total.
  */
void RainbruRPG::Network::Ident::AttributeModifierList::refresh(){
  tAttributeModifierList::const_iterator iter;

  this->total=0;

  // Iterate through list and output each element.
  for (iter=modList.begin(); iter != modList.end(); iter++){
    addToTotal(&(*iter));
  }
  
}

/** Add the value of a modifier to the total
  *
  * \param it the modifier to compute wih the total
  */
void RainbruRPG::Network::Ident::AttributeModifierList::
addToTotal(const tAttributeModifierListItem* it){

  if ( it->type==AMT_PLUS){
    total+=it->value;
  }
  else if ( it->type==AMT_MINUS){
    total-=it->value;
  }
  else{
    LOGI("Cannot get usable type");
  }
}

/** Return the total of all modifiers
  *
  * \return The total value.
  */
int RainbruRPG::Network::Ident::AttributeModifierList::getTotal(){
  return this->total;
}

/** Get the total in a string format
  *
  * It the total is null (zero), the returned string is empty. If
  * the total isn't null, The string returned contains the sign.
  *
  * \return The string of the total
  *
  */
std::string RainbruRPG::Network::Ident::AttributeModifierList::
getTotalString(){

  int i=this->getTotal();
  std::string s;
  if (i==0){
    s="";
  }
  else if (i<0){
    s=StringConv::getSingleton().itos(i);
  }
  else if (i>0){
    s="+";
    s.append(StringConv::getSingleton().itos(i));
  }

  return s;

}

/** Call this to remove a modifier
  *
  * You can't directly access to the list to remove elements. So call
  * this function to add the inverse modifier. +2 becom -2 and it result
  * as removing the modifier in the total.
  *
  * \param mod The modifier string to remove (+2 will become -2)
  */
void RainbruRPG::Network::Ident::AttributeModifierList::
addModifierInverse(std::string mod){

  bool check=true;

  tAttributeModifierListItem it;
  it.value=-1;

  char sign=mod[0];
  if (sign=='-'){
    it.type=AMT_PLUS;
  }
  else if (sign=='+'){
    it.type=AMT_MINUS;
  }
  else{
    LOGW("Cannot find the modifier's sign");
    check=false;
  }

  mod.erase(0,1);
  istringstream iss(mod);

  iss >> it.value;

  if (it.value==-1){
    LOGW("Cannot  find the modifier's value : modifier is not added");
    check=false;
  }

  if (check){
    modList.push_back(it);
    this->refresh();
  }
}
