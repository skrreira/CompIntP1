#include "../../src/analizador_lexico.h"
#include <string.h>

// Función Mockup para simular el comportamiento de "siguienteComponenteLexico()" a la hora de hacer pruebas
ComponenteLexico siguienteComponenteLexico() {
    static int contador_debug = 0;
    const char *lexemas_debug[] = {"Lexema1", "Lexema2", "Antes_de_eof", "eof"};

    ComponenteLexico componenteLexico = {0};
    strcpy(componenteLexico.lexema, lexemas_debug[contador_debug]);
    componenteLexico.token = 300 + contador_debug;
    contador_debug += 1;

    if (strcmp(componenteLexico.lexema, "eof") == 0) {
        componenteLexico.token = -1;
    }

    return componenteLexico;
}