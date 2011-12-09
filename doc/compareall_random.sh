#!/bin/bash

# usage: ./compareall_random.sh <iterations>

function zeros {
	if [ $1 -lt 10 ] ; then
		zret="00"	
	else
		if [ $1 -lt 100 ] ; then
			zret="0"
		else
			zret=""
		fi
	fi
}

for i in {1..100}; do
	zeros $i	
	z=$zret
	./compare_random.sh $z$i $1
done
