#!/bin/bash
for s in "" "-noadd" "-nomult" "-limit" ; do
	export name=nonzero$s
	echo "processing $name..."
	if [ ! -e $name.txt ] ; then
		g++ -O2 -Wall $name.cpp -o $name.exe
		./$name.exe >$name.txt
	fi
done

gawk -f filter.awk       name="gen_external" lo=3 comment="non-zero test"    nonzero.txt        > ../src/gen_external.h
gawk -f filter.awk       name="gen_nomult"   lo=6 comment="anti-nomult test" nonzero-nomult.txt > ../src/gen_nomult.h
gawk -f filter-limit.awk name="gen_limit"    lo=2 comment="anti-limit test"  nonzero-limit.txt  > ../src/gen_limit.h
python conv-hand.py <hand.in >../src/gen_hand.h

grep "almost 5 6" nonzero.txt > almost56.txt
