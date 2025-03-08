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
    
    printf("Leyendo caracteres secuencialmente:\nº");
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

void test_retroceso_caracter(const char *archivo) {
    printf("===== TEST RETROCESO PUNTERO DELANTERO ESTÁNDAR =====\n");
    FILE *fp = fopen(archivo, "r");
    inicializar_sistema_entrada(fp);
    
    char c1 = siguiente_caracter();
    char c2 = siguiente_caracter();
    retroceder_puntero_delantero();
    char c3 = siguiente_caracter();
    
    ASSERT(c2 == c3, "Retroceso de puntero delantero funciona correctamente");
    
    imprimir_buffer();
    cerrar_sistema_entrada();
    //fclose(fp);
}

void test_obtener_lexema(const char *archivo) {
    printf("===== TEST OBTENER LEXEMA =====\n");
    FILE *fp = fopen(archivo, "r");
    inicializar_sistema_entrada(fp);
    
    printf("Probando obtener lexema...\n");
    char *lexema = obtener_lexema();
    if (lexema) {
        printf("Lexema obtenido: %s\n", lexema);
        free(lexema);
    } else {
        printf("Error obteniendo lexema\n");
    }
    
    imprimir_buffer();
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
    test_lectura_secuencial_archivo_entero(archivo_prueba);   //DONE

    //test_retroceso_caracter(archivo_prueba);
    //test_obtener_lexema(archivo_prueba);
    //test_lexema_grande(archivo_prueba);
    //test_centinela_inicio_fin(archivo_prueba);
    //test_saltar_lexema(archivo_prueba);
    
    printf("===== FIN DE PRUEBAS =====\n");
    return 0;
}   