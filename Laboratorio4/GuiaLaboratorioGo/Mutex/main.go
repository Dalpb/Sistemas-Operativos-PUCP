package main

import (
	"fmt"
	"sync"
)

var (
	count int //shareed
	wg    sync.WaitGroup
	mu    sync.Mutex
)

func Worker() {
	for x := 0; x < 1000000; x++ {
		mu.Lock()   //this thread has the mutex
		count++     //Critical region protected
		mu.Unlock() //free mutex
	}
	wg.Done()
}

func main() {
	for x := 0; x < 5; x++ {
		wg.Add(1)
		go Worker()
	}
	wg.Wait()
	fmt.Printf("El valor esperado count es 5000000 y el valor final es %d\n", count)
}
