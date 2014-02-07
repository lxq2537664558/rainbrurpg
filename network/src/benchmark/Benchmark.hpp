 /*
 *  Copyright 2006-2014 Jerome PASQUIER
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

#include <sys/time.h> // use gettimeofday()
#include <string> 
#include <iostream>

using namespace std;

typedef void (*ptrfunc)(void);

// Returns the interval in seconds
double
diff( struct timeval* a, struct timeval* b)
{
  return (b->tv_sec-a->tv_sec) + ((double)(b->tv_usec-a->tv_usec)/1000000);
}

// Make a benchmark of a function pointer x times
void 
benchmark( const string& name, const string& version, ptrfunc f, int times = 1)
{
  struct timeval v1, v2;
  gettimeofday(&v1, NULL);
  for (int i=0; i < times; i++) (*f)();
  gettimeofday(&v2, NULL);
  double d = diff (&v1, &v2);
  double mspertime= (d*1000000) / times;
  cout << name << " | " << version << " | (x" << times << ") | " << d << "s" 
       << " (soit " << mspertime << "ms per time)"
       << endl;
}
