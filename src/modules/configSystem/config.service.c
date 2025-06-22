#include "includes/config.service.h"
#include "../../utils/logger.h"
#include "includes/config.repository.h"
#include <stdlib.h>
#include <string.h>

int create_config_service(ConfigSystem config) {
  if (save_config_repository(config) == -1) {
    LOG_ERROR("No se pudo guardar la configuración del sistema.");
    return -1;
  }
  LOG_INFO("Configuración del sistema guardada correctamente.");
  return 0;
}

ConfigSystem *get_config_service() {
  ConfigSystem *config = get_config_repository();
  if (!config) {
    LOG_WARNING("No se encontró ninguna configuración del sistema.");
    return NULL;
  }
  return config;
}

int update_config_service(ConfigSystem config) {
  ConfigSystem *current = get_config_repository();
  if (!current) {
    LOG_WARNING("Intento de actualizar sin configuración existente.");
    return -1;
  }

  // Rellenar campos faltantes con los valores actuales
  if (strlen(config.bussinesName) == 0) {
    strcpy(config.bussinesName, current->bussinesName);
  }

  if (config.taxes < 0) {
    config.taxes = current->taxes;
  }

  if (strlen(config.currency) == 0) {
    strcpy(config.currency, current->currency);
  }

  config.admin_id = current->admin_id; // Nunca debe cambiar

  free(current);

  if (update_config_repository(config) == -1) {
    LOG_ERROR("No se pudo actualizar la configuración del sistema.");
    return -1;
  }

  LOG_INFO("Configuración del sistema actualizada correctamente.");
  return 0;
}

int delete_config_service() {
  ConfigSystem *current = get_config_repository();
  if (!current) {
    LOG_WARNING("Intento de eliminar sin configuración existente.");
    return -1;
  }
  free(current);

  if (delete_config_repository() == -1) {
    LOG_ERROR("No se pudo eliminar la configuración del sistema.");
    return -1;
  }
  LOG_INFO("Configuración del sistema eliminada correctamente.");
  return 0;
}
