#!/bin/bash

x=0
while [ $x -lt 10 ]
do
 y=$x
 i=0
 nums=()
 while [ $y -ge 0 ]
 do
  nums[i]=$y
  y=$(($y-1))
  i=$(($i+1))
 done
 echo ${nums[*]}
 x=$(($x+1))
done

