#ifndef __gentools_h__
#define __gentools_h__

#ifndef PROBLEM_NAME
#define PROBLEM_NAME "undefined"
#endif

#ifndef GEN_PROBLEM_NAME
#define GEN_PROBLEM_NAME PROBLEM_NAME
#endif

#ifndef TEST_STR
#define TEST_STR "%03d"
#endif

#ifndef ANSWER_SUFFIX
#define ANSWER_SUFFIX ".a"
#endif

#define VERSION_A 0
#define VERSION_B 7
#define VERSION_C 245

#ifdef WIN32
#define INT64 "%I64d"
#define UINT64 "%I64u"
#else
#define INT64 "%lld"
#define UINT64 "%llu"
#endif

#ifdef TEST_GROUPS
extern const int MIN_GROUP, MAX_GROUP, TOTAL_SCORE;
extern const int GROUP_SCORE [];
extern int       group_min   [];
extern int       group_max   [];
extern int       group_size  [];
#endif

#include <algorithm>
#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <limits.h>
#include <stdint.h>

void initrand (uint32_t seed);
void initrand_str (const char * str);
void initrand_array (const unsigned * key, int len);
uint32_t randhash (const char * str);
inline double rndvalue (void);
inline double rndvalue (double range);
inline double rndvalue (double lo, double hi);
inline uint32_t rndvalue (int range);
inline uint32_t rndvalue (uint32_t range);
inline int32_t rndvalue (int32_t lo, int32_t hi);
inline uint64_t rndvalue (uint64_t range);
inline int64_t rndvalue (int64_t lo, int64_t hi);
template <class T> void rndshuffle (T * a, T * b);

namespace gentools_random_internal
{
 const int POW = 19937, MARR = POW >> 5;
 const int ARR = MARR + 1, EXTRA = (ARR << 5) - POW;
 const int SHIFT = 397, SHIFT_LIM = ARR - SHIFT, MSHIFT = SHIFT - ARR;
 const uint32_t LO_BITS = (1U << EXTRA) - 1U, HI_BITS = 0xFFFFFFFF ^ LO_BITS;
 const uint32_t A [2] = {0U, 0x9908B0DFU};
 const int TSHR1 = 11, TSHL2 = 7, TSHL3 = 15, TSHR4 = 18;
 const uint32_t TMASK2 = 0x9D2C5680U, TMASK3 = 0xEFC60000U;
 const uint32_t RND_MULT1 = 1812433253U;
 const uint32_t RND_MULT2 = 1664525U, RND_MULT3 = 1566083941U;
 const uint32_t DEFAULT_SEED = 5489U, ARRAY_SEED = 19650218U;
 const double NORM_MULT = 1.0 / 4294967296.0;

 const int UTEST_LEN = 4;
 const uint32_t UTEST_KEY [UTEST_LEN] = {0x123, 0x234, 0x345, 0x456};
 const int UTEST_STEPS = 1000;
 const uint32_t UTEST_EXPECTED_RESULT = 0xFA0596C7U;

 uint32_t cur_state [ARR];
 int cur_index = ARR + 1;

 inline uint32_t generate_element (uint32_t v0, uint32_t v1, uint32_t vshift)
 {
  uint32_t res, temp;

  temp = (v0 & HI_BITS) | (v1 & LO_BITS);
  res = vshift ^ (temp >> 1) ^ A[temp & 1U];

  return res;
 }

 inline void generate_array (void)
 {
  int i;

  for (i = 0; i < SHIFT_LIM; i++)
   cur_state[i] = generate_element (cur_state[i],
                                    cur_state[i + 1],
                                    cur_state[i + SHIFT]);

  for ( ; i < MARR; i++)
   cur_state[i] = generate_element (cur_state[i],
                                    cur_state[i + 1],
                                    cur_state[i + MSHIFT]);

  cur_state[i] = generate_element (cur_state[i],
                                   cur_state[0],
                                   cur_state[i + MSHIFT]);
 }

 inline uint32_t get_raw (void)
 {
  if (cur_index >= ARR)
  {
   if (cur_index > ARR)
    initrand (DEFAULT_SEED);
   assert (cur_index == ARR); // error if not initialized
   cur_index = 0;
   generate_array ();
  }

  return cur_state[cur_index++];
 }

 inline uint32_t get_tempered (void)
 {
  uint32_t val;

  val = get_raw ();
  val ^= val >> TSHR1;
  val ^= (val << TSHL2) & TMASK2;
  val ^= (val << TSHL3) & TMASK3;
  val ^= val >> TSHR4;

  return val;
 }

 inline void unit_test (void)
 {
  uint32_t res;
  int i;

  initrand_array (UTEST_KEY, UTEST_LEN);
  res = 0;
  for (i = 0; i < UTEST_STEPS; i++)
   res = res * RND_MULT1 + rndvalue (0);

  printf ("%08X\n", res);
  assert (res == UTEST_EXPECTED_RESULT);
 }

 struct random_state
 {
  uint32_t cur_state [ARR];
  int cur_index;

  random_state (void): cur_index (ARR + 1) {}
 };

 void save_state (random_state & st)
 {
  memmove (st.cur_state, cur_state, ARR * sizeof (uint32_t));
  st.cur_index = cur_index;
 }

 void restore_state (const random_state & st)
 {
  memmove (cur_state, st.cur_state, ARR * sizeof (uint32_t));
  cur_index = st.cur_index;
 }
} // namespace gentools_random_internal


void initrand (uint32_t seed)
{
 int i;

 using namespace gentools_random_internal;

 assert (seed != 0U);
 cur_state[0] = seed;
 for (i = 1; i < ARR; i++)
  cur_state[i] = RND_MULT1 * (cur_state[i - 1] ^ (cur_state[i - 1] >> 30)) + i;
 cur_index = ARR;
}

void initrand_str (const char * str)
{
 int i, j, k, len;

 using namespace gentools_random_internal;

 initrand (ARRAY_SEED);

 len = strlen (str);
 for (i = 1, j = 0, k = std::max (ARR, len); k > 0; k--)
 {
  cur_state[i] = (cur_state[i] ^ (RND_MULT2 *
                                  (cur_state[i - 1] ^
                                   (cur_state[i - 1] >> 30)))) +
                 (uint32_t) str[j] + j;
  i++;
  if (i >= ARR)
  {
   cur_state[0] = cur_state[MARR];
   i = 1;
  }
  j++;
  if (j >= len)
   j = 0;
 }

 for (k = MARR; k > 0; k--)
 {
  cur_state[i] = (cur_state[i] ^ (RND_MULT3 *
                                  (cur_state[i - 1] ^
                                   (cur_state[i - 1] >> 30)))) - i;
  i++;
  if (i >= ARR)
  {
   cur_state[0] = cur_state[MARR];
   i = 1;
  }
 }

 cur_state[0] = 1U << 31; // only the highest bit is relevant here
 cur_index = ARR;
}

// strip all characters with ASCII codes 32 (Space) or less
void initrand_str_strip (const char * str)
{
 int old_len = strlen (str);
 char new_str [old_len + 1];
 char * new_p;
 const char * old_p;

 new_p = new_str;
 for (old_p = str; *old_p != '\0'; old_p++)
  if (*old_p > 32)
   *(new_p++) = *old_p;
 *new_p = '\0';

 initrand_str (new_str);
}

void initrand_array (const unsigned * key, int len)
{
 int i, j, k;

 using namespace gentools_random_internal;

 initrand (ARRAY_SEED);

 for (i = 1, j = 0, k = std::max (ARR, len); k > 0; k--)
 {
  cur_state[i] = (cur_state[i] ^ (RND_MULT2 *
                                  (cur_state[i - 1] ^
                                   (cur_state[i - 1] >> 30)))) +
                 key[j] + j;
  i++;
  if (i >= ARR)
  {
   cur_state[0] = cur_state[MARR];
   i = 1;
  }
  j++;
  if (j >= len)
   j = 0;
 }

 for (k = MARR; k > 0; k--)
 {
  cur_state[i] = (cur_state[i] ^ (RND_MULT3 *
                                  (cur_state[i - 1] ^
                                   (cur_state[i - 1] >> 30)))) - i;
  i++;
  if (i >= ARR)
  {
   cur_state[0] = cur_state[MARR];
   i = 1;
  }
 }

 cur_state[0] = 1U << 31; // only the highest bit is relevant here
 cur_index = ARR;
}

uint32_t randhash (const char * str)
{
 int i;
 uint32_t res;

 using namespace gentools_random_internal;

 res = 0;
 for (i = 0; str[i] != '\0'; i++)
  res = RND_MULT1 * (res ^ (res >> 30)) + (uint32_t) str[i];

 return res;
}

inline double rndvalue (void)
{
 using namespace gentools_random_internal;

 return get_tempered () * NORM_MULT;
}

inline double rndvalue (double range)
{
 return rndvalue () * (range);
}

inline double rndvalue (double lo, double hi)
{
 return rndvalue (hi - lo) + lo;
}

inline uint32_t rndvalue (uint32_t range)
{
 using namespace gentools_random_internal;

 if (!range)
  return get_tempered ();
 else
  return ((uint64_t) get_tempered () * range + (range >> 1)) >> 32ULL;
}

inline uint32_t rndvalue (int range)
{
 return rndvalue ((uint32_t) range);
}

inline int32_t rndvalue (int32_t lo, int32_t hi)
{
 return lo + (int32_t) rndvalue (hi - lo + 1);
}

inline uint64_t rndvalue (uint64_t range)
{
 using namespace gentools_random_internal;

 uint64_t res;
 if (!range)
 {
  res = (uint64_t) get_tempered () << 32ULL;
  res |= (uint64_t) get_tempered ();
 }
 else
 {
  uint64_t lim;
  lim = uint64_t (-1);
  if (range <= (lim >> 32ULL))
   lim >>= 32ULL;
  if (range <= (lim >> 16ULL))
   lim >>= 16ULL;
  if (range <= (lim >>  8ULL))
   lim >>=  8ULL;
  if (range <= (lim >>  4ULL))
   lim >>=  4ULL;
  if (range <= (lim >>  2ULL))
   lim >>=  2ULL;
  if (range <= (lim >>  1ULL))
   lim >>=  1ULL;
  assert (range <= lim);
  do
  {
   res = (uint64_t) get_tempered () << 32ULL;
   res |= (uint64_t) get_tempered ();
   res &= lim;
  }
  while (res >= range);
 }

 return res;
}

inline int64_t rndvalue (int64_t lo, int64_t hi)
{
 return lo + (int64_t) rndvalue ((uint64_t) (hi - lo + 1));
}

template <class T> void rndshuffle (T * a, T * b)
{
 int i, k;

 for (i = 0; a + i != b; i++)
 {
  k = rndvalue (i + 1);
  std::swap (a[i], a[k]);
 }
}


#ifndef NO_STD_GEN
void open_test (void);
void close_test (void);
void log_test (void);
void verify_test (void);
void shuffle_test (void);
void output_test (void);
#ifdef GENERATE_ANSWERS
void answer_test (void);
#endif

const int MaxGenBuf = 256;

FILE * flog;
bool shuffle_flag;
char cur_test_str [MaxGenBuf];
#ifdef GENERATE_ANSWERS
char cur_answer_str [MaxGenBuf];
#endif
int cur_test, test_lo, test_hi, num_tests;


void get_time_str (char * buf)
{
 time_t raw_time;
 tm * cur_time;
 time (&raw_time);
 cur_time = localtime (&raw_time);
 sprintf (buf, "%04d-%02d-%02d %02d:%02d:%02d",
          cur_time -> tm_year + 1900, cur_time -> tm_mon + 1,
          cur_time -> tm_mday, cur_time -> tm_hour,
          cur_time -> tm_min, cur_time -> tm_sec);
}

#ifdef TEST_GROUPS
int cur_group;

void check_groups (void)
{
 int i;
 int total;

 total = 0;
 for (i = MIN_GROUP; i <= MAX_GROUP; i++)
  total += GROUP_SCORE[i];
 assert (total == TOTAL_SCORE);
}

void output_groups (void)
{
 int i;

 fprintf (flog, "\tScoring = cat ([\n");
 for (i = MIN_GROUP; i <= MAX_GROUP; i++)
 {
  if (group_size[i] == 0)
   continue;
  assert (group_size[i] == group_max[i] - group_min[i] + 1);
  fprintf (flog,
           "\t\trepl ([" TEST_STR ".." TEST_STR "], \" %.6lf\")%s\n",
           group_min[i], group_max[i],
           (double) GROUP_SCORE[i] / group_size[i],
           i == MAX_GROUP ? "" : ",");
 }
 fprintf (flog, "\t])\n");

 fprintf (flog, "\t[\n");
 for (i = MIN_GROUP; i <= MAX_GROUP; i++)
 {
  if (group_size[i] == 0)
   continue;
  assert (group_size[i] == group_max[i] - group_min[i] + 1);
  fprintf (flog,
           "\t\ttstgroupX (%3d, [" TEST_STR ".." TEST_STR "], "
           "[" TEST_STR ".." TEST_STR "])%s\n", group_max[i], 1, group_max[i],
           group_min[i], group_max[i], i == MAX_GROUP ? "" : ",");
 }
 fprintf (flog, "\t]\n");
}
#endif

void init_gen (int argc, char * argv [])
{
 char buf [MaxGenBuf];

 flog = fopen ("gen.log", "at+");
 assert (flog != NULL);
 setvbuf (flog, NULL, _IONBF, 0);
 get_time_str (buf);
 fprintf (flog, "At [%s]: "
  "this is a test generator using gentools v%d.%d.%d.\n",
  buf, VERSION_A, VERSION_B, VERSION_C);

 if (argc >= 3)
 {
  if (sscanf (argv[1], "%d", &test_lo) != 1)
   assert (false);
  if (sscanf (argv[2], "%d", &test_hi) != 1)
   assert (false);
  assert (test_lo <= test_hi);
  sprintf (buf, "tests %d..%d", test_lo, test_hi);
 }
 else if (argc >= 2)
 {
  if (sscanf (argv[1], "%d", &test_lo) != 1)
   assert (false);
  test_hi = test_lo;
  sprintf (buf, "test %d", test_lo);
 }
 else
 {
  test_lo = INT_MIN;
  test_hi = INT_MAX;
  sprintf (buf, "all tests");
 }

 fprintf (flog, "Generating %s for problem \"%s\"...\n", buf, PROBLEM_NAME);
 if (strcmp (GEN_PROBLEM_NAME, PROBLEM_NAME))
  fprintf (flog, "Using problem name \"%s\" for generator.\n",
           GEN_PROBLEM_NAME);
 cur_test = 0;
 num_tests = 0;
 shuffle_flag = false;

 initrand_str_strip (GEN_PROBLEM_NAME);

#ifdef TEST_GROUPS
 cur_group = INT_MIN;
 fprintf (flog, "Checking groups (%d..%d)...", MIN_GROUP, MAX_GROUP);
 check_groups ();
 fprintf (flog, " done.\n");
#endif
}

void exit_gen (void)
{
#ifdef TEST_GROUPS
 fprintf (flog, "Writing groups (%d..%d):\n", MIN_GROUP, MAX_GROUP);
 output_groups ();
#endif

 fprintf (flog, "Test generation successful (%d tests).\n", num_tests);
 fclose (flog);

 exit (EXIT_SUCCESS);
}


#define START_TEST(...) \
 if (start_test_internal (__LINE__, __FILE__, "" __VA_ARGS__)) \
 { \

// deprecated version of START_TEST
#define start_test(...) \
 if (start_test_internal (__LINE__, __FILE__, "" __VA_ARGS__)) \
 { \

#define END_TEST() \
  end_test_internal (__LINE__, __FILE__); \
 } \

// deprecated version of END_TEST
#define end_test() \
  end_test_internal (__LINE__, __FILE__); \
 } \

gentools_random_internal::random_state global_state;

bool start_test_internal (const int line_auto, const char * file_auto,
                          const char * comment, ...)
{
 cur_test++;
 if (!(test_lo <= cur_test && cur_test <= test_hi))
  return false;

#ifdef TEST_GROUPS
 assert (MIN_GROUP <= cur_group && cur_group <= MAX_GROUP);
#endif

 char temp [MaxGenBuf];
 char buf [MaxGenBuf];
 va_list arg_list;

 va_start (arg_list, comment);
 vsprintf (temp, comment, arg_list);
 va_end (arg_list);

 sprintf (cur_test_str, TEST_STR, cur_test);
#ifdef GENERATE_ANSWERS
 sprintf (cur_answer_str, TEST_STR ANSWER_SUFFIX, cur_test);
#endif
 fprintf (flog, "Test %s (%s): lines %d..", cur_test_str, temp, line_auto);

 gentools_random_internal::save_state (global_state);

 sprintf (buf, "%s: %s", GEN_PROBLEM_NAME, temp);
 initrand_str_strip (buf);

 open_test ();

 return true;
}

void end_test_internal (const int line_auto, const char * file_auto)
{
 fprintf (flog, "%d", line_auto);

 if (strcmp (file_auto, "gen.cpp") != 0)
 {
  fprintf (flog, " of %s", file_auto);
 }

 fprintf (flog, ", ");

 close_test ();

#ifdef TEST_GROUPS
 group_min[cur_group] = std::min (group_min[cur_group], cur_test);
 group_max[cur_group] = std::max (group_max[cur_group], cur_test);
 group_size[cur_group]++;
#endif

 log_test ();
 fprintf (flog, " ");

 if (shuffle_flag)
 {
  fprintf (flog, ".");
  shuffle_test ();
 }
 else
  fprintf (flog, "x");

 fprintf (flog, ".");
 verify_test ();

 fprintf (flog, ".");
 output_test ();

#ifdef GENERATE_ANSWERS
 fprintf (flog, ".");
 answer_test ();
#else
 fprintf (flog, "x");
#endif

 gentools_random_internal::restore_state (global_state);
 fprintf (flog, " done.\n");
 num_tests++;
}
#endif

#endif // __gentools_h__
