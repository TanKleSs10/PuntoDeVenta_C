#ifndef FILE_COMPONENT_H
#define FILE_COMPONENT_H

#include <stdio.h>
#include <stdlib.h>

// Abre un archivo y devuelve el puntero. Usa logger si hay error.
FILE* open_file(const char* path, const char* modo);

// Crea el archivo si no existe
int create_file_if_not_exists(const char* path);

// Verifica si el archivo existe
int file_exists(const char* path);

// Borra el archivo
int delete_file(const char* path);

// Lee un registro binario desde un archivo
int read_record(FILE* f, void* buffer, size_t size);

// Escribe un registro binario al archivo
int write_record(FILE* f, const void* buffer, size_t size);

#endif
