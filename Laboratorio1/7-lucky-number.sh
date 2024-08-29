#!/bin/bash
# a function return numbers: 0-255 state code
sumDigits(){
    num=$1
    acum=0
    while [ $num -gt 0 ]
    do
        dig=$(($num % 10))
        num=$(($num / 10))
        acum=$(($acum + $dig))
    done
    echo $acum
    #return $acum  is wrong only use 1 o 0
}

init=1000

while [ $init -le 10000 ]
do
    copy=$init
    while [ 1 ]
    do
        result=$(sumDigits $copy) # for catch the result
        if [ $result -lt 10 ]; then
            if [ $result -eq 7 ]; then
                echo "$init"
                break
            else
                break
            fi
        fi
        copy=$result
    done
    init=$(($init + 1))
done