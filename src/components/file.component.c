#include "file.component.h"
#include "../utils/logger.h"
#include <errno.h>
#include <stdio.h> // Asegúrate de incluir <stdio.h> para FILE y feof/fread/fwrite
#include <string.h>

FILE *open_file(const char *path, const char *modo) {
  FILE *f = fopen(path, modo);
  if (!f) {
    LOG_ERROR("No se pudo abrir el archivo '%s': %s", path, strerror(errno));
  }
  return f;
}

int delete_file(const char *path) {
  if (remove(path) != 0) {
    LOG_WARNING("No se pudo borrar el archivo '%s': %s", path, strerror(errno));
    return -1;
  }
  LOG_INFO("Archivo borrado: %s", path);
  return 0;
}

// *** FUNCIÓN read_record CORREGIDA ***
// Retorna 0 en éxito, 1 en EOF, -1 en error
int read_record(FILE *f, void *buffer, size_t size) {
  size_t items_read = fread(buffer, size, 1, f);
  if (items_read == 1) {
    return 0; // Éxito: se leyó 1 elemento completo
  } else {
    if (feof(f)) {
      return 1; // Fin de archivo
    } else {    // ferror(f)
      LOG_ERROR("Error al leer registro");
      return -1; // Error de lectura
    }
  }
}

int write_record(FILE *f, const void *buffer, size_t size) {
  if (fwrite(buffer, size, 1, f) != 1) {
    LOG_ERROR("Error al escribir registro");
    return -1;
  }
  return 0;
}
