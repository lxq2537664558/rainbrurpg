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

#include "Benchmark.hpp"

void myfunc(void)
{
  int t = 1;
  double t2 = 1 * 8000 /3;
  for (int i=0; i < 15000; i++) t2 = t+i;
}

int
main()
{
  
  benchmark ("myfunc", "v1.0", &myfunc, 1);
  benchmark ("myfunc", "v1.0", &myfunc, 10);
  benchmark ("myfunc", "v1.0", &myfunc, 100);
  benchmark ("myfunc", "v1.0", &myfunc, 1000);
  benchmark ("myfunc", "v1.0", &myfunc, 10000);
  benchmark ("myfunc", "v1.0", &myfunc, 100000);

  return 0;
}
