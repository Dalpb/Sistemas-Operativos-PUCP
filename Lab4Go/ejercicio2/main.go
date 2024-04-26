package main

import (
	"fmt"
	_ "fmt"
	_ "sync"
	"time"
	_ "time"
)

func insert_char(n string) {
	fmt.Printf(n)
}

func main() {
	for {
		time.Sleep(time.Second * 1)
		go insert_char("A")
		go insert_char("B")
		go insert_char("C")
		go insert_char("D")
		go insert_char("E")

	}
}
