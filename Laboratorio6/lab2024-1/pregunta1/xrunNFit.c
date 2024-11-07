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
    //inicialmente freep es apuntando a base
    base=pow(2,x)+.5;
    if((pt=(unsigned int *)xmalloc(base*unidad))) 
       fprintf(stdout,"Se solicitaron %d bytes y estan ubicados en %p\n",base*unidad,pt);
    else
       fprintf(stderr,"No hay suficiente memoria\n");  
    viewList();
    x++;
    if(x%2 == 0){
      //libero memoria
      printf("LISTA DESPUES DE LIBERAR LIBERO\n");
      xfree(pt);
      viewList();
    }
    if(x==4){
      x = 0;
      i++;
    }
  }
  while(i<=6);





  exit(0);                  
  
}


