package main

import (
	"fmt"
	_ "fmt"
	"sync"
	_ "sync"
	"time"
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
	fmt.Printf("C")
	ch3 <- ""
}
func insert_D() {
	<-ch3
	fmt.Printf("D")
	ch4 <- ""
}
func insert_E() {
	<-ch4
	fmt.Printf("E")
}
func insert_AoB() {
	wg.Add(1)
	time.Sleep(time.Second)
	go insert_A()
	go insert_B()
	select {
	case msg1 := <-ch1:
		wg.Done()
		fmt.Printf(msg1)
	case msg2 := <-ch2:
		wg.Done()
		fmt.Printf(msg2)
	}
	wg.Wait()
}
func main() {

	for {
		insert_AoB()
		go insert_C()
		go insert_D()
		go insert_E()
	}
}
