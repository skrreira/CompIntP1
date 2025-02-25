//aqui habra un bucle que procese cada componente,
//ademas de otras cosas como includes de la TS y estructuras de datos

#include "analizador_lexico.h" // El tipo de datos "ComponenteLexico" viene del archivo .h
#include <string.h>
#include "TS.h"
#include <ctype.h>

// Variables globales
FILE* codigo_fuente = NULL;

// Prototipado de las funciones de los autómatas de cada tipo de componente léxico:
void automata_identificador();
void automata_numeros();
//automatas para cada tipo de números?
void automata_operadores();
void automata_comentarios();
void automata_string();


// Función para determinar que hacer a partir del caracter inicial:
int reconocer_caracter_inicial(char c){
    
    // 1º CASO: Letra o barra baja => IDENTIFICADOR o "_" (caracter especial)
    if (isalpha(c) || c == '_') { return 1; }

    // 2º CASO: Número => NÚMEROS
    else if (isdigit(c)) { return 2; }

    // 3º CASO: Espacios en blanco y CR => Se avanza (no se llama a ningún autómata)
    else if (c == ' ' || c == '/t' || c == '/r' || c == '/n') { return 3; }

    // 4º CASO: Fin de archivo => Se devuelve lexema y se manda código FINAL
    else if (c == EOF) { return 4; }

    // 5º CASO: Delimitadores => Se devuelve con su codigo ASCII como token
    else if (c == ',' || c == ';' || c == ':' || c == '(' || c == ')' ||
    c == '{' || c == '}' || c == '[' || c == ']') { return 5; }

    // 6º CASO: Operadores => OPERADORES => Puede llamar a FLOAT (caso ".123") y a COMENTARIOS (caso "//" y "/*")
    else if (c == '=' || c == '+' || c == '>' || c == '.' || c == '/' || c == ':') { return 6; }

    // 7º CASO: Comillas => STRINGS => devuelve contenido entre comillas y TOKEN_STRING
    else if (c == '\'' || c == '\"') { return 7; }

    // ÚLTIMO CASO: El caracter inicial no se corresponde con ninguno de los anteriores:
    return 0; //LLAMAR A ERROR?
}

// Función para inicializar el analizador léxico: será llamada desde main:
int inicializar_analizador_lexico(FILE* codigo_fuente_arg, TablaSimbolos *ts){ 
    
    // Asignar puntero a FILE a la variable global para usar en "siguienteComponenteLexico()""
    codigo_fuente = codigo_fuente_arg;

    // Información: la TS se inicializa desde el main (asegura que se puede acceder desde cualquier parte):
    printf("\nAnalizador léxico inicializado correctamente\n");

    return 0;
};

// Función para obtener siguiente componente léxico: será llamada por el analizador sintáctico:
ComponenteLexico siguienteComponenteLexico(){

    // Inicializamos una variable de tipo "ComponenteLexico":
    ComponenteLexico componenteLexico = {0};

    // Variable para saber cuándo parar, variable de estado (del caracter inicial) y variable char:
    int stop = 0, estado = 0;
    char c;

    // Bucle while mientras no se necesite parar de procesar caracteres:
    while(!stop){

        // Leemos el siguiente caracter del documento //LUEGO SERÁ SISTEMA ENTRADA
        c = fgetc(codigo_fuente);

        // Con un switch, hacemos las acciones correspondientes dependiendo del caracter inicial:
        estado = reconocer_caracter_inicial(c);
        switch (estado)
        {
        case 1: //IDENTIFICADOR y '_'
            automata_identificador();
            break;

        case 2: //NUMEROS
            automata_numeros();
            break;

        case 3: //ESPACIOS EN BLANCO
            //aqui simplemente avanzamos el puntero
            c = fgetc(codigo_fuente); // con sistema de entrada
            continue;
            
        case 4: //FIN ARCHIVO
            //devolvemos un componente léxico
            //lexema = 'EOF' O -1
            //token = FINAL
            break;    

        case 5: //DELIMITADORES
            //devolvemos un componente léxico
            //lexema = c
            //token = valor ASCII
            break;

        case 6: //OPERADORES
            automata_operadores();
            break;
            
        case 7: //STRING
            automata_string();
            break;
    
        case 0: 
            /* code */
            //PRINTEAMOS ERROR
            break;
        }

    }

    


    
    






    // POR HACER

    // AQUI SE NECESITA EL codigo_fuente

    // autómata de reconocimiento de lexemas

    // cuando se reconoce lexema, llamada a TS:
        // se busca (función buscar)
        // si devuelve un valor, se manda tupla <valor, lexema>
        // si devuelve null, se manda tupla <valor_identificador, lexema>
            // se inserta tupla en la TS (función insertar)





    return componenteLexico;
};

// Función que implementa el autómata encargado de reconocer los identificadores:
void automata_identificador(){

    // Variable de parada:
    int stop = 0;

    // Bucle para seguir procesando caracteres hasta que no sean aceptados:
    while(!stop){
        // char c = siguiente char //TABLA SIMBOLOS
        char c;

        // Si el char no es alfanumérico o una barra baja, paramos y retrocedemos puntero.
        if(!(isalnum(c) || c != '_'))

        //AL ACABAR -> funcion auxiliar: get_lexema de sistema de entrada + función para buscar identificador en TS

    }
}

/*
EL RESTO DEL CÓDIGO ES IGUAL: hay que echarle horas. Antes de ponernos, casi vamos a implementar
el sistema de entrada antes (clase de mañana), el analizador léxico no tiene nada.*/