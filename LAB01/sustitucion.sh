#!/bin/bash
echo "Sustitucion por -> param:-word"
valorDef="definido"
valor=${valorDef:-indefinido}
echo "El valor final es ${valor}"
valor2=${valorIndef:-indefinido}
echo "valorIndef es null o no existe, el valor final es ${valor2}\n"

echo "Sustitucion por -> param:=word"
unset valorDef
echo "valorDef ahora es null, el valor defualt es ${valorDer:=DEFAULT} "


echo "Sustitucion por -> param:?msg ,bota un error con ese mensaje si es null"

echo "Sustitucion por -> param:+word"
valorDef="YA ESTOY DEFINIDO"
echo "El valor es ${valorDef}, entonces ${valorDef:+Se realiza sustitucion}"

var="Hello world"
echo "Sustitucion con param:offser"
echo "$var obtengo el estring desde la pos offset : ${var:5}"

echo "Sustitucion con param:offset:len"
echo "$var obtengo desde pos offset con un len caracteres : ${var:5:3}"

echo "#param"
echo "$var obtengo cantidad de caracteres: ${#var}"

var="Hello\nHelloWorld\n"

echo "param##word"
echo "$var remueve los march con word en param desde el inicio: ${var#Hello} "

echo "param%word"
echo "$var remueve los march con word desde el fin : ${var%%\\n}"

echo "Sustitucion con ordenes ``"
Date=`date`
echo $Date

echo "Sustitucion aritmetica"
A=3
B=2
echo "$((A+B + A/B + A*B))"

