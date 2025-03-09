#ifndef SISTEMA_ENTRADA_H
#define SISTEMA_ENTRADA_H

#include <stdio.h>
#include <string.h>

// Definiciones
#define TAM_BLOQUE 64 // Tamaño de cada bloque (sin contar centinela)
#define TAM_TOTAL_BUFFER (2 *TAM_BLOQUE + 2) // Tamaño total del buffer (contando dos bloques + centinelas)
#define MITAD_BUFFER (TAM_TOTAL_BUFFER / 2) // Mitad del buffer (acaba el primer bloque, empieza el segundo)
#define EOF_SIMULADO '\0' // Representación interna de EOF

// Estructura
typedef struct SistemaEntrada
{
    char buffer[TAM_TOTAL_BUFFER];

    int inicio;
    int delantero;

    int flag_veces_buffer_cargado; // Esta flag servirá para saber si ha entrado un lexema demasiado grande.

    FILE* codigo_fuente;
} 
SistemaEntrada;

// EXPORTAMOS se:
extern SistemaEntrada *se;


// Funciones de inicialización y cierre:
void inicializar_sistema_entrada(FILE* codigo_fuente);
void cerrar_sistema_entrada();

// Lectura caracter y retroceso puntero delantero:
char siguiente_caracter();
void casos_centinela_avanzar_puntero_delantero();
void retroceder_puntero_delantero();
void avanzar_puntero_inico();

// Manejo de buffers y EOF
void cargar_buffer(int num_buffer);

// Devolver lexema completo a analizador léxico
char* obtener_lexema();
void saltar_lexema();

// Función para debug:
void imprimir_buffer();


#endif //SISTEMA_ENTRADA_H