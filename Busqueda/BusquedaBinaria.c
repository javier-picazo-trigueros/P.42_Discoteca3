/*****************************************
 * Nombre: BusquedaBinaria
 * Argumentos: LIBRO *Fichas:       Array de las fichas de libros
 * Descripción: Después de capturar los apellidos de un autor, busca las fichas de libros de ese autor,
 *              por el método de búsqueda binaria
 *              La comparación de los apellidos se hace en mayúsculas. 
 *              Después se muestran los resultados en una pantalla de scroll.
 * Reglas de uso: 
 * Código de Retorno: N/A
 * Programador: JMSM (Sept-24)
 *****************************************/

#include "Busqueda.h"

void BusquedaBinaria(DISCO *Fichas)
{
    char *Autor;
    DISCO **Resultado=NULL;
    DISCO **Orden=NULL;
    int Hallados=0;
    struct timeval inicio, fin;
    bool Encontrado;
    
    int izquierda, derecha, medio;
    int comparacion;
    int i, j;
    char CopiaAutor[256];
    int n;

    if ((Autor=LeerAutor()) == NULL)
        return;

    gettimeofday(&inicio,NULL);

    Orden=Quicksort(Fichas, ORDEN_POR_AUTOR);
    
    // Asignar memoria para los resultados
    Resultado=(DISCO **)malloc(sizeof(DISCO *)*10);
    int DimResultado=10;
    Encontrado=false;
    
    // Búsqueda binaria del primer autor que coincide
    izquierda=0;
    derecha=Estadisticas.NumeroFichas-1;
    n=strlen(Autor);
    
    while (izquierda <= derecha) {
        medio=(izquierda+derecha)/2;
        
        // Convertir apellido a mayúsculas para comparar
        for (j=0; Orden[medio]->ApellAutor[j] != 0; j++) {
            CopiaAutor[j]=Orden[medio]->ApellAutor[j];
            if (CopiaAutor[j] < 'a')
                CopiaAutor[j]+=' ';
        }
        CopiaAutor[j]=0;
        
        comparacion=strncmp(CopiaAutor, Autor, n);
        
        if (comparacion == 0) {
            Encontrado=true;
            break;
        }
        else if (comparacion < 0) {
            izquierda=medio+1;
        }
        else {
            derecha=medio-1;
        }
    }
    
    // Si se encontró, recopilar todos los autores que coinciden
    if (Encontrado) {
        // Buscar hacia atrás desde el medio encontrado
        i=medio;
        while (i >= 0) {
            for (j=0; Orden[i]->ApellAutor[j] != 0; j++) {
                CopiaAutor[j]=Orden[i]->ApellAutor[j];
                if (CopiaAutor[j] < 'a')
                    CopiaAutor[j]+=' ';
            }
            CopiaAutor[j]=0;
            
            if (strncmp(CopiaAutor, Autor, n) == 0) {
                if (DimResultado == Hallados+1) {
                    DimResultado+=10;
                    Resultado=realloc(Resultado, sizeof(DISCO *)*DimResultado);
                }
                Resultado[Hallados]=Orden[i];
                Hallados++;
                i--;
            }
            else {
                break;
            }
        }
        
        // Buscar hacia adelante desde el medio encontrado
        i=medio+1;
        while (i < Estadisticas.NumeroFichas) {
            for (j=0; Orden[i]->ApellAutor[j] != 0; j++) {
                CopiaAutor[j]=Orden[i]->ApellAutor[j];
                if (CopiaAutor[j] < 'a')
                    CopiaAutor[j]+=' ';
            }
            CopiaAutor[j]=0;
            
            if (strncmp(CopiaAutor, Autor, n) == 0) {
                if (DimResultado == Hallados+1) {
                    DimResultado+=10;
                    Resultado=realloc(Resultado, sizeof(DISCO *)*DimResultado);
                }
                Resultado[Hallados]=Orden[i];
                Hallados++;
                i++;
            }
            else {
                break;
            }
        }
    }

    free(Orden);
    
    gettimeofday(&fin,NULL);
    Estadisticas.TiempoBusquedaBinaria=DifTiempo(inicio,fin);

    if (Encontrado == false) {
        VentanaError("No hay autores que cumplan el criterio");
        return;
    }
    
    Listado1(Resultado,Hallados,Fichas);
    free(Resultado);
    return;
    
}