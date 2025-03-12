#ifndef TABLA_SIMBOLOS_H
#define TABLA_SIMBOLOS_H

#include "hash.h"

// Estructura que encapsula la tabla hash subyacente
typedef struct {
    TablaHash tabla; // Internamente es un puntero a EntradaHash*
} TablaSimbolos;

// Funciones que exportará la Tabla de Símbolos:

// 1. Inicializa la tabla de símbolos y añade las keywords de Go.
void inicializarTS(TablaSimbolos *ts);

// 2. Inserta un nuevo <token_identificador, lexema_identificador> en la tabla de símbolos.
// Sólo insertará identificadores, todas las 'keywords' son insertadas en inicialización.
void insertarIdentificadorTS(TablaSimbolos *ts, const char* lexema); //const ya que no va a ser modificado.

// 3. Busca un lexema en la tabla de símbolos. Devuelve el token si lo encuentra, o -1 si no.
int buscarEnTS(TablaSimbolos *ts, const char *lexema);

// 4. Libera toda la memoria de la tabla de símbolos.
void liberarTS(TablaSimbolos *ts);

// 5. (Para debug) Imprime toda la tabla de símbolos.
void imprimirTS(TablaSimbolos *ts);

#endif // TABLA_SIMBOLOS_H