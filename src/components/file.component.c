#include "file.component.h"
#include "../utils/logger.h"
#include <errno.h>
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

int read_record(FILE *f, void *buffer, size_t size) {
  if (fread(buffer, size, 1, f) != 1) {
    if (feof(f))
      return 0; // fin de archivo, no error
    LOG_ERROR("Error al leer registro");
    return -1;
  }
  return 0;
}

int write_record(FILE *f, const void *buffer, size_t size) {
  if (fwrite(buffer, size, 1, f) != 1) {
    LOG_ERROR("Error al escribir registro");
    return -1;
  }
  return 0;
}
