#include "../src/hash.h"
#include <stdio.h>

int main() {
    // Declaramos la tabla hash
    TablaHash tabla;

    // 1. Inicializar tabla
    printf("[DEBUG] Inicializando tabla hash...\n");
    inicializarTablaHash(&tabla);
    imprimirTablaHash(&tabla);

    // 2. Insertar algunos valores
    int valor1 = 42, valor2 = 84, valor3 = 126;
    printf("[DEBUG] Insertando clave1 -> 42\n");
    insertarEnTablaHash(&tabla, "clave1", &valor1);
    printf("[DEBUG] Insertando clave2 -> 84\n");
    insertarEnTablaHash(&tabla, "clave2", &valor2);
    printf("[DEBUG] Insertando clave3 -> 126\n");
    insertarEnTablaHash(&tabla, "clave3", &valor3);
    imprimirTablaHash(&tabla);

    // 3. Buscar claves
    printf("[DEBUG] Buscando clave1...\n");
    int *res1 = (int *)buscarEnTablaHash(&tabla, "clave1");
    if (res1) {
        printf("clave1 encontrada, valor: %d\n", *res1);
    } else {
        printf("clave1 NO encontrada\n");
    }

    printf("[DEBUG] Buscando clave_inexistente...\n");
    int *res2 = (int *)buscarEnTablaHash(&tabla, "clave_inexistente");
    if (res2) {
        printf("clave_inexistente encontrada, valor: %d\n", *res2);
    } else {
        printf("clave_inexistente NO encontrada\n");
    }

    // 4. Liberar tabla
    printf("[DEBUG] Liberando tabla...\n");
    liberarTablaHash(&tabla);
    imprimirTablaHash(&tabla);

    return 0;
}