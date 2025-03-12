//ESTRUCTURA
/*
tenemos una función para iniciar (será nuestro main)

al iniciar, llamamos a un while que hace una llamada a siguienteComponenteLexico
hasta encontrar un EOF (token=valor ASCII de EOF)

en cada iteración, imprimimos la tupla <token, lexema> por pantalla

cuidado, para los delimitadores y los números la tupla solo accederá a valor
(darse cuenta que ( es 40 en ASCII, y ejemplos similares))

al acabar, imprimimos que el analizador_sintactico finalizo

*/


#include <stdio.h>
#include <string.h>
#include "analizador_lexico.h"
#include "errores/errores.h"
#include <unistd.h>
#include "definiciones.h"


// Función: inicia el analizador sintáctico. Usada desde el main:
int iniciar_analizador_sintactico(){ //No necesita referencia al fichero => se le pasa en el main al léxico

    // Variable para almacenar los componentes léxicos:
    ComponenteLexico componenteLexico = {0};

    // Informamos del comienzo del análisis:
    printf("\nInicio del análisis sintáctico:\n\n");
    
    // Bucle: patrón productor - consumidor, se le pide el siguiente comp. léxico al
    // analizador léxico.
    do{
        // Llamamos a la función "siguienteComponenteLexico" del analizador léxico:
        componenteLexico = siguienteComponenteLexico();

        // Imprimimos tupla <token, "lexema">,
        printf("<%d, %s>\n", componenteLexico.token, componenteLexico.lexema);

        /* NOTA: cuándo llegan delimitadores o números el encargado de poner
        correctamente el formato es el analizador léxico. Para ello va a 
        devolver como token el valor ASCII del delimitador. Los números
        tienen un identificador, como las variables pero no son comprobados
        en la tabla de símbolos, se pasan directamente. Los delimitadores
        tampoco serán comprobados en la tabla de símbolos. */

    }
    while(componenteLexico.token != FIN);

    // Informamos de que ha finalizado el analizador:
    printf("\nAnálisis finalizado\n");
    
    return 0;

}




