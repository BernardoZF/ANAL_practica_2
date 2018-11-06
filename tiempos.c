/**
 *
 * Descripcion: Implementacion de funciones de tiempo
 *
 * Fichero: tiempos.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */

#define _POSIX_C_SOURCE 199309L

#include "tiempos.h"
#include "ordenacion.h"
#include <time.h>
#include <stdlib.h>


#define CONVERSOR 1000000000L

/***************************************************/
/* Funcion: tiempo_medio_ordenacion Fecha:         */
/*                                                 */
/* Vuestra documentacion (formato igual            */
/* que en el primer apartado):                     */
/***************************************************/
short tiempo_medio_ordenacion(pfunc_ordena metodo, int n_perms, int N, PTIEMPO ptiempo)
{

  int** tabla = NULL;
  double min = INT_MAX;
  double max = INT_MIN;
  double num_ob = 0.0;
  double total_ob = 0.0;
  double time_sum = 0.0;
  int i = 0;

  struct timespec begin, end;

  if ( N <= 0 || n_perms <= 0 || metodo == NULL || ptiempo == NULL){
    return ERR;
  }

  tabla = genera_permutaciones(n_perms, N);
  if ( tabla == NULL ){
    return ERR;
  }


  for( i = 0; i < n_perms; i++){
    num_ob = 0;

    clock_gettime(CLOCK_REALTIME, &begin);


    num_ob = (long)metodo(tabla[i], 0, N - 1);
    if ( num_ob == ERR ){
      libera_perm(tabla, n_perms);
      return ERR;
    }

    if( num_ob > max ){
      max = num_ob;
    }

    if( num_ob < min ){
      min = num_ob;
    }

    clock_gettime(CLOCK_REALTIME, &end);

    time_sum += (end.tv_nsec -begin.tv_nsec)/(CONVERSOR *1.0) + (end.tv_sec - begin.tv_sec) ;


    total_ob += num_ob;
  }



    ptiempo->N = N;
    ptiempo->min_ob = min;
    ptiempo->max_ob = max;
    ptiempo->medio_ob = (total_ob / (n_perms * 1.0));
    ptiempo->tiempo = (time_sum / (n_perms * 1.0));

    libera_perm( tabla, n_perms);

    return OK;
}

/***************************************************/
/* Funcion: genera_tiempos_ordenacion Fecha:       */
/*                                                 */
/* Vuestra documentacion                           */
/***************************************************/
short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero, int num_min, int num_max,
                                int incr, int n_perms)
{
  int i =0,j = 0;
  int tamanio = 0;
  int flag = ERR;

  PTIEMPO ptime = NULL;

  if(!metodo || !fichero || num_max < 0 || num_min < 0 || incr <=0 ||
      n_perms <= 0 || num_max < num_min){
        return ERR;
      }

  tamanio = ((num_max - num_min)/ incr) + 1;

  ptime = (PTIEMPO)malloc(tamanio * sizeof(TIEMPO));
  if (!ptime){
    return ERR;
  }

  for ( i = 0, j = num_min; j <= num_max && i <tamanio; i++, j += incr){

    flag = tiempo_medio_ordenacion(metodo, n_perms, j, &ptime[i]);
    if ( flag == ERR ){
      free(ptime);
      return ERR;
    }

    printf("(N = %d) %.2f %%\r",j, ((i*100.0)/tamanio)); /* Porcentaje */
    fflush(stdout);
  }


  flag = guarda_tabla_tiempos(fichero, ptime, tamanio);
  if(flag == ERR){
    free(ptime);
    return ERR;
  }

  free(ptime);

  return OK;
}

/***************************************************/
/* Funcion: guarda_tabla_tiempos Fecha:            */
/*                                                 */
/* Vuestra documentacion (formato igual            */
/* que en el primer apartado):                     */
/***************************************************/
short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int n_tiempos)
{

  FILE *f = NULL;
  int i = 0;

  if( fichero == NULL || tiempo == NULL || n_tiempos <= 0){
    return ERR;
  }

  f = fopen(fichero, "w");
  if ( f == NULL ){
    return ERR;
  }

  fprintf(f, "N tiempo medio_ob min_ob max_ob\n");

  for ( i = 0; i < n_tiempos; i++){
    fprintf(f, "%d %f %f %d %d \n",tiempo[i].N, tiempo[i].tiempo,
      tiempo[i].medio_ob, tiempo[i].min_ob, tiempo[i].max_ob);
  }

  fclose(f);

  return OK;
}
