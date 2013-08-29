void gen_hand (void)
{
 shuffle_flag = false;

 START_TEST ("hand test 1");
 add_sequence (4, 11, 13, 22, 26);
 END_TEST ();

 START_TEST ("hand test 2");
 add_sequence (4, 11,  9, 22, 18);
 END_TEST ();

 START_TEST ("hand test 3");
 add_sequence (4, 12, 14, 24, 28);
 END_TEST ();

 START_TEST ("hand test 4");
 add_sequence (4, 15, 13, 26, 30);
 END_TEST ();

 START_TEST ("hand test 5");
 add_sequence (5,  3,  5,  7, 13,  8);
 END_TEST ();

 START_TEST ("hand test 6");
 add_sequence (5, 28,  7,  4, 29, 27);
 END_TEST ();

 START_TEST ("hand test 7");
 add_sequence (5,  2, 17, 23, 29, 27);
 END_TEST ();

 START_TEST ("hand test 8");
 add_sequence (5,  3, 11, 22, 26, 28);
 END_TEST ();

 START_TEST ("hand test 9");
 add_sequence (6,  1,  2,  3,  4,  5,  6);
 END_TEST ();

 START_TEST ("hand test 10");
 add_sequence (10,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10);
 END_TEST ();

 START_TEST ("hand test 11");
 add_sequence (10, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30);
 END_TEST ();

 START_TEST ("hand test 12");
 add_sequence (10, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29);
 END_TEST ();

 START_TEST ("hand test 13");
 add_sequence (7, 30, 30, 29, 22, 22, 20, 17);
 END_TEST ();

 START_TEST ("hand test 14");
 add_sequence (7, 30, 30, 30, 28, 23, 19, 13);
 END_TEST ();

 START_TEST ("hand test 15");
 add_sequence (7, 30, 29, 28, 26, 21, 19, 17);
 END_TEST ();

 START_TEST ("hand test 16");
 add_sequence (7, 30, 28, 26, 25, 23, 19, 18);
 END_TEST ();

 START_TEST ("hand test 17");
 add_sequence (5, 14, 16, 19, 28, 29);
 END_TEST ();

 START_TEST ("hand test 18");
 add_sequence (6, 15, 14, 13,  5, 26, 21);
 END_TEST ();

 START_TEST ("hand test 19");
 add_sequence (6,  7, 11, 13, 28, 22, 26);
 END_TEST ();

 START_TEST ("hand test 20");
 add_sequence (6,  7, 11, 13, 14, 22, 26);
 END_TEST ();

 START_TEST ("hand test 21");
 add_sequence (6,  9, 20, 28, 27, 30, 14);
 END_TEST ();

 START_TEST ("hand test 22");
 add_sequence (30, 30, 30, 29, 28, 13,  7,  3, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 29);
 END_TEST ();

 START_TEST ("hand test 23");
 add_sequence (20, 30, 30, 29, 28, 13,  7,  3, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 29);
 END_TEST ();

 START_TEST ("hand test 24");
 add_sequence (15, 30, 30, 29, 28, 13,  7,  3, 30, 30, 30, 30, 30, 30, 30, 29);
 END_TEST ();

 START_TEST ("hand test 25");
 add_sequence (12, 30, 30, 29, 28, 13,  7,  3, 30, 30, 30, 30, 29);
 END_TEST ();

 START_TEST ("hand test 26");
 add_sequence (10, 30, 30, 29, 28, 13,  7,  3, 30, 30, 29);
 END_TEST ();

 START_TEST ("hand test 27");
 add_sequence (9, 29, 28, 13,  7,  3, 30, 30, 30, 29);
 END_TEST ();

 START_TEST ("hand test 28");
 add_sequence (8, 29, 28, 13,  7,  3, 30, 30, 29);
 END_TEST ();

 START_TEST ("hand test 29");
 add_sequence (7, 29, 28, 13,  7,  3, 30, 29);
 END_TEST ();
}
