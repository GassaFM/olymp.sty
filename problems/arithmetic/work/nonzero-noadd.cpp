// Lists all tests with non-zero answer and their answers, no addition
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <map>
#include <vector>

using namespace std;

#define TASKNAME "arithmetic"

#ifdef DEBUG
#define eprintf(...) fprintf (stderr, __VA_ARGS__)
#else
#define eprintf(...) assert (true)
#endif

int const MIN_N = 1, MAX_N = 100000;
int const MIN_A = 1, MAX_A = 30;

int res;

int recur (vector <int> v)
{
 int n = (int) v.size ();

 if (n == 1)
  return v[0];

 int res = MAX_A;
 for (int i = 0; i < n - 1; i++)
  for (int j = i + 1; j < n; j++)
  {
   vector <int> u = v;
   swap (u[j], u[n - 1]);
   u.resize (n - 1);
   u[i] = abs (v[i] - v[j]);
   res = min (res, recur (u));
   if (res == 0)
    return res;
/*
   u[i] = v[i] + v[j];
   res = min (res, recur (u));
   if (res == 0)
    return res;
*/
   u[i] = v[i] * v[j];
   res = min (res, recur (u));
   if (res == 0)
    return res;
  }
 return res;
}

int solve (int mask)
{
 vector <int> v;
 for (int i = MIN_A; i <= MAX_A; i++)
  if (mask & (1 << i))
   v.push_back (i);
 return recur (v);
}

void out (int z, int mask)
{
 printf ("%d", z);
 for (int j = MIN_A; j <= MAX_A; j++)
  if (mask & (1 << j))
   printf (" %2d", j);
}

int main (void)
{
 map <int, int> s;
 for (int i = MIN_A; i <= MAX_A; i++)
  s[1 << i] = i;
 int z = 1;
 while ((int) s.size () > 0)
 {
  printf ("numbers %d total %d\n", z, (int) s.size ());
  map <int, int> t;
  for (map <int, int>::iterator it = s.begin (); it != s.end (); it++)
  {
   int mask = it -> first;
   out (z, mask);
   printf (" answer %2d\n", it -> second);
   int k = 0;
   for (int j = MIN_A; j <= MAX_A; j++)
    if (mask & (1 << j))
     k = j;

   for (k++; k <= MAX_A; k++)
   {
    assert (!(mask & (1 << k)));
    mask ^= 1 << k;

    int ok = 0;
    for (int j = MIN_A; j <= MAX_A; j++)
     if (mask & (1 << j))
     {
      mask ^= 1 << j;
      ok += (s.find (mask) != s.end ());
      mask ^= 1 << j;
     }

    if (ok == z + 1)
    {
     int w = solve (mask);
     if (w != 0)
      t[mask] = w;
    }
    else if (ok == z)
    {
     out (z + 1, mask);
     printf (" almost %d %d\n", z, z + 1);
    }

    mask ^= 1 << k;
   }
  }
  s = t;
  z++;
 }

 return 0;
}
