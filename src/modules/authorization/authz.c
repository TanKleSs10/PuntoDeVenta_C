#include "includes/authz.h"

// Permisos por rol (basado en tus valores enum)
static const long ROLE_PERMISSIONS[] = {
    [SUPERADMIN] = PERM_ALL,
    [ADMIN] = PERM_CONFIG_VIEW | PERM_USER_MANAGE | PERM_PRODUCT_CREATE |
              PERM_PRODUCT_READ | PERM_PRODUCT_UPDATE | PERM_PRODUCT_DELETE,
    [CASHIER] = PERM_PRODUCT_READ | PERM_POS_ACCESS};

bool has_permission(const Auth *session, Permission perm) {
  if (!session || session->user.role < ADMIN ||
      session->user.role > SUPERADMIN) {
    return false;
  }
  return (ROLE_PERMISSIONS[session->user.role] & perm) == perm;
}

// const char* role_to_string(UserRole role) {
//     switch (role) {
//         case SUPERADMIN: return "Superadministrador";
//         case ADMIN:      return "Administrador";
//         case CASHIER:    return "Cajero";
//         default:         return "Rol desconocido";
//     }
//}
