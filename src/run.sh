#!/bin/bash

# Compiles and executes a single C++ FLTK program
# Author: Harshit Varma

if [ $# -eq 0 ] 
then
    echo "Usage: bash run.sh <fname>"
    exit 1
fi 

FNAME=$1
# FLTK Compile:
fltk-config --compile $FNAME
# Rename the executable output file:
OUT_OLD=${FNAME::-4}
OUT_NEW="$OUT_OLD.out"
mv $OUT_OLD $OUT_NEW
# Execute:
./$OUT_NEW