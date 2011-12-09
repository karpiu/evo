#!/bin/bash
cat $1 > graph.dat
graphs=`./count_graphs.sh $1`

touch graphplot.tmp
file="graph"$graphs".gnuplot.template"
s="t"$1
opt=$(grep ${s:0:4} ../in/optimal-cmax | cut -f2)
echo "o="$opt >> graphplot.tmp
cat $file >> graphplot.tmp
gnuplot graphplot.tmp > tmp.eps
rm graphplot.tmp

epstopdf tmp.eps --outfile=$2
rm tmp.eps
rm graph.dat
