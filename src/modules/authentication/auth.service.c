#include "includes/auth.service.h"
#include "../../utils/logger.h"

int create_session_service(Auth auth) {
    if (save_session_repository(auth) == -1) {
        LOG_ERROR("create_session_service: Error al guardar la sesión.");
        return -1;
    }
    LOG_INFO("create_session_service: Sesión creada correctamente.");
    return 0;
}

Auth* get_session_service() {
    Auth* session = get_session_repository();
    if (!session) {
        LOG_WARNING("get_session_service: No existe una sesión activa.");
        return NULL;
    }
    LOG_INFO("get_session_service: Sesión obtenida correctamente.");
    return session;
}

int delete_session_service() {
    if (delete_session_repository() == -1) {
        LOG_ERROR("delete_session_service: Error al eliminar la sesión.");
        return -1;
    }
    LOG_INFO("delete_session_service: Sesión eliminada correctamente.");
    return 0;
}
