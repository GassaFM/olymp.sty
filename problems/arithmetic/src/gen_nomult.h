void gen_nomult (void)
{
 shuffle_flag = false;

 START_TEST ("anti-nomult test 1, answer 1");
 add_sequence (6, 10, 12, 13, 20, 24, 28);
 END_TEST ();

 START_TEST ("anti-nomult test 2, answer 2");
 add_sequence (6, 14, 15, 21, 26, 28, 30);
 END_TEST ();

 START_TEST ("anti-nomult test 3, answer 3");
 add_sequence (6, 11, 22, 23, 24, 26, 29);
 END_TEST ();

 START_TEST ("anti-nomult test 4, answer 4");
 add_sequence (6, 3, 7, 13, 28, 29, 30);
 END_TEST ();

 START_TEST ("anti-nomult test 5, answer 5");
 add_sequence (6, 3, 16, 23, 28, 29, 30);
 END_TEST ();

 START_TEST ("anti-nomult test 6, answer 6");
 add_sequence (6, 3, 17, 23, 28, 29, 30);
 END_TEST ();

 START_TEST ("anti-nomult test 7, answer 7");
 add_sequence (6, 11, 23, 26, 28, 29, 30);
 END_TEST ();
}
