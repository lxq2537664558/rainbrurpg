/*
 *  Copyright 2006 Jerome PASQUIER
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

/* Modifications :
 * - 31 jul 2007 : Add a test option
 * - 20 jul 2007 : Starting implementation
 *
 */

#include <iostream>
#include <string>

#include <hashfile.h>
#include <hashpassword.h>
#include <CEGUI/CEGUI.h>

#include <sigc++/sigc++.h>

using namespace std;
using namespace CEGUI;
using namespace RainbruRPG::Core;
using namespace RainbruRPG::Network::Ident;

int oldPercent=-1;



// forward declaration
void showHelp();
void fileProgress(int size, int dled, double percent);
void testHashPassword();
void oneTest(HashPassword*, const char*);
// forward declaration ended




/** The HashSum program main function
  *
  */
int main(int argc, char** argv){

  if (argc==2&&strcmp(argv[1], "-t")==0){
    testHashPassword();
  }
  else if (argc!=3){
    showHelp();
  }
  else if(strcmp(argv[1], "-f")!=0 && strcmp(argv[1], "-p")!=0){
    showHelp();
  }
  else if(strcmp(argv[1], "-f")==0){
    std::string s(argv[2]);
    cout << "Computing hashsum for file '" << s << "'"
	 << " using HashFile" <<  endl;
    HashFile hf;
    hf.progress.connect( sigc::ptr_fun(fileProgress) );
    cout << hf.getHashSum(s)<< endl;
  }
  else if(strcmp(argv[1], "-p")==0){
    CEGUI::String s(argv[2]);
    cout << "Computing hashsum for string '" << s << "'"
	 << " using HashPassword" <<  endl;
    HashPassword hp;
    cout << hp.encryptString(s.c_str())<< endl;
    
  }

  return 1;
}

void fileProgress(int size, int dled, double percent){
  if ((int)percent!=oldPercent){
    cout << "fileProgress : "<< (int)percent << "% \t("
	 << dled << "/" << size <<" bytes)" <<endl;
    oldPercent=(int)percent;
  }
}

/** Show a help message if needed
  *
  *
  *
  */
void showHelp(){
  cout << "hashsum argument error :" << endl;
  cout << "  transmsg -t test results with a basic content" << endl
       << "  transmsg -f <file_name> to get SHA-1 hashsum of a file" << endl
       << "  transmsg -p <password> to get it for a string" << endl;

}

void oneTest(HashPassword* hp, const char* pwd){
  cout << "Testing with " << pwd <<" :"<< endl;
  cout << "Direct                :"
       << hp->encryptString(pwd)<< endl;
  cout << "Through const char*   :"
       << hp->encryptString((const char*)pwd)<< endl;
  cout << "Through std::string   :"
       << hp->encryptString(std::string(pwd).c_str())<< endl;
  cout << "Through CEGUI::string :"
       << hp->encryptString(String(pwd).c_str())<< endl;

}


void testHashPassword(){
  HashPassword hp;
  oneTest(&hp, "aaa");
}
