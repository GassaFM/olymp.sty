// Factorize integers lower and higher than 2^{32}
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <map>
#include <stdint.h>
#include <vector>

using namespace std;

#define TASKNAME "arithmetic"

#ifdef WIN32
#define INT64 "%I64d"
#else
#define INT64 "%lld"
#endif

#ifdef DEBUG
#define eprintf(...) fprintf (stderr, __VA_ARGS__)
#else
#define eprintf(...) assert (true)
#endif

int const MIN_N = 1, MAX_N = 100000;
int const MIN_A = 1, MAX_A = 30;

int main (void)
{
 int64_t a;

 for (a = (1LL << 32) + 1; ; a++)
 {
  vector <int> v;
  int64_t b = a;
  for (int i = 30; i >= 2; i--)
   while (b % i == 0)
   {
    b /= i;
    v.push_back (i);
   }
  if (b == 1 && v.size () <= 7)
  {
   printf (INT64 " %d", a, (int) v.size ());
   for (int i = 0; i < (int) v.size (); i++)
    printf (" %d", v[i]);
   printf ("\n");
   break;
  }
 }

 for (a = (1LL << 32) - 1; ; a--)
 {
  vector <int> v;
  int64_t b = a;
  for (int i = 30; i >= 2; i--)
   while (b % i == 0)
   {
    b /= i;
    v.push_back (i);
   }
  if (b == 1 && v.size () <= 7)
  {
   printf (INT64 " %d", a, (int) v.size ());
   for (int i = 0; i < (int) v.size (); i++)
    printf (" %d", v[i]);
   printf ("\n");
   break;
  }
 }

 for (a = (1LL << 32) + 1; ; a++)
 {
  vector <int> v;
  int64_t b = a;
  for (int i = 30; i >= 2; i--)
   if (b % i == 0)
   {
    b /= i;
    v.push_back (i);
   }
  if (b == 1 && v.size () <= 7)
  {
   printf (INT64 " %d", a, (int) v.size ());
   for (int i = 0; i < (int) v.size (); i++)
    printf (" %d", v[i]);
   printf ("\n");
   break;
  }
 }

 for (a = (1LL << 32) - 1; ; a--)
 {
  vector <int> v;
  int64_t b = a;
  for (int i = 30; i >= 2; i--)
   if (b % i == 0)
   {
    b /= i;
    v.push_back (i);
   }
  if (b == 1 && v.size () <= 7)
  {
   printf (INT64 " %d", a, (int) v.size ());
   for (int i = 0; i < (int) v.size (); i++)
    printf (" %d", v[i]);
   printf ("\n");
   break;
  }
 }

 return 0;
}
