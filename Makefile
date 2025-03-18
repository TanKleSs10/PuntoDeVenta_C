# Detectar el sistema operativo
OS := $(shell uname -s)

ifeq ($(OS), Windows_NT)
    CC = gcc.exe
    RM = rmdir /S /Q         # Comando para eliminar carpetas en Windows
    TARGET = bin\\pos.exe    # Nombre del ejecutable en Windows
    LDFLAGS = -mconsole      # Fuerza modo consola (evita WinMain)
    MKDIR_BIN = if not exist bin mkdir bin
    MKDIR_BUILD = if not exist build mkdir build
else
    CC = gcc
    RM = rm -rf              # Comando para eliminar carpetas en Linux/macOS
    TARGET = bin/pos         # Nombre del ejecutable en Linux/macOS
    LDFLAGS =                # En Linux/macOS no se requiere -mconsole
    MKDIR_BIN = mkdir -p bin
    MKDIR_BUILD = mkdir -p build
endif

# Directorios principales
SRC_DIR = src
INC_DIR = includes
OBJ_DIR = build
BIN_DIR = bin

# Flags de compilación
CFLAGS = -Wall -Wextra -g -I$(INC_DIR) -I$(SRC_DIR)/models

# Si tu main.c está en la raíz, agrégalo manualmente:
# main.c + todos los .c de src/, controllers, models, views, helpers
SRCS = main.c \
       $(wildcard $(SRC_DIR)/*.c) \
       $(wildcard $(SRC_DIR)/controllers/*.c) \
       $(wildcard $(SRC_DIR)/models/*.c) \
       $(wildcard $(SRC_DIR)/views/*.c) \
       $(wildcard $(SRC_DIR)/helpers/*.c)

# Convierte cada archivo .c en un archivo .o en build/
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

# Regla principal para compilar todo
all: $(TARGET)

# Enlazar el ejecutable final
$(TARGET): $(OBJS)
	@$(MKDIR_BIN)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# Regla para compilar cada .c a .o
$(OBJ_DIR)/%.o: %.c
	@$(MKDIR_BUILD)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Ejecutar el programa
run: $(TARGET)
	./$(TARGET)

# Limpiar compilados
clean:
	$(RM) $(BIN_DIR) $(OBJ_DIR)
	@echo "Carpetas 'bin' y 'build' eliminadas."

# Pruebas (opcional)
test:
	@$(MKDIR_BIN)
	$(CC) $(CFLAGS) test/test.c -o $(BIN_DIR)/test -lcunit
	./$(BIN_DIR)/test
