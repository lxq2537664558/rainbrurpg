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

#include "tokenizerdbg.h"
#include <iostream>

/** The call of this method will run the debugger on the parameter
  *
  * It will print an information message on the standard output and
  * call :
  * - debugCmdType()
  * - debugTxt()
  * - debugErr()
  *
  * \param t the tTokentizerReturn structure to debug
  */
void RainbruRPG::Exception::TokenizerDbg::debug(tTokentizerReturn t ){
  cout << "===== Tokenizer debugger =====" << endl;
  debugCmdType( t );
  debugTxt( t );
  debugErr( t );
}

/** Debug the command type of a tTokentizerReturn structure
  *
  * It will print an information message according to the command type
  * of the parameter :
  * - SIMPLE COMMAND;
  * - DOUBLE COMMAND;
  * - TRIPLE COMMAND;
  * - QUAD COMMAND;
  * - QUINT COMMAND.
  *
  * \param t the tTokentizerReturn structure to debug
  */
void RainbruRPG::Exception::TokenizerDbg::debugCmdType(tTokentizerReturn t ){
  cout << "Debugging command type :" << endl;
  switch(t.cmdType){
  case TCT_SIMPLE: 
    cout << "  command type is SIMPLE COMMAND" << endl;
    break;

  case TCT_DOUBLE:
    cout << "  command type is DOUBLE COMMAND" << endl;
    break;

  case TCT_TRIPLE:
    cout << "  command type is TRIPLE COMMAND" << endl;
    break;

  case TCT_QUAD:
    cout << "  command type is QUAD COMMAND" << endl;
    break;

  case TCT_QUINT:
    cout << "  command type is QUINT COMMAND" << endl;
    break;

  default:
    cout << "  WARNING : no command type defined" << endl;

  }
  cout << endl;

}

/** Print the values of a tTokentizerReturn structure
  *
  * It will print an the values of the folowwing fields :
  * - cmd
  * - obj
  * - att
  * - val
  * - id
  *
  * \param t the tTokentizerReturn structure to debug
  */
void RainbruRPG::Exception::TokenizerDbg::debugTxt(tTokentizerReturn t ){
  cout << "Debugging value content :" << endl;
  cout << "  cmd=["<< t.cmd <<"]\t" << endl;
  cout << "  obj=["<< t.obj <<"]\t" << endl;
  cout << "  att=["<< t.att <<"]" << endl;
  cout << "  val=["<< t.val <<"]\t" << endl;
  cout << "  id =["<< t.id  <<"]" << endl;
  cout << endl;
}

/** Print the error message of a tTokentizerReturn structure
  *
  * It will print a message if an error is returned in the
  * tTokentizerReturn structure passed in parameter :
  * - The command is empty
  * - A quote is missing
  * - A bracket is missing
  * - An unknown separator (?) is missing
  * - No error
  *
  * \param t the tTokentizerReturn structure to debug
  */
void RainbruRPG::Exception::TokenizerDbg::debugErr(tTokentizerReturn t ){
  cout << "Debugging Errors :" << endl;
  switch(t.err){
  case TET_EMPTY: 
    cout << "  The command is empty" << endl;
    break;

  case TET_MISSING_QUOTE:
    cout << "  A quote is missing" << endl;
    break;

  case TET_MISSING_BRACKET:
    cout << "  A bracket is missing" << endl;
    break;

  case TET_UNKNOW_SEPARATOR_MISSING:
    cout << "  An unknown separator (?) is missing" << endl;
    break;

  default:
    cout << "  No error" << endl;

  }
  cout << endl;
}
