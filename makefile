# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -I./src/modules/users/includes

# Directorios
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
DATA_DIR = data
LOG_DIR = logs

# Buscar todos los .c recursivamente
SRCS = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Ejecutable
TARGET = $(BIN_DIR)/pos_system

# Regla principal
all: create_dirs $(TARGET)

# Compilar y linkear
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

# Compilar cada .c en su correspondiente .o en build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Crear carpetas necesarias
create_dirs:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(DATA_DIR)
	@mkdir -p $(LOG_DIR)

# Limpiar binarios y objetos
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Limpiar solo objetos
clean-obj:
	rm -rf $(BUILD_DIR)

# Limpiar solo ejecutables
clean-bin:
	rm -rf $(BIN_DIR)

run: all
	./$(TARGET)

.PHONY: all clean clean-obj clean-bin create_dirs
