package main

import (
	"fmt"
	"sync"
)

var (
	wg  sync.WaitGroup
	ch1 chan struct{} = make(chan struct{}, 1) //for admin
	ch2 chan struct{} = make(chan struct{}, 1) //for admin
	ch3 chan struct{} = make(chan struct{}, 1)
	ch4 chan struct{} = make(chan struct{}, 1)
	ch5 chan struct{} = make(chan struct{}, 1)
	ch6 chan struct{} = make(chan struct{}, 1)
	ch7 chan struct{} = make(chan struct{}, 1)
	ch8 chan struct{} = make(chan struct{}, 1)
	ch9 chan struct{} = make(chan struct{})
)

func worker1() {
	for {
		//each loop goroutine will print only one letter
		select {
		case <-ch1:
			//goes first
			fmt.Printf("A")   //print
			ch7 <- struct{}{} //call to B
		case <-ch2:
			//goes second
			<-ch8             //wait
			fmt.Printf("A")   //print
			ch3 <- struct{}{} //call to C
		}

	}
	wg.Done()
}

func worker2() {
	for {
		select {
		case <-ch1:
			//goes second
			<-ch7             //wait
			fmt.Printf("B")   //print
			ch3 <- struct{}{} //call to C
		case <-ch2:
			//goes first
			fmt.Printf("B")   //print
			ch8 <- struct{}{} //call to A
		}

	}
	wg.Done()
}

func worker3() {
	for {
		<-ch3
		fmt.Printf("C")
		ch4 <- struct{}{}
	}
	wg.Done()
}

func worker4() {
	for {
		<-ch4
		fmt.Printf("D")
		ch5 <- struct{}{}
	}
	wg.Done()
}

func worker5() {
	for {
		<-ch5
		fmt.Printf("E\n")
		//finished one loop
		ch9 <- struct{}{}
	}
	wg.Done()
}
func admin() {
	for {
		ch1 <- struct{}{}
		ch1 <- struct{}{}
		<-ch9 //wait for the next loop
		ch2 <- struct{}{}
		ch2 <- struct{}{}
		<-ch9 //wait for the next loop
	}
}

func main() {
	wg.Add(5)
	go admin()
	go worker1()
	go worker2()
	go worker3()
	go worker4()
	go worker5()
	wg.Wait()
	fmt.Printf("\n")
}
