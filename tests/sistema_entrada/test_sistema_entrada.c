#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistema_entrada.h"

#define ASSERT(cond, msg) \
    if (!(cond)) { printf("[ERROR] %s\n", msg); } else { printf("[OK] %s\n", msg); }

// TEST EXITOSO
void test_inicializacion_y_cierre(const char *archivo) {
    printf("===== TEST INICIALIZACIÓN Y CIERRE =====\n");
    FILE *fp = fopen(archivo, "r");
    ASSERT(fp != NULL, "Archivo de prueba abierto correctamente");
    
    inicializar_sistema_entrada(fp);
    ASSERT(se != NULL, "Sistema de entrada inicializado correctamente");

    imprimir_buffer();

    printf("== CARGANDO BLOQUE B ==");
    cargar_buffer(1);
    imprimir_buffer();


    printf("== CARGANDO BLOQUE A DE NUEVO ==");
    cargar_buffer(0);
    imprimir_buffer();

    cerrar_sistema_entrada();
    ASSERT(se == NULL, "Sistema de entrada cerrado correctamente");
    
    //fclose(fp);
}

// TEST: tiene que poder leer
void test_lectura_secuencial(const char *archivo) {
    printf("===== TEST LECTURA SECUENCIAL =====\n");
    FILE *fp = fopen(archivo, "r");
    inicializar_sistema_entrada(fp);
    
    printf("Leyendo caracteres secuencialmente:\n");
    for (int i = 0; i < 300 ; i++) {
        char c = siguiente_caracter();
        printf("%c", c);
    }
    printf("\n");
    
    imprimir_buffer();

    cerrar_sistema_entrada();
    //fclose(fp);
}

// TEST: tiene que poder leer todo el archivo hasta el eof de verdad.
void test_lectura_secuencial_archivo_entero(const char *archivo) {
    printf("===== TEST LECTURA SECUENCIAL ARCHIVO ENTERO =====\n");
    FILE *fp = fopen(archivo, "r");
    inicializar_sistema_entrada(fp);
    
    printf("Leyendo caracteres secuencialmente:\n");
    char c;
    do{
        c = siguiente_caracter();
        printf("%c", c);
    }
    while (c != EOF_SIMULADO); //ARREGLAR SEGURO
    
    printf("\n");
    
    imprimir_buffer();

    cerrar_sistema_entrada();
    //fclose(fp);
}

void test_retroceso_caracter_basico(const char *archivo) {
    printf("===== TEST RETROCESO PUNTERO DELANTERO ESTÁNDAR =====\n");
    FILE *fp = fopen(archivo, "r");
    inicializar_sistema_entrada(fp);
    
    printf("\nAvanzando 3 posiciones: \n");
    char c1 = siguiente_caracter();
    char c2 = siguiente_caracter();
    char c3 = siguiente_caracter();
    imprimir_buffer();


    printf("\n\nRetrocediendo 1 posicion: \n");
    retroceder_puntero_delantero();
    imprimir_buffer();
    

    char c4 = siguiente_caracter();
    ASSERT(c4 == c3, "Retroceso de puntero delantero funciona correctamente");
    
    cerrar_sistema_entrada();
    //fclose(fp);
}

/*
void test_retroceso_caracter_avanzado(const char *archivo) {
    printf("===== TEST RETROCESO PUNTERO DELANTERO ESTÁNDAR =====\n");
    FILE *fp = fopen(archivo, "r");
    inicializar_sistema_entrada(fp);

    // Cargamos los dos bloques (el A ya va con la inicialización):
    cargar_buffer(1);


    // TEST INICIO DE B //
    
    // Movemos delantero justo al inicio de B:
    printf("== Puntero delantero al inicio de B ==\n");
    se->delantero = MITAD_BUFFER;
    printf("\n\tCARACTER: %c", se->buffer[se->delantero]);

    // Imprimimos estado actual
    imprimir_buffer();

    // Devolvemos puntero delantero: tiene que ir al char anterior al centinela de A.
    retroceder_puntero_delantero();

    // Imprimimos estado actual:
    imprimir_buffer();

    // Comprobamos que al avanzar delantero de nuevo funciona, y no carga bloque por la flag:
    char c = siguiente_caracter();
    
    printf("\n\tCARACTER: %c", c);

    char c2 = siguiente_caracter();
    
    printf("\n\tCARACTER: %c", c2);

    // Imprimimos estado
    imprimir_buffer();
    

    
    // TEST INICIO DE B //
    // Repetimos el mismo proceso, pero con delantero justo al inicio de A: el resto es igual
    
    // Movemos delantero justo al inicio de B:
    printf("== Puntero delantero al inicio de A ==\n");
    se->delantero = 0;
    printf("\n\tCARACTER: %c", se->buffer[se->delantero]);

    // Imprimimos estado actual
    imprimir_buffer();

    // Devolvemos puntero delantero: tiene que ir al char anterior al centinela de A.
    retroceder_puntero_delantero();

    // Imprimimos estado actual:
    imprimir_buffer();

    // Comprobamos que al avanzar delantero de nuevo funciona, y no carga bloque por la flag:
    char c = siguiente_caracter();
    
    printf("\n\tCARACTER: %c", c);

    char c2 = siguiente_caracter();
    
    printf("\n\tCARACTER: %c", c2);

    // Imprimimos estado
    imprimir_buffer();
    

    cerrar_sistema_entrada();
    //fclose(fp);
}
*/


//TEST: DONE
void test_obtener_lexema(const char *archivo) {
    printf("===== TEST OBTENER LEXEMA =====\n");
    FILE *fp = fopen(archivo, "r");
    inicializar_sistema_entrada(fp);
    cargar_buffer(1);
    se->flag_veces_buffer_cargado = 0;
    
    /*
    printf("\n\n == CASO AMBOS BLOQUE A ==\n");
    se->inicio = 0;
    se->delantero = 54;

    printf("Probando obtener lexema...\n");
    char *lexema1 = obtener_lexema();
    if (lexema1) {
        printf("Lexema obtenido: %s\n", lexema1);
        printf("Longitud lexema: %ld\n", strlen(lexema1));
        free(lexema1);
    } else {
        printf("Error obteniendo lexema\n");
    }
    imprimir_buffer();
    

     
    printf("\n\n== CASO AMBOS BLOQUE B ==\n");
    se->inicio = MITAD_BUFFER;
    se->delantero = TAM_TOTAL_BUFFER - 15;

    printf("Probando obtener lexema...\n");
    char *lexema2 = obtener_lexema();
    if (lexema2) {
        printf("Lexema obtenido: %s\n", lexema2);
        printf("Longitud lexema: %ld\n", strlen(lexema2));
        free(lexema2);
    } else {
        printf("Error obteniendo lexema\n");
    }
    imprimir_buffer();
    

    
    printf("\n\n== CASO INICIO BLOQUE A DELANTERO BLOQUE B ==\n");
    se->inicio = 5;
    se->delantero = TAM_TOTAL_BUFFER - 35;

    printf("Probando obtener lexema...\n");
    char *lexema3 = obtener_lexema();
    if (lexema3) {
        printf("Lexema obtenido: %s\n", lexema3);
        printf("Longitud lexema: %ld\n", strlen(lexema3));
        free(lexema3);
    } else {
        printf("Error obteniendo lexema\n");
    }
    imprimir_buffer();
    

    
    printf("\n\n== CASO INICIO BLOQUE B DELANTERO BLOQUE A ==\n");
    se->inicio = TAM_TOTAL_BUFFER - 35;
    se->delantero = 5;

    printf("Probando obtener lexema...\n");
    char *lexema4 = obtener_lexema();
    if (lexema4) {
        printf("Lexema obtenido: %s\n", lexema4);
        free(lexema4);
    } else {
        printf("Error obteniendo lexema\n");
    }
    imprimir_buffer();
    */


    cerrar_sistema_entrada();
    //fclose(fp);
}

void test_lexema_grande(const char *archivo) {
    printf("===== TEST LEXEMA DEMASIADO GRANDE =====\n");
    FILE *fp = fopen(archivo, "r");
    inicializar_sistema_entrada(fp);
    
    printf("Probando lexema demasiado grande...\n");
    char *lexema = obtener_lexema();
    ASSERT(lexema == NULL, "Manejo de lexema demasiado grande correcto");
    
    imprimir_buffer();
    cerrar_sistema_entrada();
    //fclose(fp);
}

void test_centinela_inicio_fin(const char *archivo) {
    printf("===== TEST RETROCEDER PUNTERO DELANTERO EDGE CASES =====\n");
    FILE *fp = fopen(archivo, "r");
    inicializar_sistema_entrada(fp);
    
    se->delantero = 0;
    retroceder_puntero_delantero();
    ASSERT(se->delantero == TAM_TOTAL_BUFFER - 2, "Retroceso desde inicio de A correcto");
    
    se->delantero = MITAD_BUFFER + 1;
    retroceder_puntero_delantero();
    ASSERT(se->delantero == MITAD_BUFFER - 1, "Retroceso desde inicio de B correcto");
    
    imprimir_buffer();
    cerrar_sistema_entrada();
    //fclose(fp);
}

void test_saltar_lexema(const char *archivo) {

    printf("===== TEST SALTAR LEXEMA =====\n");
    FILE *fp = fopen(archivo, "r");
    inicializar_sistema_entrada(fp);
    
    
    printf("Probando saltar lexema...\n");
    se->delantero = MITAD_BUFFER;
    saltar_lexema();
    ASSERT(se->inicio == MITAD_BUFFER + 1, "Saltar lexema con centinela correcto");
    
    imprimir_buffer();
    cerrar_sistema_entrada();
    //fclose(fp);
}

int main() {
    const char *archivo_prueba = "concurrentSum.go";
    printf("===== INICIO DE PRUEBAS =====\n");
    
    //====== BÁSICOS ======//
    //test_inicializacion_y_cierre(archivo_prueba);             //DONE
    //test_lectura_secuencial(archivo_prueba);                  //DONE
    //test_lectura_secuencial_archivo_entero(archivo_prueba);   //DONE

    //test_retroceso_caracter_basico(archivo_prueba);             //DONE
    //test_retroceso_caracter_avanzado(archivo_prueba);           //DONE

    //test_obtener_lexema(archivo_prueba);  //DONJE
    test_lexema_grande(archivo_prueba);
    //test_centinela_inicio_fin(archivo_prueba);
    //test_saltar_lexema(archivo_prueba);
    
    printf("===== FIN DE PRUEBAS =====\n");
    return 0;
}   