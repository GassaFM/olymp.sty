#!/bin/sh

source include.sh

function mpost_clean()
{
pushd ../problems || exit 1
for f in * ; do
  echo $f
  if [ -d $f ] ; then
    if [ -d $f/statement ] ; then
      pushd $f/statement
      if [ -e $f.mp ] ; then
        rm $f.{log,[1-9]*}
      fi
      popd
    fi
  fi
done
popd
}

rm --force $NAME{,.en,.ru}.{log,aux,dvi,ps,pdf}
mpost_clean
