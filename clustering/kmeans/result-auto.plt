#!/usr/bin/env gnuplot --persist

# ARG1: Output file
# ARG[2-3]: Input files

set terminal pngcairo enhanced font "arial,11" fontscale 1.0
set output ARG1
set bar 1.000000 front
set title 'K-means Clustering Result'
set xlabel "x1"
set ylabel "x2"
set grid
set yrange [-1.2:1.2]
set xrange [-1.2:1.2]
set colorbox vertical origin screen 0.9, 0.2, 0 size screen 0.05, 0.6, 0 front bdefault
set style line 1 lc rgb '#d6b447' pt 6 lw 2 ps 1
set style line 2 lc rgb '#002222' pt 3 lw 2 ps 2.5
set key on outside bottom
plot ARG2 using 1:2 title 'Patterns' with points ls 1, \
     ARG3 using 1:2 title 'Centroids' with points ls 2

