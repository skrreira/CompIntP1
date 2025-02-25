//aqui habra un bucle que procese cada componente,
//ademas de otras cosas como includes de la TS y estructuras de datos

#include "analizador_lexico.h" // El tipo de datos "ComponenteLexico" viene del archivo .h
#include <string.h>
#include "TS.h"
#include <ctype.h>

// Variables globales
FILE* codigo_fuente = NULL;

// Función para determinar que hacer a partir del caracter inicial:
int reconocer_caracter_inicial(char c){
    
    // 1º CASO: Letra o barra baja => IDENTIFICADOR o "_" (caracter especial)
    if (isalpha(c) || c == '_') { return 1; }

    // 2º CASO: Número => NÚMEROS
    else if (isdigit(c)) { return 2; }

    // 3º CASO: Espacios en blanco y CR => Se avanza (no se llama a ningún autómata)
    else if (c == ' ' || c == '/t' || c == '/r' || c == '/n') { return 3; }

    // 4º CASO: Fin de archivo => Se devuelve lexema y se manda código FINAL
    else if (c == EOF) { return 4; }

    // 5º CASO: Delimitadores => Se devuelve con su codigo ASCII como token
    else if (c == ',' || c == ';' || c == ':' || c == '(' || c == ')' ||
    c == '{' || c == '}' || c == '[' || c == ']') { return 5; }

    // 6º CASO: Operadores => OPERADORES => Puede llamar a FLOAT (caso ".123") y a COMENTARIOS (caso "//" y "/*")
    else if (c == '=' || c == '+' || c == '>' || c == '.' || c == '/' || c == ':') { return 6; }

    // 7º CASO: Comillas => STRINGS => devuelve contenido entre comillas y TOKEN_STRING
    else if (c == '\'' || c == '\"') { return 7; }

}

// Función para inicializar el analizador léxico: será llamada desde main:
int inicializar_analizador_lexico(FILE* codigo_fuente_arg, TablaSimbolos *ts){ 
    
    // Asignar puntero a FILE a la variable global para usar en "siguienteComponenteLexico()""
    codigo_fuente = codigo_fuente_arg;

    // Información: la TS se inicializa desde el main (asegura que se puede acceder desde cualquier parte):
    printf("\nAnalizador léxico inicializado correctamente\n");

    return 0;
};

// Función para obtener siguiente componente léxico: será llamada por el analizador sintáctico:
ComponenteLexico siguienteComponenteLexico(){

    // Inicializamos una variable de tipo "ComponenteLexico":
    ComponenteLexico componenteLexico = {0};

    // POR HACER

    // AQUI SE NECESITA EL codigo_fuente

    // autómata de reconocimiento de lexemas

    // cuando se reconoce lexema, llamada a TS:
        // se busca (función buscar)
        // si devuelve un valor, se manda tupla <valor, lexema>
        // si devuelve null, se manda tupla <valor_identificador, lexema>
            // se inserta tupla en la TS (función insertar)









    return componenteLexico;
};
