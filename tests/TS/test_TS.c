#include <stdio.h>
#include <string.h>
#include "../src/TS.h"
#include "../src/definiciones.h" // Necesario por los tokens

int main() {
    TablaSimbolos ts;

    // 1. Inicializar tabla de símbolos
    printf("[TEST] Inicializando Tabla de Símbolos...\n");
    inicializarTS(&ts);
    imprimirTS(&ts);

    // 2. Buscar palabra reservada
    printf("\n[TEST] Buscando palabra reservada 'if'...\n");
    int token_if = buscarEnTS(&ts, "if");
    if (token_if == IF) {
        printf("[SUCCESS] 'if' encontrado, token: %d\n", token_if);
    } else {
        printf("[ERROR] 'if' no encontrado o token incorrecto\n");
    }

    // 3. Buscar palabra inexistente
    printf("\n[TEST] Buscando palabra inexistente 'nonexistent'...\n");
    int token_no_existe = buscarEnTS(&ts, "nonexistent");
    if (token_no_existe == -1) {
        printf("[SUCCESS] 'nonexistent' no encontrada, token: %d\n", token_no_existe);
    } else {
        printf("[ERROR] 'nonexistent' encontrado inesperadamente\n");
    }

    // 4. Insertar identificador nuevo
    printf("\n[TEST] Insertando identificador 'mi_variable'...\n");
    insertarIdentificadorTS(&ts, "mi_variable");

    printf("[TEST] Insertando identificador 'mi_variable2'...\n");
    insertarIdentificadorTS(&ts, "mi_variable2");

    printf("[TEST] Insertando identificador repetido 'mi_variable2'...\n");
    insertarIdentificadorTS(&ts, "mi_variable2");


    // 5. Buscar identificador insertado
    printf("\n[TEST] Buscando identificador 'mi_variable'...\n");
    int token_identificador = buscarEnTS(&ts, "mi_variable");
    if (token_identificador == TOKEN_IDENTIFICADOR) {
        printf("[SUCCESS] 'mi_variable' encontrado como identificador, token: %d\n", token_identificador);
    } else {
        printf("[ERROR] 'mi_variable' no encontrado o token incorrecto\n");
    }

    printf("[TEST] Buscando identificador 'mi_variable2'...\n");
    token_identificador = buscarEnTS(&ts, "mi_variable2");
    if (token_identificador == TOKEN_IDENTIFICADOR) {
        printf("[SUCCESS] 'mi_variable2' encontrado como identificador, token: %d\n", token_identificador);
    } else {
        printf("[ERROR] 'mi_variable2' no encontrado o token incorrecto\n");
    }

    // 6. Mostrar tabla después de insertar identificador
    printf("\n[TEST] Tabla después de insertar identificador:\n");
    imprimirTS(&ts);

    // 7. Liberar tabla
    printf("[TEST] Liberando tabla de símbolos...\n");
    liberarTS(&ts);

    // 8. Mostrar tabla tras liberar (opcional)
    printf("[TEST] Tabla después de liberar:\n");
    imprimirTS(&ts);

    return 0;
}