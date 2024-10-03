// solution by Fidel Apari Sanchez
package main

import (
	"fmt"
	"sync"
)

var (
	wg      sync.WaitGroup
	canales [10]chan struct{}
)

func config() {
	for i := 0; i < len(canales); i++ {
		canales[i] = make(chan struct{}, 1)
	}
}

func asign(i int) {

	canales[i] <- struct{}{}
}

func sincronizacion() {

	for i := 0; i < 5; i++ {
		go asign(0) //free 5 threads
	}
	//finished to print,each theards notice to the admin
	<-canales[2]
	<-canales[3]
	<-canales[4]
	<-canales[5]
	<-canales[6]

	for i := 0; i < 5; i++ {
		canales[1] <- struct{}{} //say ok to each thread
	}

	fmt.Printf("\n") //print

	go sincronizacion() //again
}

func task(n int) {
	for x := 0; x < 50; x++ {
		<-canales[0]        //wait for others threads
		fmt.Printf("%d", n) //print
		asign(n + 2)        //notice to admin
		<-canales[1]
	}
	wg.Done()
}

func main() {
	config()
	go sincronizacion()
	for x := 0; x < 5; x++ {
		wg.Add(1)
		go task(x)
	}
	wg.Wait()
	fmt.Println()
}
