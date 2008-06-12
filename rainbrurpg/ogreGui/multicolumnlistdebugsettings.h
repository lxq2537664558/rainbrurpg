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

// Forward declarations
namespace RainbruRPG{
  namespace OgreGui{
    class QuadRenderer;
    class MultiColumnList;
    class MultiColumnListItem;
    class MultiColumnListCell;
  }
}
// End of forward declarations

/** Defines the default logging value */
#define DEFAULT_DEBUG_FLAG_VALUE 0xFF

using namespace std;
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
      /** The anonymouse structure use for floag access
        *
	* You can access all of this flags manually.
	*
	*/
      struct{
	unsigned localize:1;    //!< Log item and cell number
	unsigned content :1;    //!< Log item or cell content
	unsigned unused:6;      //!< Unused member, used to pack structure size
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

      void debugItem(QuadRenderer*, MultiColumnList*, MultiColumnListItem*);
      void debugCell(QuadRenderer*, MultiColumnList*, MultiColumnListCell*);

      void setDebugFlags(unsigned int);
      void setDebugFlags(const tMultiColumnListDebugFlags&);
      
    protected:
      std::string makeDebugString(MultiColumnList*, MultiColumnListItem*);
      std::string makeDebugString(MultiColumnList*, MultiColumnListCell*);

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

    };
  }
}


#endif // _MULTI_COLUMN_LIST_DEBUG_SETTINGS_H_
