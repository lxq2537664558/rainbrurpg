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

#include "gscreateperso.h"

#include <logger.h>
#include "gameengine.h"

/** The constructor of the game state
  *
  */
void RainbruRPG::Core::gsCreatePerso::init(){
  isInit=true;

  RandomLvlMin=RANDOM_LVL_MIN;
  RandomLvlMax=RANDOM_LVL_MAX;

  levelGet=0;
  levelAvail=0;

  nextIrrID=1000;

  tabMap=new CategoryTabMap();
  //  handlerList=new AttrbHandlerList();

  this->irrDevice  = GameEngine::getSingleton().getIrrlichtDevice();
  this->driverType = GameEngine::getSingleton().getDriverType();
  this->irrDriver  = GameEngine::getSingleton().getIrrlichtDriver();
  this->irrSmgr    = GameEngine::getSingleton().getIrrlichtSmgr();
  this->irrGui     = GameEngine::getSingleton().getIrrlichtGui();

  createGui();
}

/** The destructor of the game state
  *
  */
void RainbruRPG::Core::gsCreatePerso::cleanup(){
  LOGI("    Cleaning up gsCreatePerso game state...");
  //  delete irrCamera;
   this->irrDevice=NULL;
  //  this->driverType = NULL;
  this->irrDriver  = NULL;
  this->irrSmgr    = NULL;
  this->irrGui     = NULL;

  delete tabMap;
  tabMap=NULL;

  delete handlerList;
  handlerList=NULL;
}

/** The drawing method
  * 
  * This method is called by the GameEngine for each frame. It just
  * calls the Irrlicht draw function. It also calls the drawDebug()
  * method if \c debug is set to \c true.
  *
  */
void RainbruRPG::Core::gsCreatePerso::run(){
  irrDriver->beginScene(true, true, 0);
  
  irrSmgr->drawAll();
  
  // draw gui
  irrGui->drawAll();
  
  // On a fini d'écrire	    
  irrDriver->endScene();
}

/** Creates the gui of the game GameState
  *
  * It calls drawTab() and drawAttribute for all.
  */
void RainbruRPG::Core::gsCreatePerso::createGui(){

 // Window size
 s32 winW=600;
 s32 winH=400;

 // viewport size
 rect<s32> r=irrGui->getVideoDriver()->getViewPort( );
 s32 h=r.getHeight();
 s32 w=r.getWidth();

 // Win rect
 s32 x1=(w/2)-(winW/2);
 s32 y1=20;
 s32 x2=x1+winW;
 s32 y2=y1+winH;

 //rect<s32>(150,200,250,340)
 // Tab id=1
  irrTab=irrGui->addTab(rect<s32>(0,0,w,h), 0, 1);

 // Window
 IGUIWindow* win= irrGui->addWindow( rect<s32>( x1, y1, x2, y2), false, 
			 	    L"Character creation", irrTab);

 // Widgets de 180 px centres
 s32 xBtn=(winW/2)-90;

 this->drawTab(win);


 xmlAttributeList xmlAttrbt;
 tAttributeList *attrbList=xmlAttrbt.getAttributeList();

 tAttributeList::const_iterator iter;

 // Iterate through list and output each element.
 for (iter=attrbList->begin(); iter != attrbList->end(); iter++){
   drawAttribute((*iter));
 }

 drawLevelTotals( rect<s32>(x1+20,y2-85,x1+270,y2-65), win);

 irrGui->addButton(rect<s32>(x1+20,y2-60,x1+170,y2-30), win, 101, 
		   L"Create" );

 irrGui->addButton(rect<s32>(x1+180,y2-60,x1+330,y2-30), win, 102, 
		   L"Roll" );

 irrGui->addButton(rect<s32>(x1+340,y2-60,x1+490,y2-30), win, 103, 
		   L"Cancel" );

 irrTab->setVisible(true);

}

/** Pause the game GameState
  *
  * It will stop the Irrlicht Device timer and disable the player's
  * camera input. You may call resume() to continue playing. 
  *
  *
  */
void RainbruRPG::Core::gsCreatePerso::pause(){
  LOGI("state gsCreatePerso in pause...");

  // stop the Irrlicht Engine
  irrDevice->getTimer()->stop();

  // Disabled camera input
  //  irrCamera->setInputReceiverEnabled(false);
 irrTab->setVisible(false);

}

/** Resume the game after a pause() call
  *
  * It reinitialize the erGame event receiver, send it to the Irrlicht device
  * and set the mouse cursor invisible.
  *
  */
void RainbruRPG::Core::gsCreatePerso::resume(){
  LOGI("state gsCreatePerso in Resume...");

  erGame receiver;
  // GameEngine::getSingleton().getIrrlichtDevice()->setEventReceiver(&receiver);

  if (irrDevice==0)
    LOGE("Try to setting an EventReceiver on a NULL Irrlicht Device");

  // stop the Irrlicht Engine
  irrDevice->getTimer()->start();

  // Disabled camera input
  //  irrCamera->setInputReceiverEnabled(true);

  irrDevice->getCursorControl()->setVisible(true);
  irrTab->setVisible(true);

}

/** Draw one tab by category having a 'Own'
  *
  * \param win The Irrlicht Window used as parent for widgets
  */
void RainbruRPG::Core::gsCreatePerso::drawTab(IGUIWindow* win){
 // bool=fillbackground & border
 IGUITabControl* tabc=irrGui->addTabControl(
	    rect<s32>( 10, 20, 580, 330), win, true, false );


 // Get the categories list
 xmlAttrbCatList xmlCat;
 tAttrbCatList *catList=xmlCat.getAttrbCatList();

 tAttrbCatList::const_iterator iter;

 IGUITab* tab;
 tCategoryTab* catTab;

 // Iterate through list
 for (iter=catList->begin(); iter != catList->end(); iter++){
   const char* name=(*iter)->name;
   const char* desc=(*iter)->desc;

   catTab=new tCategoryTab();
   catTab->name=name;
   catTab->nextY=50;

   if (strcmp((*iter)->tab, "Own")==0){
     stringw wname= StringConv::getSingleton().stow(name);
     stringw wdesc= StringConv::getSingleton().stow(desc);

     tab=tabc->addTab(L"");
     tab->setText(wname.c_str());

     irrGui->addStaticText(wdesc.c_str(), rect<s32>(10,20,550,50), 
			   false, true, tab);

     catTab->own=true;
     catTab->tab=tab;
   }
   else{
     catTab->own=false;
     catTab->tab=NULL;
     catTab->ownerTab=(*iter)->tab;
   }
   tabMap->push_back( catTab );
 }
}

/** Dispatch attribute by type and tab
  *
  * \param attrb The attribute to treat.
  */
void RainbruRPG::Core::gsCreatePerso::drawAttribute(tAttributeListItem* attrb){

  // get the Tab
  tCategoryTab* cat=getCategoryByName(attrb->cat);

  if (cat){
    LOGI("A category was found");
    drawAttribute(attrb,getITab(cat), cat);

  }
  else{
    LOGW("A category was not found");

  }

}

/** Get the Irrlicht to use for this category
  *
  * \param tab The tab to treate.
  *
  * \return The Irrlicht tab to use with the tCategoryTab.
  */
IGUITab* RainbruRPG::Core::gsCreatePerso::getITab( tCategoryTab* tab ){

  if (tab->own){
    return tab->tab;
  }
  else{

    tCategoryTab* cat=getCategoryByName(tab->ownerTab);

    if (cat){

      tCategoryTab* tab2=cat;
      return getITab(tab2);
    }
    else{
      LOGW("A category was not found");
    }

  }

}

/** Graphically draw the attribute
  *
  * Calls drawUserString, drawUserLongString, drawRandomLvl, drawBonusFile
  * according to the attribute type.
  *
  * \param att The attribute to draw
  * \param irrTab The Irrlicht tab receiving the widget
  * \param tab The category of the attribute
  *
  */
void RainbruRPG::Core::gsCreatePerso::drawAttribute( tAttributeListItem* att, 
						     IGUITab* irrTab,
						     tCategoryTab* tab){


  if (!tab){
    LOGW("A IGUITab is NULL");
  }
  else{
    tAttributeType type=getAttType(att);

    switch(type){
      case AT_UNKNOWN:
	LOGW("An Unknown attribute type was found");
	cout << "Attribute string :"<< att->type << endl;
	break;

      case AT_USER_STR:
	drawUserString(att, irrTab, tab);
	break;

      case AT_USER_STRL:
	drawUserLongString(att, irrTab, tab);
	break;

      case AT_RANDOM_LVL:
	drawRandomLvl(att, irrTab, tab);
	break;

      case AT_BONUS_FILE:
	drawBonusFile(att, irrTab, tab);
	break;

       case AT_XP:
	LOGW("XP type not implemented");
	break;

      case AT_LVL:
	LOGW("XP type not implemented");
	break;

   }
  }
}

/** Get the type of an attribute
  *
  * In a tAttributeListItem, the type is a const char*. According to this 
  * string, we returning type as a tAttributeType using strcmp().
  *
  * \param item The attribute we want the type
  *
  * \return The type of the given attribute
  */
tAttributeType RainbruRPG::Core::gsCreatePerso::
getAttType(tAttributeListItem* item){
  tAttributeType ret;
  ret=AT_UNKNOWN;

  const char* type=item->type;

  if (strcmp(type, "UserStr")==0){
    ret=AT_USER_STR;
  }
  else if (strcmp(type, "Xp")==0){
    ret=AT_XP;
  }
  else if (strcmp(type, "UserStrL")==0){
    ret=AT_USER_STRL;
  }
  else if (strcmp(type, "Lvl")==0){
    ret=AT_LVL;
  }
  else if (strcmp(type, "RandomLvl")==0){
    ret=AT_RANDOM_LVL;
  }
  else if (strcmp(type, "BonusFile")==0){
    ret=AT_BONUS_FILE;
  }


  return ret;
}

/** Return a category by its name
  *
  * The struct tCategoryTab contains the name of the category (field name).
  * For all category in tabMap, we test with strcmp() if the name is the same
  * as given. If it is, we return the corresponding tCategoryTab. Otherwise
  * we return \c NULL.
  *
  * \param na The name of the category to get.
  *
  * \return The named category if found, otherwise returns \c NULL
  */
tCategoryTab* RainbruRPG::Core::gsCreatePerso::
getCategoryByName(const char* na){
  bool found=false;

  CategoryTabMap::const_iterator iter;

  // Iterate through list and output each element.
  for (iter=tabMap->begin(); iter != tabMap->end(); iter++){

    if (strcmp((*iter)->name, na)==0){
      found=true;
      return (*iter);
    }
  }

  return NULL;
}

/** Draws a UserString attribute
  *
  * \param item The attribute to draw
  * \param irrTab The Irrlicht tab receiving the widget
  * \param tab The category of the attribute
  * 
  */
void RainbruRPG::Core::gsCreatePerso::drawUserString(tAttributeListItem* item, 
						     IGUITab* irrTab,
						     tCategoryTab* tab ){
  LOGI("Drawing a UserString");
  stringw wname=StringConv::getSingleton().stow(item->name);
  stringw wdesc=StringConv::getSingleton().stow(item->desc);
  s32 y=getNextY(tab);

  irrGui->addStaticText(wname.c_str(), rect<s32>(10,y+2,80,y+20), 
			false, true, irrTab);

  irrGui->addEditBox (L"", 
		      rect<s32>(90,y,200,y+20), true, irrTab, nextIrrID);

  irrGui->addStaticText(wdesc.c_str(), rect<s32>(210,y+2,500,y+20), 
			false, true, irrTab);

  increaseTabNextY(tab, 30);	

  this->addAttrbHandler(nextIrrID++, AT_USER_STR, false);
	
}

/** Draws a RandomLvl attribute
  *
  * \param item The attribute to draw
  * \param irrTab The Irrlicht tab receiving the widget
  * \param tab The category of the attribute
  * 
  */
void RainbruRPG::Core::gsCreatePerso::drawRandomLvl(tAttributeListItem* item, 
						    IGUITab* irrTab, 
						    tCategoryTab* tab ){
  LOGI("Drawing a RandomLvl");
  stringw wname=StringConv::getSingleton().stow(item->name);
  stringw wdesc=StringConv::getSingleton().stow(item->desc);
  s32 y=getNextY(tab);

  irrGui->addStaticText(wname.c_str(), rect<s32>(10,y,80,y+20), 
			false, true, irrTab);
  int i=getRandomInteger(RandomLvlMin,RandomLvlMax );
  stringw wi=StringConv::getSingleton().itow(i);

  levelGet+=i;
  levelAvail+=RandomLvlMax;


  irrGui-> addStaticText(wi.c_str(), 
			 rect<s32>(90,y,105,y+20), false, true, irrTab, 
			 nextIrrID);

  IGUIStaticText* red=irrGui-> addStaticText(L"", 
			 rect<s32>(105,y,120,y+20), false, true, irrTab, 
			 nextIrrID+1000);

  red->setOverrideColor(video::SColor(250, 0, 0, 250));

  irrGui->addStaticText(wdesc.c_str(), rect<s32>(140,y,500,y+20), 
			false, true, irrTab);

  increaseTabNextY(tab, 20);	
  this->addAttrbHandler(nextIrrID++, AT_RANDOM_LVL, true, item);

}

/** Get a random integer inside the range
  *
  * \param minRange The minimum range.
  * \param maxRange The maximum range.
  *
  * \return A integer beetwen minRange and maxRange
  */
int RainbruRPG::Core::gsCreatePerso::getRandomInteger(int minRange, 
						      int maxRange ){

  return (rand()%(maxRange-minRange))+minRange;
}

/** Draws the totals available levels and the get levels
  *
  * \param rect The rectangle where the Irrlicht StaticText is added.
  * \param win The window we create the StaticText in.
  */
void RainbruRPG::Core::gsCreatePerso::
drawLevelTotals(const irr::core::rect<s32>& rect, IGUIWindow* win){

  ostringstream oss;
  oss << "Levels (get/total available) : ";
  oss << levelGet;
  oss << "/";
  oss << levelAvail;

  stringw wi=StringConv::getSingleton().stow(oss.str());
  irrGui->addStaticText(wi.c_str(), 
			rect, 
			false, true, win, 10000);

}

/** Increase the nextY value of the given tCategoryTab
  *
  * If the given category is drawn in its own tab (tab->own=true)
  * we increase its nextY value. Otherwise, we increase its ownerTab
  * nextY value. It is a recursive function.
  *
  * \param tab The category to modify.
  * \param i The value to add to the nextY value.
  */
void RainbruRPG::Core::gsCreatePerso::increaseTabNextY(tCategoryTab* tab,
						       s32 i){

  if (tab->own){
    tab->nextY+=i;
  }
  else{
    tCategoryTab* owner=getCategoryByName(tab->ownerTab);
    increaseTabNextY(owner, i);
  }

}

/** Get the NextY value of the given category
  *
  * This function is needed because the recursive own/ownerTab case.
  *
  * \param tab The tab to treat.
  *
  * \return the nextY value of the given category or its ownerTab.
  */
s32 RainbruRPG::Core::gsCreatePerso::getNextY(tCategoryTab* tab){
  if (tab->own){
    return tab->nextY;
  }
  else{
    tCategoryTab* owner=getCategoryByName(tab->ownerTab);
    return getNextY(owner);
  }
}

/** Draws a UserLongString attribute
  *
  * \param item The attribute to draw
  * \param irrTab The Irrlicht tab receiving the widget
  * \param tab The category of the attribute
  * 
  */
void RainbruRPG::Core::gsCreatePerso::
drawUserLongString(tAttributeListItem* item, 
		   IGUITab* irrTab,
		   tCategoryTab* tab ){

  LOGI("Drawing a UserLongString");
  stringw wname=StringConv::getSingleton().stow(item->name);
  stringw wdesc=StringConv::getSingleton().stow(item->desc);

  s32 y=getNextY(tab);

  irrGui->addStaticText(wname.c_str(), rect<s32>(10,y+2,80,y+20), 
			false, true, irrTab);

  irrGui->addEditBox (L"", 
		      rect<s32>(90,y,500,y+20), true, irrTab, nextIrrID);

  irrGui->addStaticText(wdesc.c_str(), rect<s32>(90,y+25,500,y+45), 
			false, true, irrTab);

  increaseTabNextY(tab, 50);	
  this->addAttrbHandler(nextIrrID++, AT_USER_STRL, false);
}

/** Adds an attribute handler to the list
  *
  * \param id The id of the Irrlicht widget
  * \param type The type of the attribute
  * \param roll Does this attribute accept autoroll ?
  * \param it The tAttributeListItem describing the attribute.
  */
void RainbruRPG::Core::gsCreatePerso::
addAttrbHandler(s32 id, tAttributeType type, bool roll, 
		tAttributeListItem* it){
  LOGI("Adds an attribute handler");
  tPersoAttrbHandler *h=new tPersoAttrbHandler();
  h->irrId=id;
  h->type=type;
  h->roll=roll;
  h->item=it;

  handlerList->push_back(h);
}

/** Return the static list of attribute handler.
  *
  *
  * \return The global static AttrbHandlerList.
  */
AttrbHandlerList* RainbruRPG::Core::gsCreatePerso::getHandlerList(){
  return handlerList;
};

/** Draws a BonusFile attribute
  *
  * \param item The attribute to draw
  * \param irrTab The Irrlicht tab receiving the widget
  * \param tab The category of the attribute
  * 
  */
void RainbruRPG::Core::gsCreatePerso::
drawBonusFile(tAttributeListItem* item, 
	      IGUITab* irrTab, 
	      tCategoryTab* tab){

  LOGI("Drawing a BonusFile widget");
  stringw wname=StringConv::getSingleton().stow(item->name);
  stringw wdesc=StringConv::getSingleton().stow(item->desc);

  s32 y=getNextY(tab);

  irrGui->addStaticText(wname.c_str(), rect<s32>(10,y+2,80,y+20), 
			false, true, irrTab);

 irrGui->addButton(rect<s32>(90,y,190,y+20),irrTab , nextIrrID, 
		   L"Change..." );


  irrGui->addStaticText(wdesc.c_str(), rect<s32>(200,y+2,500,y+20), 
			false, true, irrTab);
  increaseTabNextY(tab, 30);	
  this->addAttrbHandler(nextIrrID++, AT_BONUS_FILE, false, item );
       cout << "[drawBonusFile]fn="<< item->param1<< endl;

}
