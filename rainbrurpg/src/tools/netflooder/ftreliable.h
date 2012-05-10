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

/** \file tools/netflooder/ftreliable.h
  * Declares a test for reliable/non-reliable packets
  *
  * Modifications :
  * - 22 sep 2008 : Single file documentation
  * - 27 mar 2007 : starting implementation
  *
  */

#ifndef FLOODER_TEST_RELIABLE
#define FLOODER_TEST_RELIABLE

#include <ctime>
#include <iostream>
#include <sigc++/sigc++.h>

#include <ChartSerie.hpp>
#include <ChartLine.hpp>
#include <NpFlooder0004.hpp>

#include "floodertestbase.h"

/** If a response is more than this, it is eaqual to this
  *
  * It is used to get a more readable chart.
  *
  */
#define MAX_INTERVAL_ACCEPTED 15000

using namespace std;

namespace RainbruRPG{
  namespace Network{

    /** A flooder test to compare performance of reliable/non-reliable packets
      *
      * 
      *
      *
      */
    class ftReliable : public FlooderTestBase{
    public:
      /** Defines a signal returning void with none parameters */
      typedef sigc::signal<void> tVoidSignal;

      ftReliable();
      virtual ~ftReliable();

      virtual int getTotalProgressStep();
      virtual void run(EnetFlooderClient* );
      virtual int getTotalSteps();

      /** A signal when test progress*/
      tVoidSignal sigProgressOneStep;

    private:
      /** Number of test for each packet type */
      int nbTest;

    };
  }
}

#endif // FLOODER_TEST_RELIABLE
