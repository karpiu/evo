#!/bin/bash
test_file=../in/$1.in
optimum_file=../in/optimal
optimum_line=`grep ^$1 $optimum_file | cut -f2- -d' '`
echo $optimum_line
