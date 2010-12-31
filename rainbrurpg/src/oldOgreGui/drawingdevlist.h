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

/** \file drawingdevlist.h
  * Declares a list of DrawingDevSettings
  *
  * Modifications :
  * - 15 oct 2009 : Made messages transatable with gettext
  * - 23 sep 2008 : \ref RainbruRPG::OgreGui::DrawingDevList::toString
  *                 "toString()" returned value bugfix
  * - 26 aug 2008 : Single file documentation
  * - 05 apr 2008 : starting implementation
  *         
  */

#ifndef _OGRE_GUI_DRAWING_DEV_LIST_H_
#define _OGRE_GUI_DRAWING_DEV_LIST_H_

#include <list>
#include <string>
#include <rainbrudef.h>    // For the GNU gettext stuff

// Forward declaration
namespace RainbruRPG{
  namespace OgreGui{
    class DrawingDevSettings;
  }
}
// End of Forward declaration


using namespace std;

namespace RainbruRPG{
  namespace OgreGui{

    /** A STL list of DrawingDevSettings pointers */
    typedef list<DrawingDevSettings*> tDrawingDevSettingsList;

    /** A list of DrawingDevSettings used by QuadRenderer
      * 
      * QuadRenderer cannot use simple STL list of DrawingDevSettings because
      * we must precompute X and Y sums to speed up drawing process. This
      * job is done by the \ref computeValues() fonction.
      *
      */
    class DrawingDevList{
    public:
      DrawingDevList();

      void addSettings(DrawingDevSettings*);
      void removeSettings(DrawingDevSettings*);

      const tDrawingDevSettingsList& getSettingList(void)const;
      int getDevXSum(void)const;
      int getDevYSum(void)const;
      bool empty()const;

      std::string toString(void)const;

    protected:
      void computeValues(void);

    private:
      /** The sum of all DevX values */
      int mDevXSum;
      /** The sum of all DevY values */
      int mDevYSum;

      /** The list of DrawingDevSettings */
      tDrawingDevSettingsList mList;

    };

  }
}

#endif // _OGRE_GUI_DRAWING_DEV_LIST_H_
