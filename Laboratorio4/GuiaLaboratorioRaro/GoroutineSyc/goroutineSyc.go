package main

import (
	"fmt"
	_ "fmt"
	"sync"
)

func routine(n int) {
	defer wg.Done() //contador -1 cuando acabe el hilo
	fmt.Printf("Im goruotine %d \n", n)
}

var wg sync.WaitGroup

func main() {

	for x := 0; x < 5; x++ {
		wg.Add(1)
		go routine(x)
	}
	//el contador es 5

	//si no lo agregase el hilo principal termina y provoca que no se realizan las demas hilos
	wg.Wait() //bloque hasta que llegue a 0
}
