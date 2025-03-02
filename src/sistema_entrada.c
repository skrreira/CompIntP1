#include <stdio.h>
#include <string.h>
#include "sistema_entrada.h"

// Variables estáticas para facilitar la comunicación entre funciones del sistema_entrada:
static SistemaEntrada *se = NULL;
static int no_cargar_bloque_flag = 0;

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

    // Hacemos las comprobaciones y el manejo de los casos en los que apuntemos a EOF:
    casos_centinela_avanzar_puntero_delantero();

    // Obtenemos el caracter:
    char c = se->buffer[se->delantero];

    // Avanzamos una posición el puntero delantero:
    se->delantero++;

    // Devolvemos el caracter:
    return c;
}

// Función para avanzar el puntero delantero una posición: gestiona casos especiales (cargar bloques):
void casos_centinela_avanzar_puntero_delantero(){

    // Antes de avanzar, gestionamos casos especiales:
    if (se->delantero == MITAD_BUFFER){     // DELANTERO => EOF de buffer A

        // Comprobamos flag para no volver a cargar el bloque si hemos retrocedido:
        if (no_cargar_bloque_flag == 0) cargar_buffer(1);
        else no_cargar_bloque_flag = 0; // flag = 0 si estaba en 1.

        se->delantero++;    // Cargamos el bloque B, y apuntamos a la primera posición de B.
        return;

    } 
    if (se->delantero == TAM_TOTAL_BUFFER-1){     // DELANTERO => EOF de buffer B

        // Comprobamos flag para no volver a cargar el bloque si hemos retrocedido:
        if (no_cargar_bloque_flag == 0) cargar_buffer(0);
        else no_cargar_bloque_flag = 0; // flag = 0 si estaba en 1.

        se->delantero = 0;  // Cargamos el bloque A, y apuntamos a la primera posición de A.
        return;
    } 

    // Si no estamos en un caso especial, no hace nada.
}

// Función para retroceder una posición el puntero delantero: gestiona casos de inicio de bloque (no carga bloques):
void retroceder_puntero_delantero(){    

    //CUIDADO: para no cargar bloques nuevos si retrocedemos y luego avanzamos => flag
    // Caso dónde estamos en el inicio del bloque A (saltamos EOF de B):
    if (se->delantero == 0){
        se->delantero = TAM_TOTAL_BUFFER - 2;   // Retrocedemos a la posición anterior del centinela de B
        no_cargar_bloque_flag = 1;
        return;
    }

    // Caso dónde estamos en el inicio del bloque B (saltamos EOF de A):
    if (se->delantero == MITAD_BUFFER + 1){
        se->delantero = MITAD_BUFFER - 1;
        no_cargar_bloque_flag = 1;
        return;
    }

    // Resto de casos (casos normales):
    se->delantero--;                
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

