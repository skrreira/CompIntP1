// Este el main del programa. Invoca al analizador sintáctico, que sigue un patrón
// productor consumidor con el analizador léxico.

#include <stdio.h>
#include <analizador_lexico.h>
#include <analizador_sintactico.h>

#include <string.h>

// Definición de constante de longitud máxima del nombre de fichero:
#define MAX_LEN_FILENAME 64;

// Se le tiene que poder mandar un documento como argumento
int main(char argc[], char* argv[]){

    //COMPROBACIÓN ARGUMENTOS:
    

    char codigo_fuente[64] = argv[1];   //todo: comprobar como hacer esto

    // Inicializar analizador léxico y estructuras de datos (constructor). Le pasamos el documento
    inicializar_analizador_lexico(codigo_fuente); //GESTIÓN DE ERRORES?

    // Llamar a función para inicializar TS. Bucle que inserta valores hardcodeados
    // pasar como argumento el documento.
    inicializar_TS(codigo_fuente); //GESTIÓN DE ERRORES

    // Iniciar definitivamente el analizador sintáctico -> llamara al léxico
    iniciar_analizador_sintactico(); //GESTIÓN DE ERROES? No necesita argumento

    
    return 0;
}