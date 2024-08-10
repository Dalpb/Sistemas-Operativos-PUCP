#!/bin/bash
#parametros 
init=$1
end=$2
num=$3

if [ $# -ne 3 ]; then
 echo "This program needs 3 arguments init,end,num"
 exit 1
fi

if [ $init -gt $end ]; then
 echo "This range its not valid"
 exit 1
fi

while [ $init -le $end ]
do
 aux=$init
 while [ $aux -ne 0 ]
 do
 dig=$(($aux % 10))
 if [ $dig -eq $num ]; then
  echo $init
  break
 fi
 aux=$(($aux /10))
 done 
 init=$(($init +1))
done

