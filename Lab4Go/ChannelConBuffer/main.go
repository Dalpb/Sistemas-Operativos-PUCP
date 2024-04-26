package main

import (
	"fmt"
	_ "fmt"
)

// canal con buffer, no bloque los hilos al instante,
// bloquea solo si, se envia datos al canal cuando esta lleno
// bloquea el hilo. si toma datos cuando el canal esta vacio
func fibonacci(n int, c chan int) {
	x, y := 0, 1

	for i := 0; i < 2*n; i++ {
		c <- x
		fmt.Printf("Orden %v - Valor: %v\n", i, x)
		x, y = y, x+y
	}

	close(c)
}

func main() {
	//canal con 100buffer
	c := make(chan int, 20)

	//capacidad del buffer
	fmt.Println(cap(c))

	go fibonacci(cap(c), c)

	for i := range c {
		fmt.Println(i)
	}
}
