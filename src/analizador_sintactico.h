
#ifndef ANALIZADOR_SINTACTICO_H
#define ANALIZADOR_SINTACTICO_H

// INCLUDES
#include <stdio.h>
#include <string.h>
#include "analizador_lexico.h"
#include <unistd.h>

// DEFINICIONES
#define TOKEN_EOF -1

//EXPORTAR FUNCION INICIAR ANALIZADOR SINTÁCTICO
int iniciar_analizador_sintactico();


#endif //ANALIZADOR_SINTACTICO_H