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

/** \file gsupdatedatafiles.h
  * Declares the state showing the datafiles that need to be updated
  *
  * Modifications :
  * - 16 aug 2008 : Single file documentation
  * - 30 jul 2007 : Starting implementation
  *
  */

#ifndef _GS_UPDATE_DATAFILES_H_
#define _GS_UPDATE_DATAFILES_H_

#include "GsMenuBase.hpp"
#include "guimanager.h"

#include <VcConstant.hpp>

namespace RainbruRPG {
  namespace Core{

    /** A game state used to show client update progression
      *
      *
      *
      */
    class gsUpdateDatafiles : public gsMenuBase{
    public:
      gsUpdateDatafiles();
      virtual ~gsUpdateDatafiles();
    };
  }
}

#endif // _GS_UPDATE_DATAFILES_H_

