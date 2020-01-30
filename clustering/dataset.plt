#!/usr/bin/env gnuplot --persist

# ARG1: Output file
# ARG[2-7]: Input files

set terminal pngcairo enhanced font "arial,11" fontscale 1.0
set output ARG1
set bar 1.000000 front
set title 'Clustering Dataset'
set xlabel "x1"
set ylabel "x2"
set grid
set yrange [-1.2:1.2]
set xrange [-1.2:1.2]
set colorbox vertical origin screen 0.9, 0.2, 0 size screen 0.05, 0.6, 0 front bdefault
set style line 1 lc rgb '#d6b447' pt 6 lw 2 ps 1
set style line 2 lc rgb '#02b8b8' pt 6 lw 2 ps 1
set style line 3 lc rgb '#ed4d4a' pt 6 lw 2 ps 1
set style line 4 lc rgb '#53a0ed' pt 6 lw 2 ps 1
set style line 5 lc rgb '#67db67' pt 6 lw 2 ps 1
set style line 6 lc rgb '#002222' pt 6 lw 2 ps 1
set key on outside bottom
plot ARG2 using 1:2 title 'C1' with points ls 1, \
     ARG3 using 1:2 title 'S1' with points ls 2, \
     ARG4 using 1:2 title 'S2' with points ls 3, \
     ARG5 using 1:2 title 'S3' with points ls 4, \
     ARG6 using 1:2 title 'S4' with points ls 5, \
     ARG7 using 1:2 title 'S5' with points ls 6

