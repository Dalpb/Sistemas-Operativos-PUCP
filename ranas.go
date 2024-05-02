package main
// logica de saltos de: https://github.com/IvanLisas/frogs/blob/master/com/source/Rana.java
import(
	"fmt"
	"sync"
)

var(
	N int = 6
	arr [7]int
	mu sync.Mutex
	wg sync.WaitGroup
)

func rana(x int, medio int){
	var i int
	var destino int
	if x <= medio { // debe saltar a la derecha
		i = x - 1
		destino = medio + x //a donde debe llegar cada uno, para los que estan antes de la mitad
		//fmt.Printf("Soy %d y mi destino es %d. Mi indice ahora es %d\n", x, destino, i)
		for i!=destino {
			mu.Lock()
			if i+1<=N && arr[i+1]==-1{// puedo saltar una piedra vacia
				//Si no se da lo siguiente, salto: no me conviene saltar no es mi destino, el de adelante de donde quiero saltar es de mi equipo (misma direccion) o el de adelante de donde quiero saltar y el de atras mio son del mismo equipo
				if !(i+1!=destino && (i+2<=N && arr[i+2]<=medio || (i-1>=0 && ((arr[i+2]>medio && arr[i-1]>medio) || (arr[i+2]<=medio && arr[i-1]<=medio))))){
					arr[i+1] = arr[i]
					arr[i] = -1
					for j:=0;j<=N;j++{
						fmt.Printf("%d ", arr[j])
					}
					fmt.Println()
					i++
				}
			} else if i+2<=N && arr[i+2]==-1{
				//Si no se da lo siguiente, salto 2 posiciones: no me conviene saltar 2 si no es mi destino, el de adelante de donde quiero saltar es de mi equipo (misma direccion) o el que esta justo en frente mio es de mi equipo
				if !(i+2!=destino && ((i+3<=N && arr[i+3]<=medio) || (i+1<=N && arr[i+1]<=medio))){
					arr[i+2] = arr[i]
					arr[i] = -1
					for j:=0;j<=N;j++{
						fmt.Printf("%d ", arr[j])
					}
					fmt.Println()
					i = i + 2
				}
			}
			mu.Unlock()
		}

	} else{ //saltar a la izquierda
		i = x
		destino = x - (medio+1) // a donde debe llegar cada uno, para los q estan despues de la mitad
		//fmt.Printf("Soy %d y mi destino es %d. Mi indice ahora es %d\n", x, destino, i)
		for i!=destino{
			mu.Lock()
			//Si no se da lo siguiente, salto: no me conviene saltar no es mi destino, el de adelante de donde quiero saltar es de mi equipo (misma direccion) o el de adelante de donde quiero saltar y el de atras mio son del mismo equipo
			if i-1>=0 && arr[i-1]==-1{// puedo saltar a una piedra vacia
				if !(i-1!=destino && (i-2>=0 && arr[i-2]>medio || (i+1<=N && ((arr[i-2]>medio && arr[i+1]>medio) || arr[i-2]<=medio && arr[i+1]<=medio)))){
					arr[i-1] = arr[i]
					arr[i] = -1
					for j:=0;j<=N;j++{
						fmt.Printf("%d ", arr[j])
					}
					fmt.Println()
					i--
				}
			} else if i-2>=0 && arr[i-2]==-1{
				//Si no se da lo siguiente, salto: no me conviene saltar no es mi destino, el de adelante de donde quiero saltar es de mi equipo (misma direccion) o el de adelante de donde quiero saltar y el de atras mio son del mismo equipo
				if !(i-2!=destino && ((i-3>=0 && arr[i-3]>medio) || (i-1>=0 && arr[i-1]>medio))){
					arr[i-2] = arr[i]
					arr[i] = -1
					for j:=0;j<=N;j++{
						fmt.Printf("%d ", arr[j])
					}
					fmt.Println()
					i = i - 2
				}
			}
			mu.Unlock()
		}
	}
	wg.Done()
}

func main(){
	var medio int
	medio = (N+1)/2
	for i:=0;i<medio;i++{
		arr[i] = i+1
	}
	arr[medio] = -1
	for i:=medio+1;i<=N;i++{
		arr[i] = i
	}

	for k:=0;k<=N;k++{
		if(k!=medio){
			go rana(arr[k], medio)
			wg.Add(1)
		}	
	}
	wg.Wait()

	/*for j:=0;j<=N;j++{
		fmt.Printf("%d ", arr[j])
	}
	fmt.Println()*/

}


