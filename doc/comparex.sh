#!/bin/bash

if [ ! -f ../in/$1.in ] ; then
	echo "Test $1 doesn't exist"
	exit 1
fi

touch makefile.tmp
num=$1
iter=$2
echo "${num}a.res: ../in/${num}.in" >> makefile.tmp
echo "	../src/evo.e -e avg -i ${iter} -x pmx < $< > \$@" >> makefile.tmp
echo "${num}b.res: ../in/${num}.in" >> makefile.tmp
echo "	../src/evo.e -e avg -i ${iter} -x ox < $< > \$@" >> makefile.tmp
echo "${num}c.res: ../in/${num}.in" >> makefile.tmp
echo "	../src/evo.e -e avg -i ${iter} -x cx < $< > \$@" >> makefile.tmp
echo "${num}.res: ${num}a.res ${num}b.res ${num}c.res" >> makefile.tmp
echo "	./joinN.sh ${num}a.res ${num}b.res ${num}c.res > \$@" >> makefile.tmp
echo "${num}.pdf: ${num}.res" >> makefile.tmp
echo "	./plot_graph.sh $< \$@" >> makefile.tmp

make ${num}.pdf -f makefile.tmp
rm makefile.tmp
