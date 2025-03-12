#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include <string.h>
#include "../libs/uthash.h" // Librería uthash.h ubicada en la carpeta libs

/**
 * Utilizamos la librería open-source uthash.h para implementar la tabla hash.
 * uthash es conocida por su eficiencia y facilidad de integración en proyectos en C.
 * Esta librería nos ahorra mucho tiempo de desarrollo y es más rápida y segura que
 * implementar una tabla hash manualmente. Además, uthash.h es solo un archivo de cabecera,
 * por lo que podemos modificar su código directamente si fuera necesario en algún momento.
 */

// Prototipado:
typedef struct ComponenteLexico ComponenteLexico;


// Estructura que representa cada entrada en la tabla hash.
// Clave: cadena de caracteres (máx 64), Valor: puntero genérico.
typedef struct {
    char clave[64];      // Clave que usaremos como identificador en la tabla hash.
    ComponenteLexico *valor;         // Valor asociado. Puntero a ComponenteLexico.
    UT_hash_handle hh;   // Macro interna de uthash. Necesaria para la gestión de la tabla hash.
} EntradaHash;

// Definimos un puntero a la tabla hash (uthash trabaja con punteros a structs).
typedef EntradaHash *TablaHash;

/**
 * Inicializa la tabla hash como vacía.
 *
 * @param tabla Puntero a la tabla hash que será inicializada en NULL.
 */
void inicializarEstructuraDatos(TablaHash *tabla);

/**
 * Inserta una clave y un valor en la tabla hash.
 * Si la clave ya existe, actualiza el valor asociado.
 *
 * @param tabla Puntero a la tabla hash.
 * @param clave Cadena que representa la clave.
 * @param valor Puntero al valor asociado a la clave.
 */
void insertarEnEstructuraDatos(TablaHash *tabla, const char *clave, void *valor);

/**
 * Busca una clave en la tabla hash y devuelve el valor asociado.
 *
 * @param tabla Puntero a la tabla hash.
 * @param clave Cadena que representa la clave.
 * @return Puntero al valor asociado o NULL si no se encuentra.
 */
ComponenteLexico *buscarEnEstructuraDatos(TablaHash *tabla, const char *clave);

/**
 * Elimina una clave y su valor asociado de la tabla hash. Realmente no hace falta.
 *
 * @param tabla Puntero a la tabla hash.
 * @param clave Cadena que representa la clave.
 */
void eliminarDeEstructuraDatos(TablaHash *tabla, const char *clave);

/**
 * Libera toda la memoria ocupada por la tabla hash.
 *
 * @param tabla Puntero a la tabla hash.
 */
void liberarEstructuraDatos(TablaHash *tabla);

/**
 * Imprime todas las claves y valores de la tabla hash.
 * IMPORTANTE: Esta función asume que los valores son enteros o punteros imprimibles.
 * Si estás almacenando estructuras complejas, deberás adaptar el printf en la implementación.
 *
 * @param tabla Puntero a la tabla hash.
 */
void imprimirEstructuraDatos(TablaHash *tabla);




#endif // HASH_H