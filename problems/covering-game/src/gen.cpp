#define PROBLEM_NAME "covering-game"
#define TEST_STR "%03d"
#include "gentools.h"

#include <cstring>
#include <string>

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

using namespace std;

const int MIN_N = 1, MAX_N = 100;

const int MAX_D = 3;
const char DIR [MAX_D] = {'l', 'r', 'b'};
const int NA = -1;

struct node
{
 int l, r, b;
};

node v [MAX_N];
string traversal;
int m, n;
double p;

void do_nothing (void)
{
// do nothing
}

void open_test (void)
{
 memset (v, NA, sizeof (v));
 n = 1;
}

int build_traversal (string cur, int ptr)
{
 string next;
 int res = 1;

 if (v[ptr].l != NA)
 {
  next = cur + "l";
  traversal += "l";
  res += build_traversal (next, v[ptr].l);
  traversal += "b";
 }

 if (v[ptr].r != NA)
 {
  next = cur + "r";
  traversal += "r";
  res += build_traversal (next, v[ptr].r);
  traversal += "b";
 }

 return res;
}

void close_test (void)
{
 assert (MIN_N <= n && n <= MAX_N);
 traversal = "";
 assert (v[0].r == NA);

 int n_check = build_traversal ("", 0);
 assert (n_check == n);
}

void log_test (void)
{
 fprintf (flog, "n = %d", n);
}

void shuffle_test (void)
{
 do_nothing ();
}

void verify_test (void)
{
// verification already done in close_test
 do_nothing ();
}

void output_test (void)
{
 FILE * fout;

 fout = fopen (cur_test_str, "wt");
 assert (fout != NULL);

 fprintf (fout, "%d\n%s\n", (int) traversal.size (), traversal.c_str ());

 fclose (fout);
}


int get_node (const string to_move)
{
 int len = to_move.size ();

 int ptr = 0;
 for (int i = 0; i < len; i++)
 {
  if      (to_move[i] == 'l')
   ptr = v[ptr].l;
  else if (to_move[i] == 'r')
   ptr = v[ptr].r;
  else
   assert (false);
  assert (ptr != NA);
 }

 return ptr;
}

void add_vertex_by_name (const string to_add_arg)
{
 assert (n < MAX_N);
 string to_add = string ("l") + to_add_arg;
 int len = to_add.size ();
 int ptr = get_node (to_add.substr (0, len - 1));

 if      (to_add[len - 1] == 'l')
 {
  assert (v[ptr].l == NA);
  v[ptr].l = n;
  v[n].b = ptr;
  n++;
 }
 else if (to_add[len - 1] == 'r')
 {
  assert (v[ptr].r == NA);
  v[ptr].r = n;
  v[n].b = ptr;
  n++;
 }
 else
 {
  assert (false);
 }
}

void add_vertex_by_node (int k, int d)
{
 assert (n < MAX_N);
 assert (0 <= k && k < n);

 if      (d == 0)
 {
  assert (v[k].l == NA);
  v[k].l = n;
  v[n].b = k;
  n++;
 }
 else if (d == 1)
 {
  assert (k != 0);
  assert (v[k].r == NA);
  v[k].r = n;
  v[n].b = k;
  n++;
 }
 else
 {
  assert (false);
 }
}

void gen_random (int num)
{
 if (n == 1)
 {
  add_vertex_by_name ("");
  num--;
 }

 for (int i = 0; i < num; i++)
 {
  int k, d;
  bool ok;
  do
  {
   k = rndvalue (1, n - 1);
   d = rndvalue (2);
   if      (d == 0)
    ok = (v[k].l == NA);
   else if (d == 1)
    ok = (v[k].r == NA);
   else
    assert (false);
  }
  while (!ok);

  add_vertex_by_node (k, d);
 }
}

int gen_full (int pos, int depth, int num = MAX_N - 1)
{
 if (n == 1)
 {
  add_vertex_by_name ("");
  num--;
 }

 if (depth == 0)
  return num;

 if (v[pos].l == NA)
 {
  add_vertex_by_node (pos, 0);
  num--;
  if (num == 0)
   return num;
 }
 num = gen_full (v[pos].l, depth - 1, num);
 if (num == 0)
  return num;

 if (v[pos].r == NA)
 {
  add_vertex_by_node (pos, 1);
  num--;
  if (num == 0)
   return num;
 }
 num = gen_full (v[pos].r, depth - 1, num);

 return num;
}

int gen_full_back (int pos, int depth, int num = MAX_N - 1)
{
 if (n == 1)
 {
  add_vertex_by_name ("");
  num--;
 }

 if (pos == 0)
  return num;

 if (depth == 0)
  return num;

 if (v[pos].l == NA)
 {
  add_vertex_by_node (pos, 0);
  num--;
  if (num == 0)
   return num;
 }
 num = gen_full_back (v[pos].l, depth - 1, num);
 if (num == 0)
  return num;

 if (v[pos].r == NA)
 {
  add_vertex_by_node (pos, 1);
  num--;
  if (num == 0)
   return num;
 }
 num = gen_full_back (v[pos].r, depth - 1, num);
 if (num == 0)
  return num;

 num = gen_full_back (v[pos].b, depth - 1, num);

 return num;
}

void gen_fat (int pos, int depth, int num = MAX_N - 1)
{
 assert (depth > 0);

 if (n == 1)
 {
  add_vertex_by_name ("");
  num--;
 }

 while (num > 0)
 {
  int k = rndvalue (1, n - 1);
  num = gen_full (k, depth, num);
 }
 assert (num == 0);
}

void gen_fat_back (int pos, int depth, int num = MAX_N - 1)
{
 assert (depth > 0);

 if (n == 1)
 {
  add_vertex_by_name ("");
  num--;
 }

 while (num > 0)
 {
  int k = rndvalue (1, n - 1);
  num = gen_full (k, depth, num);
 }
 assert (num == 0);
}


void gen_samples (void)
{
 shuffle_flag = false;

 START_TEST ("first example");
 add_vertex_by_name ("");
 add_vertex_by_name ("l");
 add_vertex_by_name ("r");
 END_TEST ();
}

void gen_small (void)
{
 shuffle_flag = false;

 START_TEST ("minimal test 1");
 END_TEST ();

 START_TEST ("minimal test 2");
 add_vertex_by_name ("");
 END_TEST ();

 START_TEST ("minimal test 3");
 add_vertex_by_name ("");
 add_vertex_by_name ("l");
 END_TEST ();

 START_TEST ("minimal test 4");
 add_vertex_by_name ("");
 add_vertex_by_name ("r");
 END_TEST ();

 START_TEST ("minimal test 5");
 add_vertex_by_name ("");
 add_vertex_by_name ("l");
 add_vertex_by_name ("ll");
 END_TEST ();

 START_TEST ("small test 1");
 gen_random (9);
 END_TEST ();

 START_TEST ("small test 2");
 gen_full (1, 2);
 END_TEST ();

 START_TEST ("small test 3");
 gen_fat (1, 1, 9);
 END_TEST ();

 START_TEST ("small test 4");
 for (int i = 1; i <= 5; i++)
 {
  gen_full_back (i, 2);
 }
 END_TEST ();

 START_TEST ("small test 5");
 gen_fat_back (1, 1, 15);
 END_TEST ();
}

void gen_medium (void)
{
 shuffle_flag = false;

 START_TEST ("medium test 1");
 gen_full (1, 3);
 END_TEST ();

 START_TEST ("medium test 2");
 gen_full (1, 4);
 END_TEST ();

 int num;

 num = 0;
 for (int len = 12; len < MAX_N; len += rndvalue (5, 10))
 {
  num++;
  START_TEST ("medium random test %d", num);
  gen_random (len);
  END_TEST ();
 }

 num = 0;
 for (int len = 13; len < MAX_N; len += rndvalue (5, 10))
 {
  num++;
  START_TEST ("medium fat test %d", num);
  int fatness = rndvalue (1, 3);
  gen_fat (1, fatness, len);
  END_TEST ();
 }

 num = 0;
 for (int len = 14; len < MAX_N; len += rndvalue (5, 10))
 {
  num++;
  START_TEST ("medium fat-back test %d", num);
  int fatness = rndvalue (1, 3);
  gen_fat_back (1, fatness, len);
  END_TEST ();
 }
}

void gen_large (void)
{
 shuffle_flag = false;

 START_TEST ("large test 1");
 gen_random (MAX_N - 1);
 END_TEST ();

 START_TEST ("large test 2");
 gen_full (1, 5);
 END_TEST ();

 START_TEST ("large test 3");
 for (int i = 1; i <= 11; i++)
 {
  gen_full_back (i, 3);
 }
 END_TEST ();

 for (int i = 1; i <= 5; i++)
 {
  START_TEST ("large fat test %d", i);
  gen_fat (1, i);
  END_TEST ();
 }

 for (int i = 1; i <= 5; i++)
 {
  START_TEST ("large fat-back test %d", i);
  gen_fat (1, i);
  END_TEST ();
 }

 START_TEST ("maximal test 1");
 {
  string cur = "";
  for (int i = 0; i < MAX_N - 1; i++)
  {
   add_vertex_by_name (cur);
   cur += "l";
  }
 }
 END_TEST ();

 START_TEST ("maximal test 2");
 {
  string cur = "";
  for (int i = 0; i < MAX_N - 1; i++)
  {
   add_vertex_by_name (cur);
   if (rndvalue (2))
    cur += "l";
   else
    cur += "r";
  }
 }
 END_TEST ();

 START_TEST ("maximal test 3");
 {
  string cur = "";
  for (int i = 0; i < MAX_N / 2; i++)
  {
   add_vertex_by_name (cur);
   cur += "l";
  }
  gen_random (MAX_N / 2 - 1);
 }
 END_TEST ();

 START_TEST ("maximal test 4");
 {
  string cur = "";
  for (int i = 0; i < MAX_N / 2; i++)
  {
   add_vertex_by_name (cur);
   if (rndvalue (2))
    cur += "l";
   else
    cur += "r";
  }
  gen_full_back (MAX_N / 4, 4);
 }
 END_TEST ();

 START_TEST ("maximal test 5");
 {
  string cur = "";
  for (int i = 0; i < MAX_N / 2; i++)
  {
   add_vertex_by_name (cur);
   cur += "l";
  }
  gen_full_back (3, 3);
  gen_full_back (MAX_N / 2 - 3 - 1, 3);
 }
 END_TEST ();

 START_TEST ("maximal test 6");
 {
  string cur = "";
  for (int i = 0; i < 25; i++)
  {
   add_vertex_by_name (cur);
   if (rndvalue (2))
    cur += "l";
   else
    cur += "r";
  }
  gen_full_back ( 3, 3);
  gen_full_back (12, 3);
  gen_full_back (21, 3);
 }
 END_TEST ();

 START_TEST ("maximal test 7");
 {
  string cur = "";
  for (int i = 0; i < 4; i++)
  {
   add_vertex_by_name (cur);
   cur += "l";
  }
  gen_full_back (4, 4);
 }
 END_TEST ();

 START_TEST ("maximal test 8");
 {
  string cur = "";
  for (int i = 0; i < 5; i++)
  {
   add_vertex_by_name (cur);
   cur += "l";
  }
  gen_full_back (5, 5);
 }
 END_TEST ();

 START_TEST ("maximal test 9");
 {
  string cur = "";
  for (int i = 0; i < 4; i++)
  {
   add_vertex_by_name (cur);
   cur += "l";
  }
  gen_full_back (4, 4);
  gen_random (MAX_N - n);
 }
 END_TEST ();

 START_TEST ("maximal test 10");
 {
  string cur = "";
  for (int i = 0; i < 5; i++)
  {
   add_vertex_by_name (cur);
   cur += "l";
  }
  gen_full_back (5, 5);
  gen_random (MAX_N - n);
 }
 END_TEST ();

 START_TEST ("maximal test 11");
 {
  string cur = "";
  for (int i = 0; i < 25; i++)
  {
   add_vertex_by_name (cur);
   if (rndvalue (2))
    cur += "l";
   else
    cur += "r";
  }
  gen_full_back ( 3, 3);
  gen_full_back (12, 3);
  gen_full_back (21, 3);
  gen_random (MAX_N - n);
 }
 END_TEST ();
}


int main (int argc, char * argv [])
{
 init_gen (argc, argv);

 gen_samples ();

 gen_small ();

 gen_medium ();

 gen_large ();

 exit_gen ();

 return 0;
}
