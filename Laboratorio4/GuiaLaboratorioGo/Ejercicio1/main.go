package main

import (
	"fmt"
	"sync"
)

var wg sync.WaitGroup //I can declare channels here

func worker1(c1 chan struct{}, c2 chan struct{}) {
	<-c1
	fmt.Printf("Sistemas ")
	wg.Done()
	c2 <- struct{}{}
}
func worker2(c1 chan struct{}) {
	fmt.Printf("INF239 ")
	wg.Done()
	c1 <- struct{}{}
}

func worker3(c2 chan struct{}, c3 chan struct{}) {
	<-c2
	fmt.Printf("Operativos ")
	wg.Done()
	c3 <- struct{}{}
}

func worker4(c3 chan struct{}) {
	<-c3
	fmt.Printf("\n")
	wg.Done()
}

func main() {
	wg.Add(4)
	ch1 := make(chan struct{})
	ch2 := make(chan struct{})
	ch3 := make(chan struct{})
	go worker1(ch1, ch2)
	go worker2(ch1)
	go worker3(ch2, ch3)
	go worker4(ch3)
	wg.Wait()
}
