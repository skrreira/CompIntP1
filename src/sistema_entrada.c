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

// Lectura caracter y retroceso puntero delantero:              // HACER DESPUÉS DE CARGAR BUFFER
char siguiente_caracter(){

    // Obtenemos el caracter:
    char c = se->buffer[se->delantero];

    // Avanzamos el puntero delantero gestionando todos los casos:
    avanzar_puntero_delantero();

    // Devolvemos el caracter:
    return c;
}

// Función para avanzar el puntero delantero una posición: gestiona casos especiales (cargar bloques)
void avanzar_puntero_delantero(){

    // Antes de avanzar, gestionamos casos especiales:
    if (se->delantero == MITAD_BUFFER){     // DELANTERO => EOF de buffer A
        cargar_buffer(1); 
        se->delantero++;    // Cargamos el bloque B, y apuntamos a la primera posición de B.
        return;
    } 
    if (se->delantero == TAM_TOTAL_BUFFER){     // DELANTERO => EOF de buffer B
        cargar_buffer(0); 
        se->delantero = 0;  // Cargamos el bloque A, y apuntamos a la primera posición de A.
        return;
    } 

    // Si no estamos en un caso especial, simplemente aumentamos delantero en 1:
    se->delantero++;

}

void retroceder_puntero_delantero(){
    se->delantero--;                //CUIDADO CON LOS INICIO DE BLOQUE
}
void avanzar_puntero_inicio(){               // LA USAMOS para GET LEXEMA => avanzamos puntero inicio hasta final
    se->inicio++;                           //CUIDADO CON LOS CASOS DE EOF
}


// Función para cargar buffer:
void cargar_buffer(int num_buffer);
int manejar_eof();

// Devolver lexema completo a analizador léxico
char* obtener_lexema();

// Función para debug:
void imprimir_buffer();




// NOTA: CON UN Poco de caña y atención a los casos especiales, esto se saca solo.

