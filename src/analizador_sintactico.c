#include <stdio.h>
#include <analizador_lexico.h>


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


