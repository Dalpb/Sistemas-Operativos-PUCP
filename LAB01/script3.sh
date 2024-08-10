#!/bin/bash
container=""
while IFS= read -r line
do
 line=( $line )
 line="${line[@]^}"
 num=""
 others=""
 i=0
 for word in $line
 do
  if [ $i -eq 0 ]; then
   num=$word
  else
   others="$others$word "
  fi
  i=$(($i+1))
 done
 container="$container$others $num\n"

done < "data - pregunta 3"

echo -e $container>data\ -\ pregunta\ 3
