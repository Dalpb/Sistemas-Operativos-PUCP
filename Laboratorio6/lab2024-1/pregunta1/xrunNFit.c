#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <math.h>

void *xmalloc (size_t nbytes);
void viewList();
void xfree(void *ap);

int main(void)
{ unsigned int x,unidad,base,i;
  unsigned int *pt;

  unidad=1024; 
  x=0;
  i = 0;
  do {
    //inicialmente freep apunta a base y en el transcurso varia entre el hueco y la base, esto es por la liberación y se apunta al bloque liberado , para la proxima asignación de memoria.
    //podemos ver mejor que se realiza next fit ,por ejmplo i=1,x=2, donde se apuntaba y base,  y al necesitar la creación del nuevo hueco que satisfaba las 257unidades , se crea otro y el freep se apunta al previo,
 

    //Al igual en i=2, x= 0; en los 3 huecos libres, buscamos asignar 65units en el hueco de 380
    printf("Iteración i: %u , x: %u\n",i,x);
    base=pow(2,x)+.5;
    if((pt=(unsigned int *)xmalloc(base*unidad))) 
       fprintf(stdout,"Se solicitaron %d bytes y estan ubicados en %p\n",base*unidad,pt);
    else
       fprintf(stderr,"No hay suficiente memoria\n");  
    viewList();
    if(x % 2 == 0 ){ 
      //x %2 != 0
      //libero memoria
      printf("LISTA DESPUÉS DE LIBERAR LIBERO\n");
      xfree(pt);
      viewList();
    }
    x++;
    if(x==4){
      x = 0;
      i++;
    }
  }
  while(i<=6);





  exit(0);                  
  
}


