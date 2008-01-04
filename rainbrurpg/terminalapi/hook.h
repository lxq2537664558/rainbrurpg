/*
 *  Copyright 2006-2008 Jerome PASQUIER
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
#ifndef HOOK_H
#define HOOK_H

#include "terminalapp.h"

//using namespace RainbruRPG::Terminal;

static void exit_error_hook (char *fmt, va_list ap){
   SLang_reset_tty ();
   SLsmg_reset_smg ();
   
   vfprintf (stderr, fmt, ap);
   fputc ('\n', stderr);
   exit (1);
}

static void demolib_exit (int sig)
{
   SLang_reset_tty ();
   SLsmg_reset_smg ();

   if (sig)
     {
	fprintf (stderr, "Exiting on signal %d\n", sig);
	exit (1);
     }
   exit (sig);
}


#ifdef SIGTSTP
static void sigtstp_handler (int sig){
   demolib_exit (sig);
}
#endif

#ifdef SIGINT
static void sigint_handler (int sig){
   demolib_exit (sig);
}
#endif

#ifdef SIGWINCH
static void sigwinch_handler (int sig){
  //  RainbruRPG::Terminal::TerminalApp::getSingleton().draw();
}
#endif

#endif // HOOK_H
