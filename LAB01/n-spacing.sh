#!/bin/bash

## $*[1] not exist -> $1 ....
echo $2
echo $1

if [ $# -ne 2  ]; then
 echo "You must include the current file and n spacing"
 exit 1
fi

if [ $1 -lt 0 ]; then
 echo "n-spacing is not valid, must be a number growned or equal than 0"
 exit 1
fi

if [ ! -f $2 ]; then 
 echo "path file must exist"
 exit 1
fi

## for read each file's line
while IFS= read -r line
do
 echo "$line"
 i=0
 ## adding n-spacing
 while [ $i -ne $1 ]
 do
  echo ""
  i=$((i + 1))
 done 
done < "$2" ##correct read passsing by argument, if its not only put the file's name
