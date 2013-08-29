#!/bin/bash
source ./include.sh
./clean.sh

echo Compiling...
if [ -e ./$1.cpp ] ; then
	g++ -O2 -Wall ./$1.cpp -o ./$1.exe
fi
if [ -e ../check.cpp ] ; then
	g++ -O2 -Wall ../check.cpp -o ../check.exe
fi

echo Testing solution...
rm -f $PROBLEM.out
for t in ../tests/??? ; do
	echo Test $t
	cp $t $PROBLEM.in
	if [ -e ./$1.py ] ; then
		python ./$1.py
	else
		./$1.exe
	fi
	if [ -e ../check.exe ] ; then
		../check.exe $PROBLEM.in $PROBLEM.out $t.a
	fi
	rm -f $PROBLEM.out
done
