#!/bin/bash
cat $1 > graph.dat
graphs=`./count_graphs.sh $1`

if [ $graphs -gt 2 ]
then
	touch graphplot.tmp
	file="graph"$graphs".gnuplot.template"
	s="t"$1
	opt=$(grep ${s:0:4} ../in/optimal-cmax | cut -f2)
	echo "o="$opt >> graphplot.tmp
	cat $file >> graphplot.tmp
	gnuplot graphplot.tmp > tmp.eps
	rm graphplot.tmp
else
	file="graph"$graphs".gnuplot"
	gnuplot $file > tmp.eps
fi


epstopdf tmp.eps --outfile=$2
rm -f tmp.eps
rm -f graph.dat
