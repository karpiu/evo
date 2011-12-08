#!/bin/bash
test_file=../in/$1.in
optimum_file=../in/optimal
eval_program=../src/eval_perm.e
optimum_line=`grep ^$1 $optimum_file | cut -f2- -d' '`
optimum=`echo $optimum_line | $eval_program $test_file`
echo $optimum
