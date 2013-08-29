#!/bin/gawk

function initrand (seed) {
	currand = seed
}

function nextrand () {
	currand = int (currand * 1664525 + 1013904223) % (65536 * 65536)
}

function rnd_double () {
	nextrand()
	return currand / (65536 * 65536)
}

function rnd_int (range) {
	return int (rnd_double() * range)
}

BEGIN {
	initrand(12345)
	if (lo == 0)
	{
		lo = 1
	}
	if (comment == "")
	{
		comment = "test"
	}
	if (name == "")
	{
		name = "gen_some_temp_file"
	}
}

// {
	if ($1 != "numbers")
	{
		n = $1 + 0
		if ($(n + 2) == "answer")
		{
			answer = $(n + 3) + 0
#			printf ("add %d %d\n", answer, n)
			p[answer, n] = p[answer, n] + 1
#			printf ("! %d %d %d\n", answer, n, p[answer, n])
			if (rnd_int(p[answer, n]) == 0)
			{
				for (i = 1; i <= n; i++)
				{
					a[answer, n, i] = $(i + 1)
				}	
			}
		}
	}
}

function print_test (answer, n) {
	printf ("\n")
	printf (" START_TEST (\"%s %d, answer %d\");\n", comment, t, answer)
	printf (" add_sequence (")
	printf ("%d", n)
	for (i = 1; i <= n; i++)
	{
		printf (", %d", a[answer, n, i])
	}
	printf (");\n")
	printf (" END_TEST ();\n")
}

END {
	printf ("void %s (void)\n", name)
	printf ("{\n")
	printf (" shuffle_flag = false;\n")

	t = 0
	for (answer = 1; answer <= 30; answer++)
	{
		for (n = lo; n <= 10; n++)
		{
			if (p[answer, n] > 0)
			{
				k = 1
				ok = 1
				while (p[answer, n + k] > 0)
				{
					if (rnd_int(2) == 0)
					{
						ok = 0
					}
					k++
				}

				if (ok)
				{
					t++
					print_test(answer, n)
				}
			}
		}
	}

	printf ("}\n")
}
