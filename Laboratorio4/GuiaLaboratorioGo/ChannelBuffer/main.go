package main

import (
	"fmt"
)

//if the capacity is full, and some value its going to insert in the channel ,the goroutine will be block

func fibonacci(n int, c chan int) {
	x, y := 0, 1

	for i := 0; i < 2*n; i++ {
		c <- x
		fmt.Printf("Orden: %v - valor: %v\n", i, x)
		x = y
		y = x + y
	}
	close(c)
}

func main() {
	c := make(chan int, 20)
	fmt.Println(cap(c))
	go fibonacci(cap(c), c)
	for i := range c {
		fmt.Println(i)
	}
}
