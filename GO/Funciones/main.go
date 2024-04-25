package main

import (
	"fmt"
	_ "fmt"
	_ "os"
)

func main() {
	fmt.Println(suma_serie_n(6, 0))

}

// los paramteros y al final el tipo que devuelve
func suma_serie_n(n int, i int) int {
	if n == i {
		return i
	} else {
		return i + suma_serie_n(n, i+1)
	}
}
