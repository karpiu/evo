set autoscale
set terminal postscript eps
set size 0.5,0.5
plot 'graph.dat' using 1:2 notitle with lines, \
     'graph.dat' using 1:3 notitle with lines