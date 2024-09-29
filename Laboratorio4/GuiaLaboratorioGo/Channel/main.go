package main

import (
	"fmt"
)

func main() {
	naturals := make(chan int) //channel type integer
	squares := make(chan int)

	//IIFE inmediately invoked Function Expression
	go func() {
		for x := 0; x < 20; x++ {
			naturals <- x //send naturals and stop
		}
		close(naturals) //dont forget it
	}()

	go func() {
		//read naturals and stop until end
		//this range reads every value in naturals, only if its was closed <- IMPORTANT.
		for x := range naturals {
			squares <- x * x
		}
		close(squares) //dont forget it
	}()

	//main thread read squares stop unitl end
	for x := range squares {
		fmt.Println(x)
	}

}
