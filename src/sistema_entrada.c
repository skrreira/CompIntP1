#include <stdio.h>
#include <string.h>
#include "sistema_entrada.h"

// Variable estática para facilitar la comunicación entre funciones del sistema_entrada:
static SistemaEntrada *se = NULL;

// Función de inicialización:
void inicializar_sistema_entrada(FILE* codigo_fuente){

    // Reservamos memoria para el struct:
    se = (SistemaEntrada*)malloc(sizeof(SistemaEntrada));

    // Comprobamos si la asignación de memoria ha sido exitosa:
    if (!se){
        // MANEJO ERROR
    }

    // Inicializamos los campos => BUFFER se inicializa solo 
    se->inicio = 0;
    se->delantero = 0;
    se->cuenta_longitud_lexema = 0;
    se->codigo_fuente = codigo_fuente;

    // Cargamos sólamente el primer bloque (mejor que cargar ambos):
    cargar_buffer(0);

}

// Función de cierre del sistema de entrada:
void cerrar_sistema_entrada(){

    // Comprobamos que el struct tenga memoria reservada:
    if (!se){
        //ERROR
        exit(0);
    }

    // Cerramos el puntero al codigo fuente:
    fclose(se->codigo_fuente);

    // Liberamos la memoria ocupada por el struct:
    free(se);    

}