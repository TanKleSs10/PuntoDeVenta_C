#include "includes/config.repository.h"
#include "../../components/file.component.h"
#include "../../utils/logger.h"
#include <stdlib.h> // Para malloc y free
#include <string.h>

#define CONFIG_FILE "data/config.dat"
#define TEMP_FILE "data/config_tmp.dat"
#define ALL_FILES "data/*.dat"

int save_config_repository(ConfigSystem config) {
  FILE *f =
      open_file(CONFIG_FILE, "wb"); // Usar "wb" para sobrescribir si ya existe
  if (!f) {
    LOG_ERROR("No se pudo abrir el archivo %s para guardar la configuración.",
              CONFIG_FILE);
    return -1;
  }
  int r = write_record(f, &config, sizeof(ConfigSystem));
  fclose(f);

  if (r != 0) {
    LOG_ERROR("Fallo al escribir la configuración en %s", CONFIG_FILE);
    return -1;
  }

  LOG_INFO("Configuración guardada correctamente en %s", CONFIG_FILE);
  return 0;
}

ConfigSystem *get_config_repository() {
  FILE *f = open_file(CONFIG_FILE, "rb");
  if (!f) {
    LOG_ERROR("No se pudo abrir el archivo %s para obtener la configuración.",
              CONFIG_FILE);
    return NULL;
  }

  ConfigSystem *config = (ConfigSystem *)malloc(sizeof(ConfigSystem));
  if (!config) {
    fclose(f);
    LOG_CRITICAL("Fallo al reservar memoria para la configuración.");
    return NULL; // Error al asignar memoria
  }

  int r = read_record(f, config, sizeof(ConfigSystem));
  fclose(f);

  if (r != 0) {
    LOG_ERROR("Error al leer la configuración desde %s", CONFIG_FILE);
    free(config);
    return NULL;
  }

  LOG_DEBUG("Configuración leída correctamente del archivo %s", CONFIG_FILE);
  return config;
}

int update_config_repository(ConfigSystem config) {
  FILE *f = open_file(CONFIG_FILE, "wb"); // Usar "wb" para sobrescribir
  if (!f) {
    LOG_ERROR(
        "No se pudo abrir el archivo %s para actualizar la configuración.",
        CONFIG_FILE);
    return -1;
  }

  int r = write_record(f, &config, sizeof(ConfigSystem));

  if (r != 0) {
    LOG_ERROR("Fallo al escribir la configuración en %s", CONFIG_FILE);
    return -1;
  }

  fclose(f);
  LOG_INFO("Configuración actualizada correctamente en %s", CONFIG_FILE);
  return r == 0 ? 0 : -1;
}

int delete_config_repository() {
  int result;

#ifdef _WIN32
  result = system("del /Q data\\*.dat");
#else
  result = system("rm -f data/*.dat");
#endif

  if (result == 0) {
    LOG_INFO("Archivos de configuración eliminados exitosamente.");
    return 0;
  } else {
    LOG_ERROR("Error al eliminar archivos de configuración.");
    return -1;
  }
}
