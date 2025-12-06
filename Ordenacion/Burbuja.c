/*****************************************
 * Nombre: Burbuja
 * Argumentos: LIBRO *Ficha:       Array de las fichas de libros
 *             int campo:          Campo por el que hacer la ordenación (Título o Autor)
 * Descripción: Ordena el array de fichas de libros en un doble puntero a las fichas de Libros,
 *              por lo que el movimient de datos se reduce al cambio de punteros.
 *              Se usa el algoritmo de ordenación de la burbuja.
 * Reglas de uso: 
 * Código de Retorno: LIBRO **: Doble puntero ordenado por el criterio pedido a las fichas de libros.
 * Programador: JMSM (Sept-24)
 *****************************************/

#include "../Discoteca.h"

DISCO **Burbuja(DISCO *Ficha,int Campo)
{
    DISCO **Orden;
    struct timeval inicio, fin;
    int i, j;
    DISCO *temp;
    int intercambio;
    int comparacion;

    gettimeofday(&inicio,NULL);
    Orden=InitOrden(Ficha);

    // Algoritmo de ordenación de burbuja
    for (i = 0; i < Estadisticas.NumeroFichas - 1; i++) {
        intercambio = 0;
        
        for (j = 0; j < Estadisticas.NumeroFichas - i - 1; j++) {
            if (Campo == ORDEN_POR_TITULO) {
                comparacion = strcmp(Orden[j]->Obra, Orden[j + 1]->Obra);
            } 
            else if (Campo == ORDEN_POR_AUTOR) {
                comparacion = strcmp(Orden[j]->ApellAutor, Orden[j + 1]->ApellAutor);
                if (comparacion == 0) {
                    comparacion = strcmp(Orden[j]->NomAutor, Orden[j + 1]->NomAutor);
                }
            }
            
            if (comparacion > 0) {
                temp = Orden[j];
                Orden[j] = Orden[j + 1];
                Orden[j + 1] = temp;
                intercambio = 1;
            }
        }
        
        if (intercambio == 0) {
            break;
        }
    }
    
    gettimeofday(&fin,NULL);
    Estadisticas.TiempoBurbuja=DifTiempo(inicio,fin);

    return(Orden);
}