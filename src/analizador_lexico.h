#ifndef ANALIZADOR_LEXICO_H
#define ANALIZADOR_LEXICO_H

// Includes
#include <stdio.h>
#include "sistema_entrada.h"
#include "TS.h"

// Tipo que utilizaremos para devolver componentes léxicos:
typedef struct ComponenteLexico{
    int token;
    char* lexema;
} ComponenteLexico;

// Función para inicializar el analizador léxico: será llamada desde main:
int inicializar_analizador_lexico(FILE* codigo_fuente, TablaSimbolos *ts); //Devolverá 1 si hay errores.

// Función para obtener siguiente componente léxico: será llamada por el analizador sintáctico:
ComponenteLexico siguienteComponenteLexico();


#endif //ANALIZADOR_LEXICO_H