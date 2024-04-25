package main

import (
	"fmt"
)

func main() {
	// Para ejecutar go  -> go build <nombre>.go
	var (
		cadena     string
		num1, num2 int32
		numDouble  float64
		numfloat   float32
	)

	cadena = "Aprendiendo GO basico :D"
	num1 = 12
	num2 = 4 + 4 //que pasa si lo coloco como float

	numDouble = 234.5434
	numfloat = 3.14

	fmt.Println("Mi cadena continene : ", cadena, "\n Tambien puedo colocar mas texto")

	fmt.Println("El valor de num1 +num2: ", num1+num2)
	fmt.Println("El valor de numDoube + numFloat: ", numDouble+float64(numfloat))

	//declaracion con valor
	var (
		pais string = "Peru"
		edad int16  = 21
	)
	fmt.Println("Vivo en ", pais)
	fmt.Println("Tengo ", edad, "años")

	//decalracion con valor y tipo implicita

	nombre := "Diego Palomino"
	fmt.Println("Mi nombre es ", nombre)

}
