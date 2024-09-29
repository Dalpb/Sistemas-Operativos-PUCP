package main

import (
	"fmt"
	_ "fmt"
	"sync"
	_ "sync"
)

func worker() {
	defer wg.Done()
	for x := 0; x < 1000000; x++ {
		//protegemos la variables compartidas para evitar race condiction
		mu.Lock() //lock , adquiere el bloqueo del mutex. Si el mutex ya está bloqueado por otro goroutine, el goroutine que llama a mu.Lock() se bloqueará hasta que el mutex esté disponible.
		count++
		mu.Unlock() //libera el bloqueo del mutex. Esto permite que otros goroutines adquieran el bloqueo y accedan al recurso compartido de manera segura.
	}

}

var (
	count int
	wg    sync.WaitGroup
	mu    sync.Mutex
)

func main() {
	for x := 0; x < 5; x++ {
		wg.Add(1)
		go worker()
	}
	wg.Wait()
	fmt.Println(count)

}
