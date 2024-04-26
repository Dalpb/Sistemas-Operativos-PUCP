package main

import (
	"fmt"
	_ "fmt"
	"sync"
	_ "sync"
)

var wg sync.WaitGroup
var x int

func worker1(ch1 chan int) {
	fmt.Printf("Sistemas ")
	ch1 <- 1
	wg.Done()
}
func worker2(ch1 chan int, ch2 chan int) {
	<-ch1 //bloque hasta que se ingrese algo
	fmt.Printf("INF239 ")
	ch2 <- 1 //blquea al wrok3 si este ingrresa antes
	wg.Done()
}
func worker3(ch2 chan int, ch3 chan int) {
	<-ch2
	fmt.Printf("Operativos ")
	ch3 <- 1
	wg.Done()
}
func worker4(ch3 chan int) {
	<-ch3
	fmt.Printf(" \n")
	wg.Done()
}

func main() {

	ch1 := make(chan int)
	ch2 := make(chan int)
	ch3 := make(chan int)

	wg.Add(4)
	go worker1(ch1)
	go worker2(ch1, ch2)
	go worker3(ch2, ch3)
	go worker4(ch3)
	wg.Wait()
}
