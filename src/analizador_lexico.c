//aqui habra un bucle que procese cada componente,
//ademas de otras cosas como includes de la TS y estructuras de datos

#include "analizador_lexico.h" // El tipo de datos "ComponenteLexico" viene del archivo .h
#include <string.h>

// Variables globales
FILE* codigo_fuente = NULL;

/* DEBUG*/
int contador_debug = 0;
const char* lexemas_debug[MAX_LEXEMA] = {"Lexema1", "Lexema2", "Antes_de_eof", "eof"};

// Función para inicializar el analizador léxico: será llamada desde main:
int inicializar_analizador_lexico(FILE* codigo_fuente_arg){ //Devolverá 1 si hay errores.

    // Asignar puntero a FILE a la variable global para usar en "siguienteComponenteLexico()""
    codigo_fuente = codigo_fuente_arg;

    // POR AHORA NO HARÁ NADA
    printf("\nAnalizador léxico inicializado correctamente\n");

    return 0;
};

// Función para obtener siguiente componente léxico: será llamada por el analizador sintáctico:
ComponenteLexico siguienteComponenteLexico(){

    ComponenteLexico componenteLexico = {0};

    // POR HACER


    return componenteLexico;
};
