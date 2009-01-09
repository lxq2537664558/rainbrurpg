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


/** \file tidentreturn.h
  * Declares the returned values used in the identification process
  *
  * Modifications :
  * - 11 aug 2008 : Single file documentation
  * - 02 jan 2007 : GNU header added
  *
  */

#ifndef T_IDENT_RETURN_H
#define T_IDENT_RETURN_H

namespace RainbruRPG{
  namespace Network {
    namespace Ident {

      /** The return values used in the identification process
        *
	*/
      enum tIdentReturn{
	TIR_SUCCESS,         //<! The process is successfull
	TIR_FAILED_LOGIN,    //<! The FTP login failed
	TIR_FAILED_LOCK,     //<! The lock process failed
	TIR_FAILED_UNLOCK,   //<! The unlock process failed
	TIR_ALREADY_LOCK,    //<! The file is already locked
	TIR_FAILED_CHDIR,    //<! The ftp chdir failed
	TIR_FAILED_TRANSFER, //<! A file transfer failed
	TIR_FAILED_OPEN,     //<! The ftp connection open() failed
	TIR_FAILED_CLOSE,    //<! The ftp connection close() failed
	TIR_UNKNOWN_ERROR    //<! An unknown error occured
      };
    }
  }
}

#endif // T_IDENT_RETURN_H
