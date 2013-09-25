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

/** \file virtualaccount.h
  * Declares a virtual account
  *
  * This file is used to define  some macro used to create a
  * virtual  account. This  informations are  shared by some
  * files  and  to  avoid  multiple definitions.  There  are
  * defined once, in this file.
  *
  * Modifications :
  * - 27 aug 2008 : Single file documentation
  * - 07 mar 2007 : Moving defines from clientconnecttest.h
  *
  */

#ifndef VIRTUAL_ACCOUNT_H
#define VIRTUAL_ACCOUNT_H

/** A name used to test the inexistance of a client
  *
  * I hope this client never exist but it will be created to test
  * some other responses.
  *
  */
#define CLIENT_NAME "ImpossibleClientNameThatDoNotExists_IHOPE"

/** A name used to test a second account
  *
  * I hope this client never exist but it will be created to test
  * some other responses.
  *
  */
#define CLIENT_NAME2 "ImpossibleClientNameThatDoNotExists_IHOPE_again"


/** It is a known password when we have to create it
  *
  */
#define CLIENT_PWD "password"

/** It is a known-to-be-wrong password
  *
  */
#define CLIENT_WRONG_PWD "WrongPassword"

/** The email address of the added account 
  *
  */
#define CLIENT_MAIL "mail@mail.mail"

/** A email address with a missing At sign
  *
  */
#define CLIENT_MAIL_EAT "mailmail.mail"

/** A email address with a missing dot
  *
  */
#define CLIENT_MAIL_EDOT "mail@mailmail"

#endif // VIRTUAL_ACCOUNT_H
