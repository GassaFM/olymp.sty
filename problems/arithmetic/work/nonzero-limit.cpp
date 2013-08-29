// Lists all tests with non-zero answer and their answers, finds upper limit
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <map>
#include <utility>
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

pair <int, int> recur (vector <int> v, int lim)
{
 int n = (int) v.size ();

 if (n == 1)
  return make_pair (v[0], lim);

 pair <int, int> res = make_pair (MAX_A, MAX_A);
 for (int i = 0; i < n - 1; i++)
  for (int j = i + 1; j < n; j++)
  {
   vector <int> u = v;
   swap (u[j], u[n - 1]);
   u.resize (n - 1);
   u[i] = abs (v[i] - v[j]);
   res = min (res, recur (u, max (lim, u[i])));
/*
   if (res.first == 0)
    return res;
*/
   u[i] = v[i] + v[j];
   res = min (res, recur (u, max (lim, u[i])));
/*
   if (res.first == 0)
    return res;
*/
   u[i] = v[i] * v[j];
   res = min (res, recur (u, max (lim, u[i])));
/*
   if (res.first == 0)
    return res;
*/
  }
 return res;
}

pair <int, int> solve (int mask)
{
 vector <int> v;
 int m = 0;
 for (int i = MIN_A; i <= MAX_A; i++)
  if (mask & (1 << i))
  {
   v.push_back (i);
   m = max (m, i);
  }
 return recur (v, m);
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
 map <int, pair <int, int> > s;
 for (int i = MIN_A; i <= MAX_A; i++)
  s[1 << i] = make_pair (i, i);
 int z = 1;
 while ((int) s.size () > 0)
 {
  printf ("numbers %d total %d\n", z, (int) s.size ());
  map <int, pair <int, int> > t;
  for (map <int, pair <int, int> >::iterator it = s.begin ();
       it != s.end (); it++)
  {
   int mask = it -> first;
   out (z, mask);
   printf (" answer %2d limit %4d\n",
           it -> second.first,
           it -> second.second);
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
     pair <int, int> w = solve (mask);
     if (w.first != 0)
      t[mask] = w;
    }

    mask ^= 1 << k;
   }
  }
  s = t;
  z++;
 }

 return 0;
}
