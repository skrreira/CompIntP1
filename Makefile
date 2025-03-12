# Nombre del ejecutable
TARGET = compilador

# Compilador
CC = gcc

# Flags de compilación
CFLAGS = -Wall -Wextra -std=c11 -g -Ilibs

# Directorios
SRC_DIR = src
ERR_DIR = $(SRC_DIR)/errores
LIB_DIR = libs

# Archivos fuente
SRC = \
    $(ERR_DIR)/errores.c \
    $(SRC_DIR)/analizador_lexico.c \
    $(SRC_DIR)/analizador_sintactico.c \
    $(SRC_DIR)/sistema_entrada.c \
    $(SRC_DIR)/hash.c \
    $(SRC_DIR)/TS.c \
    $(SRC_DIR)/main.c 

# Archivos de cabecera
HEADERS = \
    $(ERR_DIR)/errores.h \
    $(SRC_DIR)/analizador_lexico.h \
    $(SRC_DIR)/analizador_sintactico.h \
    $(SRC_DIR)/sistema_entrada.h \
    $(SRC_DIR)/hash.h \
    $(SRC_DIR)/TS.h \
    $(SRC_DIR)/definiciones.h \
    $(LIB_DIR)/uthash.h

# Objetos (cada .c se convierte en un .o)
OBJ = $(SRC:.c=.o)

# Regla principal para compilar el proyecto
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Regla para compilar archivos .c a .o
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos compilados
clean:
	rm -f $(OBJ) $(TARGET)

# Forzar recompilación
rebuild: clean $(TARGET)

# Ejecutar el programa
run: $(TARGET)
	./$(TARGET)