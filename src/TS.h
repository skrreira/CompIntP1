#ifndef TABLA_SIMBOLOS_H
#define TABLA_SIMBOLOS_H

#include "hash.h"
#include "analizador_lexico.h"

// Estructura que encapsula la tabla hash subyacente
typedef struct {
    TablaHash tabla; // Internamente es un puntero a EntradaHash*
} TablaSimbolos;

// Funciones que exportará la Tabla de Símbolos:

// 1. Inicializa la tabla de símbolos y añade las keywords de Go.
void inicializarTablaSimbolos(TablaSimbolos *ts);

// 2. Inserta un nuevo <token, lexema> en la tabla de símbolos.
void insertarEnTablaSimbolos(TablaSimbolos *ts, ComponenteLexico componenteLexico);

// 3. Busca un lexema en la tabla de símbolos. Devuelve el token si lo encuentra, o -1 si no.
int buscarEnTablaSimbolos(TablaSimbolos *ts, const char *lexema);

// 4. Libera toda la memoria de la tabla de símbolos.
void liberarTablaSimbolos(TablaSimbolos *ts);

// 5. (Para debug) Imprime toda la tabla de símbolos.
void imprimirTablaSimbolos(TablaSimbolos *ts);

#endif // TABLA_SIMBOLOS_H