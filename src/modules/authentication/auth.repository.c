#include "includes/auth.repository.h"
#include "../../components/file.component.h"
#include "../../utils/logger.h"
#include <stdlib.h>
#include <string.h>

#define AUTH_FILE "data/auth.dat"

int save_session_repository(Auth auth) {
  FILE *f = open_file(AUTH_FILE, "wb");
  if (!f) {
    LOG_ERROR("No se pudo abrir el archivo %s para guardar la sesión.",
              AUTH_FILE);
    return -1;
  }

  int r = write_record(f, &auth, sizeof(Auth));
  fclose(f);

  if (r != 0) {
    LOG_ERROR("Fallo al escribir la sesión en %s", AUTH_FILE);
    return -1;
  }

  LOG_INFO("Sesión guardada correctamente en %s", AUTH_FILE);
  return 0;
}

Auth *get_session_repository() {
  FILE *f = open_file(AUTH_FILE, "rb");
  if (!f) {
    LOG_WARNING("No se encontró sesión activa al intentar leer %s", AUTH_FILE);
    return NULL;
  }

  Auth *auth = malloc(sizeof(Auth));
  if (!auth) {
    fclose(f);
    LOG_CRITICAL("Fallo al reservar memoria para la sesión.");
    return NULL;
  }

  int r = read_record(f, auth, sizeof(Auth));
  fclose(f);

  if (r != 0) {
    LOG_ERROR("Error al leer la sesión desde %s", AUTH_FILE);
    free(auth);
    return NULL;
  }

  LOG_DEBUG("Sesión leída correctamente del archivo %s", AUTH_FILE);
  return auth;
}

int delete_session_repository() {
  if (remove(AUTH_FILE) != 0) {
    LOG_ERROR("No se pudo eliminar el archivo de sesión: %s", AUTH_FILE);
    return -1;
  }

  LOG_INFO("Sesión eliminada correctamente: %s", AUTH_FILE);
  return 0;
}
