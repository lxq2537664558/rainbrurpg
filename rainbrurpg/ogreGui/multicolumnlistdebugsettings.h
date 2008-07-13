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

/* Modifications :
 * - 07 jun 2008 : starting implementation
 *         
 */

#ifndef _MULTI_COLUMN_LIST_DEBUG_SETTINGS_H_
#define _MULTI_COLUMN_LIST_DEBUG_SETTINGS_H_

#include <string>
#include <sstream>

#include <stringconv.h> // For itobin()

#include <ogreimport.h>

// Forward declarations
namespace RainbruRPG{
  namespace OgreGui{
    class DrawingDevSettings;
    class QuadRenderer;
    class MultiColumnList;
    class MultiColumnListItem;
    class MultiColumnListCell;
  }
}
// End of forward declarations

/** Defines the default logging value */
#define DEFAULT_DEBUG_FLAG_VALUE 0xFF

/** The color used to graphically debug the drawing rectangle */
#define DEFAULT_DRAWING_RECT_COLOR 1.0f, 1.0f, 1.0f

using namespace std;
using namespace Ogre;
using namespace RainbruRPG::Core; // For StringConv

namespace RainbruRPG{
  namespace OgreGui{

    /** The union defining what should be logged
      *
      * It is used by \ref MultiColumnListDebugSettings to know
      * what should be logged. You can change these settings bt calling
      * the functions  \ref 
      * MultiColumnListDebugSettings::setDebugFlags(unsigned int) or
      * \ref MultiColumnListDebugSettings::setDebugFlags(const  tMultiColumnListDebugFlags &).
      *
      * Examples hexadecimal values for \ref direct_access :
      * - \c 0x0 will log nothing;
      * - \c 0x1 will log only localization informations;
      * - \c 0xF will log anything.
      *
      * The default log flags value is defined as a preprocessor macro
      * in the multicolumnlistdebugsettings.h file.
      *
      * \note Is you modify it, be sure the anonymous structure and 
      *       \ref direct_access have the same allocation size. The size
      *       should also be a multiple of 8.
      *
      */
    typedef union{
      /** The anonymouse structure used for individual flag access
        *
	* You can access all of this flags manually.
	*
	*/
      struct{
	unsigned localize        :1;  //!< Log item and cell number
	unsigned content         :1;  //!< Log item or cell content
	/** The rectangle where we draw is text-logged */
	unsigned drawingRect_log :1; 
	/** The rectangle where we draw is graphically drawn 
	  *
	  * The color used to draw it is defined by a macro called
	  * DEFAULT_DRAWING_RECT_COLOR
	  * in the multicolumnlistdebugsettings.h. 
	  *
	  */
	unsigned drawingRect_draw:1; 
	/** The QuadRenderer's scissor rectangle is text-logged */
	unsigned scissorRect_log:1;
	/** The QuadRenderer's scissor rectangle is draw */
	unsigned scissorRect_draw:1;
	/** Unused member, used to pack structure size */
	unsigned unused          :2; 
      };
      /** The union member used for direct hexadecimal access */
      unsigned direct_access:8;
    }tMultiColumnListDebugFlags;
    

    /** Debug settings for MultiColumnList
      *
      * This class is used by \ref wdMultiColumnList to know how to debug
      * the MultiColumnList drawing pass.
      *
      * To know what should be logged, you should see \ref 
      * tMultiColumnListDebugFlags.
      *
      */
    class MultiColumnListDebugSettings{
    public:
      MultiColumnListDebugSettings();
      MultiColumnListDebugSettings(const std::string&);
      MultiColumnListDebugSettings(const std::string&, int);
      MultiColumnListDebugSettings(const std::string&, int, int);

      ~MultiColumnListDebugSettings();

      void reset(void);

      void debugItem(QuadRenderer*, MultiColumnList*, MultiColumnListItem*,
		     const Rectangle&);
      void debugCell(QuadRenderer*, MultiColumnList*, MultiColumnListCell*,
		     const Rectangle&);

      void setDebugFlags(unsigned int);
      void setDebugFlags(const tMultiColumnListDebugFlags&);
      
      void disable(void);
      void enable(void);
      void setEnable(bool);
      bool isEnabled(void);

    protected:
      void init(void);

      std::string makeDebugString(MultiColumnList*, MultiColumnListItem*,
				  const Rectangle&);
      std::string makeDebugString(MultiColumnList*, MultiColumnListCell*,
				  const Rectangle&);

      std::string makeScissorDebugString(QuadRenderer*);
      void drawScissorRectangle(QuadRenderer*);

    private:
      /** Should we debug ? */
      bool mEnabled;

      /** The name of the MultiColumnList to debug
        *
	* If this name is empty, all MultiColumnList widgets will be debugged.
	*
	*/
      std::string mWidgetName;

      /** The number of item to be debugged
        *
	* If -1, all items will be debugged. The first item of the list is 1.
	*
	*/
      int mItemNum;

      /** The number of column to be debugged
        *
	* If -1, all columns will be debugged
	*
	*/
      int mColumnNum;

      /** Should we log output via logger */
      bool mLogout;
      /** Should we draw scissor rectangle */
      bool mDrawScissor;
      /** Set to \c true if at least one log was out*/
      bool mUsefull;

      /**  The current item we are drawing
        *
	* This number is set to 0 in reset().
	*
	*/
      int mCurrentItem;

      /**  The current cell we are drawing
        *
	* This number is set to 0 in reset().
	*
	*/
      int mCurrentCell;

      /** The debug flags used to know what should be logged	*/
      tMultiColumnListDebugFlags mFlags;
      /** The color used to draw the debugging of drawing rectangle for items*/
      ColourValue mDrawingRectangleColor;
      /** The color used to draw the debugging of drawing rectangle for items*/
      ColourValue mCellDrawingRectangleColor;
      /** The color used to draw the QuadRenderer's scissor rectangle
        *
	* This color will be used to draw the outline of the scissor rectangle
	* if the \ref tMultiColumnListDebugFlags::scissorRect_draw flag is on.
	*
	*/
      ColourValue mScissorRectangleColor;
    };
  }
}


#endif // _MULTI_COLUMN_LIST_DEBUG_SETTINGS_H_
