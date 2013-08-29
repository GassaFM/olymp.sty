#!/bin/bash

source include.sh

function mpost_make()
{
  pushd ../problems || exit 1
  for f in * ; do
    echo $f
    if [ -d $f ] ; then
      if [ -d $f/statement ] ; then
        pushd $f/statement
        if [ -e dopics.sh ] ; then
          ./dopics.sh
        fi
        if [ -e $f.mp ] ; then
          mpost $f.mp
        fi
        popd
      fi
    fi
  done
  popd
}

function doit()
{
  if $DOPDFLATEX ; then
    pdflatex $1.tex || exit 1
    pdflatex $1.tex || exit 1
  else
    latex $1.tex || exit 1
    latex $1.tex || exit 1
    dvips -t a4 $1.dvi || exit 1
    dvipdfmx -p a4 $1 || exit 1
  fi
}

#svnversion .. > revision.temp | echo X > revision.temp
mpost_make
doit $NAME.ru || exit 1
doit $NAME.en || exit 1
#rm revision.temp
#svnversion . ../problems/*/statement
