#include "includes/user.service.h"
#include "../../utils/logger.h"
#include "includes/user.model.h"
#include "includes/user.repository.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_USERNAME_LEN 3
#define MAX_USERNAME_LEN 20

int create_user_service(User user) {

  int result = save_user(user);
  if (result == 0) {
    LOG_INFO("Usuario con ID %d creado correctamente.", user.id);
  }
  return result;
}

int update_user_service(User *user, int id) {
  User *current = get_user_by_id(id);
  if (current == NULL) {
    LOG_WARNING("No existe usuario con ID %d para actualizar.", id);
    free(current);
    return -1;
  }

  // Mismo ID ya que ese no se puede modificar
  user->id = current->id;

  // actualizar campos
  if (strlen(user->username) == 0) {
    strcpy(user->username, current->username);
  }

  if (strlen(user->password) == 0) {
    strcpy(user->password, current->password);
  }

  if (user->role < 0) {
    user->role = current->role;
  }

  int result = update_user(user);
  if (result == 0) {
    LOG_INFO("Usuario con ID %d actualizado correctamente.", user->id);
  } else {
    LOG_ERROR("Error al actualizar el usuario con ID %d", user->id);
  }

  free(current);
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
