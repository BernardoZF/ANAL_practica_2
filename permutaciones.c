/**
 *
 * Descripcion: Implementacion de funciones de generacion de permutaciones
 *
 * Fichero: permutaciones.c
 * Autor: Adrián Sebastián y Bernardo Andrés Zambrano
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */


#include "permutaciones.h"

/*********************************************************/
/* Funcion: aleat_num                                    */
/* Autores: Adrián Sebastián y Bernardo Andrés Zambrano  */
/*                                                       */
/* Rutina que genera un numero aleatorio                 */
/* entre dos numeros dados                               */
/*                                                       */
/* Entrada:                                              */
/* int inf: limite inferior                              */
/* int sup: limite superior                              */
/* Salida:                                               */
/* int: numero aleatorio                                 */
/*********************************************************/
int aleat_num(int inf, int sup)
{
  int rand_num = 0;

  if ( inf > sup || inf < 0 ){
    return ERR;
  }

  rand_num = inf + (int) (((rand()*(sup-inf+1.0)))/(RAND_MAX+1.0));

  return rand_num;

}

/********************************************************/
/* Funcion: genera_perm                                 */
/* Autores: Adrián Sebastián y Bernardo Andrés Zambrano */
/*                                                      */
/* Rutina que genera una permutacion                    */
/* aleatoria                                            */
/*                                                      */
/* Entrada:                                             */
/* int n: Numero de elementos de la                     */
/* permutacion                                          */
/* Salida:                                              */
/* int *: puntero a un array de enteros                 */
/* que contiene a la permutacion                        */
/* o NULL en caso de error                              */
/********************************************************/
int* genera_perm(int N)
{
  int *perm = NULL;
  int i = 0;
  int aleat = 0;

  if ( N <= 0 ){
    return NULL;
  }

  perm = (int*)malloc(N * sizeof(int));
  if( perm == NULL ){
    return NULL;
  }

  for( i = 0; i < N ; i++){
    perm[i] = i + 1;
  }

  for ( i = 0; i < N ; i++){

    aleat = aleat_num(i, N-1);

    swap(i, aleat, perm);

  }

  return perm;
}

/*********************************************************/
/* Funcion: genera_perm                                  */
/* Autores: Adrián Sebastián y Bernardo Andrés Zambrano  */
/*                                                       */
/* Rutina que genera una permutacion                     */
/* aleatoria                                             */
/*                                                       */
/* Entrada:                                              */
/* int n: Numero de elementos de la                      */
/* permutacion                                           */
/* Salida:                                               */
/* int *: puntero a un array de enteros                  */
/* que contiene a la permutacion                         */
/* o NULL en caso de error                               */
/*********************************************************/
void swap ( int num1, int num2, int* perm){
  int aux = 0;

  if( perm == NULL || num1 < 0 || num2 < 0){
    return;
  }

  aux = perm[num1];
  perm[num1] = perm[num2];
  perm[num2] = aux;
}

/***************************************************/
/* Funcion: genera_permutaciones Fecha:            */
/* Autores:                                        */
/*                                                 */
/* Funcion que genera n_perms permutaciones        */
/* aleatorias de tamanio elementos                 */
/*                                                 */
/* Entrada:                                        */
/* int n_perms: Numero de permutaciones            */
/* int N: Numero de elementos de cada              */
/* permutacion                                     */
/* Salida:                                         */
/* int**: Array de punteros a enteros              */
/* que apuntan a cada una de las                   */
/* permutaciones                                   */
/* NULL en caso de error                           */
/***************************************************/
int** genera_permutaciones(int n_perms, int N)
{
  int** perm = NULL;
  int i = 0;

  if ( n_perms <= 0 || N <= 0 ){
    return NULL;
  }

  perm = (int**)malloc(n_perms*sizeof(int*));
  if ( perm == NULL ){
    return NULL;
  }

  for(i=0; i < n_perms; i++){
    perm[i] = genera_perm(N);
    if(perm[i] == NULL){
      return NULL;
    }
  }

  return perm;

}


void libera_perm( int** perm, int n_perms){

  int i = 0;

  if ( perm == NULL || n_perms <= 0){
    return;
  }

  if( perm == NULL || n_perms <= 0){
    return;
  }

  for ( i = 0; i < n_perms; i++ ){
    free(perm[i]);
  }

  free(perm);
}
