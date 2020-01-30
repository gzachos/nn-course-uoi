#!/usr/bin/env bash

TEMPFILE=`mktemp -p . -t tmp.XXXX`
cat ../datasets/dataset.csv | tr "," "\t" > ${TEMPFILE}

gnuplot -c result-auto.plt ./plots/result-auto.png ${TEMPFILE} ./plot_data/centroids.dat

rm ${TEMPFILE}

