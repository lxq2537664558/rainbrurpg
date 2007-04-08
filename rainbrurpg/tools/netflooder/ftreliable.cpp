/*
 *  Copyright 2006-2007 Jerome PASQUIER
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

#include "ftreliable.h"

/** The default constructor
  *
  */
RainbruRPG::Network::ftReliable::ftReliable()
  :FlooderTestBase(){

  this->name="Reliable";
  this->description="Compare performance between reliable and "
    "non-reliable packets";

}

/** The destructor
  *
  */
RainbruRPG::Network::ftReliable::~ftReliable(){

}

/** Get the total number of test realized
  *
  * It is used to set correctly the progressbar
  *
  * \return The number of step needed to finish the test
  *
  */
int RainbruRPG::Network::ftReliable::getTotalProgressStep(){
  return 1;
}

/** Runs the test using the given ENet host
  *
  * \param host The host uses to send test packets
  *
  */
void RainbruRPG::Network::ftReliable::run(EnetBase* host){

}
