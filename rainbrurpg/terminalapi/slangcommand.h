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
 *  along with Foobar; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

/** \file slangcommand.h
  * Declares a base-class used to store SLang commands
  *
  * Modifications :
  * - 19 sep 2008 : Single file documentation
  *
  */

#ifndef SLANG_COMAND_H
#define SLANG_COMAND_H


namespace RainbruRPG{
  namespace Terminal{

    /** A super-class used by ScollingPanel to store SLang commands
      *
      *
      *
      */
    class SLangCommand{
    public:
      SLangCommand();
      virtual ~SLangCommand();

      /** The drawing capability of a SLang command
        *
	* When the ScollingPanel must refresh its content, it executes
	* all SLangCommand subclasses this routine.
	*
	* \param x1 The top left physical coordonate
	* \param y1 The top left physical coordonate
	* \param x2 The bottom right physical coordonate
	* \param y2 The bottom right physical coordonate
	*
	*/
      virtual void execute(int x1, int y1, int x2, int y2)=0;
    };

  }
}

#endif // SLANG_COMAND_H
