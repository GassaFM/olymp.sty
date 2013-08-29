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
		if ($(n + 4) == "limit")
		{
			limit = $(n + 5) + 0
			p[limit, n] = p[limit, n] + 1
			if (rnd_int(p[limit, n]) == 0)
			{
				for (i = 1; i <= n; i++)
				{
					a[limit, n, i] = $(i + 1)
				}	
			}
		}
	}
}

function print_test (limit, n) {
	printf ("\n")
	printf (" START_TEST (\"%s %d, limit %d\");\n", comment, t, limit)
	printf (" add_sequence (")
	printf ("%d", n)
	for (i = 1; i <= n; i++)
	{
		printf (", %d", a[limit, n, i])
	}
	printf (");\n")
	printf (" END_TEST ();\n")
}

END {
	printf ("void %s (void)\n", name)
	printf ("{\n")
	printf (" shuffle_flag = false;\n")

	t = 0
	for (limit = 9999; limit > 30; limit--)
	{
		for (n = lo; n <= 10; n++)
		{
			if (p[limit, n] > 0)
			{
				k = 1
				ok = 1
				while (p[limit, n + k] > 0)
				{
					if (rnd_int(2) == 0)
					{
						ok = 0
					}
					k++
				}

				if (ok)
				{
					b[n]++
					if (b[n] < 10)
					{
						t++
						print_test(limit, n)
					}
				}
			}
		}
	}

	printf ("}\n")
}
