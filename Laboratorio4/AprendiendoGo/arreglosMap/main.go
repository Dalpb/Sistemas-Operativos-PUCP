package main

import (
	"fmt"
	_ "fmt"
)

// estructuras en go
type Vector struct {
	x float64
	y float64
}

func main() {

	var (
		vector1 Vector
		vector2 Vector = Vector{3.1, 4.23}
	)
	vector1.x = 2.3
	vector1.y = 25.4

	vector3 := Vector{2, 4}

	fmt.Println("Tenemos un vector3 :", vector3)
	fmt.Println("Tenemos un vector2 :", vector2)

	//arreglos
	var (
		arr1 [10]int   = [10]int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
		arr2 [4]Vector = [4]Vector{{1, 1}, {2, 2}, {3, 3}, {4, 4}}
	)

	arr3 := [5]float32{1.2, 2.3, 3.4, 4.5, 5.6}
	
	fmt.Println("Tenemos un conjutno de vectores: ", arr2)
	fmt.Println("Quiero el componenete x del segundo vector", arr2[1].x)

	fmt.Println("Un array de numeros del 1 al 10: ", arr1)
	fmt.Println("Array con float: ", arr3)

}
