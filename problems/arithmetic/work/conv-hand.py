#!/usr/bin/python
import sys

print ('void gen_hand (void)')
print ('{')
print (' shuffle_flag = false;')

t = 0
while True:
	s = sys.stdin.readline ().strip ()
	if s == '':
		s = sys.stdin.readline ().strip ()
		if s == '':
			break
	n = int (s)
	a = map (int, sys.stdin.readline ().split ())
	assert (n == len (a))

	t += 1
	print ('')
	print (' START_TEST (\"hand test {0}\");'.format (t))
	print (' add_sequence ({0}, '.format (n) +
	       ', '.join (map ('{0:2}'.format, a)) + ');')
	print (' END_TEST ();')

print ('}')
