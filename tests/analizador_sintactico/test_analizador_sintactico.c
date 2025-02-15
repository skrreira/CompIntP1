#include "../../src/analizador_lexico.h"
#include "../../src/analizador_sintactico.h"

// Función de testeo:
void test_iniciar_analizador_sintactico() {
    printf("===== INICIANDO TEST iniciar_analizador_sintactico =====\n");
    iniciar_analizador_sintactico(); // Esto usa el mock -> por el proceso de enlazado en C
    printf("===== FIN TEST iniciar_analizador_sintactico =====\n");
}

int main() {
    test_iniciar_analizador_sintactico();
    return 0;
}