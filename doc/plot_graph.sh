#!/bin/bash
cat $1 > graph.dat
graphs=`./count_graphs.sh $1`
./optimum.sh ${1%.res} > optimum.dat
file="graph"$graphs".gnuplot"
gnuplot $file > tmp.eps
epstopdf tmp.eps --outfile=$2
rm -f optimum.dat
rm -f tmp.eps
rm -f graph.dat
