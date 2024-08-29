#!/bin/bash
## Asume that the files must be in the same directory as the script
if [ $# -ne 1 ]; then
 echo "Must run this program with 1 argument"
 exit 1
fi
patter=$1
filePath=$0
fileName=${filePath#./}
for FILE in `ls`
do
 if [ "$FILE" = "$fileName" ]; then
  continue
 fi
 
 fileMod=${FILE/$patter}
 cp $FILE $fileMod
 rm $FILE
done
