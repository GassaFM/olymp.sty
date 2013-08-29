#include <algorithm>
#include <cassert>
#include <cstdio>
#include <vector>
#include <map>
#include <set>


using namespace std;

#define TASKNAME "arithmetic"

const int MaxC = 0x3f3f3f3f;

int a[123456];

vector <set <int> > v;

int main (void)
{
  freopen (TASKNAME ".in", "rt", stdin);
  freopen (TASKNAME ".out", "wt", stdout);

  int n;
  while (scanf (" %d", &n) > 0)
  {    
    int i, j, k, res;

    for (i = 0; i < n; i++)
      scanf (" %d", &a[i]);
    
    if (n >= 8)
    {
      res = 0;
      printf ("%d\n", res);
      continue;
    }
    v.clear();
    v.resize(1 << n);
    for (i = 0; i < n; i++)
      v[1 << i].insert(a[i]);
    for (i = 0 ; i < (1 << n); i++)
    {
      for (j = i & (i - 1); j > 0; j = i & (j - 1))
      {
        k = i ^ j;
        for (set <int> :: iterator itj = v[j].begin(); itj != v[j].end(); itj++)
          for (set <int> :: iterator itk = v[k].begin(); itk != v[k].end(); itk++)
          {
            if (*itj == *itk)
            {
              res = 0;
              goto a;
            }
            v[i].insert (abs(*itj - *itk)); 
            v[i].insert (*itj + *itk);
            if ((long long) *itj * *itk < 1000000)
              v[i].insert (*itj * *itk), 
            v[i].insert (abs(*itj - *itk)); 
          }
      }
    }
    res = MaxC;
    i = (1 << n) - 1;
    for (set <int> :: iterator it = v[i].begin(); it != v[i].end(); it++)
      if (res > *it)
        res = *it;
    a:   
    printf ("%d\n", res);
  }

  return 0;
}
