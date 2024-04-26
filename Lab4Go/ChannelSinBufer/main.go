package main

import (
	"fmt"
	_ "fmt"
)

func main() {
	naturals := make(chan int)
	squares := make(chan int)

	go func() {
		//el canal naturals se llena de 0,1,2,3,4..
		for x := 0; x < 20; x++ {
			naturals <- x //si ingresa este primero, espera a que se lea el valor antes de ingresar otro valor
		}
		//no recibira mas envios
		close(naturals)
	}()

	go func() {
		//si ingreso este primero, espera a que se ingrese un valor antes de asignar el valor en x
		for x := range naturals {
			squares <- x * x
		}
		close(squares)
	}()

	//espera el hilo en squares
	for x := range squares {
		fmt.Println(x)
	}
}
