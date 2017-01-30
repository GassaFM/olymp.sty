#!/bin/bash
# DOPDFLATEX=true means compiling via pdflatex; false means latex + dvipdfm
export DOPDFLATEX=true

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

doit standalone
