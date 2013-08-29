#include "gentools.h"
#include <cstdio>

void open_test (void)
{
}

void close_test (void)
{
}

void log_test (void)
{
}

void verify_test (void)
{
}

void shuffle_test (void)
{
}

void output_test (void)
{
}

int main (void)
{
 int i;
 unsigned x;

 using namespace gentools_random_internal;

 // The first 1000 random values coincide with the original list:
 // http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/MT2002/emt19937ar.html
 unit_test ();
 initrand_array (UTEST_KEY, UTEST_LEN);
 for (i = 0; i < UTEST_STEPS; i++)
 {
  x = rndvalue (0);
  printf ("%10u%c", x, (i % 5 < 4) ? ' ' : '\n');
 }

 return 0;
}
