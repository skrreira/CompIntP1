#ifndef ANALIZADOR_LEXICO_H
#define ANALIZADOR_LEXICO_H

// Definición de la longitud máxima de los lexemas:
#define MAX_LEXEMA 64

// Tipo que utilizaremos para devolver componentes léxicos:
typedef struct{
    int token;
    char lexema[MAX_LEXEMA];
} ComponenteLexico;

// Función para obtener siguiente componente léxico: será llamada por el analizador
// sintáctico:
ComponenteLexico siguienteComponenteLexico();

// EXPORTAR FUNCION INICIALIZAR ANALIZADOR LÉXICO




#endif //ANALIZADOR_LEXICO_H