
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

#ifndef ER_CREATE_PERSO_H
#define ER_CREATE_PERSO_H

#include <iostream>
#include <irrlicht.h>
#include <IEventReceiver.h>
#include <logger.h>
#include <stringconv.h>
#include <sstream>
#include <string>
#include <xmlattrbcatlist.h>
#include <xmlattributelist.h>

#include <xmlbonusfile.h>
#include <xmlbonusfilelist.h>

#include "gameengine.h"

using namespace std;
using namespace irr;
using namespace irr::gui;
using namespace RainbruRPG::Core;
using namespace RainbruRPG::Network::Ident;


namespace RainbruRPG{
  namespace Events{

    /** Defines the type of a character's attribute
      *
      *
      */
    enum tAttributeType{
      AT_UNKNOWN,      //!< A unknown attribute type
      AT_USER_STR,     //!< A string the user must fill
      AT_USER_STRL,    //!< A long string the user must fill
      AT_XP,           //!< The XP of a level
      AT_LVL,          //!< A level 
      AT_RANDOM_LVL,   //!< A level randomly roll at character creation
      AT_BONUS_FILE    //!< A bonusFile
    };

    /** A character's attribute handler
      *
      * Some character's attributes are stored in this struct to be
      * used with the events.
      */
    struct tPersoAttrbHandler{
      s32 irrId;  //!< The irrlicht id oh the associated widget
      tAttributeType type; //!< The type of the attribute
      bool roll;           //!< Must we re-roll this attribute ?
      RainbruRPG::Network::Ident::tAttributeListItem* item; //!< The item
    };

    /** Keep the 'chenge' button id to change its caption*/
    static s32 changeButtonId=-1;

    /** The last choice the user selected */
    static std::string listBoxVal="";

    /** The Irrlicht Event Recever for gsCreatePerso
      *
      * The Irrlicht IDs are reserved from 10000 to 10100 for the choice
      * selection popup.
      *
      * \warning This class is instancied and set up to the IrrlichtDevice in
      * the gsGame::run(). If we set up this in gsGame::init(), the
      * IrrlichtDevice isn't yet initialized and it may cause a SegFault.
      */
    class erCreatePerso : public IEventReceiver{
    public:
      erCreatePerso();

      virtual bool OnEvent(SEvent event);

      int getLevelGet();
      int getLevelAvail();
      void setLevelGet( int );
      void setLevelAvail( int );

    private:
      bool controlBefore(IGUIElement*);
      static void roll(IGUIElement* root, erCreatePerso*);
      static int getRandomInteger(int minRange, int maxRange );
      static bool handleBonusFileButton(s32, IGUIElement*, erCreatePerso*);

      void choicePreselection( s32, tPersoAttrbHandler*, IGUIListBox*);
      IGUIListBox* createChoiceWindow( tPersoAttrbHandler*);
      tBonusFileListItem* getBonusFileDesc(const char*);

      void showChoice(gui::IGUIElement*);
      void showChoiceModifiers(const char*);
      void changePersoFormModifier();
      void removePreselectionModidifers();
      stringw getChoiceDesc(const char*);
 
      /** The total of level you get this roll */
      int levelGet;
      /** The total of level available */
      int levelAvail;
      /** Was a choice selected 
        *
	* Used by controlBefore to test if a choice was selected.
	* Its value is modified by showChoice.
	*/
      bool choiceSelected;

      /** Is a preselection exists
        *
	* If a preselection was made for this BonusFile, we must know
	* it to remove modifiers.
	*/
      bool isPresel;

       /** The name of the preselection
        * 
	*/
      std::string preselName;

      /** Keep the xml interface to BonusFile for updating speed purpose*/
      xmlBonusFile* xmlBf;

      /** Keep the choice list to speed up search*/
      tBonusFileChoiceList *choiceList;
      /** Keep the choice description static test for updating purpose*/
      IGUIStaticText *stChoiceDesc;
       /** Keep the modifiers list static test for updating purpose*/
      IGUIListBox* lbModifiersList;
      /** The popup window to select choice */
      IGUIWindow* winSelect;	
    };
  }
}

#endif // ER_CREATE_PERSO_H
