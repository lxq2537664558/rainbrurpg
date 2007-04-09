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

/* Modifications : 
 * - 27 mar 2007 : starting implementation
 *
 */

#ifndef FLOODER_TEST_BASE
#define FLOODER_TEST_BASE

#include "enetflooderclient.h"

namespace RainbruRPG{
  namespace Network{
    /** The base class of all netflooder's tests
      *
      * This class is used to make a list of test and to make easier the
      * creation of new flood test.
      *
      * \section needs_sec Needs
      *
      * These are the goals of this class :
      * - The tests should be correctly integrate to the FOX GUI. So it must
      *   deal with ProgressBar. 
      * - Each test must deal with the EnetClient used
      *   to flood a server.
      * - Each test can be part of a ChartBase. The statistics taken from
      *   a flooder should be a single value list. So if the user chose
      *   to launch several tests, they can be drawn in a single chart.
      *
      */
    class FlooderTestBase{
    public:
      FlooderTestBase();
      virtual ~FlooderTestBase();

      /** Get the total number of test realized
        *
	* It is used to set correctly the progressbar
	*
	*/
      virtual int getTotalProgressStep()=0;

      /** Runs the test in the given ENet host
        *
	* \param host The host uses to send test packets
	*
	*/
      virtual void run(EnetFlooderClient* host)=0;

      const char* getName();
      const char* getDescription();

    protected:
      /** The test name */
      const char* name;
      /** The test description
        *
	* It must stand in only one line.
	*
	*/
      const char* description;
    };
  }
}

#endif // FLOODER_TEST_BASE