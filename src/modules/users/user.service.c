#include "includes/user.service.h"
#include "../../utils/logger.h"
#include "../../utils/utils.h"
#include "includes/user.repository.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_ID 0
#define MAX_ID 100
#define MIN_USERNAME_LEN 3
#define MAX_USERNAME_LEN 20
#define MIN_PASSWORD_LEN 3
#define MAX_PASSWORD_LEN 20

static int validate_user_data(User user, int check_id_existence) {
  if (user.id < MIN_ID || user.id > MAX_ID) {
    LOG_WARNING("El ID debe estar entre %d y %d", MIN_ID, MAX_ID);
    return -1;
  }

  if (strlen(user.username) < MIN_USERNAME_LEN ||
      strlen(user.username) > MAX_USERNAME_LEN) {
    LOG_WARNING("El nombre de usuario debe tener entre %d y %d caracteres",
                MIN_USERNAME_LEN, MAX_USERNAME_LEN);
    return -1;
  }

  if (strlen(user.password) < MIN_PASSWORD_LEN ||
      strlen(user.password) > MAX_PASSWORD_LEN) {
    LOG_WARNING("La contraseña debe tener entre %d y %d caracteres",
                MIN_PASSWORD_LEN, MAX_PASSWORD_LEN);
    return -1;
  }

  if (!role_to_string(user.role)) {
    LOG_WARNING("Rol inválido. Solo se permiten ADMIN, CASHIER o SUPERADMIN.");
    return -1;
  }

  if (check_id_existence) {
    User *existing = get_user_by_id(user.id);
    if (existing != NULL) {
      LOG_WARNING("Ya existe un usuario con ID %d", user.id);
      free(existing);
      return -1;
    }
  }

  return 0;
}

int create_user_service(User user) {

  int result = save_user(user);
  if (result == 0) {
    LOG_INFO("Usuario con ID %d creado correctamente.", user.id);
  }
  return result;
}

int update_user_service(User user) {
  if (get_user_by_id(user.id) == NULL) {
    LOG_WARNING("No existe usuario con ID %d para actualizar.", user.id);
    return -1;
  }

  if (validate_user_data(user, 0) != 0)
    return -1;

  int result = update_user(user);
  if (result == 0) {
    LOG_INFO("Usuario con ID %d actualizado correctamente.", user.id);
  } else {
    LOG_ERROR("Error al actualizar el usuario con ID %d", user.id);
  }
  return result;
}

User *find_user_by_id_service(int id) {
  User *user = get_user_by_id(id);
  if (!user) {
    LOG_WARNING("No se encontró usuario con ID %d", id);
  }
  return user;
}

User *find_user_by_username_service(char *username) {
  size_t len = strlen(username);
  if (len < MIN_USERNAME_LEN || len > MAX_USERNAME_LEN) {
    LOG_WARNING("El nombre de usuario debe tener entre %d y %d caracteres",
                MIN_USERNAME_LEN, MAX_USERNAME_LEN);
    return NULL;
  }

  User *user = get_user_by_username(username);
  if (!user) {
    LOG_WARNING("No se encontró usuario con nombre de usuario %s", username);
  }
  return user;
}

User **list_users_service(int *count) {
  User **users = list_users(count);
  if (!users) {
    LOG_ERROR("No se pudo obtener la lista de usuarios.");
  } else {
    LOG_INFO("Se listaron %d usuarios correctamente.", *count);
  }
  return users;
}

int delete_user_service(int id) {
  User *user = get_user_by_id(id);
  if (!user) {
    LOG_WARNING("No se encontró usuario con ID %d para eliminar.", id);
    return -1;
  }
  free(user);

  int result = delete_user(id);
  if (result == 0) {
    LOG_INFO("Usuario con ID %d eliminado correctamente.", id);
  } else {
    LOG_ERROR("Error al eliminar el usuario con ID %d", id);
  }
  return result;
}
