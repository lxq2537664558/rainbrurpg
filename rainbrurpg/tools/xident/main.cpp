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

/** \file tools/xident/main.cpp
  * Declares the XIdent main entry
  *
  * Modifications :
  * - 22 sep 2008 : Single file documentation
  *
  */

#include <iostream>
#include <string>

#include <logger.h>

/// Needed to include version without Ogre
#define INCLUDE_VERSION_WITHOUT_OGRE
#include <version.h>

#include <fox-1.6/fx.h>
#include <hashpassword.h>

#include "xidentwindow.h"

using namespace FX;
using namespace std;
using namespace RainbruRPG::Gui;
using namespace RainbruRPG::Network::Ident;

/// The correct user name hash sum
#define USER_HASH "20DB5DCC44B3A44C4BC0592C6AB55B8216932FE7"

/// The correct password hash sum
#define PWD_HASH  "AC3E7B007D7AB0BA379FAA8AB62D9DA35C5444F4"

/// An enumeration that defines the connection response
typedef enum{
  XIC_SUCCESS        = 0x00, //!< The connection is accepted
  XIC_WRONG_PASSWORD = 0x01, //!< The password is wrong
  XIC_WRONG_USERNAME = 0x02, //!< The username control failed
}tXIdentConnection;

// Forward declarations
int launchIdent(int argc, char **argv);
tXIdentConnection connect();
// End of forward declarations


/** xIdent main entry
  *
  * \param argc The number of command-line arguments
  * \param argv The array of command-line arguments
  *
  */
int main(int argc, char **argv){

  tXIdentConnection conn=connect();

  if (conn==XIC_SUCCESS){
    return launchIdent(argc, argv);
  }
  else{
    return conn;
  }
}

/** Launch the XIdent FOX window
  *
  * You \b must pass the main function argument to this.
  *
  * \param argc The number of command-line arguments
  * \param argv The command-line arguments array
  *
  * \return The return of the FXApp.run() function
  *
  */
int launchIdent(int argc, char **argv){
  FX::FXApp application("RainbruRPG","rainbruFreeFr");
  
  // The true should cause a segfault if omitted
  application.init(argc,argv, true);

  new XIdentWindow(&application);
  application.create();

  return application.run();
}

/** Ask a connection of the user
  *
  * It uses std::cin to get username and password from the console.
  * 
  * \return A value that define if the connection is accepted or refused.
  *
  */
tXIdentConnection connect(){
  tXIdentConnection ret;

  // The hashsum in #define directives
  std::string neededUserHash, neededPwdHash;

  // The entered values
  std::string enteredUser, enteredPwd;

  // The hashsumbased on entered values
  std::string enteredUserHash, enteredPwdHash;

  // Starting process
  neededUserHash=USER_HASH;
  neededPwdHash=PWD_HASH;

  cout << "Enter username : ";
  cin >> enteredUser;
  cout << "Enter password : ";
  cin >> enteredPwd;

  HashPassword hp;
  enteredUserHash=hp.encryptString(enteredUser.c_str());
  enteredPwdHash=hp.encryptString(enteredPwd.c_str());

  if (enteredUserHash==neededUserHash){
    if (enteredPwdHash==neededPwdHash){
      ret=XIC_SUCCESS;
      cout << "Login successfull" << endl;
    }
    else{
      cout << "Password error" << endl;
      ret=XIC_WRONG_PASSWORD;
    }
  }
  else{
    cout << "Username error" << endl;
    ret=XIC_WRONG_USERNAME;
  }
  return ret;
}
