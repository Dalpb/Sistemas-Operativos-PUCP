package main

import (
	"fmt"
	_ "fmt"
	_ "sync"
	"time"
	_ "time"
)

var (
	ch1 chan int = make(chan int)
	ch2 chan int = make(chan int)
	ch3 chan int = make(chan int)
	ch4 chan int = make(chan int)
)

func insert_A() {
	fmt.Printf("A")
	ch1 <- 1
}
func insert_B() {
	<-ch1
	fmt.Printf("B")
	ch2 <- 1
}
func insert_C() {
	<-ch2
	fmt.Printf("C")
	ch3 <- 1
}
func insert_D() {
	<-ch3
	fmt.Printf("D")
	ch4 <- 1
}
func insert_E() {
	<-ch4
	fmt.Printf("E")

}

func main() {
	for {
		time.Sleep(time.Second * 1)
		go insert_A()
		go insert_B()
		go insert_C()
		go insert_D()
		go insert_E()
	}
}
