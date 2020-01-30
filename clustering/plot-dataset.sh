#!/usr/bin/env bash

SOURCE_DIR="./datasets/"
TARGET_DIR="./plot_data/"
DATAFILE="dataset.csv"

cat ${SOURCE_DIR}/${DATAFILE} | head -100 | tr "," " " > ${TARGET_DIR}/c1.dat
cat ${SOURCE_DIR}/${DATAFILE} | head -200 | tail -100 | tr "," " " > ${TARGET_DIR}/s1.dat
cat ${SOURCE_DIR}/${DATAFILE} | head -300 | tail -100 | tr "," " " > ${TARGET_DIR}/s2.dat
cat ${SOURCE_DIR}/${DATAFILE} | head -400 | tail -100 | tr "," " " > ${TARGET_DIR}/s3.dat
cat ${SOURCE_DIR}/${DATAFILE} | head -500 | tail -100 | tr "," " " > ${TARGET_DIR}/s4.dat
cat ${SOURCE_DIR}/${DATAFILE} | tail -100 | tr "," " " > ${TARGET_DIR}/s5.dat

gnuplot -c dataset.plt ./plots/dataset.png ./plot_data/c1.dat ./plot_data/s[1-5].dat

