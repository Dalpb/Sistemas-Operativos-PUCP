package main

import (
	"fmt"
	_ "fmt"
	"sync"
	_ "sync"
	_ "time"
)

var (
	ch1 chan string = make(chan string)
	ch2 chan string = make(chan string)
	ch3 chan string = make(chan string)
	ch4 chan string = make(chan string)
	wg  sync.WaitGroup
	mu  sync.Mutex
)

func insert_A() {
	ch1 <- "A"
}
func insert_B() {
	ch2 <- "B"
}

// los AB se hacen independientes
func insert_C() {
	defer wg.Done()
	fmt.Printf("C")
	ch3 <- ""
}
func insert_D() {
	defer wg.Done()

	<-ch3
	fmt.Printf("D")
	ch4 <- ""
}
func insert_E() {
	defer wg.Done()
	<-ch4
	fmt.Printf("E")
}
func insertAB() {
	wg.Add(1)
	go insert_A()
	go insert_B()

	select {
	case msg1 := <-ch1:
		fmt.Printf(msg1)
		wg.Done()
	case msg2 := <-ch2:
		fmt.Printf(msg2)
		wg.Done()
	}
	wg.Wait()
}
func main() {

	for {
		insertAB()
		wg.Add(3)
		go insert_C()
		go insert_D()
		go insert_E()
		wg.Wait()
	}
}
