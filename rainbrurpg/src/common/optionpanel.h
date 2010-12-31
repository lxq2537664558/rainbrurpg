/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

/** \file optionpanel.h
  * Declares a panel for the launcher's options editor
  *
  * Modifications :
  * - 29 apr 2009 : Added the name member to help translation
  * - 14 mar 2009 : Using gettext strings
  * - 09 aug 2008 : Single file documentation
  *
  */

#ifndef OPTION_PANEL_H
#define OPTION_PANEL_H

#include <string>
#include <list>

#include "logger.h"
#include "optionbutton.h"

#include "rainbrudef.h"

using namespace std;


namespace RainbruRPG {
  namespace Options{

    /** A stl list of OptionButton */
    typedef list<OptionButton*> tOptionButtonList;

    /** A panel for the launcher option dialog
      *
      * It is used by the OptiionManager
      */
    class OptionPanel{
    public:
      OptionPanel(const char*, const char*);

      void setCaption(const char*);
      const char* getCaption();

      void setName(const char*);
      const char* getName() const;

      void add(OptionButton*);
      tOptionButtonList* getButtonList();
      unsigned int buttonCount();

      OptionButton* getButtonByName(const char*);

      void update();

    private:
      /** The caption of the panel */
      const char* m_caption;

      /** The name of the panel */
      const char* m_name;

      /** The list of buttons that were added to the OprionPanel */
      tOptionButtonList buttonList;
    };
  }
}


#endif // OPTION_PANEL_H
