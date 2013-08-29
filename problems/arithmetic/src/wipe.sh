#!/bin/sh
source ./include.sh
./clean.sh
rm -f ../tests/??
rm -f ../tests/??.a
rm -f ../tests/???
rm -f ../tests/???.a
rmdir ../tests
if [ "$CUSTOMWIPE" != "" ] ; then
    rm $CUSTOMWIPE
fi
rm gen.log
