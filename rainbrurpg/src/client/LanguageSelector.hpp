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

/** \file LanguageSelector.hpp
  * Header file of the client's language selector
  *
  * Modifications :
  * - 26 jul 2008 : Doxygen documentation
  *
  */

#include <fox-1.6/fx.h>
#include <Logger.hpp>
#include <XmlLanguage.hpp>

using namespace RainbruRPG::Options;

namespace RainbruRPG{
  namespace Gui{

    /** The language selector dialog
      *
      * When you launch RainbruRPG for the first time, this dialog
      * appears to let you select the default language.
      *
      * Please see the Options::xmlLanguage documentation for a deeper view
      * of the language list.
      */
    class LanguageSelector : public FX::FXDialogBox {
      FXDECLARE(LanguageSelector)
	
	public:
      LanguageSelector(FXApp *); 
      virtual ~LanguageSelector(); 
      
      virtual void create();
      /** ??
        *
	* \todo What is it ?
	*
	*/
      void update();

      /** An enumeration definining the FOX identifiers
        *
	* This identifiers are needed by the FOX toolkit to
	* handle events. The only instance of this class is
	* created by Launcher::create().
	*/
      enum{
	/** The FOX identifier of an unimplemented button */
	ID_BUTTON=FXDialogBox::ID_LAST, 
	/** The FOX identifier of the 'Cancel' button */
	ID_BTN_CANCEL,
	/** The FOX identifier of the 'OK' button */
	ID_BTN_OK,
	/** The language combobox selection change */
	ID_CHANGE_SNAP,
	/** Internally used identifier */
	ID_LAST
      };

      long onNotImplemented(FXObject *,FXSelector,void*);
      long onChangeLanguage(FXObject *,FXSelector,void*);
      long onCancelClicked(FXObject *,FXSelector,void*);
      long onOkClicked(FXObject *,FXSelector,void*);
    
    private:
      void feedComboBox(FXComboBox*);


     /** An empty default constructor
        *
	* It is required by the c++ specifications to avoid 
	* undefined references.
	*/
      LanguageSelector(){};

      /** An empty copy constructor
        *
	* It is required by the c++ specifications to avoid 
	* undefined references.
	*/
      LanguageSelector(const LanguageSelector&);

      /** An empty assignement operator
        *
	* It is required by the c++ specifications to avoid 
	* undefined references.
	*/
       LanguageSelector& operator=(const LanguageSelector&);

    }; 
  }
}



