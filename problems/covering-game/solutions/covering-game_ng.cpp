#include <cstdio>
#include <iostream>

using namespace std;

#define TASKNAME "covering-game"

int main (void)
{
  freopen (TASKNAME ".in", "rt", stdin);
  freopen (TASKNAME ".out", "wt", stdout);

  int n;
  while (scanf (" %d %*s", &n) > 0)
  {
    string res[3] = {"No", "No", "No"};
    res[(n/2 + 1) % 3] = "Yes";
    for (int i = 0; i < 3; i++)
      cout << res[i] << '\n';    
  }

  return 0;
}
