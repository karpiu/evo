#!/bin/bash
rows=`cat $1 | head --lines 1 | wc --words - | cut -c 1`
graphs=`expr $rows - 1`
echo $graphs
