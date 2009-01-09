/*
 *  Copyright 2006-2009 Jerome PASQUIER
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

/** \file launcheroptions.h
  * Header file of the client's options editor
  *
  * Modifications :
  * - 15 dec 2008 : Using ui_ptr in onAttributeChange to avoid a
  *                 'loses precision' compilation error.
  * - 26 jul 2008 : Doxygen documentation
  *
  */


#include <fox-1.6/fx.h>
#include <logger.h>
#include <optionmanager.h>
#include <optionpanel.h>
#include <optionlistattribute.h>

using namespace RainbruRPG::Options;

namespace RainbruRPG{
  namespace Gui{

    /** The option dialog of the launcher
      *
      * You can access this dialog with the 'Options' button of the 
      * launcher.
      *
      * \sa Launcher, OptionManager
      * \todo Add a screenshot
      */
    class LauncherOptions : public FX::FXDialogBox {
      FXDECLARE(LauncherOptions)
	
	public:
      LauncherOptions(FXApp *); 
      virtual ~LauncherOptions(); 
      
      virtual void create();
      void update();

      /** An enumeration definining the FOX identifiers
        *
	* This identifiers are needed by the FOX toolkit to
	* handle events.
	*/
      enum{
	/** The FOX identifier of an unimplemented button */
	ID_BUTTON=FXDialogBox::ID_LAST, 
	/** The FOX identifier of the 'Cancel' button */
	ID_BTN_CANCEL,
	/** The FOX identifier of the 'OK' button */
	ID_BTN_OK,
        /** The FOX identifier of all OptionButtons */
	ID_BTN_OPTION,
	/** A single identifier for all attributes widgets but string*/
        ID_ATTRB_WIDGET,  
	/** A identifier for string attributes
	  *
	  * Because we use SEL_CHANGED instead SEL_COMMAND for TextFields
	  */
        ID_ATTRB_STRING,  
	/** The new snapshot button */
	ID_NEW_SNAP,
	/** The save snapshot button */
	ID_SAVE_SNAP,
	/** The snapshot combobox selection change */
	ID_CHANGE_SNAP,
	/** The delete snapshot button */
	ID_DEL_SNAP,
	/** The copy snapshot button */
	ID_CPY_SNAP,
	/** Internally used identifier */
	ID_LAST
      };
      
      long onNotImplemented(FXObject *,FXSelector,void*);
      long onCancelClick(FXObject *,FXSelector,void*);
      long onOkClick(FXObject *,FXSelector,void*);
      long onOptionButtonClick(FXObject *,FXSelector,void*);
      long onAttributeChange(FXObject *,FXSelector,void*);

      long onNewSnapshot(FXObject *,FXSelector,void*);
      long onSaveSnapshot(FXObject *,FXSelector,void*);
      long onChangeSnapshot(FXObject *,FXSelector,void*);
      long onDeleteSnapshot(FXObject *,FXSelector,void*);
      long onCopySnapshot(FXObject *,FXSelector,void*);

      FX::FXIcon* loadIcon(const char* filename);
      
      FXShutterItem* addOptionPanel(FXShutter *, FXSwitcher* com, 
				    OptionPanel*);

      FXComposite* addOptionButton(FXShutterItem *, FXSwitcher* ,
				   OptionButton*);

      void addOptionAttribute(FXComposite*, OptionButton*);

      void drawInteger(FXComposite*, OptionAttribute*);
      void drawString(FXComposite*, OptionAttribute*);
      void drawBoolean(FXComposite*, OptionAttribute*);
      void drawList(FXComposite*, OptionAttribute*);
    
    private:
      /** An empty default constructor
        *
	* It is required by the c++ specifications to avoid 
	* undefined references.
	*/
      LauncherOptions(){};

      /** An empty constructor
        *
	* It is required by the c++ specifications to avoid 
	* undefined references.
	*/
      LauncherOptions(const LauncherOptions&);

      /** An empty constructor
        *
	* It is required by the c++ specifications to avoid 
	* undefined references.
	*/
      LauncherOptions &operator=(const LauncherOptions&);


      void createSnapCombo(FXComposite* parent);
      void refreshSnapCombo();
      void selectSnapshot(const char* );

      /** This identifier must be incremented each time we create a 
        * switcher panel and is set to the OptionButton::setFoxPanelId()
        *
        */
      int switchPanelId;
      
      /** Keep the FOX switcher widget
        *
	* We must keep this pointer to be able to change its current
	* visible page when a OptionButton is clicked
	*
	*/
      FXSwitcher* swi;

      /** The combo box of the snapshot name
        *
	* We must keep it to add more name or delete it.
	*/
      FXComboBox *cbSnap;
      /** The save snapshot button
        *
	* We keep it to be able to enable/disable it.
	*
	*/
      FXButton* btnSaveSnap;
    }; 
  }
}




