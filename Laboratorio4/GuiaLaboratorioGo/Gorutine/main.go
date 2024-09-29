package main

import (
	"fmt"
	"time"
)

func operation(x int) {
	fmt.Printf("I'm routine %d\n", x) //order is not defined
}
func main() {
	//initilize with main thread
	for x := 0; x < 5; x++ {
		go operation(x) //create 5 threads
	}

	time.Sleep(1 * time.Second) //main thread sleep
}
