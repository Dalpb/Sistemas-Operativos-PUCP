package main

import (
	"fmt"
	_ "fmt"
	"time"
	_ "time"
)

func routine(n int) {
	if n == 2 {
		time.Sleep(2 * time.Second)
	}
	fmt.Printf("Im goruotine %d \n", n)
}

func main() {

	for x := 0; x < 5; x++ {
		go routine(x)
	}
	time.Sleep(3 * time.Second)
}
