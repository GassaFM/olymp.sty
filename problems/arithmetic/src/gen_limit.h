void gen_limit (void)
{
 shuffle_flag = false;

 START_TEST ("anti-limit test 1, limit 874");
 add_sequence (5, 19, 22, 24, 29, 30);
 END_TEST ();

 START_TEST ("anti-limit test 2, limit 812");
 add_sequence (5, 5, 9, 18, 28, 29);
 END_TEST ();

 START_TEST ("anti-limit test 3, limit 784");
 add_sequence (5, 16, 21, 27, 28, 29);
 END_TEST ();

 START_TEST ("anti-limit test 4, limit 780");
 add_sequence (5, 14, 19, 26, 27, 30);
 END_TEST ();

 START_TEST ("anti-limit test 5, limit 722");
 add_sequence (5, 9, 19, 24, 29, 30);
 END_TEST ();

 START_TEST ("anti-limit test 6, limit 703");
 add_sequence (5, 13, 19, 24, 26, 27);
 END_TEST ();

 START_TEST ("anti-limit test 7, limit 702");
 add_sequence (5, 18, 19, 20, 25, 28);
 END_TEST ();

 START_TEST ("anti-limit test 8, limit 660");
 add_sequence (5, 13, 22, 24, 27, 30);
 END_TEST ();

 START_TEST ("anti-limit test 9, limit 650");
 add_sequence (5, 15, 18, 21, 25, 26);
 END_TEST ();

 START_TEST ("anti-limit test 10, limit 420");
 add_sequence (4, 14, 19, 22, 30);
 END_TEST ();

 START_TEST ("anti-limit test 11, limit 378");
 add_sequence (4, 13, 18, 21, 29);
 END_TEST ();

 START_TEST ("anti-limit test 12, limit 324");
 add_sequence (4, 12, 17, 19, 27);
 END_TEST ();

 START_TEST ("anti-limit test 13, limit 290");
 add_sequence (4, 10, 16, 18, 29);
 END_TEST ();

 START_TEST ("anti-limit test 14, limit 288");
 add_sequence (4, 11, 16, 18, 26);
 END_TEST ();

 START_TEST ("anti-limit test 15, limit 261");
 add_sequence (4, 9, 10, 26, 29);
 END_TEST ();

 START_TEST ("anti-limit test 16, limit 255");
 add_sequence (4, 9, 15, 17, 28);
 END_TEST ();

 START_TEST ("anti-limit test 17, limit 252");
 add_sequence (4, 10, 14, 18, 25);
 END_TEST ();

 START_TEST ("anti-limit test 18, limit 240");
 add_sequence (4, 8, 13, 18, 30);
 END_TEST ();

 START_TEST ("anti-limit test 19, limit 45");
 add_sequence (3, 5, 9, 30);
 END_TEST ();

 START_TEST ("anti-limit test 20, limit 42");
 add_sequence (3, 6, 7, 29);
 END_TEST ();

 START_TEST ("anti-limit test 21, limit 35");
 add_sequence (3, 5, 7, 30);
 END_TEST ();

 START_TEST ("anti-limit test 22, limit 33");
 add_sequence (3, 3, 11, 29);
 END_TEST ();
}
