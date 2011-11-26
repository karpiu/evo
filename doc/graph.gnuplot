set autoscale
set terminal postscript eps
set size 0.5,0.5
plot '< cat -' using 1:2 notitle with lines