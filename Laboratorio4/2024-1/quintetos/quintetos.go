// main.go
package main

import (
	"fmt"
	"sync"
)

var (
	wg       sync.WaitGroup
	channels []chan int = make([]chan int, 5)
	ready    chan struct{}
)

func admin() {
	for {
		for i := range channels {
			x := <-channels[i]
			fmt.Printf("%d", x)
		}
		fmt.Println()
	}
}

func task(n int) {
	for x := 0; x < 50; x++ {
		channels[n] <- n //each theards blocked
	}
	wg.Done()
}

func main() {

	//init each channel
	for i := range channels {
		channels[i] = make(chan int)
	}

	go admin()

	for x := 0; x < 5; x++ {
		wg.Add(1)
		go task(x)
	}
	wg.Wait()
}
