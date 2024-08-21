#!/bin/bash

if [ $# -ne 3 ]; then
    echo "You must run this script with 3 arguments, A,B,C"
    exit 1
fi

a=$1
b=$2
c=$3

dis=$(( $b**2 - 4*$a*$c ))

if [ $dis -ge 0 ]; then
    sqrt=$(echo "scale=5; sqrt($dis)"| bc)
    x1=$(echo "scale=5; (-1*$b + $sqrt) / (2*$a)" | bc)
    
    if [ $dis -eq 0 ]; then
        echo "This ecuation only has one solution"
        echo "solution: $x1"
    else
        x2=$(echo "scale=5; (-1*$b - $sqrt) / (2*$a)" | bc)
        echo -e "Solution 1: $x1 \nSolution 2: $x2"
    fi
else
    echo "This ecuation does not have real solution"
    exit 1
fi

