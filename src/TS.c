#include "TS.h"
#include "definiciones.h"
#include "hash.h"

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
    {"var", VAR}
};

// Función que calcula el número de palabras reservadas del array (cuenta los elementos):
static const int NUM_PALABRAS_RESERVADAS = sizeof(palabrasReservadas) / sizeof(palabrasReservadas[0]);

// 1. Inicializa la tabla de símbolos y añade las keywords de Go.
void inicializarTS(TablaSimbolos *ts){

    // Inicializamos Tabla Hash
    inicializarTablaHash(&ts->tabla);
    printf("Estructura de datos de la tabla de símbolos inicializada.\n\n");

    // Cargamos palabras reservadas en la tabla de símbolos:
    cargarPalabrasReservadas(&ts);
    
    // Información:
    printf("Tabla de símbolos correctamente inicializada.\n\n");

}

// Función privada para precargar las palabras reservadas de Go utilizando el array de Strings:
// Cargamos palabras reservadas => OJO, PREGUNTAR EN CLASE
void cargarPalabrasReservadas(TablaSimbolos *ts) {

    // Iteramos una vez por cada "keyword" del array:
    for (int i = 0; i < NUM_PALABRAS_RESERVADAS; i++) { 

        // Reservamos memoria para guardar un nuevo elemento tipo "ComponenteLexico":
        ComponenteLexico *nuevo = malloc(sizeof(ComponenteLexico));

        // Copiamos el valor del token del array de Strings al nuevo elemento:
        nuevo->token = palabrasReservadas[i].token;

        // Ídem con la cadena que representa el lexema:
        strcpy(nuevo->lexema, palabrasReservadas[i].lexema);

        // Insertamos el elemento en la tabla hash:
        insertarEnTablaHash(&ts->tabla, nuevo->lexema, nuevo); //lexema es la clave, nuevo es el ComponenteLExico
    }
}

// 2. Inserta un nuevo <token_identificador, lexema_identificador> en la tabla de símbolos.
// Sólo insertará identificadores, todas las 'keywords' son insertadas en inicialización.
void insertarIdentificadorTS(TablaSimbolos *ts, const char* lexema){ //const ya que no va a ser modificado.

    // Reservamos memoria para almacenar un nuevo elemento tipo "ComponenteLexico"
    ComponenteLexico *nuevo = malloc(sizeof(ComponenteLexico));

    // Copiamos el valor del token identificador:
    nuevo->token = TOKEN_IDENTIFICADOR;

    // Ídem con la cadena que representa el lexema:
    strcpy(nuevo->lexema, lexema);

    // Insertamos el elemento en la tabla hash:
    insertarEnTablaHash(&ts->tabla, nuevo->lexema, nuevo);

}

// 3. Busca un lexema en la tabla de símbolos. Devuelve el token si lo encuentra, o -1 si no.
int buscarEnTablaSimbolos(TablaSimbolos *ts, const char *lexema){

    // Llamamos a la función para buscar en la tabla hash:
    ComponenteLexico *resultado = NULL;
    resultado = buscarEnTablaHash(&ts->tabla, lexema); // devuelve NULL si no lo encuentra.

    // Si el token de resultado es NULL, devolvemos -1 (TOKEN_NO_ENCONTRADO)
    if (resultado == NULL) return TOKEN_NO_ENCONTRADO;

    // Si se ha encontrado (!=NULL) devuelve el valor del token:
    return resultado->token;

}

// 4. Libera toda la memoria de la tabla de símbolos.
void liberarTablaSimbolos(TablaSimbolos *ts){

    // Llamamos a liberar tabla hash: liberará tambien la memoria de cada uno de los ComponentesLexicos:
    liberarTablaHash(&ts->tabla);

}

// 5. (Para debug) Imprime toda la tabla de símbolos.
void imprimirTablaSimbolos(TablaSimbolos *ts){

    // Llamamos a imprimir tablaHash:
    imprimirTablaHash(&ts->tabla);

}






