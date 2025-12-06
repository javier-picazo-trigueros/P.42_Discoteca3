/*****************************************
 * Nombre: Seleccion
 * Argumentos: LIBRO *Ficha:       Array de las fichas de libros
 *             int campo:          Campo por el que hacer la ordenación (Título o Autor)
 * Descripción: Ordena el array de fichas de libros en un doble puntero a las fichas de Libros,
 *              por lo que el movimient de datos se reduce al cambio de punteros.
 *              Se usa el algoritmo de ordenación de Selección.
 * Reglas de uso: 
 * Código de Retorno: LIBRO **: Doble puntero ordenado por el criterio pedido a las fichas de libros.
 * Programador: JMSM (Sept-24)
 *****************************************/

#include "../Discoteca.h"

DISCO **Seleccion(DISCO *Ficha, int Campo)
{
    DISCO **Orden;
    struct timeval inicio, fin;
    
    int i, j, minimo;
    DISCO *temp;
    int comparacion;

    gettimeofday(&inicio,NULL);
    Orden=InitOrden(Ficha);

    // Algoritmo de Selección
    for (i = 0; i < Estadisticas.NumeroFichas - 1; i++) {
        minimo = i;
        
        for (j = i + 1; j < Estadisticas.NumeroFichas; j++) {
            if (Campo == ORDEN_POR_TITULO) {
                comparacion = strcmp(Orden[j]->Obra, Orden[minimo]->Obra);
            } 
            else if (Campo == ORDEN_POR_AUTOR) {
                comparacion = strcmp(Orden[j]->ApellAutor, Orden[minimo]->ApellAutor);
                if (comparacion == 0) {
                    comparacion = strcmp(Orden[j]->NomAutor, Orden[minimo]->NomAutor);
                }
            }
            
            if (comparacion < 0) {
                minimo = j;
            }
        }
        
        if (minimo != i) {
            temp = Orden[i];
            Orden[i] = Orden[minimo];
            Orden[minimo] = temp;
        }
    }

    gettimeofday(&fin,NULL);
    Estadisticas.TiempoSeleccion=DifTiempo(inicio,fin);

    return(Orden);
}