package main

import (
	"fmt"
	_ "fmt"
	"math"
	_ "math"
	_ "os"
	"time"
	_ "time"
)

func main() {

	defer fmt.Println("Cuando termine este codigo,yo me imprimo")

	slice1 := make([]int, 10, 15)
	for i := 0; i < 10; i++ {
		fmt.Printf("se imprime el numero: %d\n", i)
		slice1[i] = i
	}

	defer fmt.Println("Yo me imprime antes que el primer deffer")

	//range devuelve el index, y su valor -> _,valor (otra forma)
	for i, valor := range slice1 {
		if valor%2 == 0 {
			slice1[i] = int(math.Pow(2, float64(valor)))
		}
	}

	ndia := time.Now().Weekday()

	hoy := int(ndia)

	//no se colocan breaks
	switch hoy {
	case 0:
		fmt.Println("Hoy es domingo")
	case 1:
		fmt.Println("Hoy es lunes")
	case 2:
		fmt.Println("Hoy es martes")
	case 3:
		fmt.Println("Hoy es miercoles")
	case 4:
		fmt.Println("Hoy es jueves")
	case 5:
		fmt.Println("Hoy es viernes")
	case 6:
		fmt.Println("Hoy es sabado")

	}

}
