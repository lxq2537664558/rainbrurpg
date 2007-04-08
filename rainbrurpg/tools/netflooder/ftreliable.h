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

#ifndef FLOODER_TEST_RELIABLE
#define FLOODER_TEST_RELIABLE

#include "floodertestbase.h"

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
      ftReliable();
      virtual ~ftReliable();

      virtual int getTotalProgressStep();
      virtual void run(EnetBase* );
    };

  }
}

#endif // FLOODER_TEST_RELIABLE
