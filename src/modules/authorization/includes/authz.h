// authz.h (versión adaptada)
#ifndef AUTHZ_H
#define AUTHZ_H

#include "../../authentication/includes/auth.model.h" // Asumo que Auth está definido aquí
// Definición de permisos como bits
typedef enum {
    // Configuración
    PERM_CONFIG_VIEW   = 1 << 0,  // 0000 0001
    PERM_CONFIG_EDIT   = 1 << 1,  // 0000 0010
    PERM_CONFIG_DELETE = 1 << 2,  // 0000 0100

    // Usuarios
    PERM_USER_MANAGE   = 1 << 3,  // 0000 1000

    // Productos
    PERM_PRODUCT_CREATE = 1 << 4, // 0001 0000
    PERM_PRODUCT_READ   = 1 << 5, // 0010 0000
    PERM_PRODUCT_UPDATE = 1 << 6, // 0100 0000
    PERM_PRODUCT_DELETE = 1 << 7, // 1000 0000

    // POS
    PERM_POS_ACCESS     = 1 << 8, // 0001 0000 0000

    // Combinación de todos
    PERM_ALL            = 0xFFFF
} Permission;

// Función para verificar permisos
bool has_permission(const Auth* session, Permission perm);

// Función para obtener nombre del rol
const char* role_to_string(UserRole role);


#endif // AUTHZ_H
