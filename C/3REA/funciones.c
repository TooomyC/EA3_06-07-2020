/**//* 41.544.259-CESPEDES,TomasNicolas-(01-2964) *//**/


/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//* CUALQUIER INCLUDE DE BIBLIOTECA QUE NECESITE, HÁGALO ACÁ   *//**//**/

#include <string.h>
#include <stdlib.h>

/**//**//* CUALQUIER INCLUDE DE BIBLIOTECA QUE NECESITE, HÁGALO ACÁ   *//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
#include "funciones.h"
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//* ACÁ DEBE DESARROLLAR LAS FUNCIONES Y PRIMITIVAS PEDIDAS    *//**//**/
/**//**//* ADEMÁS DE CUALQUIER OTRA FUNCIÓN QUE SE REQUIERA           *//**//**/

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//* FUNCIONES Y PRIMITIVAS A DESARROLLAR                               *//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//* para la información                                                *//**/

void mostrarFinal_MIO(const void *d, FILE *fp)
{
    tFinal *dAux = (tFinal *) d;
    if(dAux == NULL)
        fprintf(fp," D. N. I.  Apellido(s), Nombre(s)\t  CodM Cal\n");

    else
       fprintf(fp,"%*s %-*s %4d %2d\n", (int)sizeof(dAux->dni) - 1, dAux->dni, (int)sizeof(dAux->apYNom) - 1, dAux->apYNom, dAux->codMat, dAux->calif);

}


int  compararFinal_MIO(const void *d1, const void *d2)
{
    return strcmp(d1, d2); ///Comparo las dos cadenas para ver si son iguales.
}


int  acumularCalif_MIO(void **dest, unsigned *tamDest,
                       const void *orig, unsigned tamOrig)
{
    tFinal **destAux= (tFinal**) dest;
    tFinal *oriAux = (tFinal*) orig;

    (*destAux)->calif += oriAux->calif;

    return 1;
}


void mostrarProm_MIO(const void *d2, int cantCalif, FILE *fp)
{
    tFinal *aux = (tFinal*) d2;
    fprintf(fp, "  --- Rindio  %d final(es) con un promedio de: %2.0f\n\n", cantCalif, (float)aux->calif/cantCalif);
}


/**//* para el TDA LISTA                                                  *//**/

int  mostrarDeIzqADer_MIO(const tLista *p,
                          void(*mostrar)(const void *, FILE *), FILE *fp) ///MUESTRA DE DERECHA A IZQUIERDA.
{
    tNodo *act = *p;
    int cant = 0;
    if(act)
    {
        mostrar(NULL, fp);

        while(act->sig)
            act = act->sig;

        while(act)
        {
            mostrar(act->info, fp);
            act = act->ant;
            cant ++;
        }
    }
    return cant;
}


void ordenarLista_MIO(tLista *p, int (*comparar)(const void *, const void *))
{
     if (!*p)
        return;

    tNodo* nodMov = *p; ///Nodo que utilizo para recorrer la lista desordenada.
    while (nodMov->sig) ///Voy al final de la lista.
        nodMov = nodMov->sig;

    tNodo* nodUlt = nodMov; ///En la lista desordenada, "nodUlt" es el nodo que apuntará al último nodo de la misma.
    tNodo* nodOrdenado = NULL; ///El Nodo Ordenado (de la lista ordenada) será nulo, porque el siguiente al primer nodo, apuntará a NULL.
    tNodo* nodPointer = nodMov; ///"nodPointer" será el nodo que apuntará al anterior del nodo en movimiento.

    while (nodUlt->ant)
    {
        /**Busco nodo con menor ocurrencia**/

        int menorApariciones = 0,
        contadorApariciones = 0;

        tNodo* nodReset = nodMov; ///Nodo con el que vuelvo al final de la lista.
        tNodo* aux = nodUlt; ///"aux" tiene que ser siempre igual al ultimo nodo desordenado de la lista.

        while (nodReset)
        {
            tNodo* nodComp = nodReset; ///Nodo que voy a utilizar para apuntar a la info a comparar.
            while (aux)
            {
                if (!comparar(nodComp->info, aux->info)) ///Si hubo coincidencia.
                    contadorApariciones ++; ///Incremento el contador, si hubo.

                aux = aux->ant; ///Hago avanzar el puntero al anterior, ya que se recorre del último al primero.
            }

            if(!menorApariciones || contadorApariciones<menorApariciones) ///En la primera pasada será 2 < 0.
            {
                menorApariciones = contadorApariciones;
                nodPointer = nodComp;
            }

            if (nodReset->ant)
            {
                nodReset = nodReset->ant; ///Avanzo el "reset" al siguiente a la derecha y reseteo el "nodMov".
                contadorApariciones = 0; ///Reseteo el contador de apariciones.
                aux = nodUlt;
            }
            else
                nodReset = NULL;
        }

        /**Acá finaliza la búsqueda del nodo con menor ocurrencia**/

        while(nodMov && nodUlt->ant)
        {
            if(!comparar(nodPointer->info, nodMov->info)) ///En caso de que me dé igual.
            {
                if(nodMov == nodUlt) ///En caso de que esté parado en el último y este sea un nodo a desenganchar, muevo el "puntero último" al anterior.
                    nodUlt = nodUlt->ant; ///El último lugar lo hace NULL.

                /**Desvinculación de Nodo**/

                tNodo* ant = nodMov->ant,* sig = nodMov->sig; ///Uso Nodo "Ant" como marca, para seguir.
                if (sig)
                    sig->ant = ant;

                if (ant)
                {
                    ant->sig = sig;
                    *p = ant;
                }
                else
                    *p = sig;

                /**Desvinculación de Nodo**/

                nodMov->sig = nodOrdenado; ///El anterior del nodo ("Nodo Movimiento") que voy a desenganchar, será lo que esté apuntando el "Nodo Ordenado".
                if(nodOrdenado) ///En caso de que el puntero no sea nulo, tengo que hacerle apuntar su ant al nodo que le engancho.
                    nodOrdenado->ant = nodMov;

                nodOrdenado = nodMov;
                nodMov = ant; ///Le asigno "anterior" al nodo movimiento para poder seguir buscando desde acá y no tener que recorrer lo que ya recorrí.
                nodOrdenado->ant = nodUlt; ///Engancho el primero de la lista ordenada...**

                if(nodUlt->ant)
                    nodUlt->sig = nodOrdenado; ///**... con el ultimo de la lista desordenada.
            }
            else
                nodMov = nodMov->ant; ///Avanzo el "Nodo movimiento".
        }
        nodPointer = nodMov = nodUlt;
    }
}

int  vaciarMostrarDetalleYProm_MIO(tLista *p, FILE *fp,
                                   int (*comparar)(const void *, const void *),
                                   int (*acumular)(void **, unsigned *,
                                                   const void *, unsigned),
                                   void (*mostrar)(const void *, FILE *),
                                   void (*mostrar2)(const void *, int, FILE *)) ///VACIA LISTA DE DERECHA A IZQUIERDA.
{
    if (!*p) ///Valido que la lista no esté vacía.
        return 0;

    int total = 0, contMat; ///Contador de materias, por alumno.
    tNodo* nodMov = *p; ///Igualo el puntero de la lista (ahora está al principio de la misma) al "Nodo Movimiento".

    while (nodMov->sig) ///Me muevo al final de la lista.
        nodMov = nodMov->sig;

    while (nodMov)
    {
        tFinal alumAux;
        tFinal* pAlumAux = &alumAux;


        alumAux.calif = 0; ///Cómo debo acumular las calificaciones, la inicializo.
        strcpy(alumAux.dni, nodMov->info); ///Copio el dni en la estructura "auxiliar de alumno".

        mostrar(NULL, fp); ///Muestro el encabezado.
        contMat = 0; ///Reseteo la cantidad de materias por alumno, ya que la voy a utilizar para el promedio.


        do{ ///El Do es porque ya voy a tener un nodo apuntado por el puntero de la lista.

            acumular( (void*)&pAlumAux, NULL, nodMov->info, (unsigned)NULL);
            mostrar(nodMov->info, fp);

            tNodo* nodAux = nodMov->ant;

            free(nodMov->info);
            free(nodMov);

            nodMov = nodAux;

            contMat++;
            total++;

        }
        while (nodMov && !comparar(alumAux.dni, nodMov->info)); ///Valido que siga habiendo un nodo y que sea del mismo DNI para seguir acumulando las calificaciones.

        mostrar2(&alumAux, contMat, fp);
    }

    *p = NULL; ///La lista está vacía, entonces seteo el puntero de la lista a NULL.

    return total;
}


/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

