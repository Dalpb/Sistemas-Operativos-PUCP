package main

import (
	"fmt"
	"sync"
)

var (
	arr     [500]int
	wg      sync.WaitGroup
	canales [20]chan struct{}
	canalOk [20]chan struct{}
	termino chan struct{} = make(chan struct{})
)

func initArr() {
	for i := 0; i < len(arr); i++ {
		arr[i] = -1
	}
	for i := 0; i < len(canales); i++ {
		canales[i] = make(chan struct{})
		canalOk[i] = make(chan struct{})
	}
}

func worker(id int) {
	defer wg.Done()

	for x := 0; x < 25; x++ {
		canales[id] <- struct{}{}       // el admin permite que imprima
		for i := 0; i < len(arr); i++ { //search
			if arr[i] == -1 {
				arr[i] = id

				break
			}
		}
		termino <- struct{}{}     //avisa a admin
		canalOk[id] <- struct{}{} //ok termino de imprimir, avisa al admin
	}
}
func admin() {
	for x := 0; x < 25; x++ { //se hara 25 veces

		for y := 0; y < len(canales); y++ { //each goroutine random
			select {
			case <-canales[0]:
				<-termino
			case <-canales[1]:
				<-termino
			case <-canales[2]:
				<-termino
			case <-canales[3]:
				<-termino
			case <-canales[4]:
				<-termino
			case <-canales[5]:
				<-termino
			case <-canales[6]:
				<-termino
			case <-canales[7]:
				<-termino
			case <-canales[8]:
				<-termino
			case <-canales[9]:
				<-termino
			case <-canales[10]:
				<-termino
			case <-canales[11]:
				<-termino
			case <-canales[12]:
				<-termino
			case <-canales[13]:
				<-termino
			case <-canales[14]:
				<-termino
			case <-canales[15]:
				<-termino
			case <-canales[16]:
				<-termino
			case <-canales[17]:
				<-termino
			case <-canales[18]:
				<-termino
			case <-canales[19]:
				<-termino
			}
		}
		//notice every thread finished
		for y := 0; y < len(canalOk); y++ {
			<-canalOk[y]
		}
	}
}
func main() {

	initArr()
	go admin()
	for i := 0; i < 20; i++ {
		wg.Add(1)
		go worker(i)
	}

	wg.Wait()
	fmt.Printf("%v\n", arr)
}
