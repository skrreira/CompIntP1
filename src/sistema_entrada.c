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

// Función para avanzar el puntero delantero una posición: gestiona casos especiales (carga bloques):
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

// Función para avanzar el puntero inicio una posición: gestiona casos especiales (sin cargar bloques)
void avanzar_puntero_inicio(){               // LA USAMOS para GET LEXEMA => avanzamos puntero inicio hasta final
    
    // Caso dónde inicio esté en la posición anterior al centinela de A:
    if (se->inicio == MITAD_BUFFER - 1){
        se->inicio = MITAD_BUFFER + 1;
        return;
    }

    // Caso dónde inicio esté en la posición anterior al centinela de A:
    if (se->inicio == TAM_TOTAL_BUFFER - 2){
        se->inicio = 0;
        return;
    }
    
    // Resto de casos:
    se->inicio++;                           
}

// Función que hace que puntero inicio se iguale con el puntero delantero => no necesitamos recuperar el lexema
void saltar_lexema(){

    // Igualamos inicio con delantero (delantero apuntará al caracter siguiente al último del comentario)
    se->inicio = se->delantero;

    //hay un problema, cuando delantero apunta al centinela, se mueve en
    //el siguiente "siguienteCaracter", por lo que si igualamos inicio, 
    // es posible que inicio se iguale a delantero cuando todavia esta en
    // el eof (centinela). Hay que gestionar este error, aunque vamos a tener 
    // casos donde inicio va a ir delante de delantero por un momento (hasta
    // la siguiente llamada a "siguienteCaracter")

    // Casos especiales:
    if (se->inicio == MITAD_BUFFER) {se->inicio = MITAD_BUFFER + 1; return;}
    else if (se->inicio == TAM_TOTAL_BUFFER - 1) {se->inicio = 0; return; }
}

// Función para cargar buffer:
void cargar_buffer(int num_buffer){

    // Si "num_buffer" = 0, cargamos bloque A, si es = 1, cargamos bloque B.

    // Bloque A:
    if (num_buffer == 0){

        // Borramos los datos residuales antes de cargar nuevos datos:
        memset(se->buffer, 0, TAM_BLOQUE);

        // Cargamos los nuevos datos utilizando fread():
        fread(&se->buffer[0], TAM_BLOQUE, 1, se->codigo_fuente);

    }

    // Bloque B:
    else if (num_buffer == 1){

        // Borramos los datos residuales antes de cargar nuevos datos:
        memset(se->buffer + MITAD_BUFFER + 1, 0, TAM_BLOQUE);

        // Cargamos los nuevos datos utilizando fread():
        fread(&se->buffer[0], TAM_BLOQUE, 1, se->codigo_fuente);

    }

    // Caso error:
    else {
        // ERROR
    }

}

// Devolver lexema completo a analizador léxico
char* obtener_lexema();

// Función para debug:
void imprimir_buffer();




x

// que es carga?


// NOTA: CON UN Poco de caña y atención a los casos especiales, esto se saca solo.

