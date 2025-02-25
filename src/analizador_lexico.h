#ifndef ANALIZADOR_LEXICO_H
#define ANALIZADOR_LEXICO_H
//HABRA QUE IMPORTAR EL SISTEMA DE ENTRADA:

// Includes
#include <stdio.h>

// Definición de la longitud máxima de los lexemas:
#define MAX_LEXEMA 64

// Tipo que utilizaremos para devolver componentes léxicos:
typedef struct{
    int token;
    char lexema[MAX_LEXEMA];
} ComponenteLexico;

// Función para inicializar el analizador léxico: será llamada desde main:
int inicializar_analizador_lexico(FILE* codigo_fuente, TablaSimbolos *ts); //Devolverá 1 si hay errores.

// Función para obtener siguiente componente léxico: será llamada por el analizador sintáctico:
ComponenteLexico siguienteComponenteLexico();


#endif //ANALIZADOR_LEXICO_H