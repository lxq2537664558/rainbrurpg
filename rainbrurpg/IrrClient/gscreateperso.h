/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

#ifndef GS_CREATE_PERSO_H
#define GS_CREATE_PERSO_H

#include <irrlicht.h>
#include <stringconv.h>
#include <xmlattrbcatlist.h>
#include <xmlattributelist.h>
#include <string>
#include <map>
#include <list>
#include <cstdlib> 
#include <ctime> 
#include <iostream>

#include "gamestate.h"
#include "irrfontmanager.h"
#include "ercreateperso.h"

using namespace std;
using namespace irr;
using namespace gui;
using namespace core;
using namespace RainbruRPG::Core;
using namespace RainbruRPG::Network::Ident;



namespace RainbruRPG {
  namespace Core {

    /** Defines the little range of random attribute generation
      *
      * It is used by gsCretaPerso and erCretaPerso
      */
#   define RANDOM_LVL_MIN 3

    /** Defines the greater range of random attribute generation
      *
      * It is used by gsCretaPerso and erCretaPerso
      */
#   define RANDOM_LVL_MAX 10


    /** A struct defining a category tab
      *
      * If own is \c true, the Tab pointer is used, otherwise, the ownerTab
      * name is used.
      *
      * The nextY value is used for the Irrlicht widget placement. 
      *
      */
    struct tCategoryTab{
      const char* name;     /*!< The name of the catgory*/
      bool own;             /*!< Is this category use its own tab*/
      IGUITab* tab;         /*!< The tab used if own is \c true*/
      const char* ownerTab; /*!< The category to use if own is \c false*/
      s32 nextY;            /*!< The next position of the widget*/
    };

    /** A stl list of CategoryTabMap
      *
      */
    typedef std::list<tCategoryTab*> CategoryTabMap;
    /** A stl list of tPersoAttrbHandler
      *
      */
    typedef std::list<tPersoAttrbHandler*> AttrbHandlerList;

    /** A static AttrbHandlerList used by gsCreatePerso and 
      * erCreatePerso.
      */
    static AttrbHandlerList* handlerList=new AttrbHandlerList();


    /** The character creation
      *
      * Here the user can create its own character. As the widgets are
      * dynamically create from xml files, the difficulty is to handle
      * the events. The events are kept by their ID (nextIrrID start 
      * at 1000), a boolean value saying if it must be roll again and 
      * a value for their tAttributeType.
      */
    class gsCreatePerso : public GameState {
     friend class RainbruRPG::Events::erCreatePerso;
    public:
      virtual void init();
      virtual void cleanup();
      
      virtual void pause();
      virtual void resume();
      
      virtual void run();

      void createGui();

      static AttrbHandlerList* getHandlerList();

    private:
 
      void drawTab(IGUIWindow*);
      void drawAttribute( tAttributeListItem* );
      void drawAttribute( tAttributeListItem*, IGUITab*, tCategoryTab*  );
      IGUITab* getITab( tCategoryTab* );
      tAttributeType getAttType(tAttributeListItem*);

      tCategoryTab* getCategoryByName(const char*);
      void drawUserString(tAttributeListItem*, IGUITab*, tCategoryTab* );
      void drawUserLongString(tAttributeListItem*, IGUITab*, tCategoryTab* );
      void drawRandomLvl(tAttributeListItem*, IGUITab*, tCategoryTab* );
      void drawBonusFile(tAttributeListItem*, IGUITab*, tCategoryTab* );

      void drawLevelTotals(const irr::core::rect<s32>& , IGUIWindow*);

      int getRandomInteger(int minRange, int maxRange);
      void increaseTabNextY(tCategoryTab*,  s32);

      void addAttrbHandler(s32, tAttributeType, bool, 
			   tAttributeListItem* it=0);

      s32 getNextY(tCategoryTab*);


      /** The Irrlicht device */
      irr::IrrlichtDevice*       irrDevice;
      /** The Irrlicht driver type */
      irr::video::E_DRIVER_TYPE  driverType;
      /** The Irrlicht video driver */
      irr::video::IVideoDriver*  irrDriver;
      /** The Irrlicht scene manager */
      irr::scene::ISceneManager* irrSmgr;
      /** The Irrlicht gui environmant */
      irr::gui::IGUIEnvironment* irrGui;

     /** The Irrlicht GUI tab in wich the menu is drawn
        *
	*/
      IGUITab * irrTab;

      /** The category list */
      CategoryTabMap* tabMap;

      // The values used to calculate random number and totals
      /** The RandomLvl min range*/
      int RandomLvlMin;
      /** The RandomLvl max range*/
      int RandomLvlMax;

      /** The total of level you get this roll */
      int levelGet;
      /** The total of level available */
      int levelAvail;

      /** The next event handler ID to give to the widget */
      s32 nextIrrID;

    };
  }
}

#endif // GS_CREATE_PERSO_H
