package main

import (
	"fmt"
	_ "fmt"
	"sync"
	_ "sync"
	_ "time"
)

var (
	ch1 chan int = make(chan int)
	ch2 chan int = make(chan int)
	ch3 chan int = make(chan int)
	ch4 chan int = make(chan int)
	wg  sync.WaitGroup
)

func insert_A() {
	defer wg.Done()

	fmt.Printf("A")
	ch1 <- 1
}
func insert_B() {
	defer wg.Done()

	<-ch4
	fmt.Printf("B")
}
func insert_C() {
	defer wg.Done()

	<-ch1
	fmt.Printf("C")
	ch2 <- 1
}
func insert_D() {
	defer wg.Done()

	<-ch2
	fmt.Printf("D")

	ch3 <- 1
}
func insert_E() {
	defer wg.Done()

	<-ch3
	fmt.Printf("E")
	ch4 <- 1
}

func main() {
	for {
		wg.Add(5)
		go insert_A()
		go insert_B()
		go insert_C()
		go insert_D()
		go insert_E()
		wg.Wait()
		wg.Add(3)
		go insert_C()
		go insert_D()
		go insert_E()
		ch1 <- 1
		<-ch4
		wg.Wait()
	}
}
