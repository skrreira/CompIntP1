# CompIntP1
# Proyecto de Compilador

Este es un proyecto de un compilador en C, diseñado para procesar código fuente a través de distintas fases como análisis léxico y sintáctico. Actualmente, el proyecto incluye un **analizador léxico**, un **analizador sintáctico** y una **tabla de símbolos**.

## 📂 Estructura del Proyecto

El código fuente se encuentra dentro del directorio `src/`, con la siguiente organización:

```
libs/
├── uthash.h

src/
├── errores/
│   ├── errores.c
│   ├── errores.h
│
├── analizador_lexico.c
├── analizador_lexico.h
│
├── analizador_sintactico.c
├── analizador_sintactico.h
│
├── definiciones.h
│
├── hash.c
├── hash.h
│
├── main.c
│
├── sistema_entrada.c
├── sistema_entrada.h
│
├── TS.c
├── TS.h
│
├── concurrentSum.go
│
├── Makefile
```

## 🚀 Ejecución y Compilación

El proyecto incluye un **Makefile**, por lo que la compilación es sencilla. Para compilar el código, simplemente ejecuta el siguiente comando en la raíz del proyecto:

```sh
make
```

Esto generará un ejecutable llamado `compilador`.

## ⚠️ Problema en el Analizador Léxico

Actualmente, existe un **error en el analizador léxico** que no ha podido ser depurado completamente. Este problema afecta el correcto funcionamiento del compilador, ya que impide el procesamiento adecuado de ciertos tokens. Sin embargo, el resto de los componentes, incluyendo el **analizador sintáctico y la tabla de símbolos**, funcionan correctamente.

Cualquier contribución para solucionar este problema es bienvenida. 😊
