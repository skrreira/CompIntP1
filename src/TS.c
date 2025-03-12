#include "TS.h"
#include "definiciones.h"
#include "hash.h"
#include "errores/errores.h"
#include "analizador_lexico.h"
#include <stdio.h>

// Define
#define TOKEN_NO_ENCONTRADO -1

// Struct
typedef struct {
    const char* lexema;
    int token;
} PalabraReservada;

// Array con las palabras reservadas de Go y sus tokens
static const PalabraReservada palabrasReservadas[] = {
    {"break", BREAK},
    {"default", DEFAULT},
    {"func", FUNC},
    {"interface", INTERFACE},
    {"select", SELECT},
    {"case", CASE},
    {"defer", DEFER},
    {"go", GO},
    {"map", MAP},
    {"struct", STRUCT},
    {"chan", CHAN},
    {"else", ELSE},
    {"goto", GOTO},
    {"package", PACKAGE},
    {"switch", SWITCH},
    {"const", CONSY},
    {"fallthrough", FALLTHROUGH},
    {"if", IF},
    {"range", RANGE},
    {"type", TYPE},
    {"continue", CONTINUE},
    {"for", FOR},
    {"import", IMPORT},
    {"return", RETURN},
    {"var", VAR},
    {"float32", FLOAT32}
};

// Función que calcula el número de palabras reservadas del array (cuenta los elementos):
static const int NUM_PALABRAS_RESERVADAS = sizeof(palabrasReservadas) / sizeof(palabrasReservadas[0]);

// Prototipo función auxiliar (no se exporta)
void cargarPalabrasReservadas(TablaSimbolos *ts);

// 1. Inicializa la tabla de símbolos y añade las keywords de Go.
void inicializarTS(TablaSimbolos *ts){

    // Inicializamos Tabla Hash
    inicializarEstructuraDatos(&ts->tabla);
    printf("Estructura de datos de la tabla de símbolos inicializada.\n\n");

    // Cargamos palabras reservadas en la tabla de símbolos:
    printf("Cargando palabras reservadas...\n");
    cargarPalabrasReservadas(ts);
    
    // Información:
    printf("Tabla de símbolos correctamente inicializada.\n\n");

}

void cargarPalabrasReservadas(TablaSimbolos *ts) {
    // Iteramos una vez por cada "keyword" del array:
    for (int i = 0; i < NUM_PALABRAS_RESERVADAS; i++) { 

        // Reservamos memoria para un nuevo ComponenteLexico
        ComponenteLexico *nuevo = malloc(sizeof(ComponenteLexico));
        if (nuevo == NULL) {
            fprintf(stderr, "Error: No se pudo asignar memoria para ComponenteLexico\n");
            exit(EXIT_FAILURE);
        }

        // Copiamos el valor del token
        nuevo->token = palabrasReservadas[i].token;

        // Asignamos memoria para el lexema y copiamos la palabra
        nuevo->lexema = malloc(strlen(palabrasReservadas[i].lexema) + 1);
        if (nuevo->lexema == NULL) {
            fprintf(stderr, "Error: No se pudo asignar memoria para nuevo->lexema\n");
            free(nuevo);  // Liberamos el ComponenteLexico antes de salir
            exit(EXIT_FAILURE);
        }
        strcpy(nuevo->lexema, palabrasReservadas[i].lexema); // Copiamos el lexema

        // Insertamos el elemento en la tabla hash:
        insertarEnEstructuraDatos(&ts->tabla, nuevo->lexema, nuevo); 
    }
}

// 2. Inserta un nuevo <token_identificador, lexema_identificador> en la tabla de símbolos.
// Sólo insertará identificadores, todas las 'keywords' son insertadas en inicialización.
void insertarIdentificadorTS(TablaSimbolos *ts, const char* lexema){ //const ya que no va a ser modificado.

    // Caso TS no inicializada:
    if (ts == NULL){
        ERROR_GENERAL();
        printf("Tabla de símbolos no inicializada.\n");
        return;
    }

    // Comprobamos si ya existe el identificador en la tabla Hash:
    if (buscarEnEstructuraDatos(&ts->tabla, lexema) != NULL) {
        printf("[WARN] Identificador '%s' ya existe en la tabla de símbolos. No se inserta.\n", lexema);
        return; 
        /* Es solo una medida de seguridad; el encargado de comprobar que no se inserten 
        repetidos va a ser el propio analizador léxico, ya que su función es insertar si
        no se encuentra un valor para un lexema dado.*/
    }

    
    // Reservamos memoria para almacenar un nuevo elemento tipo "ComponenteLexico"
    ComponenteLexico *nuevo = malloc(sizeof(ComponenteLexico));
    
    // Copiamos el valor del token identificador:
    nuevo->token = TOKEN_IDENTIFICADOR;

    // Ídem con la cadena que representa el lexema:
    nuevo->lexema = malloc(strlen(lexema) + 1);
    if (nuevo->lexema == NULL) {
        fprintf(stderr, "[ERROR] No se pudo reservar memoria para lexema '%s'.\n", lexema);
        free(nuevo); // Liberar la memoria del nodo si falla
        exit(EXIT_FAILURE);
    }
    strcpy(nuevo->lexema, lexema);

    // Insertamos el elemento en la tabla hash:
    insertarEnEstructuraDatos(&ts->tabla, nuevo->lexema, nuevo);

}

// 3. Busca un lexema en la tabla de símbolos. Devuelve el token si lo encuentra, o -1 si no.
int buscarEnTS(TablaSimbolos *ts, const char *lexema){

    // Llamamos a la función para buscar en la tabla hash:
    ComponenteLexico *resultado = NULL;
    resultado = buscarEnEstructuraDatos(&ts->tabla, lexema); // devuelve NULL si no lo encuentra.

    // Si el token de resultado es NULL, devolvemos -1 (TOKEN_NO_ENCONTRADO)
    if (resultado == NULL) return TOKEN_NO_ENCONTRADO;

    // Si se ha encontrado (!=NULL) devuelve el valor del token:
    return resultado->token;

}

// 4. Libera toda la memoria de la tabla de símbolos.
void liberarTS(TablaSimbolos *ts){

    // Llamamos a liberar tabla hash: liberará tambien la memoria de cada uno de los ComponentesLexicos:
    liberarEstructuraDatos(&ts->tabla);

}

// 5. (Para debug) Imprime toda la tabla de símbolos.
void imprimirTS(TablaSimbolos *ts){

    // Llamamos a imprimir tablaHash:
    imprimirEstructuraDatos(&ts->tabla);

}






