package main

import (
	"fmt"
	"sync"
	"time"
)

var (
	wg  sync.WaitGroup
	ch1 chan struct{} = make(chan struct{}, 1)
	ch2 chan struct{} = make(chan struct{}, 1)
	ch3 chan struct{} = make(chan struct{}, 1)
	ch4 chan struct{} = make(chan struct{}, 1)
	ch5 chan struct{} = make(chan struct{}, 1)
	ch6 chan struct{} = make(chan struct{}, 1)
)

func printA() {
	defer wg.Done()
	<-ch5
	fmt.Printf("A")
	ch2 <- struct{}{}
}
func printB() {
	defer wg.Done()

	<-ch6
	fmt.Printf("B")
	ch2 <- struct{}{}
}
func printC() {
	defer wg.Done()

	<-ch2
	fmt.Printf("C")
	ch3 <- struct{}{}
}

func printD() {
	defer wg.Done()

	<-ch3
	fmt.Printf("D")
	ch4 <- struct{}{}
}

func printE() {
	defer wg.Done()
	<-ch4
	fmt.Printf("E")
}
func main() {
	for {
		wg.Add(4)
		go printA()
		go printB()
		go printC()
		go printD()
		go printE()
		//random A o B
		select {
		case ch5 <- struct{}{}:
		case ch6 <- struct{}{}:
		}

		time.Sleep(1 * time.Second) //just for see the result, its works without it by the way
		wg.Wait()
	}
}
