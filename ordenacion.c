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

  if( tabla == NULL || ip < 0 || ip > iu){
    return ERR;
  }

  if ( ip == iu ){
    return 0;
  }
  else{
    im = (iu + ip) / 2;
    mergesort(tabla, ip, im);
    mergesort(tabla, im+1, iu);
    return merge(tabla, ip, iu, im);
  }

}


/*  CDE */
int merge(int* tabla, int ip, int iu, int imedio){

  int i, j, k;
  int *t_aux;


  t_aux=malloc((iu-ip+1)*sizeof(int));

  for (i = ip, j = imedio+1, k = 0; i <= imedio && j <=iu; k++ ){
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


  return 1;

}
