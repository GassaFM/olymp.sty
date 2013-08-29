#include <algorithm>
#include <cassert>
#include <cstdio>
#include <vector>

using namespace std;

#define IOFILES
#define TASKNAME "arithmetic"

#ifdef DEBUG
#define eprintf(...) fprintf (stderr, __VA_ARGS__)
#else
#define eprintf(...) assert (true)
#endif

int const MIN_N = 1, MAX_N = 100000;
int const MIN_A = 1, MAX_A = 30;

int res;

void recur (vector <int> v)
{
 int n = (int) v.size ();

 if (n == 1)
 {
  res = min (res, v[0]);
  return;
 }

 for (int i = 0; i < n - 1; i++)
  for (int j = i + 1; j < n; j++)
  {
   vector <int> u = v;
   swap (u[j], u[n - 1]);
   u.resize (n - 1);
   u[i] = v[i] + v[j];
   if (u[i] <= MAX_A)
   {
    recur (u);
    if (res == 0)
     return;
   }
   u[i] = v[i] * v[j];
   if (u[i] <= MAX_A)
   {
    recur (u);
    if (res == 0)
     return;
   }
   u[i] = abs (v[i] - v[j]);
   recur (u);
   if (res == 0)
    return;
  }
}

int main (void)
{
#ifdef IOFILES
 freopen (TASKNAME ".in", "rt", stdin);
 freopen (TASKNAME ".out", "wt", stdout);
#endif

 int n;
 while (scanf (" %d", &n) > 0)
 {
  assert (MIN_N <= n && n <= MAX_N);

  vector <int> v;
  for (int i = 0; i < n; i++)
  {
   int a;
   scanf (" %d", &a);
   assert (MIN_A <= a && a <= MAX_A);
   v.push_back (a);
  }

  res = MAX_A;
  recur (v);

  printf ("%d\n", res);
 }

 return 0;
}
