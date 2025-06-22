#include "includes/config.service.h"
#include "includes/config.repository.h"
#include "../../utils/logger.h"
#include <stdlib.h>

int create_config_service(ConfigSystem config) {
    if (save_config_repository(config) == -1) {
        LOG_ERROR("No se pudo guardar la configuración del sistema.");
        return -1;
    }
    LOG_INFO("Configuración del sistema guardada correctamente.");
    return 0;
}

ConfigSystem* get_config_service() {
    ConfigSystem* config = get_config_repository();
    if (!config) {
        LOG_WARNING("No se encontró ninguna configuración del sistema.");
        return NULL;
    }
    return config;
}

int update_config_service(ConfigSystem config) {
    ConfigSystem* current = get_config_repository();
    if (!current) {
        LOG_WARNING("Intento de actualizar sin configuración existente.");
        return -1;
    }
    free(current); // Liberamos para evitar memory leak

    if (update_config_repository(config) == -1) {
        LOG_ERROR("No se pudo actualizar la configuración del sistema.");
        return -1;
    }
    LOG_INFO("Configuración del sistema actualizada correctamente.");
    return 0;
}

int delete_config_service() {
    ConfigSystem* current = get_config_repository();
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
