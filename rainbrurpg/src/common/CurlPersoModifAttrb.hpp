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

/** \file CurlPersoModifAttrb.hpp
  * Defines how to submit an attribute modification
  *
  * Modifications :
  * - 27 mar 2009 : Now using gettext
  * - 04 aug 2008 : File documentation
  *
  */

#ifndef CURL_PERSO_MODIF_ATTRB_H
#define CURL_PERSO_MODIF_ATTRB_H

#include "RainbruDef.hpp"     // For the gettext stuff
#include "GlobalUri.hpp"
#include "CurlSubmitForm.hpp"
#include "xmlpersolist.h"

using namespace RainbruRPG::Network::Ident;

namespace RainbruRPG {
  namespace Network {

      /** Submits an attribute modification to the administration site
        * 
	* This form is used to modify some attribute of a character(Perso).
	* The attributes we modified must be in the same category.
	*
	*/
      class CurlPersoModifAttrb : public CurlSubmitForm{
      public:
	CurlPersoModifAttrb();
	~CurlPersoModifAttrb();

      protected:
	virtual bool controlBefore();
	virtual bool controlAfter();

      private:
	/** The xmlPersoList instance used to deal with the server*/
	xmlPersoList* xml;
      };

  }
}

#endif // CURL_PERSO_MODIF_ATTRB_H
