#!/bin/bash
cat $1 > tmp
shift
while test $# -ge 1 ;
do
    join tmp $1 > tmp2
    cp tmp2 tmp
    rm tmp2
    shift
done
cat tmp
rm tmp
