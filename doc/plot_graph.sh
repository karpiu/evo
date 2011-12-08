#!/bin/bash
cat $1 > graph.dat
graphs=`./count_graphs.sh $1`
file="graph"$graphs".gnuplot"

touch opt.dat
if [ $graphs > 2 ]
then
	s="t"$1
	opt=$(grep ${s:0:4} ../in/optimal-cmax | cut -f2)
	maxiter=$(wc -l $1 | cut -f1 -d ' ')
	for i in $(eval echo {1..$maxiter})
	do
		echo $opt >> opt.dat
	done 
fi

gnuplot $file > tmp.eps
epstopdf tmp.eps --outfile=$2
rm tmp.eps
rm graph.dat
rm opt.dat
