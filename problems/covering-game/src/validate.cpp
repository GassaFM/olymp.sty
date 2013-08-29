#include "testlib.h"
#include <set>
#include <string>

using namespace std;

const int MIN_N = 1, MAX_N = 100;

int main (void)
{
 registerValidation ();

 int m = inf.readInt (0, 198);
 inf.readEoln ();
 string traversal = inf.readLine ("[lrb]{0,198}");
 string cur = "";
 int len = traversal.size ();
 ensure (len == m);
 set <string> v;
 v.insert (cur);
 for (int i = 0; i < len; i++)
 {
  if (traversal[i] == 'b')
  {
   int t = cur.size ();
   ensure (t > 0);
   cur = cur.substr (0, t - 1);
  }
  else
  {
   if (traversal[i] == 'l')
    ensure (v.find (cur + "r") == v.end ());
   cur += traversal[i];
   ensure (v.find (cur) == v.end ());
   v.insert (cur);
  }
 }
 int n = v.size ();
 ensure (MIN_N <= n && n <= MAX_N);
 ensure (v.find ("r") == v.end ());
 inf.readEof ();

 return 0;
}
