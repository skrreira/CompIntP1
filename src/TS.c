#include "TS.h"
#include "definiciones.h"
#include "hash.h"

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
    {"var", VAR}
};

// 1. Inicializa la tabla de símbolos y añade las keywords de Go.
void inicializarTablaSimbolos(TablaSimbolos *ts){

    // Inicializamos Tabla Hash
    inicializarTablaHash(&ts->tabla);

    // Cargamos palabras reservadas => OJO, PREGUNTAR EN CLASE
    void cargarPalabrasReservadas(TablaSimbolos *ts) {
        for (int i = 0; i < NUM_PALABRAS_RESERVADAS; i++) { //VER DE DÓNDE SE SACA
            ComponenteLexico *nuevo = malloc(sizeof(ComponenteLexico));
            nuevo->token = palabrasReservadas[i].token;
            strcpy(nuevo->lexema, palabrasReservadas[i].lexema);
            insertarEnTablaHash(&ts->tabla, nuevo->lexema, nuevo);
        }
    }



}

// Función privada para precargar las palabras reservadas de Go utilizando el array de Strings:
