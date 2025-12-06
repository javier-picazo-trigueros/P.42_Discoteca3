/*****************************************
 * Nombre: Inserción
 * Argumentos: LIBRO *Ficha:       Array de las fichas de libros
 *             int campo:          Campo por el que hacer la ordenación (Título o Autor)
 * Descripción: Ordena el array de fichas de libros en un doble puntero a las fichas de Libros,
 *              por lo que el movimient de datos se reduce al cambio de punteros.
 *              Se usa el algoritmo de ordenación de Inserción.
 * Reglas de uso: 
 * Código de Retorno: LIBRO **: Doble puntero ordenado por el criterio pedido a las fichas de libros.
 * Programador: JMSM (Sept-24)
 *****************************************/

#include "../Discoteca.h"

DISCO **Insercion(DISCO *Ficha,int Campo)
{
    DISCO **Orden;
    struct timeval inicio, fin;
    
    int i, j;
    DISCO *elementoActual;
    int comparacion;

    gettimeofday(&inicio,NULL);
    Orden=InitOrden(Ficha);

    // Algoritmo de Inserción
    for (i = 1; i < Estadisticas.NumeroFichas; i++) {
        elementoActual = Orden[i];
        j = i - 1;
        
        while (j >= 0) {
            if (Campo == ORDEN_POR_TITULO) {
                comparacion = strcmp(Orden[j]->Obra, elementoActual->Obra);
            } 
            else if (Campo == ORDEN_POR_AUTOR) {
                comparacion = strcmp(Orden[j]->ApellAutor, elementoActual->ApellAutor);
                if (comparacion == 0) {
                    comparacion = strcmp(Orden[j]->NomAutor, elementoActual->NomAutor);
                }
            }
            
            if (comparacion > 0) {
                Orden[j + 1] = Orden[j];
                j--;
            } 
            else {
                break;
            }
        }
        
        Orden[j + 1] = elementoActual;
    }
    
    gettimeofday(&fin,NULL);
    Estadisticas.TiempoInsercion=DifTiempo(inicio,fin);

    return(Orden);
}