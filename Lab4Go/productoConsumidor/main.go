package main

import (
	"fmt"
	"sync"
)

var (
	buffer [5]int = [5]int{-1, -1, -1, -1, -1}
	//index  int    //?
	wg sync.WaitGroup
	mu sync.Mutex
)

func productor() {
	var index int
	for n := 0; n < 20; n++ {
		item := n * n
		index = n % 5
		buffer[index] = item
		fmt.Printf("productor %d %d %v\n", index, item, buffer)
	}
	wg.Done()
}
func consumidor() {
	var item int
	var index int
	for n := 0; n < 20; n++ {
		index = n % 5
		item = buffer[index]
		buffer[index] = -1
		fmt.Printf("Consumidor %d %d %v\n", index, item, buffer)
	}
	wg.Done()
}

func main() {
	wg.Add(2)
	go consumidor()
	go productor()
	wg.Wait()
}
