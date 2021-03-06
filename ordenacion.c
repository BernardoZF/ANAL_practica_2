/**
 *
 * Descripcion: Implementacion de funciones de ordenacion
 *
 * Fichero: ordenacion.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */

#include <stdlib.h>
#include <string.h>
#include "ordenacion.h"

/*********************************************************/
/* Funcion: SelectSort                                   */
/* Autores: Adrián Sebastián y Bernardo Andrés Zambrano  */
/*                                                       */
/* Rutina que ordena una tabla de menor                  */
/* a mayor                                               */
/*                                                       */
/* Entrada:                                              */
/* int* tabla: tabla a ordenar                           */
/* int ip: primer elemento de la tabla                   */
/* int iu: ultimo elemento de la tabla                   */
/* Salida:                                               */
/* int: numero de veces que se ejecuta la operacion      */
/* basica                                                */
/*********************************************************/
int SelectSort(int* tabla, int ip, int iu)
{
  int i = 0 , j = 0;
  int min = 0 ;
  int num_ob = 0;

  if ( tabla == NULL || ip <= 0 || ip > iu || iu <= 0){
    return -1;
  }

  for( i = ip; i < iu; i++){
    min = i;
    for(j = i+1; j<=iu; j++){
    num_ob++;
    if(tabla[j] < tabla[min]){
      min = j;
    }
  }
    swap(i, min, tabla);
  }

  return num_ob;
}


/*********************************************************/
/* Funcion: SelectSort                                   */
/* Autores: Adrián Sebastián y Bernardo Andrés Zambrano  */
/*                                                       */
/* Rutina que ordena una tabla de mayor                  */
/* a menor                                               */
/*                                                       */
/* Entrada:                                              */
/* int* tabla: tabla a ordenar                           */
/* int ip: primer elemento de la tabla                   */
/* int iu: ultimo elemento de la tabla                   */
/* Salida:                                               */
/* int: numero de veces que se ejecuta la operacion      */
/* basica                                                */
/*********************************************************/
int SelectSortInv(int* tabla, int ip, int iu)
{
  int i = 0, j = 0;
  int max = 0;
  int num_ob = 0;

  if ( tabla == NULL || ip <= 0 || ip > iu || iu <= 0){
    return -1;
  }

  for( i = ip; i < iu; i++){
    max = i;
    for(j = i+1; j<=iu; j++){
    num_ob++;
    if(tabla[j] < tabla[max]){
      max = j;
    }
  }
    swap(i, max, tabla);
  }

  return num_ob;
}



int mergesort(int* tabla, int ip, int iu){

  int im = 0;
  int num_ob = 0;
  int numob_Left = 0;
  int numob_Right = 0;

  if( tabla == NULL || ip < 0 || ip > iu){
    return ERR;
  }

  if ( ip == iu ){
    return OK;
  }
  else{
    im = (iu + ip) / 2;
    numob_Right = mergesort(tabla, ip, im);
    if ( numob_Right == ERR){
      return ERR;
    }
    numob_Left = mergesort(tabla, im+1, iu);
    if ( numob_Left == ERR){
      return ERR;
    }
    num_ob = merge(tabla, ip, iu, im);
    if ( num_ob == ERR){
      return ERR;
    }
  }
  num_ob = num_ob + numob_Right + numob_Left;


  return num_ob;
}


int merge(int* tabla, int ip, int iu, int imedio){

  int i, j, k;
  int num_ob = 0;
  int *t_aux;


  t_aux=malloc((iu-ip+1)*sizeof(int));
  if ( t_aux == NULL ){
    return ERR;
  }

  for (i = ip, j = imedio+1, k = 0; i <= imedio && j <=iu; k++ ){
    num_ob++;
    if ( tabla[i] < tabla[j]){
      t_aux[k] = tabla[i];
      i++;
    } else{
      t_aux[k] = tabla[j];
      j++;
    }
  }

  if(j>iu) {
    while ( i<=imedio){
       t_aux[k] = tabla[i];
       i++;
       k++;
    }
  } else if (i>imedio) {
    while ( j <= iu){
      t_aux[k] = tabla[j];
      j++;
      k++;
    }
  }

  memcpy(tabla+ip,t_aux,(iu-ip+1)*sizeof(int));
  free(t_aux);

  return num_ob;

}


int quicksort(int* tabla, int ip, int iu)
{

	int *medio=NULL;
	int ob=0;

	if (!tabla || ip<0 || iu<0){	
		return ERR;
		}

	medio=(int *)malloc(sizeof(int));
	if(!medio)
		return ERR;


	if (iu<ip){
		return ERR;
		}
	if (ip==iu){
		free(medio);
		return 0;
		}
	else  {
		ob+=partir(tabla,ip,iu,medio);

		if( ip < (*medio-1))
			quicksort(tabla,ip,*medio-1);
		if((*medio+1)< iu)
			quicksort(tabla,*medio+1,iu);

		}

	free(medio);
	

	return ob;
}



int partir(int* tabla, int ip, int iu, int *pos)
{
	int k;
	int i;
	int ob;
	int j;

	if(!tabla || ip < 0 || iu < 0 || !pos)
			return ERR;

	ob=medio(tabla,ip,iu, pos);

	k=tabla[*pos];

	swap(*pos, ip, tabla);


	for(i=(ip+1), ob=0, j=*pos; i<=iu; i++){
		ob++;
		if (tabla[i]<k){
			j++;
			swap(i, j, tabla);
 		}
	}
	swap(ip,j,tabla);

	*pos=j;	

	return ob;
}


int medio(int *tabla, int ip, int iu,int *pos)
{

	if (!tabla || ip < 0 || iu < 0){
		return ERR;
		}

	*pos=ip;

	return 0;
}

int quicksort_src(int* tabla, int ip, int iu)
{

	int ob=0;
	int im;

	if (!tabla || ip<0 || iu < ip){	
		return ERR;
		}

	if (ip==iu){
		return 0;
		}
	else  {
		while (ip<iu){
			ob+=partir(tabla,ip,iu,&im);
			ob+=quicksort(tabla,ip,im);
			ip=im+1;
			}
		}


	return ob;
}

