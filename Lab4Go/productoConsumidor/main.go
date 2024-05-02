package main

import (
	"fmt"
	"sync"
)

var (
	buffer [5]int = [5]int{-1, -1, -1, -1, -1}
	//index  int    //?
	count int = 0
	wg    sync.WaitGroup
	mu    sync.Mutex
	ch1   chan int = make(chan int)
	ch2   chan int = make(chan int)
)

func productor() {
	var index int
	for n := 0; n < 20; n++ {
		//no se bloquea al inicio si este ingresa, priorizo a que ingrese algo
		item := n * n
		index = n % 5
		//bloqueamos la variable compartida
		mu.Lock()
		buffer[index] = item
		mu.Unlock()
		if index == 4 {
			ch1 <- 1 //por primera vz, avisamos que llenamos complemtamente
			<-ch2    // nos bloqueamos
		}
		fmt.Printf("productor %d %d %v\n", index, item, buffer)

	}
	wg.Done()
}
func consumidor() {
	var item int
	var index int
	for n := 0; n < 20; n++ {
		index = n % 5
		//en caso se encuentre vacio, evita a que el consumidor este activo si este goroutine llega antes
		if index == 0 {
			<-ch1
		}

		mu.Lock()
		item = buffer[index]
		//bloqueamos la variable compartida
		buffer[index] = -1
		mu.Unlock()
		fmt.Printf("Consumidor %d %d %v\n", index, item, buffer)
		if index == 0 {
			ch2 <- 1
		}
	}
	wg.Done()
}

func main() {
	wg.Add(2)
	go consumidor()
	go productor()
	wg.Wait()
}
