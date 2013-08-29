#!/bin/bash
source ./include.sh
./clean.sh

echo Compiling...
if [ -e ../solutions/$SOL.cpp ] ; then
	g++ -DDEBUG -O2 -Wall ../solutions/$SOL.cpp -o ./$SOL.exe
fi
if [ -e gen.cpp ] ; then
	g++ -O2 -Wall gen.cpp -o ./gen.exe
fi
if [ -e validate.cpp ] ; then
	g++ -O2 -Wall validate.cpp -o ./validate.exe
fi
if [ -e ../check.cpp ] ; then
	g++ -O2 -Wall ../check.cpp -o ./check.exe
fi

echo Generating tests...
if [ -e small.in ] ; then
	cat small.in >>$PROBLEM.in
fi
if [ -e gen.py ] ; then
	python ./gen.py 01 >>$PROBLEM.in
fi
if [ -e gen.cpp ] ; then
	./gen.exe
fi

echo Generating answers...
for t in ??? ; do
	echo Test $t
	cp $t $PROBLEM.in
	if [ -e ./validate.exe ] ; then
		./validate.exe <$PROBLEM.in
	fi
	if [ -e ../$SOL.py ] ; then
		python ../$SOL.py
	else
		./$SOL.exe
#		./$SOL.exe 2>$t.err
#		./$SOL.exe <$t >$t.a
	fi
	cp $PROBLEM.out $t.a
	if [ -e check.exe ] ; then
		./check.exe $t $t.a $t.a
	fi
done

#echo Splitting tests...
#python ./splittests.py

if [ ! -e ../tests ] ; then
	mkdir ../tests
fi
mv ??   ../tests || mv ???   ../tests
mv ??.a ../tests || mv ???.a ../tests
if $DOCLEAN ; then
	./clean.sh
fi
