// Este el main del programa. Invoca al analizador sintáctico, que sigue un patrón
// productor consumidor con el analizador léxico.

#include <stdio.h>
#include "analizador_lexico.h"
#include "analizador_sintactico.h"
#include "errores/errores.h"
#include "TS.h"

#include <string.h>
#include <stdlib.h>

// Definición de constante de longitud máxima del nombre de fichero:
#define MAX_LEN_FILENAME 64;

// Se le tiene que poder mandar un documento como argumento
int main(int argc, char* argv[]){

    //Comprobaciones argumentos:
    if (argc != 2){
        fprintf(stderr, "Uso %s <argumento>\n", argv[0]);
        return EXIT_FAILURE;
    }

    //Abrimos el fichero:
    FILE* codigo_fuente = fopen(argv[1], "r");
    if (codigo_fuente == NULL){
        perror("Error al abrir el archivo.");
        return EXIT_FAILURE;
    }
    printf("\nArchivo abierto correctamente.\n");

    // Inicializamos la tabla de símbolos:
    TablaSimbolos ts;
    printf("\nInicializando Tabla de Símbolos...\n");
    inicializarTS(&ts);
    
    printf("\n\nImprimiendo Tabla de Símbolos...\n");
    imprimirEstructuraDatos(&(ts.tabla));

    // Inicializar analizador léxico y estructuras de datos (constructor). Le pasamos el documento
    inicializar_analizador_lexico(codigo_fuente, &ts); //GESTIÓN DE ERRORES?

    // Iniciar definitivamente el analizador sintáctico -> llamara al léxico
    iniciar_analizador_sintactico(); //GESTIÓN DE ERRORES? No necesita argumento
    
    // Una vez terminado el análisis sintáctico, volvemos a imprimir la tabla de símbolos:
    imprimirEstructuraDatos(&(ts.tabla));

    // Liberamos recursos
    //funciones para liberar cosas - VALGRIND para depurar
    fclose(codigo_fuente);

    return 0;
}