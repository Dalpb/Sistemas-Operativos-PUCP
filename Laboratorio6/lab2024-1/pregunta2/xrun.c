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
    //En las siguientes impresiones verificamos 
    printf("Iteración i: %u , x: %u\n",i,x);
    base=pow(2,x)+.5;
    if((pt=(unsigned int *)xmalloc(base*unidad))) 
       fprintf(stdout,"Se solicitaron %d bytes y estan ubicados en %p\n",base*unidad,pt);
    else
       fprintf(stderr,"No hay suficiente memoria\n");  
    viewList();
    if(x % 2 == 0){ 
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
  //PARA una ultima verificaciones

  //forme los bloques huecos -> pedimos memoria
  //pediremos 381 unidades y si es best fit deberia de ocupar memoria en el hueco de 382 y se queda con 1
  xmalloc(6065);
  viewList();
  exit(0);                  
  
}