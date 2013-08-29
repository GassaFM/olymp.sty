#define PROBLEM_NAME "arithmetic"
#define TEST_STR "%03d"
#include "gentools.h"

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

const int MIN_N = 1, MAX_N = 100000;
const int MIN_A = 1, MAX_A = 30;

int a [MAX_N];
int n;

void open_test (void)
{
 n = 0;
}

void close_test (void)
{
}

void log_test (void)
{
 fprintf (flog, "n = %d", n);
}

void shuffle_test (void)
{
 rndshuffle (a, a + n);
}

void verify_test (void)
{
 assert (MIN_N <= n && n <= MAX_N);
 for (int i = 0; i < n; i++)
  assert (MIN_A <= a[i] && a[i] <= MAX_A);
}

void output_test (void)
{
 FILE * fout;

 fout = fopen (cur_test_str, "wt");
 assert (fout != NULL);

 fprintf (fout, "%d\n", n);
 for (int i = 0; i < n; i++)
  fprintf (fout, "%d%c", a[i], "\n "[i + 1 < n]);

 fclose (fout);
}


void add_value (int value)
{
 assert (n < MAX_N);
 assert (MIN_A <= value && value <= MAX_A);
 a[n] = value;
 n++;
}

void add_sequence (int k, ...)
{
 va_list arg_list;

 va_start (arg_list, k);
 for (int i = 0; i < k; i++)
 {
  int value = va_arg (arg_list, int);
  add_value (value);
 }

 va_end (arg_list);
}

void add_sequence_repeat (int r, int k, ...)
{
 va_list arg_list;
 int i;

 va_start (arg_list, k);
 for (i = 0; i < min (r, k); i++)
 {
  int value = va_arg (arg_list, int);
  add_value (value);
 }
 va_end (arg_list);

 for ( ; i < r; i++)
 {
  add_value (a[n - k]);
 }
}

void add_random (int k = 1, int lo = MIN_A, int hi = MAX_A)
{
 for (int i = 0; i < k; i++)
 {
  int x = rndvalue (lo, hi);
  add_value (x);
 }
}

void add_random_norepeat (int k = 1, int lo = MIN_A, int hi = MAX_A)
{
 int y = MIN_A - 1;
 for (int i = 0; i < k; i++)
 {
  int x;
  do
  {
   x = rndvalue (lo, hi - 1);
  }
  while (x == y);
  y = x;
  add_value (x);
 }
}


void gen_samples (void)
{
 shuffle_flag = false;

 START_TEST ("first example");
 add_sequence (2, 1, 2);
 END_TEST ();

 START_TEST ("second example");
 add_sequence (3, 1, 2, 3);
 END_TEST ();

 START_TEST ("third example");
 add_sequence (4, 16, 2, 3, 4);
 END_TEST ();
}

void gen_small (void)
{
 shuffle_flag = false;

 START_TEST ("first minimal test");
 add_value (MIN_A);
 END_TEST ();

 START_TEST ("second minimal test");
 add_value (MAX_A);
 END_TEST ();

 for (int i = 0; i < 2; i++)
 {
  START_TEST ("shortest test %d", i + 1);
  int value = rndvalue (MIN_A + 1, MAX_A - 1);
  add_value (value);
  END_TEST ();
 }

 START_TEST ("small test 1");
 add_value (MIN_A);
 add_value (MIN_A);
 END_TEST ();

 START_TEST ("small test 2");
 add_value (MIN_A);
 add_value (MAX_A);
 END_TEST ();

 START_TEST ("small test 3");
 add_value (MAX_A);
 add_value (MAX_A);
 END_TEST ();

 START_TEST ("small test 4");
 add_value (MAX_A);
 add_value (MAX_A - 1);
 END_TEST ();

 START_TEST ("small test 5");
 add_value (MAX_A);
 add_value (MIN_A + 1);
 END_TEST ();

 for (int i = 4; i <= 8; i++)
 {
  START_TEST ("arithmetic progression %d", i + 1);
  for (int j = 0; j < i; j++)
   add_value (MIN_A + j);
  END_TEST ();
 }

 for (int i = 3; i <= 8; i++)
 {
  START_TEST ("arithmetic regression %d", i + 1);
  for (int j = 0; j < i; j++)
   add_value (MAX_A - j);
  END_TEST ();
 }

 START_TEST ("powers of two");
 for (int i = 1; i < MAX_A; i <<= 1)
  add_value (i);
 END_TEST ();

 START_TEST ("powers of two, inverted");
 for (int i = 1; i <= MAX_A - MIN_A; i <<= 1)
  add_value (MAX_A - i);
 END_TEST ();

 START_TEST ("powers of two minus one");
 for (int i = 2; i - 1 <= MAX_A; i <<= 1)
  add_value (i - 1);
 END_TEST ();

 START_TEST ("powers of two minus two");
 for (int i = 4; i - 2 <= MAX_A; i <<= 1)
  add_value (i - 2);
 END_TEST ();

 START_TEST ("powers of two minus three");
 for (int i = 4; i - 3 <= MAX_A; i <<= 1)
  add_value (i - 3);
 END_TEST ();

 START_TEST ("almost non-zero test");
 add_sequence (6, 11, 19, 20, 22, 25, 29);
 END_TEST ();

 START_TEST ("anti-noadd test 1");
 add_sequence (5, 12, 17, 20, 27, 28);
 END_TEST ();

 START_TEST ("anti-noadd test 2");
 add_sequence (5,  6,  9, 28, 29, 30);
 END_TEST ();
}

#include "gen_hand.h"

#include "gen_external.h"

#include "gen_limit.h"

#include "gen_nomult.h"

void gen_large (void)
{
 shuffle_flag = false;

 START_TEST ("first example repeated");
 add_sequence_repeat (MAX_N, 2, 1, 2);
 END_TEST ();

 START_TEST ("second example repeated");
 add_sequence_repeat (MAX_N, 3, 1, 2, 3);
 END_TEST ();

 START_TEST ("third example repeated");
 add_sequence_repeat (MAX_N, 4, 16, 2, 3, 4);
 END_TEST ();

 const int NUM = 14;
 const int LEN [NUM] = {10, 25, 43, 100, 250, 567, 1000,
                        12312, 25083, 40789, 50056, 60034, 75002, 97801};
 for (int i = 0; i < NUM; i++)
 {
  START_TEST ("large random test %d", i + 1);
  int lo = rndvalue (MIN_A, MAX_A - 1);
  add_random_norepeat (LEN[i], lo, MAX_A);
  END_TEST ();
 }

 START_TEST ("maximal test 1");
 add_random (MAX_N, 10, MAX_A);
 END_TEST ();

 START_TEST ("maximal test 2");
 add_random (MAX_N, MAX_A, MAX_A);
 END_TEST ();

 START_TEST ("maximal test 3");
 add_random_norepeat (MAX_N, 10, MAX_A);
 END_TEST ();

 START_TEST ("maximal test 4");
 add_random_norepeat (MAX_N, MAX_A - 2, MAX_A);
 END_TEST ();

 START_TEST ("maximal test 5");
 add_sequence (5, 21, 26, 28, 29, 30);
 add_random_norepeat (MAX_N - 5 * 2, 11, 20);
 add_sequence (5, 21, 26, 28, 29, 30);
 END_TEST ();

 START_TEST ("maximal test 6");
 add_sequence (5, 21, 24, 28, 29, 30);
 add_random_norepeat ((MAX_N * 2) / 3, MIN_A, 20);
 add_sequence (5, 21, 24, 28, 29, 30);
 END_TEST ();

 START_TEST ("maximal test 7");
 for (int i = 0; i < MAX_N; i++)
 {
  add_value (MAX_A - (i % MAX_A));
 }
 END_TEST ();
}


int main (int argc, char * argv [])
{
 init_gen (argc, argv);

 gen_samples ();

 gen_small ();

 gen_hand ();

 gen_external ();

 gen_limit ();

 gen_nomult ();

 gen_large ();

 exit_gen ();

 return 0;
}
