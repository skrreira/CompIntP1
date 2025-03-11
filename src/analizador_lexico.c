//aqui habra un bucle que procese cada componente,
//ademas de otras cosas como includes de la TS y estructuras de datos

#include "analizador_lexico.h" // El tipo de datos "ComponenteLexico" viene del archivo .h
#include <string.h>
#include "TS.h"
#include "errores/errores.h"
#include <ctype.h>
#include "sistema_entrada.h"
#include "definiciones.h"
                                                    // CUIDADO: AÑADIR CASO NÚMEROS IMAGINARIOS -> en cada 

                                                    // AÑADIR CASO 0_

// Variables globales
FILE* codigo_fuente = NULL;
SistemaEntrada* se = NULL;
ComponenteLexico componenteLexico;
TablaSimbolos* ts = NULL;

// Prototipado de las funciones de los autómatas de cada tipo de componente léxico:
void automata_identificador();
void automata_barra_baja();
void automata_numeros();
void automata_operadores();
void automata_comentarios();
void automata_string();

// Sub-Autómatas encargados del reconocimiento de números:

// ENTEROS:
void automata_decimal();
//void automata_binario();
//void automata_octal(); // 014 es octal
void automata_hex();

// PUNTO FLOTANTE:
void automata_decimal_float();
//void automata_binario_float();
//void automata_octal_float();
void automata_hex_float();

// IMAGINARIO: solo procesa una i => Añadimos por legibilidad
void automata_imaginario();

// Funcion auxiliar para saber si es un delimitador, operador o espacio:
int isDelimitador_Operador_o_Espacio(char c){
    return (c == ',' || c == ';' || c == ':' || c == '(' || c == ')' ||
        c == '{' || c == '}' || c == '[' || c == ']'
    || c == '=' || c == '+' || c == '>' || c == '.' || c == '/' || c == ':' ||
    c == ' ' || c == '/t' || c == '/r' || c == '/n' || c == '\'' || c == '\"');
}

// Función para determinar que hacer a partir del caracter inicial:
int reconocer_caracter_inicial(char c){
    
    // 1º CASO: Letra  => IDENTIFICADOR (puede ser llamado por el autómata de '_')
    if (isalpha(c)) { return 1; }

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

    // 8º CASO: Barra baja => puede llamar a IDENTIFICADOR (si después de la barra baja va un char alfanumérico):
    else if (c == '_') { return 8; }

    // ÚLTIMO CASO: El caracter inicial no se corresponde con ninguno de los anteriores:
    ERROR_GENERAL();
    return 0; //LLAMAR A ERROR?
}

// Función para inicializar el analizador léxico: será llamada desde main:
int inicializar_analizador_lexico(FILE* codigo_fuente_arg, TablaSimbolos *ts1){ 
    
    // Asignar puntero a FILE a la variable global para usar en "siguienteComponenteLexico()""
    codigo_fuente = codigo_fuente_arg;

    // Inicizalizamos sistema de entrada:
    se = inicializar_sistema_entrada(codigo_fuente);

    // Información: la TS se inicializa desde el main (asegura que se puede acceder desde cualquier parte):
    ts = ts1;

    printf("\nAnalizador léxico inicializado correctamente\n");

    return 0;
};

// Función para obtener siguiente componente léxico: será llamada por el analizador sintáctico:
ComponenteLexico siguienteComponenteLexico(){

    // Inicializamos la variable de tipo "ComponenteLexico":
    componenteLexico.lexema = '\0';
    componenteLexico.token = 0;

    // Variable para saber cuándo parar, variable de estado (del caracter inicial) y variable char:
    int stop = 0, estado = 0;
    char c;

    // Bucle while mientras no se necesite parar de procesar caracteres:
    while(!stop){

        // Leemos el siguiente caracter del documento //LUEGO SERÁ SISTEMA ENTRADA
        c = siguiente_caracter();

        // Con un switch, hacemos las acciones correspondientes dependiendo del caracter inicial:
        estado = reconocer_caracter_inicial(c);
        switch (estado)
        {
        case 1: //IDENTIFICADOR
            automata_identificador();
            break;

        case 2: //NUMEROS
            automata_numeros();
            break;

        case 3: //ESPACIOS EN BLANCO
            avanzar_puntero_inico();
            continue;
            
        case 4: //FIN ARCHIVO
            componenteLexico.lexema = obtener_lexema(); // Cogemos el lexema (char EOF)
            componenteLexico.token = FIN;
            break;    

        case 5: //DELIMITADORES
            componenteLexico.lexema = c;
            componenteLexico.token = c; // Conversión implícita, devolvemos el valor ASCII
            break;

        case 6: //OPERADORES
            automata_operadores();
            break;
            
        case 7: //STRING
            automata_string();
            break;

        case 8: //BARRA BAJA
            automata_barra_baja();
            break;    
    
        case 0: 
            //PRINTEAMOS ERROR y avanzamos caracter:
            ERROR_GENERAL();
            avanzar_puntero_inicio();
            break;
        }
    }

    return componenteLexico;
    retroceder_puntero_delantero();
};

// Función que implementa el autómata encargado de reconocer los identificadores y keywords:
void automata_identificador(){

    // Variable de parada:
    int stop = 0;

    // Bucle para seguir procesando caracteres hasta que no sean aceptados:
    while(!stop){
        char c = siguiente_caracter();

        // Si el char no es alfanumérico o una barra baja, paramos y retrocedemos puntero (la comprobación de doble barra baja inicial va en otro autómata)
        if(!(isalnum(c) || c != '_')){
            stop = 1;   // Avisamos para que pare
            
            componenteLexico.lexema = obtener_lexema(); //COMPROBAR: Al igual no hay que retroceder antes de obtener_lexema
            retroceder_puntero_delantero(); // Retrocedemos el puntero delantero para estar bien situado para el siguiente lexema.

            // Si no está en la tabla de símbolos, lo añadimos como identificador:
            int token_recibido = buscarEnTS(ts, componenteLexico.lexema);
            if (token_recibido == -1){
                insertarIdentificadorTS(ts, componenteLexico.lexema);
            }

            // Si ya estaba, asignamos el valor del token al componente léxico:
            else componenteLexico.token = token_recibido;
        }
    }
}

// Función que impolementa el autómata encargado de la gestión de identificadores que comienzan por '_':
void automata_barra_baja(){

    // Obtenemos siguiente char:
    char c = siguiente_caracter();

    // Si el siguiente char es otra '_', devolvemos error léxico:
    if (c == '_'){
        ERROR_GENERAL();
    }

    // Si el siguiente char es un caracter alfanumérico, redirigimos al autómata de identificadores:
    else if (isalnum(c)){
        automata_identificador();
    }

    // Si el siguiente char no es ni '_' ni alfanumérico, devolvemos identificador especial '_'
    componenteLexico.lexema = c;
    componenteLexico.token = c; // Cast implícito => devolvemos valor y no TOKEN_IDENTIFICADOR porque es especial.
    retroceder_puntero_delantero(); // Retrocedemos el puntero delantero para estar bien situado para el siguiente lexema.

}

// Función que implementa el autómata encargado de reconocer los números:
void automata_numeros(){
    
    // char c = siguiente char, lo categorizamos y lo mandamos al responsable:
    char c = siguiente_caracter();

    // Caso dónde el char es un '0':
    if(c == '0'){

        // Obtenemos el siguiente caracter al 0, y vemos que tipo de numero es:
        c = siguiente_caracter();

        //if (c == 'b' || c == 'B') automata_binario();   // Realmente no hay números binarios en el código proporcionado
        //if (c == 'o' || c == 'O') automata_octal();     // Tampoco hay números octales
        if (c == 'x' || c == 'X') automata_hex();
    }

    // Caso donde el char es un número != '0'
    else if(isdigit(c) && (c != '0')){

        automata_decimal(); // El encargado será el autómata para los decimales:
    }

    // Caso donde el char es un punto ('.'):
    else if(c == '.'){
        
        automata_decimal_float(0);   // El encargado será el autómata de los números en punto flotante, independiente de si es decimal, binario...: 
    }

    // Caso donde el siguiente caracter sea un operador, delimitador, etcera:
    else if (isDelimitador_Operador_o_Espacio(c)){
        componenteLexico.lexema = obtener_lexema();
        componenteLexico.token = TOKEN_NUMERO;
        retroceder_puntero_delantero();
    }

    // Si el primer char no es un número o un punto
    else{
    
        ERROR_GENERAL();
        
        // Devolvemos sólamente el número que reconocimos:
        componenteLexico.lexema = obtener_lexema(); //COMPROBAR: Al igual no hay que retroceder antes de obtener_lexema
        componenteLexico.token = TOKEN_NUMERO;
        retroceder_puntero_delantero(); // Retrocedemos el puntero delantero para estar bien situado para el siguiente lexema.
    }
}

// Función que implementa el autómata encargado de reconocer los números hexadecimales:
void automata_hex(){

    // Variable de parada:
    int stop = 0;
    int hayBarraBaja = 0; //flag

    // Bucle para seguir procesando caracteres hasta que no sean aceptados:
    while(!stop){

        // char c = siguiente char, comprobamos:
        char c = siguiente_caracter();

        // Comprobaciones válidas:
        if (c == '_' || hayBarraBaja != 1){
            hayBarraBaja = 1;
        }

        /*
        // Si entra un punto: hex_float:
        if (c == '.'){
            automata_hex_float();   // parte fraccionaria
        }

        // habria que comprobar si entra una P, si no entro un hexdigit de ultimo, error, si no, llamar a
        // hex float => parte exponente
        */

        // Si entra un número HEX:
        else if (isnum(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')){
            hayBarraBaja = 0;
        }

        // Si entra un delimitador u operador:
        else if (isDelimitador_Operador_o_Espacio(c)){
            componenteLexico.lexema = obtener_lexema();
            componenteLexico.token = TOKEN_NUMERO;
            retroceder_puntero_delantero();
            stop = 1;
        }

        // Si entra una barra baja, 
        else {                              // Si entra una barra baja después de otra, o cualquier cosa no hex:
            ERROR_GENERAL();
            componenteLexico.lexema = obtener_lexema();
            componenteLexico.token = TOKEN_NUMERO;
            retroceder_puntero_delantero(); // Retrocedemos el puntero delantero para estar bien situado para el siguiente lexema.
            stop = 1;
        }
    }

}

// Función que implementa el autómata encargado de reconocer los números hexadecimales:
void automata_decimal(){

    // Variable de parada:
    int stop = 0;
    int hayBarraBaja = 1; //flag => empieza en 1 porq el primer caracter no puede ser _

    // Bucle para seguir procesando caracteres hasta que no sean aceptados:
    while(!stop){

        // char c = siguiente char, comprobamos:
        char c = siguiente_caracter();

        // Comprobaciones válidas:
        if (c == '_' && hayBarraBaja != 1){
            hayBarraBaja = 1;
        }

        // Si entra un punto y no ha entrado de último una _: decimal_float:
        if (c == '.' && hayBarraBaja != 1){
            hayBarraBaja = 0;
            automata_decimal_float(0);   // parte fraccionaria
            stop = 1;
        }

        // Si entra una e, y el último caracter no es una barra baja: decimal_float:
        if ((c == 'e' || c == 'E') && hayBarraBaja == 0){
            automata_decimal_float(1);    // parte exponente
            stop = 1;
        }

        // Si entra un número decimal:
        else if (isnum(c)){
            hayBarraBaja = 0;
        }

        // Si entra un delimitador u operador:
        else if (isDelimitador_Operador_o_Espacio(c) && hayBarraBaja != 1){
            componenteLexico.lexema = obtener_lexema();
            componenteLexico.token = TOKEN_NUMERO;
            retroceder_puntero_delantero();
            stop = 1;
        }

        else {                              // Si entra una barra baja después de otra, o cualquier cosa no hex:
            ERROR_GENERAL();
            componenteLexico.lexema = obtener_lexema();
            componenteLexico.token = TOKEN_NUMERO;
            retroceder_puntero_delantero(); // Retrocedemos el puntero delantero para estar bien situado para el siguiente lexema.
            stop = 1;
        }
    }

}

// automata_hex_float()

// Función que implementa el autómata encargado de reconocer los números hexadecimales:
void automata_decimal_float(int parte_a_procesar){

    // Variable de parada:
    int stop = 0;
    int hayBarraBaja = 1; //flag
    int hayUltimoPunto = 0;
    int haySigno = 0;
    int esPrimeraIteracionExponente = 0;

    // Decidimos que bucle procesará el caracter dependiendo de si es parte decimal o exponente:
    int parteProcesarFloat = parte_a_procesar;

    

    // PARTE DECIMAL:
    if (parteProcesarFloat == 0){

        // El caracter último es un .:
        hayUltimoPunto = 1;

        // Bucle para seguir procesando caracteres hasta que no sean aceptados:
        while(!stop){

            // char c = siguiente char, comprobamos:
            char c = siguiente_caracter();

            // Comprobaciones válidas:
            if (c == '_' && hayBarraBaja != 1 && hayUltimoPunto != 1){
                hayBarraBaja = 1;
                hayUltimoPunto = 0;
            }

            // Si entra un punto: error
            if (c == '.'){
                hayBarraBaja = 0;
                ERROR_GENERAL();
                componenteLexico.lexema = obtener_lexema();
                componenteLexico.token = TOKEN_NUMERO;
                stop = 1;
            }

            // Si entra una e, y el último caracter no es un número: decimal_float:
            if ((c == 'e' || c == 'E') && hayBarraBaja != 1){
                hayBarraBaja = 0;
                hayUltimoPunto = 0;
                automata_decimal_float(1);    // parte exponente
                stop = 1;
            }

            // Si entra un número decimal:
            else if (isnum(c)){
                hayBarraBaja = 0;
                hayUltimoPunto = 0;
            }

            // Si entra un delimitador u operador:
            else if (isDelimitador_Operador_o_Espacio(c) && hayBarraBaja!=1 && hayUltimoPunto!=1){
                componenteLexico.lexema = obtener_lexema();
                componenteLexico.token = TOKEN_NUMERO;
                retroceder_puntero_delantero();
                stop = 1;
            }

            else {                              // Si entra una barra baja después de otra, o cualquier cosa diferente
                ERROR_GENERAL();
                componenteLexico.lexema = obtener_lexema();
                componenteLexico.token = TOKEN_NUMERO;
                retroceder_puntero_delantero(); // Retrocedemos el puntero delantero para estar bien situado para el siguiente lexema.
                stop = 1;
            }
        }



    }

    // PARTE EXPONENTE:
    else{
        // Bucle para seguir procesando caracteres hasta que no sean aceptados:
        while(!stop){

            // char c = siguiente char, comprobamos:
            char c = siguiente_caracter();

            // Comprobaciones válidas:
            if (c == '_' || hayBarraBaja != 1){
                hayBarraBaja = 1;
            }

            // Si entra un punto => error:
            else if (c == '.'){
                ERROR_GENERAL();
                stop = 1;
            }

            // Si entra un número decimal:
            else if (isnum(c)){
                hayBarraBaja = 0;
            }

            // Si entra un + o -, y es inmediatamente siguiente a la e/E:
            else if ((c == '+' || c == '-') && esPrimeraIteracionExponente == 0){
                hayBarraBaja = 1; //no puede entrar _
            }

            // Si entra un delimitador u operador:
            else if (isDelimitador_Operador_o_Espacio(c)){
                componenteLexico.lexema = obtener_lexema();
                componenteLexico.token = TOKEN_NUMERO;
                retroceder_puntero_delantero();
                stop = 1;
            }

            else {                              // Si entra una barra baja después de otra, o cualquier cosa no hex:
                ERROR_GENERAL();
                componenteLexico.lexema = obtener_lexema();
                componenteLexico.token = TOKEN_NUMERO;
                retroceder_puntero_delantero(); // Retrocedemos el puntero delantero para estar bien situado para el siguiente lexema.
                stop = 1;
            }

        esPrimeraIteracionExponente = 1;
        }
    }
}

// Función que implementa el autómata encargado de reconocer los números imaginarios (se llama desde el resto):
void automata_imaginario(){ // Se llama cuando se detecta una i

    // Siempre devolvemos


}


/*
EL RESTO DEL CÓDIGO ES IGUAL: hay que echarle horas. Antes de ponernos, casi vamos a implementar
el sistema de entrada antes (clase de mañana), el analizador léxico no tiene nada.*/