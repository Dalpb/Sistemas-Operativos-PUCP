
/*
 * ssoo/xalloc.98/xalloc.c
 *
 * CONTENIDO INICIAL:
 *	Codigo correspondiente a la Seccion 8.7 del libro:
 *	"The C Programing Language", de B. Kernigham y D. Ritchie.
 *
 * En este fichero se incluiran las rutinas pedidas
 *
 */

#include <unistd.h>
#include "xalloc.h"
#include <stdio.h>
/*
 * Definicion de la cabecera para huecos y bloques.
 * La union con un campo de tipo Align fuerza que el tama~no
 * de la cabecera sea multiplo del tama~no de este tipo.
 */
typedef long Align;    /* for alignment to long boundary */

union header {   /* block header: */
	struct {
		union header *ptr;  /* next block if on free list */
		size_t size;     /* size of this block */
	} s;
	Align x;             /* force alignment of blocks */
};

typedef union header Header;

/*
 * La lista de huecos esta ordenada por direcciones y es circular.
 * base es el "falso" hueco de tama~no cero que asegura que la lista
 * nunca esta vacia
 */
static Header base;   /* empty list to get started */

/*
 * freep apuntara al hueco situado en la lista antes del hueco
 * por el que comenzara la busqueda.
 * Necesario para implementar la estrategia next-fit
 */
static Header  *freep = NULL;  /* start of the free list */


#define NALLOC 1024

/*
 * morecore: ask system for more memory
 *
 * Esta funcion se llama desde xmalloc cuando no hay espacio.
 * Aumenta el tama~no de la zona de datos como minimo en NALLOC*sizeof(Header)
 * y a~nade esta nueva zona a la lista de huecos usando xfree.
 *
 */

static Header *morecore(size_t nu)
{
	char *cp;
	Header *up;

	if (nu < NALLOC)nu = NALLOC;
	cp= sbrk(nu * sizeof(Header)); /*pedimos nu*sizeof(Header) bytes y reserva memoria, pointer -> |HEADER |HEADER |HEADER |HEADER |HEADER |HEADER | -> */
	if (cp == (char *) -1) /* no space at all */
		return NULL;
	up = (Header *) cp; /*asignamos un puntero al espacio liberado*/
	up ->s.size = nu; /*colocamos la cantidad unitaria a*/
	xfree((void *)(up+1));
	return freep;
}

/* xmalloc: general-purpose storage allocator */
void *xmalloc (size_t nbytes)
{
	Header  *p, *prevp;
	size_t nunits;
	printf("Empezamos a buscar desde freep -> %p\n\n",freep);
	/*
	   Calcula cuanto ocupara la peticion medido en tama~nos de
	   cabecera (incluyendo la propia cabecera).
	   El termino "sizeof(Header)-1" provoca un redondeo por exceso.
	   El termino "+ 1" es para incluir la propia cabecera.
	*/
	nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) + 1;
	printf("Necesito de %zu unidades\n",nunits);

	/* En la primera llamada se construye una lista de huecos con un
	   unico elemento de tama~no cero (base) que se apunta a si mismo */
	if (( prevp = freep) == NULL ) { /* no free list yet */
		base.s.ptr = freep = prevp = & base;
		base.s.size = 0;
	}

	/*
	   Recorre la lista circular de huecos, empezando por el siguiente al
	   que apunta freep, hasta que encuentra uno que satisface la peticion
	   o da toda una vuelta a la lista (no hay espacio suficiente)
	*/
	for (p= prevp->s.ptr; ; prevp = p, p = p->s.ptr){
		if (p->s.size >= nunits) {  /*encontramos hueco*/
			if (p->s.size == nunits)  /* el hueco es exacto */
				prevp->s.ptr = p->s.ptr;
			else {  /* allocate tail end */
				p->s.size -= nunits;
				p+= p->s.size;
				p->s.size = nunits;
			}
			printf("El bloque a asignar se encuentra a asignar está en %p\n",p);
			freep = prevp; /* estrategia next-fit: un  bloque antes del que se asigno */
			printf("El freep apuntará %p\n",freep);
			return (void *)(p+1); /* devuelve un puntero a la zona de datos del bloque */
		}
		/* Si ha dado toda la vuelta pide mas memoria y vuelve
		   a empezar */
		if(p == freep) /* wrapped around free list */
			if ((p = morecore(nunits)) == NULL)
				return NULL;  /* si no puede dar más memoria, retorna null */
	}
}


/* xfree: put block ap in the free list provided by morecore */
void xfree(void *ap)
{
	Header *bp, *p;

	bp = (Header *)ap - 1;  /* point to block header */

	/*
	   Bucle que recorre la lista de huecos para buscar el hueco
	   anterior al bloque que se va a liberar.
	   Del bucle se sale cuando se encuentran los dos huecos
	   de la lista (el apuntado por p y el apuntado por p->s.ptr)
	   entre los que se incluira el nuevo hueco (el apuntado por bp).
	   Hay dos casos:
		- La direccion del nuevo hueco es mayor (bp > p) o
		menor (bp < p->s.ptr) que la de ningun otro hueco de la
		lista (corresponde al break)
		- La direccion del nuevo hueco esta comprendida entre
		dos huecos de la lista (corresponde a la salida normal
		del for)
	*/

	for (p= freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) //condicion para que se coloque en orden por direcciones
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;  /* freed block at start or end of arena */


	/* Comprueba compactacion con hueco posterior */
	if (bp + bp->s.size == p->s.ptr) {  /* join to upper nbr */
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else
		 bp->s.ptr = p->s.ptr;

	/* Comprueba compactacion con hueco anterior */
	if (p + p->s.size == bp) {         /* join to lower nbr */
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else
		p->s.ptr = bp;

	freep = p; /* estrategia next-fit */
}


void *xrealloc(void * ptr, size_t size){
	return NULL;
}
void viewList(){
	Header *p;
	if(freep == NULL){
		printf("List is empty \n");
		return ;
	}
	p = freep;
	printf("-----------------------------------------\n");
	printf("el puntero freep que es %p:\n",freep);
	do{
		printf("Address %p,Unidades: %zu \n",(void *)(p),p->s.size);
		p = p->s.ptr;
	}while(p != freep);

	printf("--------------------------------------------\n\n\n");
}
size_t getUnit(size_t bytes){
	return (bytes+sizeof(Header)-1)/sizeof(Header) + 1;
}
size_t getBytes(size_t units){
	return ((units-1)*sizeof(Header)) +1 - sizeof(Header);
}