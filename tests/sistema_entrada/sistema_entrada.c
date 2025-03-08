#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "sistema_entrada.h"
#include "errores/errores.h"

// Variables estáticas para facilitar la comunicación entre funciones del sistema_entrada:
extern SistemaEntrada *se = NULL; //debug, quitar extern
static int no_cargar_bloque_flag = 0;

// Función de inicialización:
void inicializar_sistema_entrada(FILE* codigo_fuente){

    // Reservamos memoria para el struct:
    se = (SistemaEntrada*)malloc(sizeof(SistemaEntrada));

    // Comprobamos si la asignación de memoria ha sido exitosa:
    if (!se){
        //ERROR
        ERROR_GENERAL();
        exit(1);
    }

    // Inicializamos los campos => BUFFER se inicializa solo 
    se->inicio = 0;
    se->delantero = 0;
    se->flag_veces_buffer_cargado = 0;
    se->codigo_fuente = codigo_fuente;

    // Asignamos un -1 a los posiciones centinela (CLARIDAD)
    se->buffer[MITAD_BUFFER] = -1;
    se->buffer[TAM_TOTAL_BUFFER - 1] = -1;

    // Cargamos sólamente el primer bloque (mejor que cargar ambos):
    cargar_buffer(0);

}

// Función de cierre del sistema de entrada:
void cerrar_sistema_entrada(){

    // Comprobamos que el struct tenga memoria reservada:
    if (!se){
        //ERROR
        ERROR_GENERAL();
        exit(1);
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

    // Flag de cargar buffer a 0:
    se->flag_veces_buffer_cargado = 0;
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

        // Aumentamos en 1 la cuenta de la flag de las cargas del buffer:
        se->flag_veces_buffer_cargado++;

    }

    // Bloque B:
    else if (num_buffer == 1){

        // Borramos los datos residuales antes de cargar nuevos datos:
        memset(se->buffer + MITAD_BUFFER, 0, TAM_BLOQUE);   //quitamos el +1?

        // Cargamos los nuevos datos utilizando fread():
        fread(&se->buffer + MITAD_BUFFER, TAM_BLOQUE, 1, se->codigo_fuente);

        // Aumentamos en 1 la cuenta de la flag de las cargas del buffer:
        se->flag_veces_buffer_cargado++;

    }

    // Caso error:
    else {
        // ERROR
        ERROR_GENERAL();
        exit(1);
    }

}

// Devolver lexema completo a analizador léxico
char* obtener_lexema(){
    
    char* lexema = NULL;
    int longitud = 0, inicio = se->inicio, delantero = se->delantero;

    // Variable para el caso de que el lexema sea demasiado grande:
    int ind = 0;

    // Error: lexema demasiado grande para el buffer
    if (se->flag_veces_buffer_cargado > 1) { 
        
        // ERROR
        ERROR_GENERAL();
        
        // Aunque sea un error, devolvemos la parte final del lexema:
        
        // Determinamos que parte final recuperar:
        if (delantero > MITAD_BUFFER - 1){
            ind = MITAD_BUFFER;
        }
        else {
            ind = 0;
        }
        longitud = delantero - ind;

        // Más adelante, hacemos la asignación de memoria y copiamos el lexema, como si fuera un caso normal
    }

    // Caso en el que inicio y delantero están en la misma mitad del buffer
    else if ((inicio < MITAD_BUFFER - 1 && delantero < MITAD_BUFFER - 1) || (inicio > MITAD_BUFFER - 1 && delantero > MITAD_BUFFER - 1)) {
        longitud = delantero - inicio;
    }

    // Caso en el que inicio y delantero están en mitades opuestas (cruce de buffers)
    else {
        if (delantero > MITAD_BUFFER) { // Cruza desde buffer A a B
            longitud = (MITAD_BUFFER - inicio - 1) + (delantero - (MITAD_BUFFER));
        } else { // Cruza desde buffer B a A
            longitud = (TAM_TOTAL_BUFFER - 1 - inicio) + delantero + 1; // Los -1, son para no contar centinelas.
        } // añadir un +1?
    }

    // Reservamos memoria para el lexema
    lexema = (char*)malloc((longitud + 1) * sizeof(char));
    if (lexema == NULL) return NULL; // ERROR

    // Copiar caracteres del buffer al lexema de manera eficiente

    // Caso error:
    if (se->flag_veces_buffer_cargado > 1){
        // Copiamos solo la parte final:
        memcpy(lexema, &se->buffer[ind], longitud);
    }

    else if ((inicio < MITAD_BUFFER - 1 && delantero < MITAD_BUFFER - 1) 
    || (inicio > MITAD_BUFFER - 1 && delantero > MITAD_BUFFER - 1)) {

        // Caso donde todo el lexema está en una parte del buffer
        memcpy(lexema, &se->buffer[inicio], longitud);

    } else {

        // Caso donde el lexema está dividido en dos mitades (doble buffer)
        int primera_parte = (TAM_TOTAL_BUFFER - 1 - inicio);
        memcpy(lexema, &se->buffer[inicio], primera_parte);
        memcpy(lexema + primera_parte, &se->buffer[MITAD_BUFFER], delantero - (MITAD_BUFFER));
    }

    lexema[longitud] = '\0'; // Agregar terminador de cadena

    // Actualizar inicio del buffer
    se->inicio = delantero;
    se->flag_veces_buffer_cargado = 0;

    return lexema;

}

// Función para debug:
void imprimir_buffer(){
    printf("\nBUFFER ACTUAL: {");

    for(int i = 0; i < TAM_TOTAL_BUFFER; i++){

        switch (se->buffer[i])
        {
        case '\n': printf("'\\n' | "); break;
        case '\t': printf("'\\t' | "); break;
        default: printf("%c | ", se->buffer[i]); break;
        }

    }

    printf(" }\n");

}


