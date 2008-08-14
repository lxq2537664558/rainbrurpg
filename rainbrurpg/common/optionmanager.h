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

/** \file optionmanager.h
  * Declares the option manager singleton
  *
  * Modifications :
  * - 09 aug 2008 : Single file documentation
  *
  */

#ifndef OPTION_MANAGER_H
#define OPTION_MANAGER_H

#include "singleton.h"
#include "logger.h"
#include "optionpanel.h"
#include "options.h"

#include <list>

using namespace std;

namespace RainbruRPG {
  namespace Options{

    /** A stl list of OptionPanel
      *
      */
    typedef list<OptionPanel*> tOptionPanelList;

    /** Provides an interface beetween plugins, launcher and game.
      *
      * This singleton is used to add options that can be modified by
      * the launcher option editor. The values are stored and loaded all the
      * same way, so it is easy for a plugin to add a panel, button and/or
      * new attribute.
      *
      * It is organized in OptionPanel, OptionButton and OptionAttribute.
      * This hierarchy provides a way to store a large number of options. 
      * The options are stored in a file called options.xml, loaded
      * by xmlOptions.
      *
      * The basic options of the core game are created by the Options class, 
      * using this manager. Take a look at its implementation if you want to 
      * create your own options.
      *
      */
    class OptionManager : public RainbruRPG::Core::Singleton<OptionManager>{
    public:
      /** An empty default constructor */
      OptionManager(){};

      void add(OptionPanel*);
      tOptionPanelList* getPanelList();
      unsigned int panelCount();

      OptionPanel* getPanelByName(const char*);
      OptionButton* getButtonByName(const char*, const char*);

      void createAttributes();
      void setAttributesDefaultValues();

      void saveCurrentSnapshot(const char*);
      void loadSnapshot(const char*);
      void deleteSnapshot(const char*);

      void setDamage(bool);
      bool isDamage();

      void setLastUse(const char*);
      const char* getLastUse();

      void init();
      void cleanup();

      void update();

    private:
      /** Unimplemented copy constructors
        *
	* In a singleton the use of this method must be forbidden.
	*
	* \param obj An OptionManager
	*/
      OptionManager(const OptionManager& obj);

      /** Unimplemented assignment
        *
	* In a singleton the use of this method must be forbidden.
	* \param obj An OptionManager
	*/
      OptionManager& operator=(const OptionManager& obj);

      /** The list of Panel that represents a snapshot
        *
	*/
      tOptionPanelList panelList;

      /** Tells if the current snapshot is or not modified
        *
	* This value is modfied by the general callback of the 
	* LauncherOption's OptionAttribute s.
	*
	*/
      bool damage;

      /** Keep a pointer to options to reset the default values
        *
	*/
      Options* options;
    };
  }
}
#endif // OPTION_MANAGER_H
