#!/bin/bash
# Nombre del fichero de entrada
input=$1
# Nombre del fichero de salida (Igual que el de entrada pero acabado en .eps)
output=${input%.*}.eps
cat << _end_ | gnuplot 2> /dev/null
set terminal postscript eps color
set output "${output}"
set key right bottom
set ylabel "Time elapsed (microseconds)"
set xlabel "Size"
plot "${input}" using 1:2 t "Observed time" w l, "${input}" using 1:3 t "Estimated time" w l
_end_
