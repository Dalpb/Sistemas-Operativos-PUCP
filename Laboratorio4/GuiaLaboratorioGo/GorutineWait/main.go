package main

import (
	"fmt"
	"sync"
)

var wg sync.WaitGroup //barrier

func operation(x int) {
	defer wg.Done()                   // counter --
	fmt.Printf("I'm routine %d\n", x) //order is not defined
}

func main() {
	//If the main thread dies, the program will terminate.
	for x := 0; x < 5; x++ {
		wg.Add(1) //the counter ++
		go operation(x)
	}
	wg.Wait() //main thread will wait here until count is zero
}
