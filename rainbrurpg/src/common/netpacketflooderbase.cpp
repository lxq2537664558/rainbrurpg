/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file netpacketflooderbase.cpp
  * Implements the flooder base packet sent over Enet network for 
  *
  */

#include "netpacketflooderbase.h"

/** The constructor
  *
  * \param id The packet identifier
  * \param r The response identifier
  *
  */
RainbruRPG::Network::NetPacketFlooderBase::
NetPacketFlooderBase(tNetPacketIdentifier id , guint16 r)
  :NetPacketBase(id)
{
  setResponseId(r);

}

/** Changes the response identifier
  *
  * \param r The new identifier
  *
  */
void RainbruRPG::Network::NetPacketFlooderBase::setResponseId(guint16 r){
  responseId=r;
}

/** Get the response identifier
  *
  * \return The response identifier
  *
  */
guint16 RainbruRPG::Network::NetPacketFlooderBase::getResponseId(){
  return responseId;
}
