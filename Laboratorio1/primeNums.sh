#!/bin/bash

num=60000
col=20
row=()
while [ $num -le 63000 ]
do
 i=1
 count=0
 while [ $i -le $num ]
 do
  mod=$(($num % $i))
  if [ $mod -eq 0 ]; then
   count=$(($count +1))
  fi 
  if [ $count -gt 2 ]; then ## if its not prime break loop 
   break
  fi
  i=$(($i + 1))
 done
 
 if [ $count -eq 2 ]; then
  echo $num  
 fi
 
done
