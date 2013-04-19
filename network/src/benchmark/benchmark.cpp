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
