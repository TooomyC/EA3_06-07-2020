/**//* 41.544.259-CESPEDES,TomasNicolas-(01-2964) *//**/


/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//* CUALQUIER INCLUDE DE BIBLIOTECA QUE NECESITE, HÁGALO ACÁ   *//**//**/

/**//**//* CUALQUIER INCLUDE DE BIBLIOTECA QUE NECESITE, HÁGALO ACÁ   *//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
#include "funciones.h"
#include <stdlib.h>
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//* ACÁ DEBE DESARROLLAR LAS FUNCIONES Y PRIMITIVAS PEDIDAS    *//**//**/
/**//**//* ADEMÁS DE CUALQUIER OTRA FUNCIÓN QUE SE REQUIERA           *//**//**/
char* strcpy(char *cadena1, const char *cadena2);
int strcmp(const char *cadena1, const char *cadena2);
int redondear(float nro, float cant);
void mayOcurrenciaNodos (tNodo* nodMov, char* clave, int(*comparar)(const void*, const void*));

char* strcpy(char *cadena1, const char *cadena2)
{
    char* ret = cadena1;

    while (*cadena2)
        *cadena1 ++ = *cadena2 ++;

    *cadena1 = *cadena2;

    return (char*)ret;
}

int strcmp(const char *cadena1, const char *cadena2)
{
     while(*cadena1 && (*cadena1 == *cadena2))
     {
        cadena1++;
        cadena2++;
     }

    return *(char*)cadena1 - *(char*)cadena2;
}

int redondear(float nro, float cant)
{
    int x = nro / cant; ///X representa el cociente entero de la division. ///cant es la cantidad de materias.
    float y = nro / cant; ///Y representa el cociente decimal de la division.
    float res = x - y; ///Utilizo la resta para guardar el resultado de la misma, y así saber como redondear.

    if(res <= 0.5) ///En base a esta comparacion, me permite saber cómo redondear el resultado.
        return x; ///Se redondea de 0.5 hacia abajo del resultado.

    return x + 1; ///Se redondea de 0.5 hacia arriba del resultado.
}

void mayOcurrenciaNodos (tNodo* nodMov, char* clave, int(*comparar)(const void*, const void*))
{
    int mayOcurrencias = 0, ///Cuenta cantidad de veces el de mayor ocurrencia.
        contAparicion = 0; ///Contador de apariciones individual por clave.

    tNodo* reset = nodMov; ///Este Nodo sirve para volver al inicio de la lista.
    char cadComparacion[11]; ///En esta cadena voy a guardar las claves que estoy contando sus apariciones.

    while (nodMov->sig)
    {
        strcpy(cadComparacion, nodMov->info); ///Tengo la clave del primer nodo.
        while (nodMov)
        {
            if (!comparar(cadComparacion, nodMov->info)) ///Pregunto si hubo coincidencia.
               contAparicion ++; ///Incremento el contador de apariciones, si hubo.

            nodMov = nodMov->sig; ///Hago avanzar el puntero al siguiente.
        }

        if (contAparicion > mayOcurrencias)
        {
            mayOcurrencias = contAparicion;
            strcpy(clave, cadComparacion); ///Guardo en "clave" la cadena que apareció mas veces, hasta ahora.
        }

        nodMov = reset = reset -> sig; ///Avanzo el "Reset" al siguiente, e igualo al "Nodo movimiento" a la siguiente sub-lista.
        contAparicion = 0; ///Reseteo el contador de apariciones.
    }
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//* FUNCIONES Y PRIMITIVAS A DESARROLLAR                               *//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//* para la información                                                *//**/

void mostrarFinal_MIO(const void *d, FILE *fp)
{
    tFinal *dAux = (tFinal *) d;
    if(dAux == NULL)
        fprintf(fp,"\nD. N. I.  Apellido(s), Nombre(s)\t  CodM Cal\n");

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
    fprintf(fp, "  --- Rindio %d final(es) con un promedio de: %d\n", cantCalif, redondear(aux->calif, cantCalif));
}

/**//* para el TDA LISTA                                                  *//**/

int  mostrarDeIzqADer_MIO(const tLista *p,
                          void(*mostrar)(const void *, FILE *), FILE *fp)
{
    tNodo *act = *p;
    int cant = 0;
    if(act)
    {
        mostrar(NULL, fp);

        while(act->ant)
            act = act->ant;

        while(act)
        {
            mostrar(act->info, fp);
            act = act->sig;
            cant ++;
        }
    }
    return cant;
}


void ordenarLista_MIO(tLista *p, int (*comparar)(const void *, const void *))
{
    if (!*p)
        return;

    tNodo* nodMovim = *p; ///Nodo que utilizo para recorrer la lista desordenada.
    char cadAux [11]; ///Esta cadena la voy a usar a la hora de comparar.
    while (nodMovim->ant) ///Voy al principio de la lista.
        nodMovim = nodMovim->ant;

    tNodo* nodPrimero = nodMovim; ///En la lista desordenada, nodPrimero es el nodo que apuntará al primer nodo de la misma.
    tNodo* nodOrden = NULL; ///El Nodo Ordenado será nulo, para que sea el anterior del primer ordenado.

    while (nodPrimero->sig)
    {
        mayOcurrenciaNodos(nodPrimero, cadAux, comparar);

        while(nodMovim)
        {
            if( !comparar(cadAux, nodMovim->info) ){
                if(nodMovim == nodPrimero) ///Este if sirve en caso de que el "Nodo movimiento" esté en la posición del primero y este sea uno a desvincular.
                    nodPrimero = nodPrimero->sig; ///Por esto que dije, muevo el puntero Primero.

                /** Desvinculación de Nodos **/
                tNodo* ant = nodMovim->ant; ///Creo un Nodo Anterior.
                tNodo* sig = nodMovim->sig; ///Utilizo el Nodo Siguiente como marca.

                if (ant)
                    ant->sig = sig;

                if (sig)
                {
                    sig->ant = ant;
                    *p = sig;
                }
                else
                    *p = ant;

                /** Desvinculación de Nodos **/

                nodMovim->ant = nodOrden; ///El anterior del nodo ("Nodo Movimiento") que voy a desenganchar, será lo que esté apuntando el "Nodo Ordenado".

                if(nodOrden) ///En caso de que el puntero no sea nulo, tengo que hacerle apuntar su sig, el nodo que le engancho.
                    nodOrden->sig = nodMovim;

                nodOrden = nodMovim;
                nodMovim = sig; ///Le asigno siguiente al nodo movimiento para poder seguir buscando desde acá, y no tener que recorrer todo lo que ya recorrí.
                nodOrden->sig = nodPrimero; ///Engancho el último de la lista ordenada, con el primero de la lista desordenada.
                nodPrimero->ant = nodOrden;
            }
            else
                nodMovim = nodMovim->sig; ///Avanzo el Nodo Movimiento.
        }

        nodMovim = nodPrimero; ///Muevo al principio de la lista ordenada, el "Nodo Movimiento" para empezar de nuevo.
    }
}


int  vaciarMostrarDetalleYProm_MIO(tLista *p, FILE *fp,
                                   int (*comparar)(const void *, const void *),
                                   int (*acumular)(void **, unsigned *,
                                                   const void *, unsigned),
                                   void (*mostrar)(const void *, FILE *),
                                   void (*mostrar2)(const void *, int, FILE *)) ///MODIFICAR COMENTARIOS
{
    if (!*p) ///Valido que la lista no esté vacía.
        return 0;

    int total = 0, contMat; ///Contador de materias, por alumno.
    tNodo* nodMov = *p; ///Igualo el puntero de la lista (ahora que lo tengo al principio de la misma), al "Nodo Movimiento".

    while (nodMov->ant) ///Me muevo al principio de la lista.
        nodMov = nodMov->ant;

    while (nodMov)
    {
        tFinal alumAux;
        tFinal* pAlumAux = &alumAux;


        alumAux.calif = 0; ///Cómo debo acumular las calificaciones, la inicializo.
        strcpy(alumAux.dni, nodMov->info); ///Copio el dni en la estructura "auxiliar de alumno".

        mostrar(NULL, fp);
        contMat = 0; ///Reseteo la cantidad de materias por alumno, ya que la voy a utilizar para el promedio.


        do{ ///El Do es porque ya voy a tener un nodo apuntado por el puntero de la lista.

            acumular( (void*)&pAlumAux, NULL, nodMov->info, (unsigned)NULL);
            mostrar(nodMov->info, fp);

            tNodo* nodAux = nodMov->sig;

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

