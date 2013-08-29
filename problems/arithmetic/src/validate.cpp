#include "testlib.h"
#include <stdint.h>
#include <string>

const int MIN_N = 1, MAX_N = 100000;
const int MIN_A = 1, MAX_A = 30;

int main (void)
{
 registerValidation ();

 int n = inf.readInt (MIN_N, MAX_N);
 inf.readEoln ();
 for (int i = 0; i < n; i++)
 {
  if (i > 0)
   inf.readSpace ();
  inf.readInt (MIN_A, MAX_A);
 }
 inf.readEoln ();
 inf.readEof ();

 return 0;
}
