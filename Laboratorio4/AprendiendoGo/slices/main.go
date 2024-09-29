package main

import (
	"fmt"
	_ "fmt"
)

func main() {
	//slice  -> representa un arreglo dinamico ,puede crecer
	primos := [6]int{2, 3, 5, 7, 11, 13}

	//de primos declaro a slice tomo los valors desde index 1 a 3
	slice1 :=
		primos[1:4]
	fmt.Println("EL arreglo primos contiene: ", primos)
	fmt.Println("El slice creado es :", slice1)

	//con make se pude crear sin especificar tamaño
	slice2 := make([]int, 2, 4)
	//longitud -> tiene 2 elementos inicializados
	//capacidad -> tiene el capacidad 4 , puedo extenderlo a hasta 4 elementos
	slice2[0] = 1
	slice2[1] = 100

	fmt.Println(slice2, len(slice2), cap(slice2))
	//extiendo hasta su capacidad maxima
	slice2 = slice2[0:4]
	fmt.Println(slice2, len(slice2), cap(slice2))

	//si quiero extende más que la capacdiad, esto cambia auto la capacidad ,por 2
	slice2 = append(slice2, 2, 3, 5, 1, 53)
	fmt.Println(slice2, len(slice2), cap(slice2))

	//maps
	diccionary := make(map[string]int)

	diccionary["hola"] = 0
	diccionary["soy"] = 1
	diccionary["un"] = 2
	diccionary["informatico"] = 3

	fmt.Println(diccionary)
	fmt.Println(diccionary["hola"])
}
