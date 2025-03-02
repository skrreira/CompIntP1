#ifndef SISTEMA_ENTRADA_H
#define SISTEMA_ENTRADA_H

#include <stdio.h>
#include <string.h>

// Definiciones
#define TAM_BLOQUE 4096 // Tamaño de cada bloque (sin contar centinela)
#define TAM_TOTAL_BUFFER 2*TAM_BLOQUE+2 // Tamaño total del buffer (contando dos bloques + centinelas)
#define MITAD_BUFFER TAM_TOTAL_BUFFER/2 // Mitad del buffer (acaba el primer bloque, empieza el segundo)
#define EOF_SIMULADO '\0' // Representación interna de EOF

// Estructura
typedef struct SistemaEntrada
{
    char buffer[TAM_TOTAL_BUFFER];

    int inicio;
    int delantero;
    // BUFFER ACTUAL?

    int cuenta_longitud_lexema; // Debe ser menor a TAM_BLOQUE

    FILE* codigo_fuente;
} 
SistemaEntrada;


// Funciones de inicialización y cierre:
void inicializar_sistema_entrada(FILE* codigo_fuente);
void cerrar_sistema_entrada();

// Lectura caracter y retroceso puntero delantero:
char siguiente_caracter();
void retroceder_puntero_delantero();
void avanzar_puntero_inico();

// Manejo de buffers y EOF
void cargar_buffer(int num_buffer);
int manejar_eof();

// Devolver lexema completo a analizador léxico
char* obtener_lexema();

// Función para debug:
void imprimir_buffer();






























#endif //SISTEMA_ENTRADA_H