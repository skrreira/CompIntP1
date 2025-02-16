#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * uthash representa la tabla hash como un puntero a la primera entrada.
 * No hay una estructura "tabla", sino que el puntero apunta al primer elemento
 * de una lista enlazada hash interna gestionada por uthash.
 * Cuando la tabla está vacía, el puntero es NULL.
 */
void inicializarTablaHash(TablaHash *tabla) {
    *tabla = NULL; // Esto indica que la tabla está vacía
}

/*
 * Inserta una clave y un valor en la tabla hash.
 * Si la clave ya existe, se actualiza el valor asociado.
 */
void insertarEnTablaHash(TablaHash *tabla, const char *clave, void *valor) {
    EntradaHash *entrada;

    /*
     * uthash - HASH_FIND_STR:
     * -------------------------------------
     * Busca en la tabla por clave (tipo string).
     * - *tabla: el puntero a la tabla hash (cabeza de la lista)
     * - clave: la cadena que es la clave de búsqueda
     * - entrada: se asignará el puntero a la entrada encontrada (o NULL si no existe)
     */
    HASH_FIND_STR(*tabla, clave, entrada);

    if (entrada == NULL) {
        // La clave no está en la tabla, debemos crear una nueva entrada

        // Reservamos memoria para una nueva entrada
        entrada = (EntradaHash *)malloc(sizeof(EntradaHash));
        if (!entrada) {
            fprintf(stderr, "Error: No se pudo asignar memoria para la entrada hash\n");
            exit(EXIT_FAILURE);
        }

        // Copiamos la clave en la estructura, asegurándonos de no desbordar
        strncpy(entrada->clave, clave, sizeof(entrada->clave) - 1);
        entrada->clave[sizeof(entrada->clave) - 1] = '\0'; // Siempre terminamos en '\0'

        /*
         * uthash - HASH_ADD_STR:
         * -------------------------------------
         * Añade la nueva entrada a la tabla hash.
         * - *tabla: el puntero a la tabla hash (cabeza de la lista)
         * - clave: campo de la estructura que es la clave (nombre del campo en EntradaHash)
         * - entrada: el puntero a la entrada que queremos añadir
         * uthash utiliza el campo clave como índice para calcular el hash.
         */
        HASH_ADD_STR(*tabla, clave, entrada);
    }

    // Actualizamos el valor asociado (o lo establecemos si es una entrada nueva)
    entrada->valor = valor;
}

/*
 * Busca una clave en la tabla hash y devuelve el valor asociado.
 * Devuelve NULL si la clave no está en la tabla.
 */
ComponenteLexico *buscarEnTablaHash(TablaHash *tabla, const char *clave) {
    EntradaHash *entrada;

    /*
     * uthash - HASH_FIND_STR:
     * -------------------------------------
     * Igual que en insertar, buscamos por clave.
     * Devuelve NULL si no se encuentra la clave.
     */
    HASH_FIND_STR(*tabla, clave, entrada);

    if (entrada) {
        return entrada->valor;
    } else {
        return NULL;
    }
}

/*
 * Elimina una clave y su valor asociado de la tabla hash.
 */
void eliminarDeTablaHash(TablaHash *tabla, const char *clave) {
    EntradaHash *entrada;

    // Buscamos la clave en la tabla
    HASH_FIND_STR(*tabla, clave, entrada);

    if (entrada) {
        /*
         * uthash - HASH_DEL:
         * -------------------------------------
         * Elimina una entrada de la tabla hash.
         * - *tabla: puntero a la tabla hash (cabeza de la lista)
         * - entrada: puntero a la entrada que queremos eliminar
         * Esto elimina el nodo de la tabla, pero no libera la memoria.
         */
        HASH_DEL(*tabla, entrada);

        // Liberamos la memoria que habíamos reservado al insertar
        free(entrada);
    }
}

/*
 * Libera toda la memoria ocupada por la tabla hash.
 */
void liberarTablaHash(TablaHash *tabla) {
    EntradaHash *entrada, *tmp;

    /*
     * uthash - HASH_ITER:
     * -------------------------------------
     * Permite recorrer la tabla hash en orden arbitrario.
     * - hh: nombre del campo UT_hash_handle en la estructura EntradaHash
     * - *tabla: puntero a la tabla hash (cabeza de la lista)
     * - entrada: puntero que en cada iteración apunta a la entrada actual
     * - tmp: puntero temporal usado internamente para evitar problemas al eliminar
     */
    HASH_ITER(hh, *tabla, entrada, tmp) {

        // Eliminamos la entrada de la tabla
        HASH_DEL(*tabla, entrada);

        // Liberamos el ComponenteLexico*
        free(entrada->valor);

        // Liberamos la memoria de la entrada
        free(entrada);
    }

    // Dejamos la tabla vacía (NULL)
    *tabla = NULL;
}

/*
 * Imprime todas las claves y valores de la tabla hash.
 * Nota: Solo imprime el puntero del valor. Si se almacenan valores
 * más complejos, el usuario debe interpretar el puntero correctamente.
 */
void imprimirTablaHash(TablaHash *tabla) {
    EntradaHash *entrada, *tmp;

    printf("Contenido de la tabla hash:\n");

    if (*tabla == NULL) {
        printf("[La tabla está vacía]\n");
        return;
    }

    // Iteramos sobre todas las entradas de la tabla
    HASH_ITER(hh, *tabla, entrada, tmp) {
        printf("Clave: %s, Valor (puntero): %p\n", entrada->clave, entrada->valor);
    }
}