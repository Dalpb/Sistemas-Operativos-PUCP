package main

import (
	"fmt"
	"time"
)

var (
	ch1 chan struct{} = make(chan struct{}, 1)
	ch2 chan struct{} = make(chan struct{}, 1)
	ch3 chan struct{} = make(chan struct{}, 1)
	ch4 chan struct{} = make(chan struct{}, 1)
)

func printA() {
	fmt.Printf("A")
	ch1 <- struct{}{}
}
func printB() {
	<-ch1
	fmt.Printf("B")
	ch2 <- struct{}{}
}
func printC() {
	<-ch2
	fmt.Printf("C")
	ch3 <- struct{}{}
}

func printD() {
	<-ch3
	fmt.Printf("D")
	ch4 <- struct{}{}
}

func printE() {
	<-ch4
	fmt.Printf("E")
}
func main() {
	for {
		go printA()
		go printB()
		go printC()
		go printD()
		go printE()
		time.Sleep(1 * time.Second) //just for see the result, its works without it by the way
	}

}
