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

/** \file tools/netflooder/chartviewer.h
  * Declares a dialog used to view netflooder charts
  *
  * Modifications :
  * - 20 sep 2008 : Single file documentation
  * - 12 apr 2007 : Starting implementation
  *
  */

#include <fox-1.6/fx.h>
#include <Logger.hpp>

namespace RainbruRPG{
  namespace Gui{

    /** The NetFlooder chart viewer
      *
      *
      *
      */
    class ChartViewer : public FX::FXDialogBox {
      FXDECLARE(ChartViewer)
	
	public:
      ChartViewer(FXApp *, const char*, int width=200, int height=100); 
      virtual ~ChartViewer(); 
      
      virtual void create();

      /** An enumeration definining the FOX identifiers
        *
	* This identifiers are needed by the FOX toolkit to
	* handle events.
	*/
      enum{
	/** The FOX identifier of an unimplemented button */
	ID_NYI=FXDialogBox::ID_LAST, 
	/** The close button identifier */
	ID_CLOSE,
	/** Internally used identifier */
	ID_LAST
      };
      
      long onNotImplemented(FXObject *,FXSelector,void*);
      long onClose(FXObject *,FXSelector,void*);

    private:
      /** An empty default constructor
        *
	* It is required by the c++ specifications to avoid 
	* undefined references.
	*/
      ChartViewer(){};

      /** An empty constructor
        *
	* It is required by the c++ specifications to avoid 
	* undefined references.
	*/
      ChartViewer(const ChartViewer&);

      /** An empty constructor
        *
	* It is required by the c++ specifications to avoid 
	* undefined references.
	*/
      ChartViewer &operator=(const ChartViewer&);

      FX::FXImage* loadImage(const char* filename);

      
    }; 
  }
}

