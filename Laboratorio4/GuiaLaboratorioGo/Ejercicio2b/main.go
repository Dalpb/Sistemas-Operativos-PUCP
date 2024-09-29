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
	<-ch1
	defer wg.Done()
	fmt.Printf("A")
	ch3 <- struct{}{}
}
func printB() {
	<-ch2
	defer wg.Done()
	fmt.Printf("B")
	ch3 <- struct{}{}
}
func printC() {
	<-ch3
	defer wg.Done()
	fmt.Printf("C")
	ch4 <- struct{}{}
}

func printD() {
	<-ch4
	defer wg.Done()
	fmt.Printf("D")
	ch5 <- struct{}{}
}

func printE() {
	<-ch5
	defer wg.Done()
	fmt.Printf("E")
}
func main() {
	ch1 <- struct{}{}
	wg.Add(4)
	sw := 1
	for {
		go printA()
		go printB()
		go printC()
		go printD()
		go printE()
		wg.Wait()
		sw = sw * -1
		switch sw {
		case 1:
			ch1 <- struct{}{}
		case -1:
			ch2 <- struct{}{}
		}
		wg.Add(4)
		time.Sleep(1 * time.Second) //just for see the result, its works without it by the way
	}
}
